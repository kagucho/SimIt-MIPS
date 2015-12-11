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
#include <cstring>
#include <cstdlib>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/stat.h>
#include "util.hpp"
#include "dyn_mips_emul.hpp"
#include "decomp_common.hpp"
#include "arch.hpp"
#include "build_dll.hpp"

//using std::vector;
using namespace emulator;

bool dyn_mips_emulator::create_new_lib(mips_addr_t addr)
{
	unsigned blk_ind = addr>>shiftval;

	decomp_at(blk_ind, dll_ind);
	// see if build successful
	if (build_new_lib(dll_ind)) {
		// see if cacheable
		if (load_lib(blk_ind, dll_ind))
			dump_cache_dir(blk_ind, dll_ind);
		// always increment index to avoid naming conflict
		dll_ind++;
		return true;
	}
	// something is wrong, stop simulation
	if (status==ST_RUNNING)
		status = ST_ELSE;
	return false;
}

void dyn_mips_emulator::decomp_at(unsigned blk_ind, unsigned ind)
{
	FILE* outfile;
	char funname[1024];
	/*starting address for decomp:
		reads current pc and aligns it with the lines/file
		parameter*/
	const mips_addr_t fstart = blk_ind << shiftval;
	const mips_addr_t fend = fstart + (1<<shiftval);

	/*create cpps*/
	sprintf(funname,"%s/Xcompiled_%u.cpp", cache_dir, ind);
	outfile = fopen(funname, "w");
	if(outfile == NULL) {
		fprintf(stderr, "Can't open file to write");
		exit(1);
	}

	fprintf(outfile, "#include <arch.hpp>\n");
	fprintf(outfile, "using namespace emulator;\n");
	fprintf(outfile, "typedef dyn_mips_emulator mips_emul_t;\n");

	decomp_block(outfile, this, fstart, fend, ind);

	fclose(outfile);
	/*end cpp code*/
}


void dyn_mips_emulator::dump_cache_dir(unsigned blk_ind, unsigned ind)
{
	FILE *outfile;

	/*addr backup data*/
	char fullpath[1024];
	sprintf(fullpath,"%s/cache.dat",cache_dir);
    outfile = fopen(fullpath, "a");
    if(outfile == NULL) {                                                       
        fprintf(stderr, "Can't open cache.dat");
        exit(1);
    }

    fprintf(outfile, "%u %u\n", blk_ind, ind);  
	fclose(outfile);
}

bool dyn_mips_emulator::ld_lib(unsigned dll_ind)
{
	char ldstring[1024];
	sprintf(ldstring,
		CXX FP_OPTION MORE_OPTION " %s/Xcompiled_%u.o"
		" -o %s/libXcompiled_%u.so",
		cache_dir, dll_ind, cache_dir, dll_ind);

	if (showmsg)
		fprintf(stderr, "%s\n", ldstring);

	if (system(ldstring)==0) {
		if (showmsg)
			fprintf(stderr, "...done!\n");
		return true;
	}
	if (showmsg)
		fprintf(stderr, "...failed!\n");
	return false;
}

bool dyn_mips_emulator::build_new_lib(unsigned ind)
{
    char compilestring[1024];
	char sedstring[1024];

	sprintf(sedstring,
		SED " \"s/READ_GPR(0)/0/g\" %s/Xcompiled_%u.cpp > %s/tmp.cpp",
		cache_dir, ind, cache_dir);

    sprintf(compilestring, 
		CXX FP_OPTION MORE_OPTION " %s/tmp.cpp"
		" -Wl,-soname,libXcompiled_%u.so"
		" -o %s/libXcompiled_%u.so"
		" -I%s/include -DDYNAMIC -DSIM_LITE",
		cache_dir, ind, cache_dir, ind, PREFIX);

	if (tocount)
		strcat(compilestring, " -DCOUNT_COMPILED");

	if (selfmod)
		strcat(compilestring, " -DSUPPORT_SELF_MOD");

	if (showmsg)
		fprintf(stderr,"%s\n", compilestring);

	if (system(sedstring)==0 && system(compilestring)==0) {
		if (showmsg)
			fprintf(stderr,"...done!\n");
		return true;
	}
	if (showmsg)
		fprintf(stderr,"...failed!\n");
	return false;
}



bool dyn_mips_emulator::create_cache_dir(char* home, char* progname)
{
	char buf[256];
	char *pnstop;

	strcpy(buf, home);
	strcat(buf, "/.emips/");

	pnstop = strrchr(progname, '/');
	if (pnstop==NULL) 
		pnstop = progname;
	
	if (!access(buf, W_OK)) {
		strcat(buf, pnstop);
		if ((!access(buf, W_OK)) || (!mkdir(buf, 0770))) {
			cache_dir = strdup(buf);
			return cache_dir!=NULL;
		}
		else
			return false;
	}
	else if (!mkdir(buf, 0770)) {	
		strcat(buf, pnstop);
		if(!mkdir(buf, 0770)) {
			cache_dir = strdup(buf);
			return cache_dir!=NULL;
		}
		else
			return false;
	}
	return true;
}

bool dyn_mips_emulator::dump_prog_stats(char *progname, char *statpath)
{
	FILE* statfile;
	struct stat progstat;
	struct stat newprogstat;

	//check if the binary exists and read status data
	if(!stat(progname, &newprogstat) && (!access(statpath,R_OK)))
	{
		//read old status data
		statfile = fopen(statpath, "r");
		if(statfile == NULL) {
			fprintf(stderr, "Can't open %s to read\n", statpath);
        	exit(1);
    	}

		fread(&progstat, sizeof(struct stat), 1, statfile);
		fclose(statfile);

		//compare new and old status items
		if(progstat.st_ino == newprogstat.st_ino && 
			progstat.st_size == newprogstat.st_size &&
			progstat.st_mtime == newprogstat.st_mtime &&
			progstat.st_ctime == newprogstat.st_ctime)
			return false;
		else {
			//over-write old status data with new status data
			statfile = fopen(statpath, "w");
			if(statfile == NULL) {
				fprintf(stderr, "Can't open %s to write\n", statpath);
   	    	 	exit(1);
			}
			fwrite(&newprogstat, sizeof(struct stat), 1, statfile);
			fclose(statfile);
			return true;
		}
	}

	statfile = fopen(statpath, "w");
	if(statfile == NULL) {
		fprintf(stderr, "Can't open %s to write\n", statpath);
       	exit(1);
   	}
	fwrite(&newprogstat, sizeof(struct stat), 1, statfile);
	fclose(statfile);
	return true;	
}


bool dyn_mips_emulator::load_or_create_cache(char* prog_name)
{
	if (!create_cache_dir(getenv("HOME"), prog_name)) {
		fprintf(stderr,
			"Cannot create cache due to insufficient permission!\n");
		return false;
	}

	char *statpath, *addrpath;

	statpath = (char *)malloc(strlen(cache_dir)+16);
	addrpath = (char *)malloc(strlen(cache_dir)+16);

	strcpy(statpath, cache_dir);
	strcpy(addrpath, cache_dir);

	strcat(statpath, "/stat.dat");
	strcat(addrpath, "/cache.dat");

	if (dump_prog_stats(prog_name, statpath) || access(addrpath, R_OK)!=0) {
		FILE* addrfile = fopen(addrpath, "w");
		fprintf(addrfile,"%u %u %u\n", shiftval, tocount?1:0, selfmod?1:0);
		fclose(addrfile);
	}

	read_cache(addrpath);

	free(statpath);
	free(addrpath);
	return true;
}


void dyn_mips_emulator::read_cache(const char* fullpath)
{
	FILE* datin;
	unsigned val1, val2, val3;

	datin = fopen(fullpath, "r");
	if(datin == NULL) {
        fprintf(stderr, "Can't open data file to read");
        exit(1);
    }

	/* first line contains blocksize:unsigned, tocount:bool, selfmod:bool */
	dll_ind = 0;
	if (fscanf(datin, "%u %u %u", &val1, &val2, &val3) < 3 ||
		val1 != shiftval || val2!=tocount || val3!=selfmod) {
		fclose(datin);
		datin = fopen(fullpath, "w");
		fprintf(datin,"%u %u %u\n", shiftval, tocount?1:0, selfmod?1:0);
	}
	else{
		/* subsequent lines contains blk_address, dll_index */
		while(fscanf(datin, "%u %u", &val1, &val2) != EOF) {
			load_lib(val1, val2);
			if (val2>=dll_ind) dll_ind = val2+1; //avoid naming clash
		}
	}

	fclose(datin);
}

struct dyn_mips_emulator::dll_info_t *
	dyn_mips_emulator::open_dll(unsigned blk_ind, unsigned ind)
{
	char libname[1024];
	void *handle;
	
	sprintf(libname, "%s/libXcompiled_%u.so", cache_dir, ind);
	handle = dlopen(libname, RTLD_LAZY);
    if (!handle) {
  		fputs (dlerror(), stderr);
		exit(1);
	 }

	struct dll_info_t *ndll = (struct dll_info_t *)malloc(sizeof(dll_info_t));
	if (ndll==NULL) {
		fputs("Out of memory\n", stderr);
		exit(1);
	}

	ndll->handle = handle;
	ndll->index = blk_ind;
	ndll->findex = ind;

	dll_list->push_back(ndll);
	dll_num++;

	return ndll;
}

void dyn_mips_emulator::close_dll(struct dll_info_t *pdll)
{
	// close this if has not been closed before (selfmod may have closed it)
	if (pdll->handle!=NULL) dlclose(pdll->handle);
	free(pdll);
	dll_num--;
}

bool dyn_mips_emulator::load_lib(unsigned blk_ind, unsigned ind)
{	
	char* error;
	char funname[1024];
	fpointer_t fptr;
	
	struct dll_info_t *ndll = open_dll(blk_ind, ind);

	sprintf(funname, "compiled_%u", ind);
	fptr = (fpointer_t)dlsym(ndll->handle, funname);
    if ((error = dlerror())!= NULL)  {           
	   	fputs(error, stderr);                                
    	exit(1);
	}

	blk_info[blk_ind].count = (u_word_t)-1; 
	blk_info[blk_ind].dll_fptr = fptr;
	blk_info[blk_ind].dll_info = ndll;

	return (blk_info[blk_ind].flag&0x2)==0;
}

bool dyn_mips_emulator::unload_lib(unsigned blk_ind)
{
	/* clear the block */
	if (blk_info[blk_ind].dll_fptr) {
		blk_info[blk_ind].dll_fptr = NULL;
		blk_info[blk_ind].count = 0;
		dlclose(blk_info[blk_ind].dll_info->handle);
		blk_info[blk_ind].dll_info->handle = NULL;
	}
	return true;
}


