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

#include "decomp.hpp"

#if HAVE_SYS_RESOURCE_H && HAVE_SYS_TIME_H
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#endif

using namespace emulator;

static void usage(char *fname)
{
	fprintf(stderr, 
		"usage : %s [-c] [-v] [-l num]"
		" <file name>\n"
		"  -c : to count in simulation\n"
		"  -v : verbose simulation\n"
		"  -l : K instructions per page, default 1K\n"
		"  -h : print this message and quit\n"
		"  file name : the MIPS ELF32 program to translate\n", fname);
}

static mips_emulator *mltr = NULL;

static unsigned iLog2(uint32_t num)
{       
	uint32_t power = 0;
	uint32_t logval =1;

	while(logval < num){
	    logval*=2;
	    power++;
	}   
	    
	return power;
} 

int main(int argc, char *argv[], char *envp[])
{
	int i;
	char *bin_name;
	char *prog_name = NULL;
	bool verbose = false;
	bool tocount = false;
	unsigned shift_val = 10;

	for(i = 1; i < argc; i++)
	{
		if(strcmp(argv[i], "-c") == 0) tocount = true; else
		if(strcmp(argv[i], "-v") == 0) verbose = true; else
		if(strcmp(argv[i], "-l") == 0) {
			double temp1 = atof(argv[++i])*(1<<10);
			shift_val = iLog2((uint32_t)temp1);
			if (shift_val<9) shift_val = 9;
		} else
		if(strcmp(argv[i], "-h") == 0 || argv[i][0]=='-') 
			{usage(argv[0]); return 1;} else
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
		mltr->load_program(prog_name, argc - i, argv + i, envp);
		decomp(prog_name, argc - i, argv + i, envp, mltr, shift_val, tocount, verbose);
		delete mltr;
	}
	else {
		usage(argv[0]);
		return 1;
	}

	return 0;
}
