/*************************************************************************
    Copyright (C) 2005 Joseph D'Errico, Wei Qin
    See file COPYING for more information.

    This program is free software; you can redistribute it and/or modify    
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*************************************************************************/
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <sys/stat.h>

#include "decomp_server.hpp"
#include "decomp_common.hpp"
#include "build_dll.hpp"

using namespace emulator;


static ssize_t sendall(int fd, const void *buf, size_t nbyte)
{
	ssize_t nwritten = 0, n;

	do {
		if ((n = send(fd, &((const char *)buf)[nwritten],
			nbyte - nwritten, 0)) == -1) {
			if (errno == EINTR)
				continue;
			else
				return -1;
		}
		nwritten += n;
	} while (nwritten < nbyte);

	return nwritten;
}

static ssize_t recvall(int fd, void *buf, size_t nbyte)
{
	ssize_t nread = 0, n;

	do {
		if ((n = recv(fd, &((char *)buf)[nread],
			nbyte - nread, 0)) == -1) {
			if (errno == EINTR)
				continue;
			else
				return -1;
		}
		if (n == 0)
			return nread;
		nread += n;
	} while (nread < nbyte);

	return nread;
}

//constructor
decomp_server::decomp_server(bool verbose, uint32_t portnum, bool tolink) :
	verbose(verbose), portnum(portnum), tolink(tolink)
{
	emu = new mips_emulator(false);
}

//destructor
decomp_server::~decomp_server()
{
	delete emu;
}

uint32_t decomp_server::run(const char *temp_path)
{ 
	char obj_path[128];

	decomp_count = 0;
	strcpy(obj_path, temp_path);
	strcat(obj_path, "/c.o");

	int create_socket, new_socket;
	struct sockaddr_in address;
	if ((create_socket = socket(AF_INET, SOCK_STREAM, 0))>0 && verbose)
		if (verbose)
			 fprintf(stderr, "The socket was successfully created.\n");

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(portnum);
	if (bind(create_socket, (struct sockaddr *)&address,
		   sizeof(address))==0)

	if (verbose)
		fprintf(stderr, "Binding Socket, port num %d\n", portnum);

	listen(create_socket, 3);

	while (true) {

		socklen_t addrlen = sizeof(struct sockaddr_in);
		new_socket = accept(create_socket, (struct sockaddr*)&address,&addrlen);
		if (new_socket>0 && verbose)									 
			 fprintf(stderr, "The Client %s is connected...\n",
				inet_ntoa(address.sin_addr));
	
		int response = 1;
		if (verbose) fprintf(stderr, "waiting for response...\n");
	
		while (response>0)
		{
			int baddr, bsize, ind;
			bool selfmod, tocount;

			response = recvall(new_socket, &baddr, sizeof(baddr));
			if (response>0)
			{
				if (verbose) {
					fprintf(stderr, "Response received...\n");
					fprintf(stderr, "Start address = %d\n", baddr);
				}
	
				recvall(new_socket, &bsize, sizeof(int));
				recvall(new_socket, &ind, sizeof(int));
				recvall(new_socket, &selfmod, 1);
				recvall(new_socket, &tocount, 1);
	
				if (verbose) {
					fprintf(stderr, "bufsize = %d\n", bsize);
					fprintf(stderr, "index   = %d\n", ind);
					fprintf(stderr, "selfmod = %d\n", selfmod);
					fprintf(stderr, "tocount = %d\n", tocount);
				}
				char buf[1024];
				ssize_t cnt = 0;
				while (cnt < bsize)
				{
					ssize_t res = (bsize-cnt)>1024?1024:bsize-cnt;
					if ((res=recvall(new_socket, buf, res))>0)
					{
						emu->mem->write_block(cnt+baddr, buf, res);
					}
					cnt += res;
				}

				if (verbose)
					fprintf(stderr, "Code to compile received...\n");
	
				/* Note that we always send 4 more bytes. This is useful when
				   the last instruction in a block is a branch. In this case,
				   its delay slot instruction is needed for decompilation.
				   But we don't directly decompile this 4 bytes themselves.
				 */
				if (compile_block(baddr, bsize-4, ind,
					tocount, selfmod, temp_path)) {
	
					struct stat stat_stru;
					stat(obj_path, &stat_stru);
					int objsize = stat_stru.st_size; // 32bit size
					int linking = tolink;
					sendall(new_socket, &objsize, sizeof(int));
					sendall(new_socket, &linking, sizeof(int));
	
					FILE* fp = fopen(obj_path, "r");
					unsigned nread;
					while ((nread=fread(buf, 1, 1024, fp))>0)
					{
						sendall(new_socket, buf, nread);
					}
					if (verbose)
						fprintf(stderr, "Sent obj code, size %d...\n", objsize);
	
					fclose(fp);
				}
				// else need to do something !!!
			}
			decomp_count++;
		}
	
		close(new_socket);
	}

	close(create_socket);

	return decomp_count;
}


bool decomp_server::compile_block(uint32_t addr, uint32_t size, unsigned ind,
	bool tocount, bool selfmod, const char *temp_path)
{

	char fname[128];
	FILE* outfile;

	strcpy(fname, temp_path);
	strcat(fname, "/a.cpp");

	/*create cpps*/
	outfile = fopen(fname, "w");
	if(outfile == NULL) {
		fprintf(stderr, "Can't open file to write");
		exit(1);
	}

	fprintf(outfile, "#include <arch.hpp>\n");
	fprintf(outfile, "using namespace emulator;\n");
	fprintf(outfile, "typedef dyn_mips_emulator mips_emul_t;\n");

	decomp_block(outfile, emu, addr, addr+size, ind);

	fclose(outfile);

	char compilestring[1024];
	char sedstring[1024];

	sprintf(sedstring,
		SED " \"s/READ_GPR(0)/0/g\" %s/a.cpp > %s/b.cpp",
		temp_path, temp_path);

	if (tolink)
		sprintf(compilestring, 
			CXX FP_OPTION MORE_OPTION " %s/b.cpp"
			" -Wl,-soname,libXcompiled_%u.so"
			" -o %s/c.o"
			" -I%s/include -DDYNAMIC -DSIM_LITE",
			temp_path, ind, temp_path, PREFIX);
	else
		sprintf(compilestring, 
			CXX FP_OPTION MORE_OPTION " %s/b.cpp"
			" -c -o %s/c.o"
			" -I%s/include -DDYNAMIC -DSIM_LITE",
			temp_path, temp_path, PREFIX);

	if (tocount)
		strcat(compilestring, " -DCOUNT_COMPILED");

	if (selfmod)
		strcat(compilestring, " -DSUPPORT_SELF_MOD");

	if (verbose)
		fprintf(stderr, "%s\n", compilestring);

	if (system(sedstring)==0 && system(compilestring)==0) {
		if (verbose) fprintf(stderr,"...done!\n");
		return true;
	}

	if (verbose) fprintf(stderr,"...failed!\n");
	return false;
}

