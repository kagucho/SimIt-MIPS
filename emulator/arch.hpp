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

#ifndef ARCH_H
#define ARCH_H

#ifdef DYNAMIC
#include "dyn_mips_emul.hpp"
#else
#include "mips_emul.hpp"
#endif

#include <cmath>

typedef emulator::mips_emulator emulator_t;

typedef mips_inst_t target_inst_t;
typedef mips_address_t target_addr_t;

void do_syscall(emulator_t *emu, mips_address_t pc);
char *emit_code(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow);

#endif
