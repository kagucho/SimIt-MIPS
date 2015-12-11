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
#include "mips_gen.hpp"
char *emitc_nop(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"");
	return buf;
}

char *emitc_add(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_GPR(READ_GPR(%u) + READ_GPR(%u), %u);\n"
	"	", ((inst>>21)&31), ((inst>>16)&31), ((inst>>11)&31));
	return buf;
}

char *emitc_addi(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_GPR(READ_GPR(%u) + (hword_t)%u, %u);\n"
	"	", ((inst>>21)&31), ((inst>>0)&65535), ((inst>>16)&31));
	return buf;
}

char *emitc_addiu(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_GPR(READ_GPR(%u) + (hword_t)%u, %u);\n"
	"	", ((inst>>21)&31), ((inst>>0)&65535), ((inst>>16)&31));
	return buf;
}

char *emitc_addu(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_GPR(READ_GPR(%u) + READ_GPR(%u), %u);\n"
	"	", ((inst>>21)&31), ((inst>>16)&31), ((inst>>11)&31));
	return buf;
}

char *emitc_sub(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_GPR(READ_GPR(%u) - READ_GPR(%u), %u);\n"
	"	", ((inst>>21)&31), ((inst>>16)&31), ((inst>>11)&31));
	return buf;
}

char *emitc_subu(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_GPR(READ_GPR(%u) - READ_GPR(%u), %u);\n"
	"	", ((inst>>21)&31), ((inst>>16)&31), ((inst>>11)&31));
	return buf;
}

char *emitc_mult(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	product = ((dword_t)(word_t)READ_GPR(%u) * (dword_t)(word_t)READ_GPR(%u));\n"
	"	WRITE_LO((word_t)product);\n"
	"	WRITE_HI((word_t)(product>>32));\n"
	"	", ((inst>>21)&31), ((inst>>16)&31));
	return buf;
}

char *emitc_multu(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	product = ((u_dword_t)READ_GPR(%u) * (u_dword_t)READ_GPR(%u));\n"
	"	WRITE_LO((word_t)product);\n"
	"	WRITE_HI((word_t)(product>>32));\n"
	"	", ((inst>>21)&31), ((inst>>16)&31));
	return buf;
}

char *emitc_div(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_LO((word_t)READ_GPR(%u) / (word_t)READ_GPR(%u));\n"
	"	WRITE_HI((word_t)READ_GPR(%u) % (word_t)READ_GPR(%u));\n"
	"	", ((inst>>21)&31), ((inst>>16)&31), ((inst>>21)&31), ((inst>>16)&31));
	return buf;
}

char *emitc_divu(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_LO(READ_GPR(%u) / READ_GPR(%u));\n"
	"	WRITE_HI(READ_GPR(%u) % READ_GPR(%u));\n"
	"	", ((inst>>21)&31), ((inst>>16)&31), ((inst>>21)&31), ((inst>>16)&31));
	return buf;
}

char *emitc_and(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_GPR(READ_GPR(%u) & READ_GPR(%u), %u);\n"
	"	", ((inst>>21)&31), ((inst>>16)&31), ((inst>>11)&31));
	return buf;
}

char *emitc_andi(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_GPR(READ_GPR(%u) & (u_hword_t)%u, %u);\n"
	"	", ((inst>>21)&31), ((inst>>0)&65535), ((inst>>16)&31));
	return buf;
}

char *emitc_nor(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_GPR(~(READ_GPR(%u) | READ_GPR(%u)), %u);\n"
	"	", ((inst>>21)&31), ((inst>>16)&31), ((inst>>11)&31));
	return buf;
}

char *emitc_or(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_GPR(READ_GPR(%u) | READ_GPR(%u), %u);\n"
	"	", ((inst>>21)&31), ((inst>>16)&31), ((inst>>11)&31));
	return buf;
}

char *emitc_ori(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_GPR(READ_GPR(%u) | (u_hword_t)%u, %u);\n"
	"	", ((inst>>21)&31), ((inst>>0)&65535), ((inst>>16)&31));
	return buf;
}

char *emitc_xor(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_GPR(READ_GPR(%u) ^ READ_GPR(%u), %u);\n"
	"	", ((inst>>21)&31), ((inst>>16)&31), ((inst>>11)&31));
	return buf;
}

char *emitc_xori(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_GPR(READ_GPR(%u) ^ (u_hword_t)%u, %u);\n"
	"	", ((inst>>21)&31), ((inst>>0)&65535), ((inst>>16)&31));
	return buf;
}

char *emitc_sll(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_GPR(READ_GPR(%u) << %u, %u);\n"
	"	", ((inst>>16)&31), ((inst>>6)&31), ((inst>>11)&31));
	return buf;
}

char *emitc_sllv(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_GPR(READ_GPR(%u) << (0x1F&READ_GPR(%u)), %u);\n"
	"	", ((inst>>16)&31), ((inst>>21)&31), ((inst>>11)&31));
	return buf;
}

char *emitc_srl(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_GPR((u_word_t)READ_GPR(%u) >> %u, %u);\n"
	"	", ((inst>>16)&31), ((inst>>6)&31), ((inst>>11)&31));
	return buf;
}

char *emitc_srlv(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_GPR((u_word_t)READ_GPR(%u) >> (0x1F&READ_GPR(%u)), %u);\n"
	"	", ((inst>>16)&31), ((inst>>21)&31), ((inst>>11)&31));
	return buf;
}

char *emitc_sra(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_GPR((word_t)READ_GPR(%u) >> %u, %u);\n"
	"	", ((inst>>16)&31), ((inst>>6)&31), ((inst>>11)&31));
	return buf;
}

char *emitc_srav(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_GPR((word_t)READ_GPR(%u) >> (0x1F&READ_GPR(%u)), %u);\n"
	"	", ((inst>>16)&31), ((inst>>21)&31), ((inst>>11)&31));
	return buf;
}

char *emitc_slt(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_GPR(((word_t)READ_GPR(%u) < (word_t)READ_GPR(%u)) ? 1 : 0, %u); \n"
	"	", ((inst>>21)&31), ((inst>>16)&31), ((inst>>11)&31));
	return buf;
}

char *emitc_slti(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_GPR(((word_t)READ_GPR(%u) < (hword_t)%u) ? 1 : 0, %u); \n"
	"	", ((inst>>21)&31), ((inst>>0)&65535), ((inst>>16)&31));
	return buf;
}

char *emitc_sltiu(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_GPR((READ_GPR(%u) < (u_word_t)(hword_t)%u) ? 1 : 0, %u); \n"
	"	", ((inst>>21)&31), ((inst>>0)&65535), ((inst>>16)&31));
	return buf;
}

char *emitc_sltu(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_GPR((READ_GPR(%u) < READ_GPR(%u)) ? 1 : 0, %u); \n"
	"	", ((inst>>21)&31), ((inst>>16)&31), ((inst>>11)&31));
	return buf;
}

char *emitc_beq(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\tif (READ_GPR(%u) == READ_GPR(%u)) {\n", ((inst>>21)&31), ((inst>>16)&31));
	buf = emit_code(buf, emm, curpc+4, fstart, fend, true);

	target_addr_t jpc = curpc+4+((hword_t)((inst>>0)&65535) << 2);
	if (jpc<fstart || jpc>=fend)
		buf += sprintf(buf, "\tLONG_JUMP(%uU,%uU);\n", curpc, jpc);
	else
		buf += sprintf(buf, "\tJUMP(%uU, %uU, L%x);\n", curpc, jpc, jpc);
	buf += sprintf(buf, "\t}\n");
	return buf;
}

char *emitc_bgez(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\tif ((word_t)READ_GPR(%u) >= 0) {\n", ((inst>>21)&31));
	buf = emit_code(buf, emm, curpc+4, fstart, fend, true);

	target_addr_t jpc = curpc+4+((hword_t)((inst>>0)&65535) << 2);
	if (jpc<fstart || jpc>=fend)
		buf += sprintf(buf, "\tLONG_JUMP(%uU,%uU);\n", curpc, jpc);
	else
		buf += sprintf(buf, "\tJUMP(%uU, %uU, L%x);\n", curpc, jpc, jpc);
	buf += sprintf(buf, "\t}\n");
	return buf;
}

char *emitc_bgezal(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_RA(%u+4);\n"
	"", curpc+4);
	buf += sprintf(buf, "\tif ((word_t)READ_GPR(%u) >= 0) {\n", ((inst>>21)&31));
	buf = emit_code(buf, emm, curpc+4, fstart, fend, true);

	target_addr_t jpc = curpc+4+((hword_t)((inst>>0)&65535) << 2);
	if (jpc<fstart || jpc>=fend)
		buf += sprintf(buf, "\tLONG_JUMP(%uU,%uU);\n", curpc, jpc);
	else
		buf += sprintf(buf, "\tJUMP(%uU, %uU, L%x);\n", curpc, jpc, jpc);
	buf += sprintf(buf, "\t}\n");
	return buf;
}

char *emitc_bgtz(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\tif ((word_t)READ_GPR(%u) > 0) {\n", ((inst>>21)&31));
	buf = emit_code(buf, emm, curpc+4, fstart, fend, true);

	target_addr_t jpc = curpc+4+((hword_t)((inst>>0)&65535) << 2);
	if (jpc<fstart || jpc>=fend)
		buf += sprintf(buf, "\tLONG_JUMP(%uU,%uU);\n", curpc, jpc);
	else
		buf += sprintf(buf, "\tJUMP(%uU, %uU, L%x);\n", curpc, jpc, jpc);
	buf += sprintf(buf, "\t}\n");
	return buf;
}

char *emitc_blez(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\tif ((word_t)READ_GPR(%u) <= 0) {\n", ((inst>>21)&31));
	buf = emit_code(buf, emm, curpc+4, fstart, fend, true);

	target_addr_t jpc = curpc+4+((hword_t)((inst>>0)&65535) << 2);
	if (jpc<fstart || jpc>=fend)
		buf += sprintf(buf, "\tLONG_JUMP(%uU,%uU);\n", curpc, jpc);
	else
		buf += sprintf(buf, "\tJUMP(%uU, %uU, L%x);\n", curpc, jpc, jpc);
	buf += sprintf(buf, "\t}\n");
	return buf;
}

char *emitc_bltzal(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_RA(%u+4);\n"
	"", curpc+4);
	buf += sprintf(buf, "\tif ((word_t)READ_GPR(%u) < 0) {\n", ((inst>>21)&31));
	buf = emit_code(buf, emm, curpc+4, fstart, fend, true);

	target_addr_t jpc = curpc+4+((hword_t)((inst>>0)&65535) << 2);
	if (jpc<fstart || jpc>=fend)
		buf += sprintf(buf, "\tLONG_JUMP(%uU,%uU);\n", curpc, jpc);
	else
		buf += sprintf(buf, "\tJUMP(%uU, %uU, L%x);\n", curpc, jpc, jpc);
	buf += sprintf(buf, "\t}\n");
	return buf;
}

char *emitc_bltz(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\tif ((word_t)READ_GPR(%u) < 0) {\n", ((inst>>21)&31));
	buf = emit_code(buf, emm, curpc+4, fstart, fend, true);

	target_addr_t jpc = curpc+4+((hword_t)((inst>>0)&65535) << 2);
	if (jpc<fstart || jpc>=fend)
		buf += sprintf(buf, "\tLONG_JUMP(%uU,%uU);\n", curpc, jpc);
	else
		buf += sprintf(buf, "\tJUMP(%uU, %uU, L%x);\n", curpc, jpc, jpc);
	buf += sprintf(buf, "\t}\n");
	return buf;
}

char *emitc_bne(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\tif (READ_GPR(%u) != READ_GPR(%u)) {\n", ((inst>>21)&31), ((inst>>16)&31));
	buf = emit_code(buf, emm, curpc+4, fstart, fend, true);

	target_addr_t jpc = curpc+4+((hword_t)((inst>>0)&65535) << 2);
	if (jpc<fstart || jpc>=fend)
		buf += sprintf(buf, "\tLONG_JUMP(%uU,%uU);\n", curpc, jpc);
	else
		buf += sprintf(buf, "\tJUMP(%uU, %uU, L%x);\n", curpc, jpc, jpc);
	buf += sprintf(buf, "\t}\n");
	return buf;
}

char *emitc_j(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf = emit_code(buf, emm, curpc+4, fstart, fend, true);

	target_addr_t jpc = (curpc+4&0xF0000000)|(((inst>>0)&67108863)<<2);
	if (jpc<fstart || jpc>=fend)
		buf += sprintf(buf, "\tLONG_JUMP(%uU,%uU);\n", curpc, jpc);
	else
		buf += sprintf(buf, "\tJUMP(%uU, %uU, L%x);\n", curpc, jpc, jpc);
	return buf;
}

char *emitc_jal(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_RA(%u+4);\n"
	"", curpc+4);
	buf = emit_code(buf, emm, curpc+4, fstart, fend, true);

	target_addr_t jpc = (curpc+4&0xF0000000)|(((inst>>0)&67108863)<<2);
	if (jpc<fstart || jpc>=fend)
		buf += sprintf(buf, "\tLONG_JUMP(%uU,%uU);\n", curpc, jpc);
	else
		buf += sprintf(buf, "\tJUMP(%uU, %uU, L%x);\n", curpc, jpc, jpc);
	return buf;
}

char *emitc_jalr(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_RA(%u+4);\n"
	"", curpc+4);
	buf = emit_code(buf, emm, curpc+4, fstart, fend, true);
	buf += sprintf(buf, "\tjpc = READ_GPR(%u);\n", ((inst>>21)&31));
	buf += sprintf(buf, "\tif (jpc<%uU || jpc>=%uU ) {\n", fstart, fend);
	buf += sprintf(buf, "\t\tLONG_JUMP(%uU, jpc);\n\t}\n", curpc);
	buf += sprintf(buf, "\telse\n");
	buf += sprintf(buf, "\t\tJUMP(%uU, jpc, *labels[(jpc-%uU)/4]);\n", curpc, fstart);
	return buf;
}

char *emitc_jr(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf = emit_code(buf, emm, curpc+4, fstart, fend, true);
	buf += sprintf(buf, "\tjpc = READ_GPR(%u);\n", ((inst>>21)&31));
	buf += sprintf(buf, "\tif (jpc<%uU || jpc>=%uU ) {\n", fstart, fend);
	buf += sprintf(buf, "\t\tLONG_JUMP(%uU, jpc);\n\t}\n", curpc);
	buf += sprintf(buf, "\telse\n");
	buf += sprintf(buf, "\t\tJUMP(%uU, jpc, *labels[(jpc-%uU)/4]);\n", curpc, fstart);
	return buf;
}

char *emitc_mfhi(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_GPR(READ_HI(),%u);\n"
	"	", ((inst>>11)&31));
	return buf;
}

char *emitc_mflo(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_GPR(READ_LO(),%u);\n"
	"	", ((inst>>11)&31));
	return buf;
}

char *emitc_mthi(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_HI(READ_GPR(%u));\n"
	"	", ((inst>>21)&31));
	return buf;
}

char *emitc_mtlo(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_LO(READ_GPR(%u));\n"
	"	", ((inst>>21)&31));
	return buf;
}

char *emitc_mfc1(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_GPR(READ_WFP(%u), %u);\n"
	"	", ((inst>>11)&31), ((inst>>16)&31));
	return buf;
}

char *emitc_mtc1(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"    WRITE_WFP(READ_GPR(%u), %u); \n"
	"	", ((inst>>16)&31), ((inst>>11)&31));
	return buf;
}

char *emitc_cfc1(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	if(%u == 31)\n"
	"		WRITE_GPR(READ_FCSR(), %u);\n"
	"	", ((inst>>11)&31), ((inst>>16)&31));
	return buf;
}

char *emitc_ctc1(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	if(%u == 31)\n"
	"    	WRITE_FCSR(READ_GPR(%u)); \n"
	"	", ((inst>>11)&31), ((inst>>16)&31));
	return buf;
}

char *emitc_lb(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_GPR((byte_t)READ_BYTE(READ_GPR(%u)+(hword_t)%u), %u);\n"
	"	", ((inst>>21)&31), ((inst>>0)&65535), ((inst>>16)&31));
	return buf;
}

char *emitc_lbu(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_GPR((u_byte_t)READ_BYTE(READ_GPR(%u)+(hword_t)%u), %u);\n"
	"	", ((inst>>21)&31), ((inst>>0)&65535), ((inst>>16)&31));
	return buf;
}

char *emitc_lh(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_GPR((hword_t)READ_HWORD(READ_GPR(%u)+(hword_t)%u), %u);\n"
	"	", ((inst>>21)&31), ((inst>>0)&65535), ((inst>>16)&31));
	return buf;
}

char *emitc_lhu(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_GPR((u_hword_t)READ_HWORD(READ_GPR(%u)+(hword_t)%u), %u);\n"
	"	", ((inst>>21)&31), ((inst>>0)&65535), ((inst>>16)&31));
	return buf;
}

char *emitc_lw(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_GPR((u_word_t)READ_WORD(READ_GPR(%u)+(hword_t)%u), %u);\n"
	"	", ((inst>>21)&31), ((inst>>0)&65535), ((inst>>16)&31));
	return buf;
}

char *emitc_lwl(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"    addr = (hword_t)%u + READ_GPR(%u);\n"
	"    addr2 = (0xFFFFFFFC)&addr;\n"
	"    offr = (addr - addr2+1)*8;\n"
	"    offm =   ((0x00000003)&(~(addr - addr2)))*8;\n"
	"    WRITE_GPR(((u_word_t)READ_WORD(addr2) << offm)|(((u_dword_t)0xFFFFFFFF >> offr) & READ_GPR(%u)), %u);\n"
	"	", ((inst>>0)&65535), ((inst>>21)&31), ((inst>>16)&31), ((inst>>16)&31));
	return buf;
}

char *emitc_lwr(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"      addr = (hword_t)%u + READ_GPR(%u);\n"
	"      addr2 = (0xFFFFFFFC)&addr;\n"
	"      offr = (((0x00000003)&(~(addr - addr2)))+1)*8;\n"
	"      offm = (addr - addr2)*8;\n"
	"      WRITE_GPR(((u_word_t)READ_WORD(addr2) >> offm)|(((u_dword_t)0xFFFFFFFF << offr) & READ_GPR(%u)), %u);\n"
	"	", ((inst>>0)&65535), ((inst>>21)&31), ((inst>>16)&31), ((inst>>16)&31));
	return buf;
}

char *emitc_lui(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"    WRITE_GPR(((u_hword_t)%u<<16), %u); //%x\n"
	"	", ((inst>>0)&65535), ((inst>>16)&31), inst);
	return buf;
}

char *emitc_sb(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\tMARK_PC(%u);\n", in_shadow?curpc-4:curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_BYTE((u_byte_t)READ_GPR(%u), READ_GPR(%u)+(hword_t)%u);\n"
	"	", ((inst>>16)&31), ((inst>>21)&31), ((inst>>0)&65535));
	return buf;
}

char *emitc_sh(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\tMARK_PC(%u);\n", in_shadow?curpc-4:curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_HWORD((u_hword_t)READ_GPR(%u), READ_GPR(%u)+(hword_t)%u);\n"
	"	", ((inst>>16)&31), ((inst>>21)&31), ((inst>>0)&65535));
	return buf;
}

char *emitc_sw(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\tMARK_PC(%u);\n", in_shadow?curpc-4:curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_WORD((u_word_t)READ_GPR(%u), READ_GPR(%u)+(hword_t)%u);\n"
	"	", ((inst>>16)&31), ((inst>>21)&31), ((inst>>0)&65535));
	return buf;
}

char *emitc_swl(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\tMARK_PC(%u);\n", in_shadow?curpc-4:curpc);
	buf += sprintf(buf, "\n"
	"      addr = (hword_t)%u + READ_GPR(%u);\n"
	"      addr2 = (0xFFFFFFFC)&addr;\n"
	"      for(int i=3; addr2<=addr; i--,addr2++)\n"
	"      	WRITE_BYTE(((u_byte_t)(READ_GPR(%u)>>(i*8))), addr2);\n"
	"	", ((inst>>0)&65535), ((inst>>21)&31), ((inst>>16)&31));
	return buf;
}

char *emitc_swr(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\tMARK_PC(%u);\n", in_shadow?curpc-4:curpc);
	buf += sprintf(buf, "\n"
	"      addr = (hword_t)%u + READ_GPR(%u);\n"
	"      addr2 = (0xFFFFFFFC & addr)+3;\n"
	"      for(int i=0; addr<=addr2; i++,addr++)\n"
	"      	WRITE_BYTE(((u_byte_t)(READ_GPR(%u)>>(i*8))), addr);\n"
	"	", ((inst>>0)&65535), ((inst>>21)&31), ((inst>>16)&31));
	return buf;
}

char *emitc_lwc1(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_WFP((word_t)READ_WORD(READ_GPR(%u)+(hword_t)%u), %u);\n"
	"	", ((inst>>21)&31), ((inst>>0)&65535), ((inst>>16)&31));
	return buf;
}

char *emitc_swc1(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\tMARK_PC(%u);\n", in_shadow?curpc-4:curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_WORD((u_word_t)READ_WFP(%u), READ_GPR(%u)+(hword_t)%u);\n"
	"	", ((inst>>16)&31), ((inst>>21)&31), ((inst>>0)&65535));
	return buf;
}

char *emitc_ll(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_GPR((word_t)READ_WORD(READ_GPR(%u)+(hword_t)%u), %u);\n"
	"	", ((inst>>21)&31), ((inst>>0)&65535), ((inst>>16)&31));
	return buf;
}

char *emitc_sc(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\tMARK_PC(%u);\n", in_shadow?curpc-4:curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_WORD((u_word_t)READ_GPR(%u), READ_GPR(%u)+(hword_t)%u);\n"
	"	WRITE_GPR(1,%u);\n"
	"	", ((inst>>16)&31), ((inst>>21)&31), ((inst>>0)&65535), ((inst>>16)&31));
	return buf;
}

char *emitc_brk(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	emm->break_point();\n"
	"	");
	return buf;
}

char *emitc_abs_d(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"    WRITE_DFP(fabs(READ_DFP(%u)),%u);	\n"
	"	", ((inst>>11)&31), ((inst>>6)&31));
	return buf;
}

char *emitc_abs_s(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"    WRITE_SFP(fabs(READ_SFP(%u)),%u);	\n"
	"	", ((inst>>11)&31), ((inst>>6)&31));
	return buf;
}

char *emitc_add_d(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_DFP(READ_DFP(%u)+READ_DFP(%u),%u);  \n"
	"	", ((inst>>11)&31), ((inst>>16)&31), ((inst>>6)&31));
	return buf;
}

char *emitc_add_s(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_SFP(READ_SFP(%u)+READ_SFP(%u),%u);  \n"
	"	", ((inst>>11)&31), ((inst>>16)&31), ((inst>>6)&31));
	return buf;
}

char *emitc_cvt_d_s(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_DFP((double)READ_SFP(%u),%u);\n"
	"	", ((inst>>11)&31), ((inst>>6)&31));
	return buf;
}

char *emitc_cvt_d_w(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_DFP((double)READ_WFP(%u),%u);\n"
	"	", ((inst>>11)&31), ((inst>>6)&31));
	return buf;
}

char *emitc_cvt_s_d(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_SFP((spfloat_t)READ_DFP(%u),%u);\n"
	"	", ((inst>>11)&31), ((inst>>6)&31));
	return buf;
}

char *emitc_cvt_s_w(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_SFP((spfloat_t)READ_WFP(%u),%u);\n"
	"	", ((inst>>11)&31), ((inst>>6)&31));
	return buf;
}

char *emitc_cvt_w_d(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	switch(READ_RM()){\n"
	"        case 1:\n"
	"            fixed_word = (word_t)READ_DFP(%u);\n"
	"            break;\n"
	"        case 2:                                               \n"
	"            fixed_word = (word_t)ceil(READ_DFP(%u));                   \n"
	"            break;                                            \n"
	"        case 3:                                               \n"
	"            fixed_word = (word_t)floor(READ_DFP(%u));                  \n"
	"            break;                                            \n"
	"        default:                                              \n"
	"        case 0:                                               \n"
	"            fixed_word = (word_t)rint(READ_DFP(%u));                   \n"
	"    };\n"
	"	WRITE_WFP(fixed_word,%u);    \n"
	"	", ((inst>>11)&31), ((inst>>11)&31), ((inst>>11)&31), ((inst>>11)&31), ((inst>>6)&31));
	return buf;
}

char *emitc_cvt_w_s(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	switch(READ_RM()){\n"
	"        case 1:\n"
	"            fixed_word = (word_t)READ_SFP(%u);\n"
	"            break;\n"
	"        case 2:                                               \n"
	"            fixed_word = (word_t)ceil((double)READ_SFP(%u));                   \n"
	"            break;                                            \n"
	"        case 3:                                               \n"
	"            fixed_word = (word_t)floor((double)READ_SFP(%u));                  \n"
	"            break;                                            \n"
	"        default:                                              \n"
	"        case 0:                                               \n"
	"            fixed_word = (word_t)rint((double)READ_SFP(%u));                   \n"
	"    };\n"
	"	WRITE_WFP(fixed_word,%u);    \n"
	"	", ((inst>>11)&31), ((inst>>11)&31), ((inst>>11)&31), ((inst>>11)&31), ((inst>>6)&31));
	return buf;
}

char *emitc_div_d(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_DFP(READ_DFP(%u)/READ_DFP(%u),%u);  \n"
	"	", ((inst>>11)&31), ((inst>>16)&31), ((inst>>6)&31));
	return buf;
}

char *emitc_div_s(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_SFP(READ_SFP(%u)/READ_SFP(%u),%u);  \n"
	"	", ((inst>>11)&31), ((inst>>16)&31), ((inst>>6)&31));
	return buf;
}

char *emitc_mov_d(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_DFP(READ_DFP(%u),%u);  \n"
	"	", ((inst>>11)&31), ((inst>>6)&31));
	return buf;
}

char *emitc_mov_s(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_SFP(READ_SFP(%u),%u);  \n"
	"	", ((inst>>11)&31), ((inst>>6)&31));
	return buf;
}

char *emitc_mul_d(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_DFP(READ_DFP(%u)*READ_DFP(%u),%u);  \n"
	"	", ((inst>>11)&31), ((inst>>16)&31), ((inst>>6)&31));
	return buf;
}

char *emitc_mul_s(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_SFP(READ_SFP(%u)*READ_SFP(%u),%u);  \n"
	"	", ((inst>>11)&31), ((inst>>16)&31), ((inst>>6)&31));
	return buf;
}

char *emitc_neg_d(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_DFP(0-READ_DFP(%u),%u);  \n"
	"	", ((inst>>11)&31), ((inst>>6)&31));
	return buf;
}

char *emitc_neg_s(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_SFP(0-READ_SFP(%u),%u);  \n"
	"	", ((inst>>11)&31), ((inst>>6)&31));
	return buf;
}

char *emitc_sub_d(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_DFP(READ_DFP(%u)-READ_DFP(%u),%u);  \n"
	"	", ((inst>>11)&31), ((inst>>16)&31), ((inst>>6)&31));
	return buf;
}

char *emitc_sub_s(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	WRITE_SFP(READ_SFP(%u)-READ_SFP(%u),%u);  \n"
	"	", ((inst>>11)&31), ((inst>>16)&31), ((inst>>6)&31));
	return buf;
}

char *emitc_c_cond_d(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	unordered = isnan(READ_DFP(%u)) | isnan(READ_DFP(%u));\n"
	"	if(unordered) {\n"
	"		equal = false;\n"
	"		less = false;                                    \n"
	"    }                                                         \n"
	"    else{\n"
	"		equal = READ_DFP(%u) == READ_DFP(%u);\n"
	"		less = READ_DFP(%u) < READ_DFP(%u);\n"
	"    }\n"
	"\n"
	"	if(((%u&0x4) && less)||((%u&0x2) && equal)||((%u&0x1) && unordered))\n"
	"		SET_FCC(%u);\n"
	"	else\n"
	"		CLEAR_FCC(%u);\n"
	"	", ((inst>>11)&31), ((inst>>16)&31), ((inst>>11)&31), ((inst>>16)&31), ((inst>>11)&31), ((inst>>16)&31), ((inst>>0)&15), ((inst>>0)&15), ((inst>>0)&15), ((inst>>8)&7), ((inst>>8)&7));
	return buf;
}

char *emitc_c_cond_s(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	unordered = isnan(READ_SFP(%u)) | isnan(READ_SFP(%u));\n"
	"	if(unordered) {\n"
	"		equal = false;\n"
	"		less = false;                                    \n"
	"    }                                                         \n"
	"    else{\n"
	"		equal = READ_SFP(%u) == READ_SFP(%u);\n"
	"		less = READ_SFP(%u) < READ_SFP(%u);\n"
	"    }\n"
	"\n"
	"	if(((%u&0x4) && less)||((%u&0x2) && equal)||((%u&0x1) && unordered))\n"
	"		SET_FCC(%u);\n"
	"	else\n"
	"		CLEAR_FCC(%u);\n"
	"	", ((inst>>11)&31), ((inst>>16)&31), ((inst>>11)&31), ((inst>>16)&31), ((inst>>11)&31), ((inst>>16)&31), ((inst>>0)&15), ((inst>>0)&15), ((inst>>0)&15), ((inst>>8)&7), ((inst>>8)&7));
	return buf;
}

char *emitc_bc1f(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\tif (!READ_FCC(%u)) {\n", ((inst>>18)&7));
	buf = emit_code(buf, emm, curpc+4, fstart, fend, true);

	target_addr_t jpc = curpc+4+((hword_t)((inst>>0)&65535) << 2);
	if (jpc<fstart || jpc>=fend)
		buf += sprintf(buf, "\tLONG_JUMP(%uU,%uU);\n", curpc, jpc);
	else
		buf += sprintf(buf, "\tJUMP(%uU, %uU, L%x);\n", curpc, jpc, jpc);
	buf += sprintf(buf, "\t}\n");
	return buf;
}

char *emitc_bc1t(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\tif (READ_FCC(%u)) {\n", ((inst>>18)&7));
	buf = emit_code(buf, emm, curpc+4, fstart, fend, true);

	target_addr_t jpc = curpc+4+((hword_t)((inst>>0)&65535) << 2);
	if (jpc<fstart || jpc>=fend)
		buf += sprintf(buf, "\tLONG_JUMP(%uU,%uU);\n", curpc, jpc);
	else
		buf += sprintf(buf, "\tJUMP(%uU, %uU, L%x);\n", curpc, jpc, jpc);
	buf += sprintf(buf, "\t}\n");
	return buf;
}

char *emitc_syscall(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow)
{
	target_inst_t inst = emm->mem->read_word_fast(curpc);
	buf += sprintf(buf, "\n"
	"	DO_SYSCALL(emm,%u);\n"
	"	", curpc);
	return buf;
}

