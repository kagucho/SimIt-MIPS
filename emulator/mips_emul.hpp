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
#ifndef MIPS_EMUL_H
#define MIPS_EMUL_H

#include "emumem.h"

/*static const char * const mnemonic_table[INST_TOTAL] = {
  "add", "addi", "addiu", "addu", "sub", "subu",
  "mult", "multu", "div", "divu", "and", "andi",
  "nor", "or", "ori", "xor", "xori", "sll", "sllv",
  "srl", "srlv", "sra", "srav", "slt", "slti",
  "sltiu", "sltu", "beq", "bgez", "bgezal", "bgtz",
  "blez", "bltzal", "bltz", "bne", "j", "jal",
  "jalr", "jr", "mfhi", "mflo", "mthi", "mtlo",
  "lb", "lbu", "lh", "lhu", "lw", 
*/
namespace emulator {

  union cop1_reg {
	spfloat_t spf[2];
	double dpf;
	word_t fixedw[2];
  };

  struct mips_registers {
	u_word_t gpr[NUM_GPR];			//general purpose registers
	union cop1_reg fpr[NUM_FPR];
	u_word_t iandr;					//fp implementation and revision
	u_word_t fcsr;					//floating point control/status reg
	u_word_t pc;					//program counter
	u_word_t hi;					//mult register for [63:32]
	u_word_t lo;					//mult register for [31:0]
  };

  class mips_emulator {

  public:
	enum status_t {
		ST_RESET,		// just reset, empty
		ST_IDLE,		// program loaded
		ST_RUNNING,
		ST_DEBUGGING,
		ST_ERROR,		// memory protection violation
		ST_EXIT,		// program exit normally
		ST_SIGINT,		// user interrupted
		ST_BREAK,		// brk instruction
		ST_ELSE,		// unknown error
	};

	/* constructor */
	mips_emulator(bool verbose);

	/* destructor */
	~mips_emulator();

	/* load a program */
	void load_program(const char *filename,
			int argc, char *argv[], char *envp[]);

	/* reload the program, for restarting debugger */
	void reload();

	/* reset everything */
	void reset();

	/* if verbose flag set */
	bool is_verbose() const {return verbose;}

	/* running a program */
	uint64_t run();
	uint64_t run_count(uint64_t&);

	/* debugging a program */
	void debug();

	/* gdb remote debugging */
	int gdb(char *socket_name);

	/* program exit */
	void prog_exit(int);
	bool is_done() const {return status==ST_EXIT;}

	/* user interruption */
	void interrupt();
	bool is_interrupted() const {return status==ST_SIGINT;}

	/* brk instruction */
	void break_point();
	bool is_broken() const {return status==ST_BREAK;}

	/* error */
	void seg_fault();
	bool is_fault() const {return status==ST_ERROR;}

	/* check status */
    void set_running() {status = ST_RUNNING;}
	bool is_running() const {return status==ST_RUNNING;}
	bool is_debugging() const {return status==ST_DEBUGGING;}

	/* get exit code of the program */
	int get_retcode() const {return retcode;}

	/* instruction counters */
	void increment_compile_count(uint32_t val) {ccount += val;}
	void increment_interpret_count(uint32_t val) {icount += val;}

	//void increment_type_count(int ind, uint32_t val) {counters[ind] += val;}
	uint64_t get_total_count() const {return icount;}

	void reset_instruction_counters();
	void dump_instruction_counters(FILE *);

	/* control flow maintenance */
	void set_delay_slot() {delay_slot = true;}

	void set_next_pc(mips_addr_t np) {nextPC = np;}

	/* some system-call library variables */
	mips_addr_t get_brk() const {return brk_point;}
	mips_addr_t get_mmap_brk() const {return mmap_brk_point;}

	void set_brk(mips_addr_t new_brk) {brk_point = new_brk;}
	void set_mmap_brk(mips_addr_t new_mmap_brk) {
		mmap_brk_point = new_mmap_brk;
	}

	/* accessing registers */
	void WriteGPR(u_word_t data, mips_address_t reg_addr) {
		if(reg_addr != 0) regs.gpr[reg_addr] = data;
	}

	void WritePC(u_word_t newPC) {
		regs.pc = newPC;
	}
	
	void WriteHI(u_word_t newHI) {
		regs.hi = newHI;
	}
	
	void WriteLO(u_word_t newLO) {
		regs.lo = newLO;
	}

	void WriteDFP(double newDPF, mips_address_t cop1_addr) {
		regs.fpr[cop1_addr/2].dpf = newDPF;
	}

	void WriteSFP(float newSPF, mips_address_t cop1_addr) {
		regs.fpr[cop1_addr/2].spf[cop1_addr%2] = newSPF;
	}

	void WriteFixedW(word_t newFixedW, mips_address_t cop1_addr) {
		regs.fpr[cop1_addr/2].fixedw[cop1_addr%2] = newFixedW;
	}

	void SetFCC(int cc) {
		if(cc == 0)
			regs.fcsr=(regs.fcsr | 0x800000);
		else 
			regs.fcsr=(regs.fcsr | (0x1000000 << cc));
	}

	void ClearFCC(int cc) {
		if(cc == 0)
			regs.fcsr=(regs.fcsr & 0xFF7FFFFF); 
		else
			regs.fcsr=(regs.fcsr & (0xFEFFFFFF << cc));
	}

	void WriteFCSR(u_word_t control_word);
		
	//read from regs
	u_word_t ReadGPR(mips_address_t addr) const {
		return regs.gpr[addr];
	}
	
	u_word_t ReadPC() const {
		return regs.pc;
	}
	
	u_word_t ReadHI() const {
		return regs.hi;
	}
	
	u_word_t ReadLO() const {
		return regs.lo;
	}
		
	double ReadDFP(mips_address_t cop1_addr) const {
		return regs.fpr[cop1_addr/2].dpf;
	}

	spfloat_t ReadSFP(mips_address_t cop1_addr) const {
		return regs.fpr[cop1_addr/2].spf[cop1_addr%2];
	}

	word_t ReadFixedW(mips_address_t cop1_addr) const {
		return regs.fpr[cop1_addr/2].fixedw[cop1_addr%2];
	}

	bool ReadFCC(int cc) const {
		if(cc == 0)
			return regs.fcsr & 0x800000;
		else
			return regs.fcsr & (0x1000000 << cc);
	}

	u_word_t ReadFCSR() const {
		return regs.fcsr;
	}

	/* memory is public */
	memory *mem;

  private:

	/* gdb-debug routines */
	bool registers_from_string(char *buf);
	void registers_to_string(char *buf);

	void gdb_prepare_resume_reply(char *buf, char *, unsigned char *);
	void gdb_trace(int count);
	void gdb_go_to(mips_addr_t addr);

	/* built-in debug routines */
	void debug_disasm(FILE *stream, mips_addr_t addr);
	void debug_dump(FILE *stream, mips_addr_t addr);
	void debug_trace(int count);
	void debug_dump_registers(FILE *stream, int floatmode);
	void debug_go_to(mips_addr_t addr);

  protected:

	/* if an instruction is BREAK */
	bool is_break_inst(mips_inst_t inst) {
		return (inst & 0xFC00003F)==0x0000000D;
	}

	/* execute a single instruction */
	void execute(mips_inst_t inst);

	/* registers & memory */
	mips_registers regs;

	bool delay_slot;
	mips_addr_t nextPC; 

	/* instruction counter */
	uint64_t icount, ccount;
	//uint64_t counters[INST_TOTAL];
	int retcode;		// valid on ST_EXIT
	enum status_t  status;

	target_addr_t brk_point;
	target_addr_t mmap_brk_point;


	bool verbose;
	const char *fname_cache;
	int  argc_cache;
	char **argv_cache;
	char **envp_cache;
  };
}


#endif
