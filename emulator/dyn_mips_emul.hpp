#ifndef DYN_MIPS_EMUL_H
#define DYN_MIPS_EMUL_H

#include <setjmp.h>
#include <mips_emul.hpp>

//#define MAXFUNS 262144
namespace emulator {

class dyn_mips_emulator: public mips_emulator {

    typedef void (*fpointer_t)(mips_emulator*, mips_addr_t);

  public:

	/* constructor */
	dyn_mips_emulator(uint32_t threshold, uint32_t shiftval,
		bool verbose, bool tocount, bool selfmod);

	/* destructor */
	~dyn_mips_emulator();

	/* to run a program */
	uint64_t run();

	/* initialize cache */
	bool load_or_create_cache(char* prog_name);

	/* check whether write invalidates compiled region */
	void check_write(mips_addr_t addr) {
		blk_info[addr>>shiftval].uncacheable = true;
		if (blk_info[addr>>shiftval].dll_fptr) invalidate_dll(addr);
	}

	void check_write_blk(mips_addr_t addr, unsigned size);

	/* mark pc for compiled code */
	void mark_pc(mips_addr_t pc) {marked_pc = pc;}

  private:

	const uint32_t threshold;
	const uint32_t shiftval;
	const bool tocount;
	const bool selfmod;

	bool in_compiled;			// in compiled code

	char *cache_dir;	

	unsigned dll_ind;			// dll file name index, always grow
	unsigned dll_num;			// number of dlls

	struct dll_info_t {
		mips_addr_t index;		// index of the blk
		unsigned findex;		// filename
		void *handle;			// dll handle
		struct dll_info_t *prev;// linked list	
		struct dll_info_t *next;// linked list	
	} dll_head, dll_tail;

	struct blk_info_t {
		u_word_t count;			// counter for the block;
		fpointer_t dll_fptr;	// pointer to the function, NULL if not cached
		bool uncacheable;		// cannot cache? true if self-modified code
		struct dll_info_t *dll_info;	// pointer to the dll block
	} *blk_info;

	mips_addr_t marked_pc;
	jmp_buf jbuf;

	bool create_new_lib(mips_addr_t);
	void decomp_at(unsigned, unsigned);
	bool build_new_lib(unsigned);
	bool link_lib(unsigned, unsigned);
	bool unlink_lib(unsigned);
	void close_dll(struct dll_info_t *);
	struct dll_info_t *open_dll(unsigned, unsigned);
	void dump_addr_data(unsigned, unsigned);

	void invalidate_dll(mips_addr_t);

	bool create_cache_dir(char* home, char* progname);

	/* read addr.dat file */
    void read_addr_data(const char*);

	bool dump_prog_stats(char *progname, char *statpath);

};


}


#endif
