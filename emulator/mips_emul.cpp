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
#include <cstring>
#include <cstdlib>
#include <config.h>
#if HAVE_FENV_H
#include <fenv.h>
#endif
#include "mips_emul.hpp"
#include "mips_iss.hpp"

#include "auto_impl.h"
#include "mips_dec.h"

#if 0
#define INUM(a,b,c) a,
static const char * const mnemonic_table[] = {
#include "inst_num.def"
};
#undef INUM
#endif

using namespace emulator;

mips_emulator::mips_emulator(bool v)
{
	mem = new memory;
	verbose = v;

	reset();
}

mips_emulator::~mips_emulator()
{
	delete mem;
}

void mips_emulator::reset()
{
	mem->reset();

	status = ST_RESET;
	delay_slot = false;

	// reset stats
	reset_instruction_counters();

	// reset registers
	memset(&regs, 0, sizeof(regs));

#if HAVE_FENV_H
	//set fp rounding mode
	fesetround(FE_TONEAREST);
#endif
}

void mips_emulator::prog_exit(int ret)
{
	status = ST_EXIT;
	retcode = ret;
}

void mips_emulator::interrupt()
{
	if (status==ST_RUNNING || status==ST_DEBUGGING)
		status = ST_SIGINT;
	else
		exit(0);
}

void mips_emulator::break_point()
{
	if (status==ST_RUNNING || status==ST_DEBUGGING)
		status = ST_BREAK;

	// if this is in delay slot, then npc = pc; else pc = pc-4;
	// so that at the end of execute(), the pc remains unchanged
	if (delay_slot)
		set_next_pc(ReadPC());
	else
		WritePC(ReadPC()-4);
}

void mips_emulator::seg_fault()
{
	status = ST_ERROR;
	retcode = 1;
}

void mips_emulator::execute(mips_inst_t inst)
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

uint64_t mips_emulator::run(){ 

	mips_inst_t inst;

	icount = 0;
	status = ST_RUNNING;
	while(status==ST_RUNNING)
	{
		inst = mem->read_word_fast(ReadPC());
		//fprintf(stderr,"%08x : %08x\n",ReadPC(),inst);
		execute(inst);
		icount++;
	}
	
	return icount;
}

uint64_t mips_emulator::run_count(uint64_t& maxcount){ 
	
	mips_inst_t inst;

	icount = 0;
	status = ST_RUNNING;
	while(status==ST_RUNNING && icount<maxcount)
	{
		inst = mem->read_word_fast(ReadPC());
		execute(inst);
		icount++;
	}
	
	return icount;
}

void mips_emulator::dump_instruction_counters(FILE *filename)
{
#if 0
	fprintf(filename, "\n");
	for(int i = 0; i < INST_TOTAL; i++) {
		if(counters[i] > 0) {
			fprintf(filename, "%s : ", mnemonic_table[i]);
			dump_int64(counters[i], filename);
			if(counters[i] > 1000000) {
				fputs(" (", filename);
				dump_int64_smart(counters[i], filename);
				fputs(")", filename);
			}
			fputs("\n", filename);
		}
	}
#endif
	fputs("Total instructions : ", filename);
	dump_int64(icount+ccount, filename);
	if (icount > 1000000) {
		fputs(" (", filename);
		dump_int64_smart(icount+ccount, filename);
		fputs(")", filename);
	}
	fputs("\n", filename);

	fputs("Percentage interpreted : ", filename);
	fprintf(filename, "%.2f\n", (double)icount*100.0/(icount+ccount));
}

void mips_emulator::reset_instruction_counters()
{
	icount = 0;
	ccount = 0;
#if 0
	for(int i=0; i< INST_TOTAL; i++)
		counters[i] = 0;
#endif
}


void impl_default(IMPL_FORMALS)
{
    fprintf(stderr, "Attempted to execute a bogus opcode at 0x%08x"
        " (inst = 0x%08x), ignored...\n", emm->ReadPC()-4, inst);
}


void mips_emulator::WriteFCSR(u_word_t control_word) {
	regs.fcsr = control_word;

#if HAVE_FENV_H
	switch(regs.fcsr&0x3) {
		case 1:
			fesetround(FE_TOWARDZERO);
			break;
		case 2:
			fesetround(FE_UPWARD);
			break;
		case 3:
			fesetround(FE_DOWNWARD);
		default:
		case 0:
			fesetround(FE_TONEAREST);
	};
#endif

}
