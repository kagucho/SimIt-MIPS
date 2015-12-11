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

#include "emumem.h"

#ifdef EMUMEM_FAST
#include <unistd.h>
#include <sys/mman.h>
#include <assert.h>
#endif

#include <cstring>
#include <iostream>

using namespace emulator;

#ifdef EMUMEM_SAFE
#include <csignal>

memory::memory()
{
	memset(primary_hash_table, 0, sizeof(primary_hash_table));
	page_count = 0;
	cache_valid = 0;
	cached_addr = 0;
}

memory::~memory()
{
	reset();
}

memory::memory(const memory& mem)
{
	unsigned int i, j;

	memset(primary_hash_table, 0, sizeof(primary_hash_table));
	page_count = 0;

	for(i = 0; i < PRIMARY_MEMORY_TABLE_SIZE; i++)
	{
		const secondary_memory_hash_table_t *secondary_hash_table =
		   mem.primary_hash_table[i];
		
		if(secondary_hash_table)
		{
			secondary_memory_hash_table_t *secondary_hash_table_cpy = 
				new secondary_memory_hash_table_t;
			memset(secondary_hash_table_cpy, 0,
				sizeof(secondary_memory_hash_table_t));
			primary_hash_table[i] = secondary_hash_table_cpy;

			for(j = 0; j < SECONDARY_MEMORY_TABLE_SIZE; j++)
			{
				const memory_page_table_entry_t *pte = 
					secondary_hash_table->pte[j];

				if (pte) {
					memory_page_table_entry_t *pte_cpy =
						new memory_page_table_entry_t;
					pte_cpy->addr = pte->addr;
					pte_cpy->storage = new byte_t[MEMORY_PAGE_SIZE];
					pte_cpy->access = pte->access;
					pte_cpy->ext = pte->ext;
					memcpy(pte_cpy->storage, pte->storage, MEMORY_PAGE_SIZE);
					secondary_hash_table_cpy->pte[j] = pte_cpy;
					page_count++;
				}

			}
		}
	}
	cache_valid = 0;
	cached_addr = 0;
}

void memory::reset()
{
	unsigned int i, j;
	
	for(i = 0; i < PRIMARY_MEMORY_TABLE_SIZE; i++)
	{
		secondary_memory_hash_table_t *secondary_hash_table =
		   primary_hash_table[i];
		
		if(secondary_hash_table)
		{
			for(j = 0; j < SECONDARY_MEMORY_TABLE_SIZE; j++)
			{
				memory_page_table_entry_t *pte = secondary_hash_table->pte[j];

				if (pte) {
					delete [] pte->storage;
					delete pte;
				}
			}
			delete secondary_hash_table;
		}
	}
	memset(primary_hash_table, 0, sizeof(primary_hash_table));
	page_count = 0;

	cache_valid = 0;
	cached_addr = 0;
}


memory_page_table_entry_t *memory::allocate_page(target_addr_t index)
{
	uint32_t h1, h2;
	memory_page_table_entry_t *pte;
	secondary_memory_hash_table_t *secondary_hash_table;
		
	h1 = hash1(index);
	secondary_hash_table = primary_hash_table[h1];
		
	if(!secondary_hash_table)
	{
		secondary_hash_table = new secondary_memory_hash_table_t;
		memset(secondary_hash_table, 0,
			sizeof(secondary_memory_hash_table_t));
		primary_hash_table[h1] = secondary_hash_table;
	}
		
	h2 = hash2(index);
	pte = new memory_page_table_entry_t;
	pte->addr = index;
	pte->storage = new byte_t[MEMORY_PAGE_SIZE];
	memset(pte->storage, 0, MEMORY_PAGE_SIZE);
	secondary_hash_table->pte[h2] = pte;
	page_count++;
	/* default pages are readable and writable but not executable */
	pte->access = MEMORY_PAGE_READABLE | MEMORY_PAGE_WRITABLE;
	pte->ext = NULL;
	return pte;
}

/* memory protection error */
void memory::error(target_addr_t addr, unsigned access, unsigned action) {
	fault_addr = addr;
	fault_access = access;
	fault_action = action;
	raise(SIGUSR1);
}

#endif

#ifdef EMUMEM_FAST
void memory::init()
{
	for(unsigned frame_index = 0; frame_index < MMAP_FRAME_NUM; frame_index++)
	{
		mmap_frame[frame_index] = 0;
	}
	page_count = 0;
}

memory::memory()
{
	init();
}

memory::memory(const memory& mem)
{
	init();

	for(unsigned frame_index = 0; frame_index < MMAP_FRAME_NUM; frame_index++)
	{
		if (mem.mmap_frame[frame_index]) {
			allocate_frame(frame_index);
			const target_addr_t offset = frame_index << MMAP_FRAME_SHIFT;
			memcpy(mmap_frame[frame_index]+offset,
				mem.mmap_frame[frame_index]+offset, MMAP_FRAME_SIZE);
		}
	}
}

memory::~memory()
{
	reset();
}

void memory::reset()
{
	for(unsigned frame_index = 0; frame_index < MMAP_FRAME_NUM; frame_index++)
	{
		byte_t * frame_start = mmap_frame[frame_index];
		if (frame_start != 0)
		{
			const target_addr_t offset = frame_index << MMAP_FRAME_SHIFT;
			munmap(frame_start + offset, MMAP_FRAME_SIZE);
			mmap_frame[frame_index] = 0;
		}
	}

	page_count = 0;
}

byte_t * memory::allocate_frame(target_addr_t index)
{
	byte_t * frame_start = reinterpret_cast<byte_t *>
		(mmap(0, MMAP_FRAME_SIZE, PROT_READ|PROT_WRITE,
			  MAP_PRIVATE|MAP_ANONYMOUS, -1, 0));
	assert(frame_start != MAP_FAILED);

	page_count++;

	const target_addr_t frame_begin_offset = index << MMAP_FRAME_SHIFT;
	return mmap_frame[index] = frame_start - frame_begin_offset;
}
#endif

dword_t memory::read_dword(target_addr_t addr)
{
	dword_t value;
	byte_t *ptr;
        
#ifdef EMUMEM_SAFE
	/* if crossing page boundary */
	if ((addr%MEM_PAGE_BOUNDARY) > MEM_PAGE_BOUNDARY-sizeof(dword_t)) {
		read_block(&value, addr, sizeof(dword_t));
	}
	else {
		ptr = translate(addr, MEMORY_PAGE_READABLE);
		value = ptr?*reinterpret_cast<dword_t*>(ptr):intf->read_dword(addr);
	}
#else
	ptr = translate(addr, MEMORY_PAGE_READABLE);
	value = *reinterpret_cast<dword_t*>(ptr);
#endif
 
ret_pt:
#if WORDS_BIGENDIAN==TARGET_LITTLE_ENDIAN                     
	return swap_dword(value);                          
#else                                                         
	return value;                                     
#endif                    
}

void memory::write_dword(target_addr_t addr, dword_t value)
{
	dword_t val;
                                                              
#if WORDS_BIGENDIAN==TARGET_LITTLE_ENDIAN                     
	val = swap_dword(value);                           
#else                                                         
	val = value;                                      
#endif                                                        
                                                              
#ifdef EMUMEM_SAFE
	/* if crossing page boundary */
	if ((addr%MEM_PAGE_BOUNDARY) > MEM_PAGE_BOUNDARY-sizeof(dword_t)) {
		write_block(addr, &val, sizeof(dword_t));
		return;
	}
	byte_t *ptr = translate(addr, MEMORY_PAGE_WRITABLE);
	if (ptr) *reinterpret_cast<dword_t*>(ptr) = val;
	else intf->write_dword(addr, val);
#else
	byte_t *ptr = translate(addr, MEMORY_PAGE_WRITABLE);
	*reinterpret_cast<dword_t*>(ptr) = val;
#endif
}


#define MEM_BLOCK_CODE(to,from,frame_size) \
if(size > 0) \
{ \
	const target_addr_t frame_offset = addr % frame_size; \
	byte_t *frame_addr = reinterpret_cast<byte_t *>(translate(addr,MEM_ACC)); \
	target_addr_t sz = frame_size - frame_offset;	 \
	if(size > sz) \
	{ \
		MEM_BLOCK_OP(to, from, sz); \
		size -= sz; \
		addr += sz; \
		buf = reinterpret_cast<byte_t *>(buf) + sz; \
		\
		if(size >= frame_size) \
		{ \
			do \
			{ \
				frame_addr = reinterpret_cast<byte_t *>(translate(addr,MEM_ACC)); \
				MEM_BLOCK_OP(to, from, frame_size); \
				size -= frame_size; \
				addr += frame_size; \
				buf = reinterpret_cast<byte_t *>(buf) + frame_size; \
			} while(size >= frame_size); \
		} \
		\
		if(size > 0) \
		{ \
			frame_addr = reinterpret_cast<byte_t *>(translate(addr,MEM_ACC)); \
			MEM_BLOCK_OP(to, from, size); \
		} \
	} \
	else \
	{ \
		MEM_BLOCK_OP(to, from, size); \
	} \
}

#ifdef EMUMEM_SAFE
#define FRAME_SIZE MEMORY_PAGE_SIZE
#endif

#ifdef EMUMEM_FAST
#define FRAME_SIZE MMAP_FRAME_SIZE
#endif

void memory::read_block(void *buf, target_addr_t addr, unsigned int size)
{
#ifdef EMUMEM_SAFE
#define MEM_BLOCK_OP(tt,ff,ss) \
	if (frame_addr) memcpy(tt,ff,ss); else intf->read_block(tt, addr, ss);
#else
#define MEM_BLOCK_OP memcpy
#endif
#define MEM_ACC MEMORY_PAGE_READABLE
MEM_BLOCK_CODE(buf,frame_addr,FRAME_SIZE)
#undef MEM_BLOCK_OP
#undef MEM_ACC
}

void memory::write_block(target_addr_t addr, void *buf, unsigned int size)
{
#ifdef EMUMEM_SAFE
#define MEM_BLOCK_OP(tt,ff,ss) \
	if (frame_addr) memcpy(tt,ff,ss); else intf->write_block(addr, ff, ss);
#else
#define MEM_BLOCK_OP memcpy
#endif
#define MEM_ACC MEMORY_PAGE_READABLE
MEM_BLOCK_CODE(frame_addr,buf,FRAME_SIZE)
#undef MEM_BLOCK_OP
#undef MEM_ACC
}

void memory::set_block(target_addr_t addr, byte_t value, unsigned int size)
{
	void * buf = 0;
#ifdef EMUMEM_SAFE
#define MEM_BLOCK_OP(tt,ff,ss) \
	if (frame_addr) memset(tt,ff,ss); else intf->write_set(addr, 0, ss);
#else
#define MEM_BLOCK_OP memset
#endif
#define MEM_ACC MEMORY_PAGE_READABLE
MEM_BLOCK_CODE(frame_addr,value,FRAME_SIZE)
#undef MEM_BLOCK_OP
#undef MEM_ACC
}

#undef FRAME_SIZE


#ifdef TEST_MEMORY
bool memory::test()
{
	unsigned int i;
	bool ret = true;

	/* test half_word */
	halfword_t hw;
	for (i=0; i<1024;i+=2)
		write_half_word(i, (halfword_t)i);

	for (i=0; i<1024;i+=2)
		if ((hw=read_half_word(i))!=(halfword_t)i ||
			read_byte(i)!=(byte_t)i ||
			read_byte(i+1)!=(byte_t)(i>>8)) {
			ret = false;
			std::cerr << "halfword test failed at " << i << ", get " << hw
				  << std::endl;
		}

	/* test word */
	word_t w;
	for (i=0; i<1024;i+=4)
		write_word(i, (word_t)i);

	for (i=0; i<1024;i+=4)
		if ((w=read_word(i))!=i ||
			read_byte(i)!=(byte_t)i ||
			read_byte(i+3)!=(byte_t)(i>>24)) {
			ret = false;
			std::cerr << "word test failed at " << i << ", get " << w
				  << std::endl;
		}

	/* test dword */
	dword_t dw;
	for (i=0; i<1024;i+=8)
		write_dword(i, ((dword_t)i<<32)|i);

	for (i=0; i<1024;i+=8)
		if ((dw=read_dword(i))!=(((dword_t)i<<32)|i) ||
			read_byte(i)!=(byte_t)i ||
			read_byte(i+7)!=(byte_t)(i>>24)) {
			ret = false;
			std::cerr << "dword test failed at " << i << ", get " << dw 
				  << std::endl;
		}

	/* alignment test at page boundary*/
	for (i=0; i<8; i++) {
		write_word(MEM_PAGE_BOUNDARY-i, 0xAABBCCDD);
		w = read_word(MEM_PAGE_BOUNDARY-i);
		if (w != 0xAABBCCDD) {
			std::cerr << "word alignment test failed at " << i << ", get " << w
				<< std::endl;
		}
	}


	/* alignment test at page boundary*/
	for (i=0; i<16; i++) {
		write_dword(MEM_PAGE_BOUNDARY-i, 0x66778899AABBCCDDULL);
		dw = read_dword(MEM_PAGE_BOUNDARY-i);
		if (dw != 0x66778899AABBCCDDULL) {
			std::cerr << "dword alignment test failed at " << i << ", get "
				<< dw << std::endl;
		}
	}

	/* alignment test at page boundary*/
	for (i=0; i<4; i++) {
		write_half_word(MEM_PAGE_BOUNDARY-i, 0x6677);
		hw = read_half_word(MEM_PAGE_BOUNDARY-i);
		if (hw != 0x6677) {
			std::cerr << "hword alignment test failed at " << i << ", get "
				<< hw << std::endl;
		}
	}

	/* test block */
	char hello[] = "hello world!\n";
	char bufff[sizeof(hello)];
	

	write_block(MEM_PAGE_BOUNDARY-1, hello, sizeof(hello));
	read_block(bufff, MEM_PAGE_BOUNDARY-1, sizeof(hello));

	for (i=0; i<sizeof(hello);i+=8)
		if (bufff[i]!=hello[i]) {
			ret = false;
			std::cerr << "block test failed at " << i << ", get " << bufff[i]
				  << std::endl;
		}

	/* test copy constructor using word */
	for (i=0; i<1024;i+=4)
		write_word(i, (word_t)i);

	memory mem(*this);
	for (i=0; i<1024;i+=4)
		if ((w=mem.read_word(i))!=i ||
			mem.read_byte(i)!=(byte_t)i ||
			mem.read_byte(i+3)!=(byte_t)(i>>24)) {
			ret = false;
			std::cerr << "copy test failed at " << i << ", get " << w
				  << std::endl;
		}

	if (mem.page_count != page_count) {
		std::cerr << "page count mismatch after copying" << std::endl;
		ret = false;
	}

	return ret;
}

int main()
{
	memory amem;
	if (amem.test())
		std::cerr << "memory test passed!" << std::endl;
	else
		std::cerr << "memory test failed!" << std::endl;
}
#endif

