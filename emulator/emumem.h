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

#if !defined(HAVE_MMAP) || !defined(HAVE_SYS_MMAN_H)
#define EMUMEM_SAFE
#undef  EMUMEM_FAST
#endif

// exclusive option
#ifdef EMUMEM_FAST
#undef EMUMEM_SAFE
#endif



namespace emulator {

/* these are the memory page protection flags */
const unsigned int MEMORY_PAGE_READABLE=1;
const unsigned int MEMORY_PAGE_WRITABLE=2;
const unsigned int MEMORY_PAGE_EXECUTABLE=4;
const unsigned int MEMORY_PAGE_IOMAPPED=8;
const unsigned int MEMORY_PAGE_CACHEABLE=16;

#ifdef EMUMEM_SAFE
const unsigned int MEMORY_PAGE_SIZE_BITS = 12;
const unsigned int MEMORY_PAGE_SIZE = 1 << MEMORY_PAGE_SIZE_BITS;

const unsigned int PRIMARY_MEMORY_TABLE_BITS = 12;
const unsigned int PRIMARY_MEMORY_TABLE_SIZE = 1 << PRIMARY_MEMORY_TABLE_BITS;
const unsigned int SECONDARY_MEMORY_TABLE_BITS = 
	sizeof(target_addr_t)*8- PRIMARY_MEMORY_TABLE_BITS - MEMORY_PAGE_SIZE_BITS;
const unsigned int SECONDARY_MEMORY_TABLE_SIZE =
	1 << SECONDARY_MEMORY_TABLE_BITS;

#define MEM_PAGE_BOUNDARY MEMORY_PAGE_SIZE

class memory_ext_interface {

  public:

	virtual byte_t read_byte(target_addr_t addr) = 0;
	virtual void write_byte(target_addr_t addr, byte_t value) = 0;
	
	virtual halfword_t read_half_word(target_addr_t addr) = 0;
	virtual	void write_half_word(target_addr_t addr, halfword_t value) = 0;

	virtual word_t read_word(target_addr_t addr) = 0;
	virtual void write_word(target_addr_t addr, word_t value) = 0;

	virtual	dword_t read_dword(target_addr_t addr) = 0;
	virtual	void write_dword(target_addr_t addr, dword_t value) = 0;

	virtual void read_block(void *buf, target_addr_t, unsigned int size) = 0;
	virtual void write_block(target_addr_t, void *buf, unsigned int size) = 0;
	virtual void write_set(target_addr_t, byte_t value, unsigned int size) = 0;

};

typedef struct memory_page_table_entry_t
{
	target_addr_t addr;
	byte_t *storage;
	unsigned access;
	memory_ext_interface *ext;

} memory_page_table_entry_t;

typedef struct
{
	memory_page_table_entry_t *pte[SECONDARY_MEMORY_TABLE_SIZE];
} secondary_memory_hash_table_t;

#else //#ifdef EMUMEM_FAST
const unsigned int MMAP_FRAME_BITS = 10;
const unsigned int MMAP_FRAME_NUM = 1 << MMAP_FRAME_BITS;
const unsigned int MMAP_FRAME_SHIFT = sizeof(target_addr_t)*8 - MMAP_FRAME_BITS;
const unsigned int MMAP_FRAME_SIZE = 1 << MMAP_FRAME_SHIFT;
const unsigned int MMAP_OFFSET_MASK = MMAP_FRAME_SIZE - 1;
#define MEM_PAGE_BOUNDARY MMAP_FRAME_SIZE
#endif


class memory
{
	public:
		/* constructor */
		memory();

		/* destructor */
		~memory();

		/* copy constructor, not implemented for fast mode*/
		memory(const memory&);

		/* free all memory pages */
		void reset();

#ifdef EMUMEM_SAFE
		target_addr_t get_fault_addr() const {return fault_addr;}
		unsigned get_fault_action() const {return fault_action;}
		unsigned get_fault_access() const {return fault_access;}

		/* address translation */
		byte_t * translate(target_addr_t addr, unsigned ac)
		{
			target_addr_t offset = addr % MEMORY_PAGE_SIZE;
			memory_page_table_entry_t *pte = get_page(addr);

			if (pte->access & MEMORY_PAGE_IOMAPPED) {
				intf = pte->ext;
				return NULL;
			}
			if ((ac & pte->access)!=ac) {
				error(addr, pte->access, ac);
			}
			return pte->storage + offset;
		}

		/* fast address translation using cached page pointer
		 * this assumes that the access mode is read|execute (inst. fetch)
		 */
		byte_t * translate_fast(target_addr_t addr)
		{
 			memory_page_table_entry_t *pte; 
			target_addr_t index = addr >> MEMORY_PAGE_SIZE_BITS; 
			target_addr_t offset = addr % MEMORY_PAGE_SIZE; 

		    if (cache_valid & (cached_addr==index))
				pte = cached_pte; 
		    else {

				cached_pte = pte = get_page(addr);
				cached_addr = index;

				if (pte->access & MEMORY_PAGE_IOMAPPED) {
					intf = pte->ext;
					cache_valid = 0; // do not cache io mapped
					return NULL;
				}

				cache_valid = (unsigned)-1;
				unsigned def_ac = MEMORY_PAGE_READABLE|MEMORY_PAGE_EXECUTABLE;
				if ((pte->access & def_ac) != def_ac) {
					error(addr, pte->access, def_ac);
					cache_valid = 0; // do not cache bad access
				}
			}

			return pte->storage + offset;
		}

		/* set the permission bits of a page */
		unsigned get_page_permission(target_addr_t addr)
		{
			return get_page(addr)->access;
		}

		/* set the permission bits of a page, does not affect mapped bit */
		void set_page_permission(target_addr_t addr, unsigned ac)
		{
			unsigned old_access = get_page_permission(addr);
			get_page(addr)->access = ac | (old_access & MEMORY_PAGE_IOMAPPED);
			cache_valid = 0; // reset cache in case affected
		}

		void set_permission(target_addr_t addr, unsigned size, unsigned ac)
		{
			target_addr_t aligned_addr = align_to_page_boundary(addr);
			for (;aligned_addr<addr+size; aligned_addr+=MEMORY_PAGE_SIZE) {
				set_page_permission(aligned_addr, ac);
			}
		}

		void map_page(target_addr_t addr, memory_ext_interface *if0)
		{
 			memory_page_table_entry_t *pte = get_page(addr);
			pte->ext = if0;
			pte->access |= MEMORY_PAGE_IOMAPPED;
		}

		void unmap_page(target_addr_t addr)
		{
 			memory_page_table_entry_t *pte = get_page(addr);
			pte->ext = NULL;
			pte->access &= ~MEMORY_PAGE_IOMAPPED;
		}

#endif // EMUMEM_SAFE

#ifdef EMUMEM_FAST
		/* address translation */
		byte_t *translate(target_addr_t addr, unsigned useless)
		{
			const target_addr_t frame_index = addr >> MMAP_FRAME_SHIFT;
			byte_t * const frame_start = mmap_frame[frame_index];

			if (!frame_start) {
				byte_t * const frame_start = allocate_frame(frame_index);
				return frame_start + addr;
			}

			return frame_start + addr;
		}

		/* fast address translation */
		byte_t *translate_fast(target_addr_t addr)
		{
			return translate(addr, 0);
		}
#endif

		byte_t read_byte(target_addr_t addr)
		{
			byte_t *ptr = translate(addr, MEMORY_PAGE_READABLE);

#ifdef EMUMEM_SAFE
			return ptr?*ptr:intf->read_byte(addr);
#else 
			return *ptr;
#endif
		}

		void write_byte(target_addr_t addr, byte_t value)
		{
			byte_t *ptr = translate(addr, MEMORY_PAGE_WRITABLE);
#ifdef EMUMEM_SAFE
			if (ptr) *ptr = value; else intf->write_byte(addr, value);
#else
			*ptr = value;
#endif
		}

		word_t read_word(target_addr_t addr)
		{

			word_t value;
			byte_t *ptr;

#ifdef EMUMEM_SAFE
			/* if crossing page boundary */
			if ((addr%MEM_PAGE_BOUNDARY) > MEM_PAGE_BOUNDARY-sizeof(word_t)) {
				read_block(&value, addr, sizeof(word_t));
			}
			else
			{
				ptr = translate(addr, MEMORY_PAGE_READABLE);
				value = ptr?*reinterpret_cast<word_t*>(ptr):
							intf->read_word(addr);
			}
#else 
			ptr = translate(addr, MEMORY_PAGE_READABLE);
			value = *reinterpret_cast<word_t*>(ptr);
#endif

#if WORDS_BIGENDIAN==TARGET_LITTLE_ENDIAN
			return swap_word(value);
#else
			return value;
#endif
		}

		void write_word(target_addr_t addr, word_t value)
		{
			word_t val;

#if WORDS_BIGENDIAN==TARGET_LITTLE_ENDIAN
			val = swap_word(value);
#else
			val = value;
#endif

#ifdef EMUMEM_SAFE
			/* if crossing page boundary */
			if ((addr%MEM_PAGE_BOUNDARY) > MEM_PAGE_BOUNDARY-sizeof(word_t)) {
				write_block(addr, &val, sizeof(word_t));
				return;
			}

			byte_t *ptr = translate(addr, MEMORY_PAGE_WRITABLE);
			if (ptr) *reinterpret_cast<word_t*>(ptr) = val;
			else intf->write_word(addr, val);
#else
			byte_t *ptr = translate(addr, MEMORY_PAGE_WRITABLE);
			*reinterpret_cast<word_t*>(ptr) = val; 
#endif
		}

		halfword_t read_half_word(target_addr_t addr)
		{
			halfword_t value;
			byte_t *ptr;

#ifdef EMUMEM_SAFE
			/* if crossing page boundary */
			if ((addr%MEM_PAGE_BOUNDARY) > MEM_PAGE_BOUNDARY-sizeof(halfword_t)) {
				read_block(&value, addr, sizeof(halfword_t));
			}
			else
			{

				ptr = translate(addr, MEMORY_PAGE_READABLE);
				value = ptr?*reinterpret_cast<halfword_t*>(ptr):
							intf->read_half_word(addr);
			}
#else 
			ptr = translate(addr, MEMORY_PAGE_READABLE);
			value = *reinterpret_cast<word_t*>(ptr);
#endif

#if WORDS_BIGENDIAN==TARGET_LITTLE_ENDIAN
			return swap_half_word(value);
#else
			return value;
#endif
		}

		void write_half_word(target_addr_t addr, halfword_t value)
		{
			halfword_t val;

#if WORDS_BIGENDIAN==TARGET_LITTLE_ENDIAN
			val = swap_half_word(value);
#else
			val = value;
#endif
 
#ifdef EMUMEM_SAFE
			/* if crossing page boundary */
			if ((addr%MEM_PAGE_BOUNDARY) > MEM_PAGE_BOUNDARY-sizeof(halfword_t)) {
				write_block(addr, &val, sizeof(halfword_t));
				return;
			}

			byte_t *ptr = translate(addr, MEMORY_PAGE_WRITABLE);
			if (ptr) *reinterpret_cast<halfword_t*>(ptr) = val;
			else intf->write_half_word(addr, val);
#else
			byte_t *ptr = translate(addr, MEMORY_PAGE_WRITABLE);
			*reinterpret_cast<halfword_t*>(ptr) = val; 
#endif
		}

		/* dword operations */
		dword_t read_dword(target_addr_t addr);
		void write_dword(target_addr_t addr, dword_t value);

		/* block operations */
		void read_block(void *buf, target_addr_t addr, unsigned int size);
		void write_block(target_addr_t, void *buf, unsigned int size);
		void set_block(target_addr_t addr, byte_t value, unsigned int size);

#ifdef EMUMEM_SAFE
		/* some useful utilities */
		target_addr_t align_to_page_boundary(target_addr_t addr)
		{
			return addr - (addr % MEM_PAGE_BOUNDARY);                  
		}
#endif

#ifdef TEST_MEMORY
		/* memory test , true->succeed */
		bool test();
#endif

		/* for instruction fetching only
		 * this assumes that the access mode is read|execute (inst. fetch) */
		word_t read_word_fast(target_addr_t addr) {

#ifdef EMUMEM_SAFE
			if ((addr%MEM_PAGE_BOUNDARY) > MEM_PAGE_BOUNDARY-sizeof(word_t))
				return read_word(addr);
#endif

#if WORDS_BIGENDIAN==TARGET_LITTLE_ENDIAN
		    return swap_word(*reinterpret_cast<word_t *>(translate_fast(addr)));
#else
		    return *reinterpret_cast<word_t *>(translate_fast(addr));
#endif
		}                               

		/* return the number of pages allocated */
		unsigned int get_page_count() {
			return page_count;
		}

	private:

		static u_hword_t swap_half_word(u_hword_t val) {
			return (val>>8) | (val<<8);
		}

		static u_word_t swap_word(u_word_t val) {
			return (val>>24) | ((val>>8)&0xFF00) |
				   ((val&0xFF00)<<8) |  (val<<24) ;
		}

		static u_dword_t swap_dword(u_dword_t val) {
			return ((dword_t)swap_word((word_t)val)<<32) |
				    (dword_t)swap_word((word_t)(val>>32));
		}

#ifdef EMUMEM_SAFE
		/* memory protection error */
		void error(target_addr_t addr, unsigned access, unsigned action);

		static uint32_t hash1(target_addr_t index)
		{
			return index / SECONDARY_MEMORY_TABLE_SIZE;
		}

		static uint32_t hash2(target_addr_t index)
		{
			return index % SECONDARY_MEMORY_TABLE_SIZE;
		}

		memory_page_table_entry_t *allocate_page(target_addr_t index);

		memory_page_table_entry_t *search_page(target_addr_t index)
		{
			uint32_t h1;
			uint32_t h2;
			secondary_memory_hash_table_t *secondary_hash_table;

			h1 = hash1(index);
			secondary_hash_table = primary_hash_table[h1];

			if(secondary_hash_table)
			{
				h2 = hash2(index);
				return secondary_hash_table->pte[h2];
			}
			return 0;
		}

		memory_page_table_entry_t *get_page(target_addr_t addr)
		{
			memory_page_table_entry_t *pte;
	
			addr = addr >> MEMORY_PAGE_SIZE_BITS;
			pte = search_page(addr);
			if(!pte)
				pte = allocate_page(addr);

			return pte;
		}

		secondary_memory_hash_table_t 
			*primary_hash_table[PRIMARY_MEMORY_TABLE_SIZE];

		/* for possibly sequential reads by read_word_fast */
		target_addr_t cached_addr;
		memory_page_table_entry_t *cached_pte;
		unsigned cache_valid;

		memory_ext_interface *intf;	/* triggered memory map interface */
		target_addr_t fault_addr;	/* address that last cause memory fault */
		unsigned fault_access;		/* access control bits */
		unsigned fault_action;		/* the access attempt */
#endif

#ifdef EMUMEM_FAST
		void init();

		byte_t * allocate_frame(target_addr_t index);

		byte_t * mmap_frame[MMAP_FRAME_NUM];
#endif

		unsigned int page_count;	/* stats information */


};

} /* namespace */

#endif
