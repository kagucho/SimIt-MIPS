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
#include <mips_emul.hpp>
#include <config.h>

#if HAVE_SYS_RESOURCE_H && HAVE_SYS_TIME_H
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#endif

using namespace emulator;

static void usage(char *fname)
{
	char *cp;
	if ((cp = strrchr(fname, '/'))!=NULL) cp++;
	else cp = fname;
	fprintf(stderr, 
		"usage : %s [-d] [-v] [-m num] [-h]"
		" <file name> <args...>\n"
		"  -d : debugging mode\n"
		"  -v : verbose\n"
#ifdef SIM_SAFE
		"  -gdb addr : gdb debugging\n"
#endif
		"  -m : maximum number of instructions to simulate\n"
		"  -h : print this message and quit\n"
		"  file name : the MIPS ELF32 program to simulate\n"
		"  args : arguments to the program\n", cp);
}

static mips_emulator *mltr = NULL;

static void sig_handler(int signum)
{
	/* do nothing if the simulator does not exist */
	if (mltr==NULL) exit(0);

	if (signum==SIGINT) {
		mltr->interrupt();
	}
	else if (signum==SIGUSR1) {
		mltr->seg_fault();
	}
}

int main(int argc, char *argv[], char *envp[])
{
	int i;
	char *bin_name;
	char *prog_name = NULL;
	bool verbose = false;
	bool debugging = false;
#ifdef SIM_SAFE
	char *in_addr = NULL;
	bool gdb = false;
#endif
	uint64_t max_inum = (uint64_t)-1;
	void (*prev_sig_handler)(int);

	for(i = 1; i < argc; i++)
	{
		if(strcmp(argv[i], "-d") == 0) debugging = true; else
		if(strcmp(argv[i], "-v") == 0) verbose = true; else
		if(strcmp(argv[i], "-m") == 0) max_inum = ato_uint64(argv[++i]); else
#ifdef SIM_SAFE
		if(strcmp(argv[i], "-gdb") == 0) gdb=true,in_addr = argv[++i]; else
#endif
		if(strcmp(argv[i], "-h") == 0 || argv[i][0]=='-') 
			{usage(argv[0]); return 0;} else
		if(!prog_name)
		{
			prog_name = argv[i];
			break;
		}	
	}
	
	if ((bin_name = strrchr(argv[0], '/'))!=NULL) bin_name++; 
	else bin_name = argv[0];

	/* emulator instance */
	if(prog_name)
	{

		mltr = new mips_emulator(verbose);
		signal(SIGUSR1, sig_handler);
		prev_sig_handler = signal(SIGINT, sig_handler); 

		mltr->load_program(prog_name, argc - i, argv + i, envp);

		if(debugging){
			mltr->debug();
		}
#ifdef SIM_SAFE
		else if (gdb) {
			mltr->gdb(in_addr);
		}
#endif
		else {

			fprintf(stderr, "%s: Simulation starts ...\n", bin_name);

#if HAVE_SYS_RESOURCE_H && HAVE_SYS_TIME_H
			struct timeval begin_u, end_u, begin_s, end_s;
			struct rusage usg;
			float user_time, sys_time;
			getrusage(RUSAGE_SELF, &usg);
			begin_u = usg.ru_utime;
			begin_s = usg.ru_stime;
#endif

			uint64_t icount;
			if (max_inum==(uint64_t)-1)
				icount = mltr->run();
			else
				icount = mltr->run_count(max_inum);

#if HAVE_SYS_RESOURCE_H && HAVE_SYS_TIME_H
			getrusage(RUSAGE_SELF, &usg);
			end_u = usg.ru_utime;
			end_s = usg.ru_stime;
			user_time = (end_u.tv_sec+end_u.tv_usec/1000000.0)-
				(begin_u.tv_sec+begin_u.tv_usec/1000000.0);
			sys_time = (end_s.tv_sec+end_s.tv_usec/1000000.0)-
				(begin_s.tv_sec+begin_s.tv_usec/1000000.0);
#endif

			if (mltr->is_interrupted())
				fprintf(stderr, "%s: Simulation stopped by user.\n", bin_name);
			else if (mltr->get_retcode()==0)
				fprintf(stderr, "%s: Program exited normally.\n",
					bin_name);
			else
				fprintf(stderr, "%s: Program exited with code %d.\n",
					bin_name, mltr->get_retcode());

#if HAVE_SYS_RESOURCE_H && HAVE_SYS_TIME_H
			fprintf(stderr, "Total user time  : %.3f sec.\n"
				"Total system time: %.3f sec.\n"
				"Simulation speed : %.3e inst/sec.\n",
				user_time, sys_time, icount/(user_time+sys_time));
#endif
			mltr->dump_instruction_counters(stderr);

#ifdef EMUMEM_HASH
			fprintf(stderr, "Total 4K memory pages allocated : %d\n",
				mltr->mem->get_page_count());
#endif

#ifdef EMUMEM_MMAP
			fprintf(stderr, "Total 4M memory pages allocated : %d\n",
				mltr->mem->get_page_count());
#endif

		}

		if(prev_sig_handler != SIG_ERR) signal(SIGINT, SIG_DFL);
		signal(SIGUSR1, SIG_IGN);

		delete mltr;
	}
	else usage(argv[0]);

	return 0;
}
