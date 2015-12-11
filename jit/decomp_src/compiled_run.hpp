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
#ifndef COMPILED_RUN_HPP
#define COMPILED_RUN_HPP

#include "Scompiled_all.hpp"
void run_compiled(emulator::mips_emulator *emm);
extern uint64_t njumps;

#ifdef NOMEMINLINE
word_t mem_read_word(emulator::mips_emulator *emm, target_addr_t ind);
byte_t mem_read_byte(emulator::mips_emulator *emm, target_addr_t ind);
halfword_t mem_read_half_word(emulator::mips_emulator *emm, target_addr_t ind);
dword_t mem_read_dword(emulator::mips_emulator *emm, target_addr_t ind);
void mem_write_word(emulator::mips_emulator *emm, target_addr_t ind, word_t var);
void mem_write_byte(emulator::mips_emulator *emm, target_addr_t ind, byte_t var);
void mem_write_half_word(emulator::mips_emulator *emm, target_addr_t ind, halfword_t var);
void mem_write_dword(emulator::mips_emulator *emm, target_addr_t ind, dword_t var);
#endif
#endif
