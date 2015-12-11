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
#ifndef CGEN_HPP
#define CGEN_HPP
#include "arch.hpp"
char *emitc_nop(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_add(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_addi(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_addiu(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_addu(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_sub(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_subu(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_mult(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_multu(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_div(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_divu(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_and(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_andi(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_nor(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_or(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_ori(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_xor(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_xori(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_sll(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_sllv(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_srl(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_srlv(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_sra(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_srav(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_slt(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_slti(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_sltiu(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_sltu(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_beq(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_bgez(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_bgezal(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_bgtz(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_blez(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_bltzal(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_bltz(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_bne(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_j(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_jal(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_jalr(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_jr(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_mfhi(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_mflo(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_mthi(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_mtlo(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_mfc1(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_mtc1(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_cfc1(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_ctc1(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_lb(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_lbu(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_lh(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_lhu(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_lw(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_lwl(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_lwr(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_lui(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_sb(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_sh(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_sw(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_swl(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_swr(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_lwc1(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_swc1(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_ll(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_sc(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_brk(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_abs_d(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_abs_s(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_add_d(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_add_s(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_cvt_d_s(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_cvt_d_w(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_cvt_s_d(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_cvt_s_w(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_cvt_w_d(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_cvt_w_s(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_div_d(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_div_s(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_mov_d(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_mov_s(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_mul_d(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_mul_s(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_neg_d(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_neg_s(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_sub_d(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_sub_s(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_c_cond_d(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_c_cond_s(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_bc1f(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_bc1t(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
char *emitc_syscall(char *, emulator_t *, target_addr_t, target_addr_t, target_addr_t, bool);
#endif
