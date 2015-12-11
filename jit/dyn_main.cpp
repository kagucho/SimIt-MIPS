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

#include <cstdio>
#include <csignal>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include "build_dll.hpp"
#include <dyn_mips_emul.hpp>
#include <config.h>

#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <errno.h>

#if HAVE_SYS_RESOURCE_H && HAVE_SYS_TIME_H
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/stat.h>
#endif

#include "util.hpp"

#define MAX_SERV 32 //number of servers could go upto 32

static pthread_mutex_t my_mut;
static pthread_cond_t  my_cond;
static int server_count;
static int compile_count[MAX_SERV];

static struct serv_address {
	char ipaddr[64];
	int portno;
} server_dir[MAX_SERV];

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


static void usage(char *fname)
{
  char *cp;
	if ((cp = strrchr(fname, '/'))!=NULL) cp++;
	else cp = fname;
	fprintf(stderr,
		"usage : %s [-t num] [-l num] [-f fname] [-c] [-m] [-v] [-w] [-h]"
		" <file name> <args...>\n"
		"  -l : K insts per compilation block, default 1K\n"
		"  -t : M insts to interpret before compiling the block, default 64M\n"
		"  -f : configuration file for decompilation servers\n"
		"  -c : count insts \n"
		"  -m : support self-modifying code\n"
		"  -v : verbose simulator\n"
		"  -w : verbose communication\n"
		"  -h : print this message and quit\n"
		"  file name : the MIPS ELF32 program to simulate\n"
		"  args : arguments to the program\n", cp);

}

static dyn_mips_emulator *mltr = NULL;
static bool showmsg;

static void sig_handler(int signum)
{
	/* do nothing if the simulator does not exist */
	if (mltr==NULL) exit(0);

	if (signum==SIGINT) {
		mltr->interrupt();
	}
}


static uint32_t iLog2(uint32_t num)
{
	uint32_t power = 0;
	uint32_t logval =1;

	while(logval < num){
		logval*=2;
		power++;
	}

	return power;
}


void* compile_thread(void* param)
{
	static int server_index=0;
	struct sockaddr_in address;
	int my_index;
	int my_socket;

	dyn_mips_emulator *emul = (dyn_mips_emulator*)param;

	if ((my_socket = socket(AF_INET,SOCK_STREAM,0))>0)
		if (showmsg)
		 fprintf(stderr, "The socket was created %d\n",my_socket);

 
	pthread_mutex_lock(&my_mut);
	my_index = server_index++;
	pthread_mutex_unlock(&my_mut);

	address.sin_family= AF_INET;
	address.sin_port = htons(server_dir[my_index].portno);
	inet_pton(AF_INET, server_dir[my_index].ipaddr, &address.sin_addr);

	if (showmsg)
		fprintf(stderr, "Trying to connect with server %s:%d...\n",
			server_dir[my_index].ipaddr, server_dir[my_index].portno);

	if (connect(my_socket, (struct sockaddr*)&address, sizeof(address))==0) {
		if (showmsg)
			fprintf(stderr, "Connection was accepted by server %s:%d.n",
				server_dir[my_index].ipaddr, server_dir[my_index].portno);
	}
	else {
		fprintf(stderr, "Connection was rejected by server %s:%d.\n",
			server_dir[my_index].ipaddr, server_dir[my_index].portno);
		pthread_exit(NULL);
	}

	pthread_mutex_lock(&my_mut);
	server_count++;
	pthread_mutex_unlock(&my_mut);

	/* Size of a block to be compiled. We always send 4 more bytes so
	   that if the last instruction is a branch, its delay slot instruction
	   can be found when decompiling.
	 */
	int bufsize = (1<<(emul->get_shiftval()))+4;
	void *buf = malloc(bufsize);
	char selfmod = emul->is_selfmod();
	char tocount = emul->is_tocount();

	while(1)
	{
		unsigned dll_ind;
		unsigned thr_ind;

		emul->get_block_to_compile(&dll_ind, &thr_ind);

		if (showmsg)
			fprintf(stderr,"start to compile ...\n");	

		/* send the block of data to be compiled along with index*/
		uint32_t fstart = thr_ind << (emul->get_shiftval());

		if (showmsg)
			fprintf(stderr, "sending the start address %d...\n", fstart);

		if((sendall(my_socket, &fstart, sizeof(fstart)))>0)
		{
			emul->mem->read_block(buf,fstart,bufsize);

			if (showmsg)
				fprintf(stderr, "sending the bufsize %d...\n", bufsize);
			sendall(my_socket, &bufsize, sizeof(bufsize));
			if (showmsg)
				fprintf(stderr, "sending the dll_ind %d...\n", dll_ind);
			sendall(my_socket, &dll_ind, sizeof(dll_ind));
			if (showmsg)
				fprintf(stderr, "sending the selfmod flag %d...\n", selfmod);
			sendall(my_socket, &selfmod, 1);
			if (showmsg)
				fprintf(stderr, "sending the tocount flag %d...\n", tocount);
			sendall(my_socket, &tocount, 1);
			int pkt_size=sendall(my_socket, buf, bufsize);
			if (showmsg)
				fprintf(stderr, "sending block of size %d...\n", pkt_size);
		}

		int objsize, islinked;
		recvall(my_socket, &objsize, sizeof(int));
		recvall(my_socket, &islinked, sizeof(int));

		if (showmsg)
			fprintf(stderr, "objsize = %d islinked=%d\n", objsize, islinked);

		compile_count[my_index]++;

		char pkt[1024];
		char fname[1024];

		if (islinked)
			sprintf(fname, "%s/libXcompiled_%u.so",
				emul->get_cache_dir(), dll_ind);
		else
			sprintf(fname, "%s/Xcompiled_%u.o",
				emul->get_cache_dir(), dll_ind);

		FILE* fp = fopen(fname, "w");
		int rem = objsize, recd=1;
		while (recd>0 && rem>0)
		{
			recd = recvall(my_socket, pkt, rem<1024?rem:1024);
			if (recd>0)
			{
				fwrite(pkt, 1, recd, fp);
				rem-=recd;
			}
		}
		fclose(fp);

		if (showmsg)
			fprintf(stderr,"Compiled code received of size %d\n", objsize);

		/* if code is not linked, link it */
		if (islinked==0)
			emul->ld_lib(dll_ind);

		if (emul->load_lib(thr_ind, dll_ind))
		{
			emul->dump_cache_dir(thr_ind, dll_ind);
			if (showmsg)
				fprintf(stderr, "File successfully linked...\n");
		}
	}
	free(buf);
	close(my_socket);
	pthread_exit(NULL);
}

/* this function reads the config file and populates the server database*/
int read_servers(const char* fname)
{
	char buf1[64];
	int  ii = 0;
	
	if (fname==NULL) return 0;

	FILE* fp = fopen(fname,"r");
	if (!fp)
	{
		fprintf(stderr, "Could not open config file %s\n", fname);
		return 0;
	}

	// donot use scanf %s since it is not safe
	while (fgets(buf1, 64, fp)!=NULL)
	{
		char *ptr;
		if ((ptr = strtok(buf1, "\n\t "))==NULL) return ii;
		strncpy(server_dir[ii].ipaddr, ptr, 63);
		if ((ptr = strtok(NULL, "\n\t "))==NULL) return ii;
		server_dir[ii].portno = atoi(ptr);
		ii++;

		/* read as many as I can remember. */
		if (ii==MAX_SERV) break;
	}

	fclose(fp);
	return ii;
}

int main(int argc, char *argv[], char *envp[])
{
	int i;
	char *bin_name;
	char *configfile = NULL;
	char *prog_name = NULL;

	void (*prev_sig_handler)(int);

	uint32_t shift_val = 10;
	uint32_t threshold = 1<<26;
	bool verbose = false;
	bool tocount = false;
	bool selfmod = false;

	for(i = 1; i < argc; i++)
	{
		if(strcmp(argv[i], "-l") == 0) {

			double temp1 = atof(argv[++i])*(1<<10);
			shift_val = iLog2((uint32_t)temp1);
			if (shift_val<9) shift_val = 9; // minimum size of blocks
		}
		else if(strcmp(argv[i], "-t") == 0) {
			threshold = (uint32_t)(atof(argv[++i])*(1<<20));
		}
		else if(strcmp(argv[i], "-v") == 0) {
			verbose = true;
		}
		else if(strcmp(argv[i], "-c") == 0) {
			tocount = true;
		}
		else if(strcmp(argv[i], "-m") == 0) {
			selfmod = true;
		}
		else if(strcmp(argv[i], "-w") == 0) {
			showmsg = true;
		}
		else if(strcmp(argv[i], "-f") == 0) {
			configfile = argv[++i];
		}
		else if(strcmp(argv[i], "-h") == 0 || argv[i][0]=='-') {
			usage(argv[0]); return 0;
		}
		else if(!prog_name) {
			prog_name = argv[i];
			break;
		}
	}

	if ((bin_name = strrchr(argv[0], '/'))!=NULL) bin_name++;
	else bin_name = argv[0];

	/* emulator instance */
	if(prog_name)
	{
		pthread_cond_init(&my_cond, NULL);
		pthread_mutex_init(&my_mut, NULL);

		int nserver = read_servers(configfile);

		mltr = new dyn_mips_emulator(threshold, shift_val+2,
					verbose, showmsg, tocount, selfmod);

		mltr->load_program(prog_name, argc - i, argv + i, envp);

		if (!mltr->load_or_create_cache(prog_name))
			exit(1);

		for (i=0; i<nserver; i++) {
			pthread_t tid;
			pthread_create(&tid, NULL, &compile_thread, mltr);
		}

		// create a new simulator object
		prev_sig_handler = signal(SIGINT, sig_handler);

#if HAVE_SYS_RESOURCE_H && HAVE_SYS_TIME_H
		struct timeval begin_u, end_u, begin_s, end_s,
				cbegin_u, cend_u, cbegin_s, cend_s;
		struct rusage usg, cusg;
		float sim_user_time, sim_sys_time, child_user_time, child_sys_time;
		getrusage(RUSAGE_SELF, &usg);
		getrusage(RUSAGE_CHILDREN, &cusg);
		begin_u = usg.ru_utime;
		cbegin_u = cusg.ru_utime;
		begin_s = usg.ru_stime;
		cbegin_s = cusg.ru_stime;
#endif

		uint64_t icount;

		/* if there is no server found, then traditional run */
		if (nserver==0) 
			icount = mltr->run_solo();
		else
			icount = mltr->run_parallel();

#if HAVE_SYS_RESOURCE_H && HAVE_SYS_TIME_H
		getrusage(RUSAGE_SELF, &usg);
		getrusage(RUSAGE_CHILDREN, &cusg);
		end_u = usg.ru_utime;
		cend_u = cusg.ru_utime;
		end_s = usg.ru_stime;
		cend_s = cusg.ru_stime;
		sim_user_time = (end_u.tv_sec+end_u.tv_usec/1000000.0)-
			(begin_u.tv_sec+begin_u.tv_usec/1000000.0);
		sim_sys_time = (end_s.tv_sec+end_s.tv_usec/1000000.0)-
			(begin_s.tv_sec+begin_s.tv_usec/1000000.0);
		child_user_time = (cend_u.tv_sec+cend_u.tv_usec/1000000.0)-
			(cbegin_u.tv_sec+cbegin_u.tv_usec/1000000.0);
		child_sys_time = (cend_s.tv_sec+cend_s.tv_usec/1000000.0)-
			(cbegin_s.tv_sec+cbegin_s.tv_usec/1000000.0);
		fprintf(stderr, "Total user time  : %.3f sec.\n"
			"Total system time: %.3f sec.\n",
			child_user_time+sim_user_time, child_sys_time+sim_sys_time);
		fprintf(stderr, "Simulation user time  : %.3f sec.\n"
			"Simulation system time: %.3f sec.\n",
			sim_user_time, sim_sys_time);
		fprintf(stderr, "Caching user time  : %.3f sec.\n"
			"Caching system time: %.3f sec.\n",
			child_user_time, child_sys_time);
#endif

		if (tocount){
			fprintf(stderr, "Simulation speed : %.3e inst/sec.\n",
				icount/(child_user_time+sim_user_time+
					child_sys_time+sim_sys_time));
			mltr->dump_instruction_counters(stderr);
		}
		if(prev_sig_handler != SIG_ERR) signal(SIGINT, SIG_DFL);

		if (nserver>0) {
			fprintf(stderr, "Connected servers : %d of %d.\n",
				server_count, nserver);
			fprintf(stderr, "Requested blocks  : %d.\n",
				mltr->get_num_reqs());
			fprintf(stderr, "Compilation count :\n");
			for (int ii=0; ii<nserver; ii++)
				fprintf(stderr, "  server %d: %d\n", ii, compile_count[ii]);
		}
	}
	else usage(argv[0]);

	delete mltr;

	return 0;
}
