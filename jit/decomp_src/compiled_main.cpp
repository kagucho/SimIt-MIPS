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
#include <config.h>

#include "compiled_run.hpp"
#include "Scompiled_all.hpp"

#if HAVE_SYS_RESOURCE_H && HAVE_SYS_TIME_H
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#endif

uint64_t njumps;
using namespace emulator;

static mips_emulator *mltr = NULL;

static void sig_handler(int signum)
{
	/* do nothing if the simulator does not exist */
	if (mltr==NULL) exit(0);

	if (signum==SIGINT) {
		mltr->interrupt();
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

	if ((bin_name = strrchr(argv[0], '/'))!=NULL) bin_name++; 
	else bin_name = argv[0];

	if (argc<2) {
		fprintf(stderr, "%s: Missing target program path.\n");
		exit(1);
	}

	prog_name = argv[1];

	/* emulator instance */
	if(prog_name)
	{
		//printf("PNtrue\n");
		mltr = new mips_emulator(VERBOSE);
		prev_sig_handler = signal(SIGINT, sig_handler); 

		mltr->load_program(prog_name, argc - 1, argv + 1, envp);
		fprintf(stderr, "%s: Simulation starts ...\n", bin_name);

#if HAVE_SYS_RESOURCE_H && HAVE_SYS_TIME_H
			struct timeval begin_u, end_u, begin_s, end_s;
			struct rusage usg;
			float user_time, sys_time;
			getrusage(RUSAGE_SELF, &usg);
			begin_u = usg.ru_utime;
			begin_s = usg.ru_stime;
#endif

			run_compiled(mltr);

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
				"Total system time: %.3f sec.\n",
				user_time, sys_time);
#ifdef COUNT_COMPILED	
			fprintf(stderr, "Simulation speed : %.3e inst/sec.\n",
				mltr->get_total_count()/(user_time+sys_time));
			mltr->dump_instruction_counters(stderr);
#endif
#endif
			fprintf(stderr, "Total long jumps : %lld\n", njumps);

			if(prev_sig_handler != SIG_ERR) 
			  signal(SIGINT, SIG_DFL);

			delete mltr;
	}
	
	return 0;
}
