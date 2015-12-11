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
#include <cstdio>
#include <pthread.h>

#include "util.hpp"
#include "dyn_mips_emul.hpp"

#include "mips_iss.hpp"
#include "auto_impl.h"
#include "mips_dec.h"

using namespace emulator;

//constructor
dyn_mips_emulator::dyn_mips_emulator(uint32_t threshold, uint32_t shiftval,
	bool verbose, bool showmsg, bool tocount, bool selfmod) :
	mips_emulator(verbose), threshold(threshold),
	shiftval(shiftval), showmsg(showmsg), tocount(tocount), selfmod(selfmod)
{
	cache_dir = NULL;

	unsigned num_blks = 1<<(32-shiftval);	
	blk_info = (struct blk_info_t *)calloc(num_blks, sizeof(struct blk_info_t));

	req_num = 0;
	dll_ind = 0;
	dll_num = 0;

	dll_list = new vp_list;
	tid_list = new uw_list;

	pthread_cond_init(&my_cond, NULL);
	pthread_mutex_init(&my_mut, NULL);
}

//destructor
dyn_mips_emulator::~dyn_mips_emulator()
{
	// close all dll libraries
	while (!dll_list->empty()) {
		close_dll((struct dll_info_t *)(dll_list->pop_front()));
	}

	delete dll_list;
	delete tid_list;

	free(blk_info);
	blk_info = NULL;
	if (cache_dir) free(cache_dir);
	cache_dir = NULL;
}

void dyn_mips_emulator::execute(mips_inst_t inst)
{
	bool delay_flag = delay_slot;
	decode_main(this, inst);
	if(delay_flag) {
		WritePC(nextPC);
		delay_slot = is_break_inst(inst); //break inst. has no side effect
	}
	else { //increment PC+4
		WritePC(ReadPC() + 4);
	}
}

uint64_t dyn_mips_emulator::run_solo()
{
	icount = 0;
	ccount = 0;

	/* from long jump */
	if (setjmp(jbuf)==1) {
		// resume from this instruction
		WritePC(marked_pc);
	}
	run_solo_internal();
	return icount+ccount;
}

void dyn_mips_emulator::run_solo_internal()
{
	mips_inst_t inst;

	status = ST_RUNNING;
	while(status==ST_RUNNING)
	{
		unsigned ind = ReadPC() >> shiftval;
		if (blk_info[ind].dll_fptr && !delay_slot) 		{
			in_compiled = true;
			(*(blk_info[ind].dll_fptr))(this, ReadPC());
			in_compiled = false;
		}
		else if(blk_info[ind].count > threshold && !delay_slot)
		{
			blk_info[ind].count = 0;
			if (create_new_lib(ReadPC())) {
				in_compiled = true;
				(blk_info[ind].dll_fptr)(this,ReadPC());
				in_compiled = false;
			}
		}
		else 
		{
			inst = mem->read_word_fast(ReadPC());
			execute(inst);
			blk_info[ind].count++;
			icount++;
		}
	}
}

uint64_t dyn_mips_emulator::run_parallel()
{ 
	icount = 0;
	ccount = 0;

	/* from long jump */
	if (setjmp(jbuf)==1) {
		// resume from this instruction
		WritePC(marked_pc);
	}
	run_parallel_internal();
	return icount+ccount;
}


void dyn_mips_emulator::run_parallel_internal()
{
	mips_inst_t inst;

	status = ST_RUNNING;
	while(status==ST_RUNNING)
	{
		unsigned ind = ReadPC() >> shiftval;
		if (blk_info[ind].count > threshold && !delay_slot) {
			if (blk_info[ind].dll_fptr) {
				in_compiled = true;
				(*(blk_info[ind].dll_fptr))(this, ReadPC());
				in_compiled = false;
				continue;
			}
			else if ((blk_info[ind].flag&1)==0) {
				blk_info[ind].flag |= 1;
				req_num++;
				pthread_mutex_lock(&my_mut);
				tid_list->push_back(ind);
				pthread_cond_signal(&my_cond);
				pthread_mutex_unlock(&my_mut);
				continue;
			}
		}
		inst = mem->read_word_fast(ReadPC());
		execute(inst);
		blk_info[ind].count++;
		icount++;
	}
}

void dyn_mips_emulator::get_block_to_compile(unsigned *dll, unsigned *blk)
{
	pthread_mutex_lock(&my_mut);
	while (tid_list->empty())
		pthread_cond_wait(&my_cond, &my_mut);

	// thr_inds acts as a FIFO, can use stack style by popping the back
	*blk = tid_list->pop_front();
#if 0
		unsigned ind=0;
        unsigned max_cnt = threshold;                                 
        uw_list::iterator uwit, maxit;                        
        for (uwit=maxit=tid_list->begin();              
             uwit!=tid_list->end(); uwit++,ind++) {           
            if (blk_info[*uwit].count > max_cnt) {      
                maxit = uwit;
				max_cnt = blk_info[*uwit].count;
            }
        }
		//fprintf(stderr, "value %d %d\n", max_cnt, ind);
        *blk = *maxit;
		tid_list->erase(maxit);
#endif

	*dll = dll_ind++;
	pthread_mutex_unlock(&my_mut);
}

void dyn_mips_emulator::check_write_blk(mips_addr_t addr, unsigned size)
{
	mips_addr_t aligned_addr = (addr>>shiftval)<<shiftval;
	for (;aligned_addr<addr+size;aligned_addr+=1<<shiftval) {
		check_write(addr);
	}
}

void dyn_mips_emulator::invalidate_dll(mips_addr_t addr)
{
	//fprintf(stderr, "Modifying compiled block at %u\n", addr);
	unsigned blk_ind = addr>>shiftval;
	unload_lib(blk_ind);
	if (in_compiled) {
		longjmp(jbuf, 1);
	}
}
