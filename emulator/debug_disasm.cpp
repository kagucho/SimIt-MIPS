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
#include "misc.hpp"
#include "debug_disasm.hpp"

#define RTYPE 0
#define ITYPE 1
#define JTYPE 3
#define FTYPE 4



#define GPR_NAME(xx) mips_gpr_names[xx]


void mips_disassemble(mips_inst_t inst, u_word_t pc, char disasm[256])
{ 
  char *buf = disasm;
  int inst_type;

  sprintf(buf, " Invalid Instruction: %x\n", inst);
  
  if(0);
#define IDEF(a,b,c,d) \
  else if ((inst & b) == c) buf += sprintf(buf, "%s ", #a);
#include "mips_inst.def"
#undef IDEF
  else
    return;
 
  if(inst == 0x00000000) {
    sprintf(buf, "\n");
    return;
  }
  
  inst_type = getInstType(inst);
  
  switch(inst_type)
    {
    case JTYPE:
      //j inst type
      sprintf(buf, "%x\n",ADFLD);
      break;
    case ITYPE:
      //i inst type
      if(isOneOpBranch(inst))
	sprintf(buf, "$%s, %i\n",GPR_NAME(RSFLD),(hword_t)IMFLD);
      else if(isLoadStore(inst))
	sprintf(buf, "$%s, %i($%s)\n",GPR_NAME(RTFLD),(hword_t)IMFLD,GPR_NAME(RSFLD));
      else if(isFPLoadStore(inst))
	sprintf(buf, "$f%u, %i($%s)\n",FTFLD,(hword_t)IMFLD,GPR_NAME(RSFLD));
      else
	sprintf(buf, "$%s, $%s, %i\n",GPR_NAME(RTFLD),GPR_NAME(RSFLD),IMFLD);
      break;
	case FTYPE:
      //floating point instruction
	  if(isCVT(inst))	
	sprintf(buf, "$f%u, $f%u\n",FDFLD,FSFLD);
	  else if(isCompare(inst))
	sprintf(buf, "%u, $f%u, $f%u\n",(FDFLD>>2),FSFLD,FTFLD);
	  else if(isFPBranch(inst))
	sprintf(buf, "%u, %i\n",(FTFLD>>2),IMFLD); 
	  else if(isGPR_FP_Move(inst))
	sprintf(buf, "$%s, $f%u\n",GPR_NAME(RTFLD),FSFLD);
	  else if(isGPR_FCR_Move(inst))
	sprintf(buf, "$%s, $%u\n",GPR_NAME(RTFLD),FSFLD);
	  else
	sprintf(buf, "$f%u, $f%u, $f%u\n",FDFLD,FSFLD,FTFLD);
      break;
    default:
    case RTYPE:
      //r inst type
      if((0x3F&inst)==0x12) //syscall
		return;
      else if(isShift(inst))
	sprintf(buf, "$%s, $%s, %i\n",GPR_NAME(RDFLD),GPR_NAME(RTFLD),SHFLD);
      else if(isROneOp(inst))
	sprintf(buf, "$%s\n", GPR_NAME(RSFLD));
      else if(isRTwoOp(inst))
	sprintf(buf, "$%s, $%s\n",GPR_NAME(RSFLD),GPR_NAME(RTFLD));
      else if(isRMt(inst))
	sprintf(buf, "$%s\n",GPR_NAME(RSFLD));
      else if(isRMf(inst))
	sprintf(buf, "$%s\n",GPR_NAME(RDFLD));
      else
	sprintf(buf, "$%s, $%s, $%s\n",GPR_NAME(RDFLD),GPR_NAME(RSFLD),GPR_NAME(RTFLD));
    };
}

bool isRMt(const mips_inst_t inst)
{
  const mips_inst_t funct=(0x3F&inst);

    if((funct  == 0x10) && (funct == 0x11))
      return true;
    else
      return false;
}

bool isRMf(const mips_inst_t inst)
{
  const mips_inst_t funct=(0x3F&inst);

    if((funct  == 0x12) && (funct == 0x13))
      return true;
    else
      return false;
}

bool isROneOp(const mips_inst_t inst)
{
	const mips_inst_t funct=(0x3F&inst);

	if((funct == 0x08) || (funct == 0x09))
		return true;
	else
		return false;
}

bool isRTwoOp(const mips_inst_t inst)
{
  const mips_inst_t funct=(0x3F&inst);

    if((funct  >= 0x18) && (funct <= 0x1b))
      return true;
    else
      return false;
}

bool isLoadStore(const mips_inst_t inst)
{
  const mips_inst_t opcode=(0xFC000000&inst)>>26;

    if(((opcode  >= 0x20) && (opcode <= 0x2e)) ||
       (opcode == 0x30) || (opcode == 0x38))
      return true;
    else
      return false;
}

bool isFPLoadStore(const mips_inst_t inst)
{	
  const mips_inst_t opcode=(0xFC000000&inst)>>26;

	if(opcode == 0x31 || opcode == 0x39)
		return true;
	else
		return false;
}

bool isOneOpBranch(const mips_inst_t inst)
{
  const mips_inst_t opcode=(0xFC000000&inst)>>26;

    if((opcode  == 0x00) || (opcode == 0x01) ||
       (opcode == 0x06) || (opcode == 0x07))
      return true;
    else
      return false;
}

bool isShift(const mips_inst_t inst)
{
    const mips_inst_t funct=(0x3F&inst);

    if((funct == 0x00) || (funct == 0x01) || (funct == 0x03))
      return true;
    else
      return false;
}

bool isCVT(const mips_inst_t inst)
{
	const mips_inst_t funct=(0x3F&inst);

	if((funct == 32) || (funct == 33) || (funct == 36))
		return true;
	else
		return false;
}

bool isCompare(const mips_inst_t inst)
{
	const mips_inst_t funct=(0x3F&inst);

	if(funct >= 48)
		return true;
	else
		return false;
}

int getInstType(const mips_inst_t inst)
{
  const mips_inst_t opcode=(0xFC000000&inst)>>26;
  
  if(opcode == 0)
    return RTYPE;
  else if((opcode  == 0x02) || (opcode == 0x03))
    return JTYPE;
  else if(opcode == 0x11)
	return FTYPE;
  else return ITYPE;
}

bool isGPR_FP_Move(const mips_inst_t inst)
{
	if(RSFLD == 0 || RSFLD == 4)
		return true;
	else
		return false;
}

bool isGPR_FCR_Move(const mips_inst_t inst)
{
	if(RSFLD == 2 || RSFLD == 6)
		return true;
	else
		return false;
}

bool isFPBranch(const mips_inst_t inst)
{
	if(RSFLD == 8)
		return true;
	else
		return false;
}
