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
#include "compiled_run.hpp"
#include "Scompiled_all.hpp"
#include <cstdlib>

using namespace emulator;

void run_compiled(mips_emulator *emm)
{
	fpointer *func_ptrs;

	// function pointers
	func_ptrs = (fpointer *)calloc(1<<(32-SHIFT_VAL), sizeof(fpointer));
	for (unsigned ii=0; ii<NUM_FUNCS; ii++) {
		unsigned ind = func_addrs[ii]>>SHIFT_VAL;
		func_ptrs[ind] = compiled_funct[ii];
	}

	emm->set_running();

	while(emm->is_running()) //this needs to be changed so the file can stop
	{
		mips_addr_t jumppc = emm->ReadPC();
		njumps++;
		func_ptrs[jumppc>>SHIFT_VAL](emm, jumppc);
	}

	free(func_ptrs);
}

#ifdef NOMEMINLINE
word_t mem_read_word(mips_emulator *emm, target_addr_t ind) {
	return emm->mem->read_word(ind);
}

byte_t mem_read_byte(mips_emulator *emm, target_addr_t ind) {
	return emm->mem->read_byte(ind);
}

halfword_t mem_read_half_word(mips_emulator *emm, target_addr_t ind) {
	return emm->mem->read_half_word(ind);
}

dword_t mem_read_dword(mips_emulator *emm, target_addr_t ind) {
	return emm->mem->read_dword(ind);
}

void mem_write_word(mips_emulator *emm, target_addr_t ind, word_t var) {
	emm->mem->write_word(ind, var);
}

void mem_write_byte(mips_emulator *emm, target_addr_t ind, byte_t var) {
	emm->mem->write_byte(ind, var);
}

void mem_write_half_word(mips_emulator *emm, target_addr_t ind, halfword_t var) {
	emm->mem->write_half_word(ind, var);
}

void mem_write_dword(mips_emulator *emm, target_addr_t ind, dword_t var) {
	emm->mem->write_dword(ind, var);
}

#endif
