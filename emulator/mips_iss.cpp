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
#include "mips_iss.hpp"
#include <cmath>
void impl_nop(emulator_t *emm, target_inst_t inst)
{


}

void impl_add(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rd = (inst>>11)&31;
	unsigned rt = (inst>>16)&31;

	WRITE_GPR(READ_GPR(rs) + READ_GPR(rt), rd);
	
}

void impl_addi(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rt = (inst>>16)&31;
	unsigned imm = (inst>>0)&65535;

	WRITE_GPR(READ_GPR(rs) + (hword_t)imm, rt);
	
}

void impl_addiu(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rt = (inst>>16)&31;
	unsigned imm = (inst>>0)&65535;

	WRITE_GPR(READ_GPR(rs) + (hword_t)imm, rt);
	
}

void impl_addu(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rd = (inst>>11)&31;
	unsigned rt = (inst>>16)&31;

	WRITE_GPR(READ_GPR(rs) + READ_GPR(rt), rd);
	
}

void impl_sub(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rd = (inst>>11)&31;
	unsigned rt = (inst>>16)&31;

	WRITE_GPR(READ_GPR(rs) - READ_GPR(rt), rd);
	
}

void impl_subu(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rd = (inst>>11)&31;
	unsigned rt = (inst>>16)&31;

	WRITE_GPR(READ_GPR(rs) - READ_GPR(rt), rd);
	
}

void impl_mult(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rt = (inst>>16)&31;
	dword_t product;

	product = ((dword_t)(word_t)READ_GPR(rs) * (dword_t)(word_t)READ_GPR(rt));
	WRITE_LO((word_t)product);
	WRITE_HI((word_t)(product>>32));
	
}

void impl_multu(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rt = (inst>>16)&31;
	dword_t product;

	product = ((u_dword_t)READ_GPR(rs) * (u_dword_t)READ_GPR(rt));
	WRITE_LO((word_t)product);
	WRITE_HI((word_t)(product>>32));
	
}

void impl_div(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rt = (inst>>16)&31;

	WRITE_LO((word_t)READ_GPR(rs) / (word_t)READ_GPR(rt));
	WRITE_HI((word_t)READ_GPR(rs) % (word_t)READ_GPR(rt));
	
}

void impl_divu(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rt = (inst>>16)&31;

	WRITE_LO(READ_GPR(rs) / READ_GPR(rt));
	WRITE_HI(READ_GPR(rs) % READ_GPR(rt));
	
}

void impl_and(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rd = (inst>>11)&31;
	unsigned rt = (inst>>16)&31;

	WRITE_GPR(READ_GPR(rs) & READ_GPR(rt), rd);
	
}

void impl_andi(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rt = (inst>>16)&31;
	unsigned imm = (inst>>0)&65535;

	WRITE_GPR(READ_GPR(rs) & (u_hword_t)imm, rt);
	
}

void impl_nor(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rd = (inst>>11)&31;
	unsigned rt = (inst>>16)&31;

	WRITE_GPR(~(READ_GPR(rs) | READ_GPR(rt)), rd);
	
}

void impl_or(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rd = (inst>>11)&31;
	unsigned rt = (inst>>16)&31;

	WRITE_GPR(READ_GPR(rs) | READ_GPR(rt), rd);
	
}

void impl_ori(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rt = (inst>>16)&31;
	unsigned imm = (inst>>0)&65535;

	WRITE_GPR(READ_GPR(rs) | (u_hword_t)imm, rt);
	
}

void impl_xor(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rd = (inst>>11)&31;
	unsigned rt = (inst>>16)&31;

	WRITE_GPR(READ_GPR(rs) ^ READ_GPR(rt), rd);
	
}

void impl_xori(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rt = (inst>>16)&31;
	unsigned imm = (inst>>0)&65535;

	WRITE_GPR(READ_GPR(rs) ^ (u_hword_t)imm, rt);
	
}

void impl_sll(emulator_t *emm, target_inst_t inst)
{
	unsigned rd = (inst>>11)&31;
	unsigned rt = (inst>>16)&31;
	unsigned shamt = (inst>>6)&31;

	WRITE_GPR(READ_GPR(rt) << shamt, rd);
	
}

void impl_sllv(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rd = (inst>>11)&31;
	unsigned rt = (inst>>16)&31;

	WRITE_GPR(READ_GPR(rt) << (0x1F&READ_GPR(rs)), rd);
	
}

void impl_srl(emulator_t *emm, target_inst_t inst)
{
	unsigned rd = (inst>>11)&31;
	unsigned rt = (inst>>16)&31;
	unsigned shamt = (inst>>6)&31;

	WRITE_GPR((u_word_t)READ_GPR(rt) >> shamt, rd);
	
}

void impl_srlv(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rd = (inst>>11)&31;
	unsigned rt = (inst>>16)&31;

	WRITE_GPR((u_word_t)READ_GPR(rt) >> (0x1F&READ_GPR(rs)), rd);
	
}

void impl_sra(emulator_t *emm, target_inst_t inst)
{
	unsigned rd = (inst>>11)&31;
	unsigned rt = (inst>>16)&31;
	unsigned shamt = (inst>>6)&31;

	WRITE_GPR((word_t)READ_GPR(rt) >> shamt, rd);
	
}

void impl_srav(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rd = (inst>>11)&31;
	unsigned rt = (inst>>16)&31;

	WRITE_GPR((word_t)READ_GPR(rt) >> (0x1F&READ_GPR(rs)), rd);
	
}

void impl_slt(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rd = (inst>>11)&31;
	unsigned rt = (inst>>16)&31;

	WRITE_GPR(((word_t)READ_GPR(rs) < (word_t)READ_GPR(rt)) ? 1 : 0, rd); 
	
}

void impl_slti(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rt = (inst>>16)&31;
	unsigned imm = (inst>>0)&65535;

	WRITE_GPR(((word_t)READ_GPR(rs) < (hword_t)imm) ? 1 : 0, rt); 
	
}

void impl_sltiu(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rt = (inst>>16)&31;
	unsigned imm = (inst>>0)&65535;

	WRITE_GPR((READ_GPR(rs) < (u_word_t)(hword_t)imm) ? 1 : 0, rt); 
	
}

void impl_sltu(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rd = (inst>>11)&31;
	unsigned rt = (inst>>16)&31;

	WRITE_GPR((READ_GPR(rs) < READ_GPR(rt)) ? 1 : 0, rd); 
	
}

void impl_beq(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rt = (inst>>16)&31;
	unsigned imm = (inst>>0)&65535;
	if (READ_GPR(rs) == READ_GPR(rt)) {
		SET_PC(READ_PC()+4+((hword_t)imm << 2));
		SET_DELAY();
	}
}

void impl_bgez(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned imm = (inst>>0)&65535;
	if ((word_t)READ_GPR(rs) >= 0) {
		SET_PC(READ_PC()+4+((hword_t)imm << 2));
		SET_DELAY();
	}
}

void impl_bgezal(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned imm = (inst>>0)&65535;

	WRITE_RA(READ_PC()+4+4);

	if ((word_t)READ_GPR(rs) >= 0) {
		SET_PC(READ_PC()+4+((hword_t)imm << 2));
		SET_DELAY();
	}
}

void impl_bgtz(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned imm = (inst>>0)&65535;
	if ((word_t)READ_GPR(rs) > 0) {
		SET_PC(READ_PC()+4+((hword_t)imm << 2));
		SET_DELAY();
	}
}

void impl_blez(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned imm = (inst>>0)&65535;
	if ((word_t)READ_GPR(rs) <= 0) {
		SET_PC(READ_PC()+4+((hword_t)imm << 2));
		SET_DELAY();
	}
}

void impl_bltzal(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned imm = (inst>>0)&65535;

	WRITE_RA(READ_PC()+4+4);

	if ((word_t)READ_GPR(rs) < 0) {
		SET_PC(READ_PC()+4+((hword_t)imm << 2));
		SET_DELAY();
	}
}

void impl_bltz(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned imm = (inst>>0)&65535;
	if ((word_t)READ_GPR(rs) < 0) {
		SET_PC(READ_PC()+4+((hword_t)imm << 2));
		SET_DELAY();
	}
}

void impl_bne(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rt = (inst>>16)&31;
	unsigned imm = (inst>>0)&65535;
	if (READ_GPR(rs) != READ_GPR(rt)) {
		SET_PC(READ_PC()+4+((hword_t)imm << 2));
		SET_DELAY();
	}
}

void impl_j(emulator_t *emm, target_inst_t inst)
{
	unsigned ad = (inst>>0)&67108863;
		SET_PC((READ_PC()+4&0xF0000000)|(ad<<2));
		SET_DELAY();
}

void impl_jal(emulator_t *emm, target_inst_t inst)
{
	unsigned ad = (inst>>0)&67108863;

	WRITE_RA(READ_PC()+4+4);

		SET_PC((READ_PC()+4&0xF0000000)|(ad<<2));
		SET_DELAY();
}

void impl_jalr(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;

	WRITE_RA(READ_PC()+4+4);

		SET_PC(READ_GPR(rs));
		SET_DELAY();
}

void impl_jr(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
		SET_PC(READ_GPR(rs));
		SET_DELAY();
}

void impl_mfhi(emulator_t *emm, target_inst_t inst)
{
	unsigned rd = (inst>>11)&31;

	WRITE_GPR(READ_HI(),rd);
	
}

void impl_mflo(emulator_t *emm, target_inst_t inst)
{
	unsigned rd = (inst>>11)&31;

	WRITE_GPR(READ_LO(),rd);
	
}

void impl_mthi(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;

	WRITE_HI(READ_GPR(rs));
	
}

void impl_mtlo(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;

	WRITE_LO(READ_GPR(rs));
	
}

void impl_mfc1(emulator_t *emm, target_inst_t inst)
{
	unsigned rt = (inst>>16)&31;
	unsigned fs = (inst>>11)&31;

	WRITE_GPR(READ_WFP(fs), rt);
	
}

void impl_mtc1(emulator_t *emm, target_inst_t inst)
{
	unsigned rt = (inst>>16)&31;
	unsigned fs = (inst>>11)&31;

    WRITE_WFP(READ_GPR(rt), fs); 
	
}

void impl_cfc1(emulator_t *emm, target_inst_t inst)
{
	unsigned rt = (inst>>16)&31;
	unsigned fs = (inst>>11)&31;

	if(fs == 31)
		WRITE_GPR(READ_FCSR(), rt);
	
}

void impl_ctc1(emulator_t *emm, target_inst_t inst)
{
	unsigned rt = (inst>>16)&31;
	unsigned fs = (inst>>11)&31;

	if(fs == 31)
    	WRITE_FCSR(READ_GPR(rt)); 
	
}

void impl_lb(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rt = (inst>>16)&31;
	unsigned imm = (inst>>0)&65535;

	WRITE_GPR((byte_t)READ_BYTE(READ_GPR(rs)+(hword_t)imm), rt);
	
}

void impl_lbu(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rt = (inst>>16)&31;
	unsigned imm = (inst>>0)&65535;

	WRITE_GPR((u_byte_t)READ_BYTE(READ_GPR(rs)+(hword_t)imm), rt);
	
}

void impl_lh(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rt = (inst>>16)&31;
	unsigned imm = (inst>>0)&65535;

	WRITE_GPR((hword_t)READ_HWORD(READ_GPR(rs)+(hword_t)imm), rt);
	
}

void impl_lhu(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rt = (inst>>16)&31;
	unsigned imm = (inst>>0)&65535;

	WRITE_GPR((u_hword_t)READ_HWORD(READ_GPR(rs)+(hword_t)imm), rt);
	
}

void impl_lw(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rt = (inst>>16)&31;
	unsigned imm = (inst>>0)&65535;

	WRITE_GPR((u_word_t)READ_WORD(READ_GPR(rs)+(hword_t)imm), rt);
	
}

void impl_lwl(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rt = (inst>>16)&31;
	unsigned imm = (inst>>0)&65535;
	target_addr_t addr;
	target_addr_t addr2;
	word_t offr;
	word_t offm;

    addr = (hword_t)imm + READ_GPR(rs);
    addr2 = (0xFFFFFFFC)&addr;
    offr = (addr - addr2+1)*8;
    offm =   ((0x00000003)&(~(addr - addr2)))*8;
    WRITE_GPR(((u_word_t)READ_WORD(addr2) << offm)|(((u_dword_t)0xFFFFFFFF >> offr) & READ_GPR(rt)), rt);
	
}

void impl_lwr(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rt = (inst>>16)&31;
	unsigned imm = (inst>>0)&65535;
	target_addr_t addr;
	target_addr_t addr2;
	word_t offr;
	word_t offm;

      addr = (hword_t)imm + READ_GPR(rs);
      addr2 = (0xFFFFFFFC)&addr;
      offr = (((0x00000003)&(~(addr - addr2)))+1)*8;
      offm = (addr - addr2)*8;
      WRITE_GPR(((u_word_t)READ_WORD(addr2) >> offm)|(((u_dword_t)0xFFFFFFFF << offr) & READ_GPR(rt)), rt);
	
}

void impl_lui(emulator_t *emm, target_inst_t inst)
{
	unsigned rt = (inst>>16)&31;
	unsigned imm = (inst>>0)&65535;

    WRITE_GPR(((u_hword_t)imm<<16), rt);
	
}

void impl_sb(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rt = (inst>>16)&31;
	unsigned imm = (inst>>0)&65535;

	WRITE_BYTE((u_byte_t)READ_GPR(rt), READ_GPR(rs)+(hword_t)imm);
	
}

void impl_sh(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rt = (inst>>16)&31;
	unsigned imm = (inst>>0)&65535;

	WRITE_HWORD((u_hword_t)READ_GPR(rt), READ_GPR(rs)+(hword_t)imm);
	
}

void impl_sw(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rt = (inst>>16)&31;
	unsigned imm = (inst>>0)&65535;

	WRITE_WORD((u_word_t)READ_GPR(rt), READ_GPR(rs)+(hword_t)imm);
	
}

void impl_swl(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rt = (inst>>16)&31;
	unsigned imm = (inst>>0)&65535;
	target_addr_t addr;
	target_addr_t addr2;

      addr = (hword_t)imm + READ_GPR(rs);
      addr2 = (0xFFFFFFFC)&addr;
      for(int i=3; addr2<=addr; i--,addr2++)
      	WRITE_BYTE(((u_byte_t)(READ_GPR(rt)>>(i*8))), addr2);
	
}

void impl_swr(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rt = (inst>>16)&31;
	unsigned imm = (inst>>0)&65535;
	target_addr_t addr;
	target_addr_t addr2;

      addr = (hword_t)imm + READ_GPR(rs);
      addr2 = (0xFFFFFFFC & addr)+3;
      for(int i=0; addr<=addr2; i++,addr++)
      	WRITE_BYTE(((u_byte_t)(READ_GPR(rt)>>(i*8))), addr);
	
}

void impl_lwc1(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rt = (inst>>16)&31;
	unsigned imm = (inst>>0)&65535;

	WRITE_WFP((word_t)READ_WORD(READ_GPR(rs)+(hword_t)imm), rt);
	
}

void impl_swc1(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rt = (inst>>16)&31;
	unsigned imm = (inst>>0)&65535;

	WRITE_WORD((u_word_t)READ_WFP(rt), READ_GPR(rs)+(hword_t)imm);
	
}

void impl_ll(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rt = (inst>>16)&31;
	unsigned imm = (inst>>0)&65535;

	WRITE_GPR((word_t)READ_WORD(READ_GPR(rs)+(hword_t)imm), rt);
	
}

void impl_sc(emulator_t *emm, target_inst_t inst)
{
	unsigned rs = (inst>>21)&31;
	unsigned rt = (inst>>16)&31;
	unsigned imm = (inst>>0)&65535;

	WRITE_WORD((u_word_t)READ_GPR(rt), READ_GPR(rs)+(hword_t)imm);
	WRITE_GPR(1,rt);
	
}

void impl_brk(emulator_t *emm, target_inst_t inst)
{

	emm->break_point();
	
}

void impl_abs_d(emulator_t *emm, target_inst_t inst)
{
	unsigned fs = (inst>>11)&31;
	unsigned fd = (inst>>6)&31;

    WRITE_DFP(fabs(READ_DFP(fs)),fd);	
	
}

void impl_abs_s(emulator_t *emm, target_inst_t inst)
{
	unsigned fs = (inst>>11)&31;
	unsigned fd = (inst>>6)&31;

    WRITE_SFP(fabs(READ_SFP(fs)),fd);	
	
}

void impl_add_d(emulator_t *emm, target_inst_t inst)
{
	unsigned fs = (inst>>11)&31;
	unsigned ft = (inst>>16)&31;
	unsigned fd = (inst>>6)&31;

	WRITE_DFP(READ_DFP(fs)+READ_DFP(ft),fd);  
	
}

void impl_add_s(emulator_t *emm, target_inst_t inst)
{
	unsigned fs = (inst>>11)&31;
	unsigned ft = (inst>>16)&31;
	unsigned fd = (inst>>6)&31;

	WRITE_SFP(READ_SFP(fs)+READ_SFP(ft),fd);  
	
}

void impl_cvt_d_s(emulator_t *emm, target_inst_t inst)
{
	unsigned fs = (inst>>11)&31;
	unsigned fd = (inst>>6)&31;

	WRITE_DFP((double)READ_SFP(fs),fd);
	
}

void impl_cvt_d_w(emulator_t *emm, target_inst_t inst)
{
	unsigned fs = (inst>>11)&31;
	unsigned fd = (inst>>6)&31;

	WRITE_DFP((double)READ_WFP(fs),fd);
	
}

void impl_cvt_s_d(emulator_t *emm, target_inst_t inst)
{
	unsigned fs = (inst>>11)&31;
	unsigned fd = (inst>>6)&31;

	WRITE_SFP((spfloat_t)READ_DFP(fs),fd);
	
}

void impl_cvt_s_w(emulator_t *emm, target_inst_t inst)
{
	unsigned fs = (inst>>11)&31;
	unsigned fd = (inst>>6)&31;

	WRITE_SFP((spfloat_t)READ_WFP(fs),fd);
	
}

void impl_cvt_w_d(emulator_t *emm, target_inst_t inst)
{
	unsigned fs = (inst>>11)&31;
	unsigned fd = (inst>>6)&31;
	word_t fixed_word;

	switch(READ_RM()){
        case 1:
            fixed_word = (word_t)READ_DFP(fs);
            break;
        case 2:                                               
            fixed_word = (word_t)ceil(READ_DFP(fs));                   
            break;                                            
        case 3:                                               
            fixed_word = (word_t)floor(READ_DFP(fs));                  
            break;                                            
        default:                                              
        case 0:                                               
            fixed_word = (word_t)rint(READ_DFP(fs));                   
    };
	WRITE_WFP(fixed_word,fd);    
	
}

void impl_cvt_w_s(emulator_t *emm, target_inst_t inst)
{
	unsigned fs = (inst>>11)&31;
	unsigned fd = (inst>>6)&31;
	word_t fixed_word;

	switch(READ_RM()){
        case 1:
            fixed_word = (word_t)READ_SFP(fs);
            break;
        case 2:                                               
            fixed_word = (word_t)ceil((double)READ_SFP(fs));                   
            break;                                            
        case 3:                                               
            fixed_word = (word_t)floor((double)READ_SFP(fs));                  
            break;                                            
        default:                                              
        case 0:                                               
            fixed_word = (word_t)rint((double)READ_SFP(fs));                   
    };
	WRITE_WFP(fixed_word,fd);    
	
}

void impl_div_d(emulator_t *emm, target_inst_t inst)
{
	unsigned fs = (inst>>11)&31;
	unsigned ft = (inst>>16)&31;
	unsigned fd = (inst>>6)&31;

	WRITE_DFP(READ_DFP(fs)/READ_DFP(ft),fd);  
	
}

void impl_div_s(emulator_t *emm, target_inst_t inst)
{
	unsigned fs = (inst>>11)&31;
	unsigned ft = (inst>>16)&31;
	unsigned fd = (inst>>6)&31;

	WRITE_SFP(READ_SFP(fs)/READ_SFP(ft),fd);  
	
}

void impl_mov_d(emulator_t *emm, target_inst_t inst)
{
	unsigned fs = (inst>>11)&31;
	unsigned fd = (inst>>6)&31;

	WRITE_DFP(READ_DFP(fs),fd);  
	
}

void impl_mov_s(emulator_t *emm, target_inst_t inst)
{
	unsigned fs = (inst>>11)&31;
	unsigned fd = (inst>>6)&31;

	WRITE_SFP(READ_SFP(fs),fd);  
	
}

void impl_mul_d(emulator_t *emm, target_inst_t inst)
{
	unsigned fs = (inst>>11)&31;
	unsigned ft = (inst>>16)&31;
	unsigned fd = (inst>>6)&31;

	WRITE_DFP(READ_DFP(fs)*READ_DFP(ft),fd);  
	
}

void impl_mul_s(emulator_t *emm, target_inst_t inst)
{
	unsigned fs = (inst>>11)&31;
	unsigned ft = (inst>>16)&31;
	unsigned fd = (inst>>6)&31;

	WRITE_SFP(READ_SFP(fs)*READ_SFP(ft),fd);  
	
}

void impl_neg_d(emulator_t *emm, target_inst_t inst)
{
	unsigned fs = (inst>>11)&31;
	unsigned fd = (inst>>6)&31;

	WRITE_DFP(0-READ_DFP(fs),fd);  
	
}

void impl_neg_s(emulator_t *emm, target_inst_t inst)
{
	unsigned fs = (inst>>11)&31;
	unsigned fd = (inst>>6)&31;

	WRITE_SFP(0-READ_SFP(fs),fd);  
	
}

void impl_sub_d(emulator_t *emm, target_inst_t inst)
{
	unsigned fs = (inst>>11)&31;
	unsigned ft = (inst>>16)&31;
	unsigned fd = (inst>>6)&31;

	WRITE_DFP(READ_DFP(fs)-READ_DFP(ft),fd);  
	
}

void impl_sub_s(emulator_t *emm, target_inst_t inst)
{
	unsigned fs = (inst>>11)&31;
	unsigned ft = (inst>>16)&31;
	unsigned fd = (inst>>6)&31;

	WRITE_SFP(READ_SFP(fs)-READ_SFP(ft),fd);  
	
}

void impl_c_cond_d(emulator_t *emm, target_inst_t inst)
{
	unsigned cc = (inst>>8)&7;
	unsigned cond = (inst>>0)&15;
	unsigned fs = (inst>>11)&31;
	unsigned ft = (inst>>16)&31;
	bool less;
	bool equal;
	bool unordered;

	unordered = isnan(READ_DFP(fs)) | isnan(READ_DFP(ft));
	if(unordered) {
		equal = false;
		less = false;                                    
    }                                                         
    else{
		equal = READ_DFP(fs) == READ_DFP(ft);
		less = READ_DFP(fs) < READ_DFP(ft);
    }

	if(((cond&0x4) && less)||((cond&0x2) && equal)||((cond&0x1) && unordered))
		SET_FCC(cc);
	else
		CLEAR_FCC(cc);
	
}

void impl_c_cond_s(emulator_t *emm, target_inst_t inst)
{
	unsigned cc = (inst>>8)&7;
	unsigned cond = (inst>>0)&15;
	unsigned fs = (inst>>11)&31;
	unsigned ft = (inst>>16)&31;
	bool less;
	bool equal;
	bool unordered;

	unordered = isnan(READ_SFP(fs)) | isnan(READ_SFP(ft));
	if(unordered) {
		equal = false;
		less = false;                                    
    }                                                         
    else{
		equal = READ_SFP(fs) == READ_SFP(ft);
		less = READ_SFP(fs) < READ_SFP(ft);
    }

	if(((cond&0x4) && less)||((cond&0x2) && equal)||((cond&0x1) && unordered))
		SET_FCC(cc);
	else
		CLEAR_FCC(cc);
	
}

void impl_bc1f(emulator_t *emm, target_inst_t inst)
{
	unsigned imm = (inst>>0)&65535;
	unsigned cc = (inst>>18)&7;
	if (!READ_FCC(cc)) {
		SET_PC(READ_PC()+4+((hword_t)imm << 2));
		SET_DELAY();
	}
}

void impl_bc1t(emulator_t *emm, target_inst_t inst)
{
	unsigned imm = (inst>>0)&65535;
	unsigned cc = (inst>>18)&7;
	if (READ_FCC(cc)) {
		SET_PC(READ_PC()+4+((hword_t)imm << 2));
		SET_DELAY();
	}
}

void impl_syscall(emulator_t *emm, target_inst_t inst)
{

	DO_SYSCALL(emm,READ_PC());
	
}

