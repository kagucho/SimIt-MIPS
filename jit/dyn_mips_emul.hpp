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
#ifndef DYN_MIPS_EMUL_H
#define DYN_MIPS_EMUL_H

#include <setjmp.h>
#include <pthread.h>
#include <mips_emul.hpp>

/* forward declaration so that do not need to include list */
namespace emulator {

/* unsigned word list */
class uw_list;
/* void pointer list */
class vp_list;

class dyn_mips_emulator: public mips_emulator {

	typedef void (*fpointer_t)(mips_emulator*, mips_addr_t);

	struct dll_info_t {
		mips_addr_t index;		// index of the blk
		unsigned findex;		// filename
		void *handle;			// dll handle
	};

  public:

	/* constructor */
	dyn_mips_emulator(uint32_t threshold, uint32_t shiftval,
		bool verbose, bool showmsg, bool tocount, bool selfmod);

	/* destructor */
	~dyn_mips_emulator();

	/* to run a program */
	uint64_t run_solo();
	uint64_t run_parallel();

	/* initialize cache */
	bool load_or_create_cache(char* prog_name);


	/* methods related to self-modifying checking */
	/* check whether write invalidates compiled region */
	void check_write(mips_addr_t addr) {
		blk_info[addr>>shiftval].flag |= 0x2;
		if (blk_info[addr>>shiftval].dll_fptr) invalidate_dll(addr);
	}

	/* check whether write_block invalidates compiled region */
	void check_write_blk(mips_addr_t addr, unsigned size);

	/* invalidate a DLL due to self-modification */
	void invalidate_dll(mips_addr_t);

	/* mark pc for compiled code */
	void mark_pc(mips_addr_t pc) {marked_pc = pc;}


	/* methods related to DLL management */
	bool ld_lib(unsigned);
	bool load_lib(unsigned, unsigned);
	void dump_cache_dir(unsigned, unsigned);

	/* methods related to building blocks */
	void get_block_to_compile(unsigned *dll_index, unsigned *blk_index);

	unsigned get_num_reqs() const {return req_num;}

  private:

	bool create_new_lib(mips_addr_t);
	void decomp_at(unsigned, unsigned);
	bool build_new_lib(unsigned);
	bool unload_lib(unsigned);
	void close_dll(struct dll_info_t *);
	struct dll_info_t *open_dll(unsigned, unsigned);

	bool create_cache_dir(char* home, char* progname);
	bool dump_prog_stats(char *progname, char *statpath);

	/* read addr.dat file */
    void read_cache(const char*);

  public:

	bool is_tocount() const {return tocount;}
	bool is_selfmod() const {return selfmod;}
	uint32_t get_shiftval() const {return shiftval;}
	const char *get_cache_dir() const {return cache_dir;}

  private:

	const uint32_t threshold;
	const uint32_t shiftval;
	const bool showmsg;
	const bool tocount;
	const bool selfmod;

	bool in_compiled;			// in compiled code

	unsigned req_num;			// total number of requests
	unsigned dll_ind;			// dll file name index, always grow
	unsigned dll_num;			// number of dlls

	char *cache_dir;	

	vp_list *dll_list;			// list of dll info;
	uw_list *tid_list;			// list of thread indexes
	
	mips_addr_t marked_pc;		// pc of last memory write
	jmp_buf jbuf;				// setjmp buffer


	struct blk_info_t {
		unsigned count;			// counter for the block;
		unsigned flag;			// bit 1, cannot cache; bit 0, in compilation
		fpointer_t dll_fptr;	// pointer to the function, NULL if not cached
		struct dll_info_t *dll_info;	// pointer to the dll block
	} *blk_info;


	void execute(mips_inst_t inst);
	void run_solo_internal();
	void run_parallel_internal();

	pthread_mutex_t my_mut;
	pthread_cond_t  my_cond;

};
    
}


#endif
