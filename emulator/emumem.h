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

#ifndef __EMU_MEMORY_H__
#define __EMU_MEMORY_H__

#include <config.h>
#include <misc.hpp>
#include <cstring>

namespace emulator {

/* these are the memory page protection flags */
/* flag value -> meaning
   1   --> normal but empty page, meaning storage not allocated yet
   2   --> remapped memory
   4   --> bad address, bus error, other bits must be clear

   16  --> normal page, readable
   32  --> normal page, writable
   64  --> normal page, executable

   16, 32, 64 can be combined.
   1, 2, 4 cannot be combined, if any of these bits is set,
   then 16, 32, 64 will be stealthily shifted by 12 bits
*/
const unsigned int MEMORY_PAGE_EMPTY      = 1;
const unsigned int MEMORY_PAGE_REMAPPED   = 2;
const unsigned int MEMORY_PAGE_UNAVAIL    = 4;
const unsigned int MEMORY_PAGE_READABLE   = 16;
const unsigned int MEMORY_PAGE_WRITABLE   = 32;
const unsigned int MEMORY_PAGE_EXECUTABLE = 64; // not really useful

/* internal macros, user should not use these */
#define MEMORY_PAGE_PERM_SHIFT 12
#define MEMORY_PAGE_PERM_MASK  \
	(MEMORY_PAGE_READABLE | MEMORY_PAGE_WRITABLE | MEMORY_PAGE_EXECUTABLE)
#define MEMORY_PAGE_SLOW \
	(MEMORY_PAGE_EMPTY | MEMORY_PAGE_REMAPPED | MEMORY_PAGE_UNAVAIL)
#define MEMORY_PAGE_AVAIL_SLOW \
	(MEMORY_PAGE_EMPTY | MEMORY_PAGE_REMAPPED)

/* these are memory paging parameter, default page size = 64KB */
const unsigned int MEMORY_PAGE_SIZE_BITS  = 16;
const unsigned int MEMORY_PAGE_SIZE       = 1 << MEMORY_PAGE_SIZE_BITS;
const unsigned int MEMORY_PAGE_TABLE_BITS = 
	sizeof(target_addr_t) * 8 - MEMORY_PAGE_SIZE_BITS;
const unsigned int MEMORY_PAGE_TABLE_SIZE = 1 << MEMORY_PAGE_TABLE_BITS;



typedef struct memory_page_table_entry_t
{
	unsigned int flag;
	byte_t *ptr;
} memory_page_table_entry_t;


const unsigned int MEMORY_ERROR_READ_PERM   = MEMORY_PAGE_READABLE;
const unsigned int MEMORY_ERROR_WRITE_PERM  = MEMORY_PAGE_WRITABLE;
const unsigned int MEMORY_ERROR_EXEC_PERM   = MEMORY_PAGE_EXECUTABLE;
const unsigned int MEMORY_ERROR_BADADDR     = MEMORY_PAGE_UNAVAIL;
const unsigned int MEMORY_ERROR_MISALIGN    = 128;

typedef struct memory_fault_info_t
{
	target_addr_t addr;
	unsigned int code;
} memory_fault_info_t;

/* an abstract class as page remapping interface */
class memory_ext_interface {

  public:

	virtual byte_t read_byte(target_addr_t addr,
							memory_fault_info_t *f) = 0;
	virtual void write_byte(target_addr_t addr, byte_t value,
							memory_fault_info_t *f) = 0;
	
	virtual halfword_t read_halfword(target_addr_t addr,
							memory_fault_info_t *f) = 0;
	virtual	void write_halfword(target_addr_t addr, halfword_t value,
							memory_fault_info_t *f) = 0;

	virtual word_t read_word(target_addr_t addr,
							memory_fault_info_t *f) = 0;
	virtual void write_word(target_addr_t addr, word_t value,
							memory_fault_info_t *f) = 0;

	virtual	dword_t read_dword(target_addr_t addr,
							memory_fault_info_t *f) = 0;
	virtual	void write_dword(target_addr_t addr, dword_t value,
							memory_fault_info_t *f) = 0;
	
	// returns the number of bytes processed,
	// on error, can be less than argument size
	virtual unsigned int read_block(void *buf, target_addr_t,
							unsigned int size, memory_fault_info_t *f) = 0;
	virtual unsigned int write_block(target_addr_t, void *buf,
							unsigned int size, memory_fault_info_t *f) = 0;
	virtual unsigned int set_block(target_addr_t, byte_t value,
							unsigned int size, memory_fault_info_t *f) = 0;
};

class memory
{
	public:
	/* constructor, 
	   def_perm sets the default permission of all pages. */
	memory(unsigned int def_valid = MEMORY_PAGE_PERM_MASK);

	/* destructor */
	~memory();

	/* copy constructor, not implemented for fast mode*/
	memory(const memory&);

	/* free all memory pages, but preserve remapping and permissions */
	void reset();

	/* check fault information */
	target_addr_t get_fault_addr() const {return fault_info.addr;}
	unsigned int get_fault_code() const {return fault_info.code;}

	// get the permission bits of a page
	unsigned int get_page_permission(target_addr_t addr) const; 
	void set_page_permission(target_addr_t addr, unsigned int perm);
	void set_region_permission(target_addr_t addr,
					unsigned int size, unsigned int perm);


	// remap and unmap a page, page is unavailable after successful unmap
	void remap_page(target_addr_t addr,
					memory_ext_interface *mif, unsigned int perm);
	void unmap_page(target_addr_t addr);

	// remap and unmap a region
	void remap_region(target_addr_t addr, unsigned int size,
					memory_ext_interface *mif, unsigned int perm);
	void unmap_region(target_addr_t addr, unsigned int size);


	// mark a page as available or unavailable
	void mark_page_available(target_addr_t addr, unsigned int perm);
	void mark_page_unavailable(target_addr_t addr);

	// mark a region as available or unavailable
	void mark_region_available(target_addr_t addr,
					unsigned int size, unsigned int perm);
	void mark_region_unavailable(target_addr_t addr, unsigned int size);


	/*******************************************************************
		Below are the main interface functions.
	*******************************************************************/

	byte_t read_byte(target_addr_t addr,
			memory_fault_info_t *f = NULL)
	{
		const memory_page_table_entry_t *pte = get_page(addr);
		/* if empty (not allocated), remapped, bad, or not readable */
		if (!(pte->flag & MEMORY_PAGE_READABLE)) {
			return read_byte_slow(addr, f);
		}
		return *(pte->ptr + addr);
	}

	void write_byte(target_addr_t addr, byte_t value,
			memory_fault_info_t *f = NULL)
	{
		const memory_page_table_entry_t *pte = get_page(addr);
		/* if empty (not allocated), remapped, bad, or not writable */
		if (!(pte->flag & MEMORY_PAGE_WRITABLE))
			write_byte_slow(addr, value, f);
		else
			*(pte->ptr + addr) = value;
	}

	word_t read_word_fast(target_addr_t addr,
			memory_fault_info_t *f = NULL)
	{
		return read_word(addr, f);
	}

	word_t read_word(target_addr_t addr,
			memory_fault_info_t *f = NULL)
	{
		/* if crossing page boundary */
		if (cross_page_boundary(addr, sizeof(word_t)))
		{
			return read_word_slow(addr, f);
		}
		else 
		{
			const memory_page_table_entry_t *pte = get_page(addr);
			/* if empty (not allocated), remapped, bad, or not readable */
			if (!(pte->flag & MEMORY_PAGE_READABLE))
				return read_word_slow(addr, f);
			else
#if WORDS_BIGENDIAN==TARGET_LITTLE_ENDIAN
				return swap_word(*reinterpret_cast<word_t *>
									(pte->ptr + addr));
#else
				return *reinterpret_cast<word_t*>(pte->ptr + addr);
#endif
		}
	}

	void write_word(target_addr_t addr, word_t value,
			memory_fault_info_t *f = NULL)
	{
		/* if crossing page boundary */
		if (cross_page_boundary(addr, sizeof(word_t)))
		{
			write_word_slow(addr, value, f);
			return;
		}

		const memory_page_table_entry_t *pte = get_page(addr);
		/* if empty (not allocated), remapped, bad, or not writable */
		if (!(pte->flag & MEMORY_PAGE_WRITABLE))
			write_word_slow(addr, value, f);
		else
#if WORDS_BIGENDIAN==TARGET_LITTLE_ENDIAN
			*reinterpret_cast<word_t*>(pte->ptr + addr) = swap_word(value);
#else
			*reinterpret_cast<word_t*>(pte->ptr + addr) = value;
#endif
	}

	halfword_t read_halfword(target_addr_t addr,
			memory_fault_info_t *f = NULL)
	{
		/* if crossing page boundary */
		if (cross_page_boundary(addr, sizeof(halfword_t)))
		{
			return read_halfword_slow(addr, f);
		}
		else {
			const memory_page_table_entry_t *pte = get_page(addr);
			/* if empty (not allocated), remapped, bad, or not readable */
			if (!(pte->flag & MEMORY_PAGE_READABLE))
				return read_halfword_slow(addr, f);
			else
#if WORDS_BIGENDIAN==TARGET_LITTLE_ENDIAN
				return swap_halfword(*reinterpret_cast<halfword_t*>
										(pte->ptr + addr));
#else
				return *reinterpret_cast<halfword_t *>(pte->ptr + addr);
#endif
		}
	}

	void write_halfword(target_addr_t addr, halfword_t value,
			memory_fault_info_t *f = NULL)
	{
		/* if crossing page boundary */
		if (cross_page_boundary(addr, sizeof(halfword_t)))
		{
			write_halfword_slow(addr, value, f);
			return;
		}

		const memory_page_table_entry_t *pte = get_page(addr);
		/* if empty (not allocated), remapped, bad, or not writable */
		if (!(pte->flag & MEMORY_PAGE_WRITABLE))
			write_halfword_slow(addr, value, f);
		else
#if WORDS_BIGENDIAN==TARGET_LITTLE_ENDIAN
			*reinterpret_cast<halfword_t*>(pte->ptr + addr) =
					swap_halfword(value);
#else
			*reinterpret_cast<halfword_t*>(pte->ptr + addr) = value;
#endif
	}

	/* dword operations */
	dword_t read_dword(target_addr_t addr,
			memory_fault_info_t *f = NULL)
	{
		/* if crossing page boundary */
		if (cross_page_boundary(addr, sizeof(dword_t)))
		{
			return read_dword_slow(addr, f);
		}
		else 
		{
			const memory_page_table_entry_t *pte = get_page(addr);
			/* if empty (not allocated), remapped, bad, or not readable */
			if (!(pte->flag & MEMORY_PAGE_READABLE))
				return read_dword_slow(addr, f);
			else
#if WORDS_BIGENDIAN==TARGET_LITTLE_ENDIAN
				return swap_dword(*reinterpret_cast<dword_t*>
										(pte->ptr + addr));
#else
				return *reinterpret_cast<dword_t*>(pte->ptr + addr);
#endif
		}

	}

	void write_dword(target_addr_t addr, dword_t value,
			memory_fault_info_t *f = NULL)
	{
		/* if crossing page boundary */
		if (cross_page_boundary(addr, sizeof(dword_t)))
		{
			write_dword_slow(addr, value, f);
			return;
		}

		const memory_page_table_entry_t *pte = get_page(addr);
		/* if empty (not allocated), remapped, bad, or not writable */
		if (!(pte->flag & MEMORY_PAGE_WRITABLE))
			write_dword_slow(addr, value, f);
		else
#if WORDS_BIGENDIAN==TARGET_LITTLE_ENDIAN
			*reinterpret_cast<dword_t*>(pte->ptr + addr) =
							swap_dword(value);
#else
			*reinterpret_cast<dword_t*>(pte->ptr + addr) = value;
#endif
	}


	/* block operations */
	unsigned int read_block(void *buf, target_addr_t addr,
			unsigned int size, memory_fault_info_t *f = NULL);
	unsigned int write_block(target_addr_t, void *buf,
			unsigned int size, memory_fault_info_t *f = NULL);
	unsigned int set_block(target_addr_t addr, byte_t value,
			unsigned int size, memory_fault_info_t *f = NULL);

	/*******************************************************************
		End of main interface functions.
	*******************************************************************/


	/* test if an address crosses page boundary, size < MEM_PAGE_SIZE */
	bool cross_page_boundary(target_addr_t addr, unsigned int size) const
	{
		return (addr & (MEMORY_PAGE_SIZE - 1)) >
				(MEMORY_PAGE_SIZE - size);
	}

	/* some useful utilities */
	target_addr_t align_to_page_boundary(target_addr_t addr) const
	{
		return addr - (addr & (MEMORY_PAGE_SIZE-1));                  
	}

	/* return the number of pages allocated */
	unsigned int get_page_count() const {
		return page_count;
	}

#ifdef TEST_MEMORY
	/* memory test , true->succeed */
	bool test();
#endif

	private:

	halfword_t swap_halfword(halfword_t val) const
	{
		return (val>>8) | (val<<8);
	}

	word_t swap_word(word_t val) const
	{
		return (val>>24) | ((val>>8)&0xFF00) |
			   ((val&0xFF00)<<8) |  (val<<24) ;
	}

	dword_t swap_dword(dword_t val) const
	{
		return ((dword_t)swap_word((word_t)val)<<32) |
			    (dword_t)swap_word((word_t)(val>>32));
	}

	/* storage allocated for a normal page */
	bool page_allocated(const memory_page_table_entry_t *pte) const 
	{
		return ((pte->flag & MEMORY_PAGE_SLOW)==0);
	}

	/* storage allocated for a normal page */
	bool page_allocated(target_addr_t addr) const 
	{
		target_addr_t page_index = addr >> MEMORY_PAGE_SIZE_BITS;
		return ((page_table[page_index].flag & MEMORY_PAGE_SLOW)==0);
	}

	const memory_page_table_entry_t *get_page(target_addr_t addr) const
	{
		target_addr_t page_index = addr >> MEMORY_PAGE_SIZE_BITS;
		return page_table + page_index;
	}

	memory_page_table_entry_t *get_page(target_addr_t addr)
	{
		target_addr_t page_index = addr >> MEMORY_PAGE_SIZE_BITS;
		return page_table + page_index;
	}

	/* address translation */
	bool translate(byte_t **des, target_addr_t addr, unsigned perm) const
	{
		const memory_page_table_entry_t *pte = get_page(addr);

		/* if empty (not allocated), remapped or bad */
		if ((pte->flag & perm) != perm) {
			return false;
		}
		/* normal page with space already allocated */
		*des = pte->ptr + addr;
		return true;
	}

	/* memory fault */
	void report_fault(target_addr_t addr, unsigned int code,
			memory_fault_info_t *f);

	void write_dword_slow(target_addr_t addr, dword_t value,
			memory_fault_info_t *f);
	void write_word_slow(target_addr_t addr, word_t value,
			memory_fault_info_t *f);
	void write_byte_slow(target_addr_t addr, byte_t value,
			memory_fault_info_t *f);
	void write_halfword_slow(target_addr_t addr, halfword_t value,
			memory_fault_info_t *f);

	dword_t read_dword_slow(target_addr_t addr, memory_fault_info_t *f);
	word_t read_word_slow(target_addr_t addr, memory_fault_info_t *f);
	byte_t read_byte_slow(target_addr_t addr, memory_fault_info_t *f);
	halfword_t read_halfword_slow(target_addr_t addr,
			memory_fault_info_t *f);

	unsigned int read_block_within_page(void *buf,
		target_addr_t addr, unsigned int size, memory_fault_info_t *f);
	unsigned int write_block_within_page(target_addr_t,
		void *buf, unsigned int size, memory_fault_info_t *f);
	unsigned int set_block_within_page(target_addr_t addr,
		byte_t value, unsigned int size, memory_fault_info_t *f);

	void allocate_page(memory_page_table_entry_t *pte);

	// returns true if there is a permission fault, f will be set
	bool check_page_permission(target_addr_t addr,
			unsigned int perm, memory_fault_info_t *f);
			
	memory_page_table_entry_t page_table[MEMORY_PAGE_TABLE_SIZE];

	memory_fault_info_t fault_info;
	unsigned int page_count;	/* stats information */

};

} /* namespace */

#endif
