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
#ifndef MISC_HPP
#define MISC_HPP

#include <bittypes.hpp>
#include <cstdio>

#define TARGET_LITTLE_ENDIAN 1
#ifndef WORDS_BIGENDIAN
#define WORDS_BIGENDIAN 0
#endif

#ifdef  SIM_LITE
#define EMUMEM_FAST
#else
#define EMUMEM_SAFE
#define SIM_SAFE
#define COUNT_INST
#endif


#define NUM_GPR 32
#define NUM_FPR 16

//keep these defs
typedef float spfloat_t; //not doing the fp
typedef double dpfloat_t;//not doing the fp
typedef uint64_t u_dword_t;
typedef int64_t dword_t;
typedef uint32_t u_word_t;
typedef int32_t word_t;
typedef uint16_t u_hword_t;
typedef int16_t hword_t;
typedef uint8_t u_byte_t;
typedef int8_t byte_t;
typedef uint32_t mips_address_t;
typedef uint32_t mips_inst_t;
typedef uint32_t mips_addr_t;

//emumem needs the following types
typedef uint32_t target_addr_t;
typedef hword_t halfword_t;

#define TRUE 1
#define FALSE 0

/*memory operation macros*/
#define READ_WORD(ind) (emm->mem->read_word(ind))
#define READ_HWORD(ind) (emm->mem->read_half_word(ind))
#define READ_DWORD(ind) (emm->mem->read_dword(ind))
#define READ_BYTE(ind) (emm->mem->read_byte(ind))
#define MEM_READ(buf, addr, size) (emu->mem->read_block(buf, addr, size))

#ifdef SUPPORT_SELF_MOD
#ifdef DYNAMIC
#define WRITE_WORD(var, ind) \
	(static_cast<emulator::dyn_mips_emulator *>(emm)->check_write(ind),emm->mem->write_word(ind, var))
#define WRITE_HWORD(var, ind) \
	(static_cast<emulator::dyn_mips_emulator *>(emm)->check_write(ind),emm->mem->write_half_word(ind, var))
#define WRITE_BYTE(var, ind) \
	(static_cast<emulator::dyn_mips_emulator *>(emm)->check_write(ind),emm->mem->write_byte(ind, var))
#define WRITE_DWORD(var, ind) \
	(static_cast<emulator::dyn_mips_emulator *>(emm)->check_write(ind),emm->mem->write_dword(ind, var)) //NOT NEEDED
#define WRITE_BYTE(var, ind) \
	(static_cast<emulator::dyn_mips_emulator *>(emm)->check_write(ind),emm->mem->write_byte(ind, var))
#define MEM_WRITE(addr, buf, size) \
	(static_cast<emulator::dyn_mips_emulator *>(emu)->check_write_blk(addr, size),emu->mem->write_block(addr, buf, size))
#else
#error "Configuration error"
#endif
#else
#define WRITE_WORD(var, ind) (emm->mem->write_word(ind, var))
#define WRITE_HWORD(var, ind) (emm->mem->write_half_word(ind, var))
#define WRITE_BYTE(var, ind) (emm->mem->write_byte(ind, var))
#define WRITE_DWORD(var, ind) (emm->mem->write_dword(ind, var)) //NOT NEEDED
#define WRITE_BYTE(var, ind) (emm->mem->write_byte(ind, var))
#define MEM_WRITE(addr, buf, size) (emu->mem->write_block(addr, buf, size))
#endif

/*instruction tokenizing macros*/
#define RSFLD ((inst>>21)&31)
#define RTFLD ((inst>>16)&31)
#define RDFLD ((inst>>11)&31)
#define SHFLD ((inst>>6)&31)
#define IMFLD (inst&65535)
#define ADFLD (inst&67108863)

/*for COP1*/
#define FDFLD SHFLD
#define FSFLD RDFLD
#define FTFLD RTFLD

/*register operation macros*/
#define READ_GPR(ind) (emm->ReadGPR(ind))
#define WRITE_GPR(val, ind) (emm->WriteGPR(val, ind))
#define READ_HI() (emm->ReadHI())
#define READ_LO() (emm->ReadLO())
#define WRITE_HI(val) (emm->WriteHI(val))
#define WRITE_LO(val) (emm->WriteLO(val))
#define WRITE_PC(val) (emm->WritePC(val))
#define READ_PC() (emm->ReadPC())
#define WRITE_RA(val) WRITE_GPR(val,31)

/*COP1 operation macros*/
#define READ_SFP(ind) (emm->ReadSFP(ind))
#define READ_DFP(ind) (emm->ReadDFP(ind))
#define READ_WFP(ind) (emm->ReadFixedW(ind))
#define WRITE_SFP(val, ind) (emm->WriteSFP(val, ind))
#define WRITE_DFP(val, ind) (emm->WriteDFP(val, ind))
#define WRITE_WFP(val, ind) (emm->WriteFixedW(val, ind))
#define READ_FCC(ind) (emm->ReadFCC(ind))
#define CLEAR_FCC(ind) (emm->ClearFCC(ind))
#define SET_FCC(ind) (emm->SetFCC(ind))
#define READ_FCSR() (emm->ReadFCSR())
#define WRITE_FCSR(val) (emm->WriteFCSR(val))
#define READ_RM() (emm->ReadFCSR()&0x3)

/*emulator does not allow for multiprogramming or shared memory
  so this is hard-coded*/
#define ATOMIC_UPDATE 1

/*register values*/
#define RS READ_GPR(RSFLD)
#define RT READ_GPR(RTFLD)
#define SHAMT SHFLD

/*fp register values*/
#define DFS READ_DFP(FSFLD)
#define DFD READ_DFP(FDFLD)
#define DFT READ_DFP(FTFLD)

#define SFS READ_SFP(FSFLD)
#define SFD READ_SFP(FDFLD)
#define SFT READ_SFP(FTFLD)

#define WFS READ_WFP(FSFLD)

/*sets flags to execute in the delay slot of a branch/jump*/
#define SET_DELAY() (emm->set_delay_slot())
#define SET_PC(val) (emm->set_next_pc(val))

#ifdef COUNT_COMPILED
#define LONG_JUMP(_cpc, _targ) \
    {emm->increment_compile_count((_cpc>>2)-_lpc+2);emm->WritePC(_targ);return;}
#define JUMP(_cpc,_tpc,_targ) \
    {emm->increment_compile_count((_cpc>>2)-_lpc+2);_lpc=_tpc>>2;goto _targ;}
#else
#define LONG_JUMP(_cpc,_targ) {emm->WritePC(_targ);return;}
#define JUMP(_cpc,_tpc,_targ) goto _targ;
#endif


#ifdef DYNAMIC
#define MARK_PC(_vpc) emm->mark_pc(_vpc)
#else
#define MARK_PC(_vpc)
#endif

uint64_t ato_uint64(char *input);
void dump_int64(uint64_t value, FILE *stream);
void dump_int64_smart(uint64_t value, FILE *stream);

/*wrapper for syscall function*/
#define DO_SYSCALL(a,b) do_syscall(a,b); \
	if(!a->is_running()) return;

/* stack grows to smaller address, mmap area grows toward bigger address */
/* 0xd0000000 to MMAP_BASE is used by floating point emulation, see nwfpe.h */
#define STACK_BASE 0xc0000000
#define MMAP_BASE  0xd4000000
#define MAX_ENVIRON (16 * 1024)
#define STACK_SIZE (1024 * 1024)

//number of instructions implemented
#define INST_TOTAL 92

#define IMPL_FORMALS emulator_t *emm, mips_inst_t inst
#define IMPL_ARGS    emm, inst

#define EMITC_FORMALS char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool in_shadow
#define EMITC_ARGS buf, emm, curpc, fstart, fend, in_shadow


//instruction counter, count individual types of instructions
#ifdef COUNT_INST
#define INC_COUNTER(a) emm->increment_type_count(a,1);
#else
#define INC_COUNTER(a) 
#endif

#endif
