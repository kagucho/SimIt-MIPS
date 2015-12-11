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
#ifndef DEBUG_DISASM_HPP
#define DEBUG_DISASM_HPP

#include "misc.hpp"
//from gnu mips-dis.c
static const char * const mips_gpr_names[32] = {
  "zero", "at",   "v0",   "v1",   "a0",   "a1",   "a2",   "a3",
  "t0",   "t1",   "t2",   "t3",   "t4",   "t5",   "t6",   "t7",
  "s0",   "s1",   "s2",   "s3",   "s4",   "s5",   "s6",   "s7",
  "t8",   "t9",   "k0",   "k1",   "gp",   "sp",   "s8",   "ra"
};

void mips_disassemble(mips_inst_t inst, u_word_t pc, char disasm[]);
bool isRMt(const mips_inst_t inst);
bool isRMf(const mips_inst_t inst);
bool isROneOp(const mips_inst_t inst);
bool isRTwoOp(const mips_inst_t inst);
bool isLoadStore(const mips_inst_t inst);
bool isFPLoadStore(const mips_inst_t inst);
bool isOneOpBranch(const mips_inst_t inst);
bool isShift(const mips_inst_t inst);
bool isCVT(const mips_inst_t inst);
bool isCompare(const mips_inst_t inst);
bool isFPBranch(const mips_inst_t inst);
bool isGPR_FP_Move(const mips_inst_t inst);
bool isGPR_FCR_Move(const mips_inst_t inst);
int getInstType(const mips_inst_t inst);

#endif
