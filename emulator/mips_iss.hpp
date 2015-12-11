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
#ifndef ISS_HPP
#define ISS_HPP
#include "arch.hpp"
void impl_nop(emulator_t *emm, target_inst_t inst);
void impl_add(emulator_t *emm, target_inst_t inst);
void impl_addi(emulator_t *emm, target_inst_t inst);
void impl_addiu(emulator_t *emm, target_inst_t inst);
void impl_addu(emulator_t *emm, target_inst_t inst);
void impl_sub(emulator_t *emm, target_inst_t inst);
void impl_subu(emulator_t *emm, target_inst_t inst);
void impl_mult(emulator_t *emm, target_inst_t inst);
void impl_multu(emulator_t *emm, target_inst_t inst);
void impl_div(emulator_t *emm, target_inst_t inst);
void impl_divu(emulator_t *emm, target_inst_t inst);
void impl_and(emulator_t *emm, target_inst_t inst);
void impl_andi(emulator_t *emm, target_inst_t inst);
void impl_nor(emulator_t *emm, target_inst_t inst);
void impl_or(emulator_t *emm, target_inst_t inst);
void impl_ori(emulator_t *emm, target_inst_t inst);
void impl_xor(emulator_t *emm, target_inst_t inst);
void impl_xori(emulator_t *emm, target_inst_t inst);
void impl_sll(emulator_t *emm, target_inst_t inst);
void impl_sllv(emulator_t *emm, target_inst_t inst);
void impl_srl(emulator_t *emm, target_inst_t inst);
void impl_srlv(emulator_t *emm, target_inst_t inst);
void impl_sra(emulator_t *emm, target_inst_t inst);
void impl_srav(emulator_t *emm, target_inst_t inst);
void impl_slt(emulator_t *emm, target_inst_t inst);
void impl_slti(emulator_t *emm, target_inst_t inst);
void impl_sltiu(emulator_t *emm, target_inst_t inst);
void impl_sltu(emulator_t *emm, target_inst_t inst);
void impl_beq(emulator_t *emm, target_inst_t inst);
void impl_bgez(emulator_t *emm, target_inst_t inst);
void impl_bgezal(emulator_t *emm, target_inst_t inst);
void impl_bgtz(emulator_t *emm, target_inst_t inst);
void impl_blez(emulator_t *emm, target_inst_t inst);
void impl_bltzal(emulator_t *emm, target_inst_t inst);
void impl_bltz(emulator_t *emm, target_inst_t inst);
void impl_bne(emulator_t *emm, target_inst_t inst);
void impl_j(emulator_t *emm, target_inst_t inst);
void impl_jal(emulator_t *emm, target_inst_t inst);
void impl_jalr(emulator_t *emm, target_inst_t inst);
void impl_jr(emulator_t *emm, target_inst_t inst);
void impl_mfhi(emulator_t *emm, target_inst_t inst);
void impl_mflo(emulator_t *emm, target_inst_t inst);
void impl_mthi(emulator_t *emm, target_inst_t inst);
void impl_mtlo(emulator_t *emm, target_inst_t inst);
void impl_mfc1(emulator_t *emm, target_inst_t inst);
void impl_mtc1(emulator_t *emm, target_inst_t inst);
void impl_cfc1(emulator_t *emm, target_inst_t inst);
void impl_ctc1(emulator_t *emm, target_inst_t inst);
void impl_lb(emulator_t *emm, target_inst_t inst);
void impl_lbu(emulator_t *emm, target_inst_t inst);
void impl_lh(emulator_t *emm, target_inst_t inst);
void impl_lhu(emulator_t *emm, target_inst_t inst);
void impl_lw(emulator_t *emm, target_inst_t inst);
void impl_lwl(emulator_t *emm, target_inst_t inst);
void impl_lwr(emulator_t *emm, target_inst_t inst);
void impl_lui(emulator_t *emm, target_inst_t inst);
void impl_sb(emulator_t *emm, target_inst_t inst);
void impl_sh(emulator_t *emm, target_inst_t inst);
void impl_sw(emulator_t *emm, target_inst_t inst);
void impl_swl(emulator_t *emm, target_inst_t inst);
void impl_swr(emulator_t *emm, target_inst_t inst);
void impl_lwc1(emulator_t *emm, target_inst_t inst);
void impl_swc1(emulator_t *emm, target_inst_t inst);
void impl_ll(emulator_t *emm, target_inst_t inst);
void impl_sc(emulator_t *emm, target_inst_t inst);
void impl_brk(emulator_t *emm, target_inst_t inst);
void impl_abs_d(emulator_t *emm, target_inst_t inst);
void impl_abs_s(emulator_t *emm, target_inst_t inst);
void impl_add_d(emulator_t *emm, target_inst_t inst);
void impl_add_s(emulator_t *emm, target_inst_t inst);
void impl_cvt_d_s(emulator_t *emm, target_inst_t inst);
void impl_cvt_d_w(emulator_t *emm, target_inst_t inst);
void impl_cvt_s_d(emulator_t *emm, target_inst_t inst);
void impl_cvt_s_w(emulator_t *emm, target_inst_t inst);
void impl_cvt_w_d(emulator_t *emm, target_inst_t inst);
void impl_cvt_w_s(emulator_t *emm, target_inst_t inst);
void impl_div_d(emulator_t *emm, target_inst_t inst);
void impl_div_s(emulator_t *emm, target_inst_t inst);
void impl_mov_d(emulator_t *emm, target_inst_t inst);
void impl_mov_s(emulator_t *emm, target_inst_t inst);
void impl_mul_d(emulator_t *emm, target_inst_t inst);
void impl_mul_s(emulator_t *emm, target_inst_t inst);
void impl_neg_d(emulator_t *emm, target_inst_t inst);
void impl_neg_s(emulator_t *emm, target_inst_t inst);
void impl_sub_d(emulator_t *emm, target_inst_t inst);
void impl_sub_s(emulator_t *emm, target_inst_t inst);
void impl_c_cond_d(emulator_t *emm, target_inst_t inst);
void impl_c_cond_s(emulator_t *emm, target_inst_t inst);
void impl_bc1f(emulator_t *emm, target_inst_t inst);
void impl_bc1t(emulator_t *emm, target_inst_t inst);
void impl_syscall(emulator_t *emm, target_inst_t inst);
#endif
