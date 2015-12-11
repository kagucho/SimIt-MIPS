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

#include <cassert>
#include <cstring>
#include <iostream>
#include <csignal>

using namespace emulator;

memory::memory(unsigned int def_perm)
{
	def_perm &= MEMORY_PAGE_PERM_MASK;

	/* if nonempty permission, then all pages are valid by default */
	if (def_perm) 
	{
		for (unsigned int ii=0; ii<MEMORY_PAGE_TABLE_SIZE; ii++)
			page_table[ii].flag = 
				MEMORY_PAGE_EMPTY | (def_perm << MEMORY_PAGE_PERM_SHIFT);
	}
	/* otherwise all pages are invalid by default */
	else 
	{
		for (unsigned int ii=0; ii<MEMORY_PAGE_TABLE_SIZE; ii++)
			page_table[ii].flag = MEMORY_PAGE_UNAVAIL;
	}

	page_count = 0;
}

memory::~memory()
{
	reset();
}

memory::memory(const memory& mem)
{

	page_count = 0;
	for(unsigned ii = 0; ii < MEMORY_PAGE_TABLE_SIZE; ii++)
	{
		page_table[ii].flag = mem.page_table[ii].flag;
		if (page_allocated(mem.page_table + ii))
		{
			page_table[ii].ptr = new byte_t[MEMORY_PAGE_SIZE];
			memcpy(page_table[ii].ptr,
				mem.page_table[ii].ptr + (ii << MEMORY_PAGE_SIZE_BITS),
				MEMORY_PAGE_SIZE);
			page_table[ii].ptr -= ii << MEMORY_PAGE_SIZE_BITS;
			page_count++;
		}
	}
}

void memory::reset()
{
	for(unsigned int ii = 0; ii < MEMORY_PAGE_TABLE_SIZE; ii++)
	{
		memory_page_table_entry_t *pte = page_table + ii;
		if (page_allocated(pte)) 
		{
			pte->flag |= MEMORY_PAGE_EMPTY;
			delete [] (pte->ptr + 
					((pte - page_table) << MEMORY_PAGE_SIZE_BITS));
		}
	}
	page_count = 0;
}



unsigned int memory::get_page_permission(target_addr_t addr) const
{
	const memory_page_table_entry_t *pte = get_page(addr);
	unsigned int flag = pte->flag;
	if (flag & MEMORY_PAGE_SLOW)
		flag >>= MEMORY_PAGE_PERM_SHIFT;
	return (flag & MEMORY_PAGE_PERM_MASK);
}

void memory::set_page_permission(target_addr_t addr, unsigned int perm)
{
	memory_page_table_entry_t *pte = get_page(addr);

	// do nothing if the page is not available
	if (pte->flag & MEMORY_PAGE_UNAVAIL) return;

	// otherwise set permission
	perm &= MEMORY_PAGE_PERM_MASK;
	if (pte->flag & MEMORY_PAGE_SLOW) 
	{
		perm = perm << MEMORY_PAGE_PERM_SHIFT;        
		pte->flag &= ~(MEMORY_PAGE_PERM_MASK << MEMORY_PAGE_PERM_SHIFT);
		pte->flag |= perm;
	}
	else
	{
		pte->flag &= ~MEMORY_PAGE_PERM_MASK;
		pte->flag |= perm;
	}
}

void memory::set_region_permission(target_addr_t addr,
	unsigned int size, unsigned int perm)
{
	target_addr_t aligned_addr = align_to_page_boundary(addr);      
	for (; aligned_addr < addr + size; aligned_addr += MEMORY_PAGE_SIZE)   
		set_page_permission(aligned_addr, perm);
}



void memory::remap_page(target_addr_t addr, 
	memory_ext_interface *mif, unsigned int perm)
{
	memory_page_table_entry_t *pte = get_page(addr);

	/* free space if the page is allocated some space */
	if (page_allocated(pte))
		delete [] (pte->ptr + ((pte - page_table) << MEMORY_PAGE_SIZE_BITS));

	pte->flag = MEMORY_PAGE_REMAPPED; 
	pte->flag |= (perm & MEMORY_PAGE_PERM_MASK) << MEMORY_PAGE_PERM_SHIFT;
	pte->ptr = reinterpret_cast<byte_t *>(mif);
}

void memory::unmap_page(target_addr_t addr)
{
	memory_page_table_entry_t *pte = get_page(addr);
	if (pte->flag & MEMORY_PAGE_REMAPPED)
		pte->flag = MEMORY_PAGE_UNAVAIL;
}

void memory::remap_region(target_addr_t addr, unsigned int size,
	memory_ext_interface *mif, unsigned int perm)
{
	target_addr_t aligned_addr = align_to_page_boundary(addr);      
	for (; aligned_addr < addr + size; aligned_addr += MEMORY_PAGE_SIZE)   
		remap_page(aligned_addr, mif, perm);
}

void memory::unmap_region(target_addr_t addr, unsigned int size)
{
	target_addr_t aligned_addr = align_to_page_boundary(addr);      
	for (; aligned_addr < addr + size; aligned_addr += MEMORY_PAGE_SIZE)   
		unmap_page(aligned_addr);
}



void memory::mark_page_available(target_addr_t addr, unsigned int perm)
{
	memory_page_table_entry_t *pte = get_page(addr);
	perm &= MEMORY_PAGE_PERM_MASK;

	/* if already available, change the permission only */
	if (page_allocated(pte)) 
		pte->flag = perm;
	else
		pte->flag = MEMORY_PAGE_EMPTY | (perm << MEMORY_PAGE_PERM_SHIFT);
}

void memory::mark_page_unavailable(target_addr_t addr)
{
	memory_page_table_entry_t *pte = get_page(addr);

	/* free space if the page is allocated some space */
	if (page_allocated(pte))
		delete [] (pte->ptr + ((pte - page_table) << MEMORY_PAGE_SIZE_BITS));
	pte->flag = MEMORY_PAGE_UNAVAIL; 
}

void memory::mark_region_available(target_addr_t addr,
	unsigned int size, unsigned int perm)
{
	target_addr_t aligned_addr = align_to_page_boundary(addr);      
	for (; aligned_addr < addr + size; aligned_addr += MEMORY_PAGE_SIZE)   
		mark_page_available(aligned_addr, perm);
}

void memory::mark_region_unavailable(target_addr_t addr, unsigned int size)
{
	target_addr_t aligned_addr = align_to_page_boundary(addr);      
	for (; aligned_addr < addr + size; aligned_addr += MEMORY_PAGE_SIZE)   
		mark_page_unavailable(aligned_addr);
}



void memory::allocate_page(memory_page_table_entry_t *pte)
{
	assert(!page_allocated(pte));

	pte->ptr = new byte_t[MEMORY_PAGE_SIZE];
	memset(pte->ptr, 0, MEMORY_PAGE_SIZE);
	// inherit the permission bits if any
	pte->flag = (pte->flag >> MEMORY_PAGE_PERM_SHIFT) & MEMORY_PAGE_PERM_MASK;

	// subtract the starting address from the ptr so that it is easier
	// to compute the actual address, see translate() for clue
	pte->ptr -= (pte - page_table) << MEMORY_PAGE_SIZE_BITS;
	page_count++;
}



unsigned int memory::read_block_within_page(void *buf, target_addr_t addr,
		unsigned int size, memory_fault_info_t *f)
{
	memory_page_table_entry_t *pte = get_page(addr);
	if (check_page_permission(addr, MEMORY_PAGE_READABLE, f))
		return 0;

	/* check if crossing page boundary */
	if ((addr >> MEMORY_PAGE_SIZE_BITS) !=
		((addr + size - 1) >> MEMORY_PAGE_SIZE_BITS))
	{
		size = MEMORY_PAGE_SIZE - (addr & (MEMORY_PAGE_SIZE - 1));
	}

	// check storage allocation
	if (pte->flag & MEMORY_PAGE_REMAPPED) 
		size = reinterpret_cast<memory_ext_interface *>(pte->ptr)->
				read_block(buf, addr, size, f);
	else
	{
		if (pte->flag & MEMORY_PAGE_EMPTY) 
			allocate_page(pte);
		memcpy(buf, pte->ptr + addr, size);
	}

	return size;
}

unsigned int memory::read_block(void *buf, target_addr_t addr,
		unsigned int size, memory_fault_info_t *f)
{
	unsigned int sz, len = 0;

	/* crossing the page boundary */
	while (len < size)
	{
		if ((sz = read_block_within_page(buf, addr+len, size-len, f))==0)
			break;
		len += sz;
		buf = reinterpret_cast<byte_t *>(buf) + sz;
	}
	return len;
}

unsigned int memory::write_block_within_page(target_addr_t addr, void *buf, 
		unsigned int size, memory_fault_info_t *f)
{
	memory_page_table_entry_t *pte = get_page(addr);
	if (check_page_permission(addr, MEMORY_PAGE_WRITABLE, f))
		return 0;

	/* check if crossing page boundary */
	if ((addr >> MEMORY_PAGE_SIZE_BITS) !=
		((addr + size - 1) >> MEMORY_PAGE_SIZE_BITS))
	{
		size = MEMORY_PAGE_SIZE - (addr & (MEMORY_PAGE_SIZE - 1));
	}

	if (pte->flag & MEMORY_PAGE_REMAPPED) 
		size = reinterpret_cast<memory_ext_interface *>(pte->ptr)->
				write_block(addr, buf, size, f);
	else {
		if (pte->flag & MEMORY_PAGE_EMPTY) 
			allocate_page(pte);
		memcpy(pte->ptr + addr, buf, size);
	}

	return size;
}

unsigned int memory::write_block(target_addr_t addr, void *buf,
		unsigned int size, memory_fault_info_t *f)
{
	unsigned int sz, len = 0;

	/* crossing the page boundary */
	while (len < size)
	{
		if ((sz = write_block_within_page(addr+len, buf, size-len, f))==0)
			break;
		len += sz;
		buf = reinterpret_cast<byte_t *>(buf) + sz;
	}
	return len;
}

unsigned int memory::set_block_within_page(target_addr_t addr, byte_t value, 
		unsigned int size, memory_fault_info_t *f)
{
	memory_page_table_entry_t *pte = get_page(addr);
	if (check_page_permission(addr, MEMORY_PAGE_WRITABLE, f))
		return 0;

	/* check if crossing page boundary */
	if ((addr >> MEMORY_PAGE_SIZE_BITS) !=
		((addr + size - 1) >> MEMORY_PAGE_SIZE_BITS))
	{
		size = MEMORY_PAGE_SIZE - (addr & (MEMORY_PAGE_SIZE - 1));
	}

	if (pte->flag & MEMORY_PAGE_REMAPPED) 
		size = reinterpret_cast<memory_ext_interface *>(pte->ptr)->
				set_block(addr, value, size, f);
	else {
		if (pte->flag & MEMORY_PAGE_EMPTY) 
			allocate_page(pte);
		memset(pte->ptr + addr, value, size);
	}

	return size;
}


unsigned int memory::set_block(target_addr_t addr, byte_t value,
		unsigned int size, memory_fault_info_t *f)
{
	unsigned int sz, len = 0;

	/* crossing the page boundary */
	while (len < size)
	{
		if ((sz = set_block_within_page(addr+len, value, size-len, f))==0)
			break;
		len += sz;
	}
	return len;
}


bool memory::check_page_permission(target_addr_t addr,
		unsigned int perm, memory_fault_info_t *f)
{
	const memory_page_table_entry_t *pte = get_page(addr);
	// check storage allocation
	if (pte->flag & MEMORY_PAGE_UNAVAIL) 
	{
		report_fault(addr, MEMORY_ERROR_BADADDR, f);
		return true;
	}

	unsigned int priv = pte->flag & MEMORY_PAGE_PERM_MASK;
	if (pte->flag & MEMORY_PAGE_AVAIL_SLOW) 
		priv = (pte->flag >> MEMORY_PAGE_PERM_SHIFT) & MEMORY_PAGE_PERM_MASK;

	perm &= ~priv;
	if (perm) {
		report_fault(addr, perm, f);
		return true;
	}
	return false;
}

void memory::report_fault(target_addr_t addr, unsigned fault,
		memory_fault_info_t *f)
{
	if (f==NULL) {
		fault_info.addr = addr;
		fault_info.code = fault;
	}
	else {
		f->addr = addr;
		f->code = fault;
	}
	raise(SIGUSR1);
}


byte_t memory::read_byte_slow(target_addr_t addr,
		memory_fault_info_t *f)
{
	memory_page_table_entry_t *pte = get_page(addr);
	if (check_page_permission(addr, MEMORY_PAGE_READABLE, f))
		return 0;

	// check storage allocation
	if (pte->flag & MEMORY_PAGE_EMPTY) 
	{
		allocate_page(pte);
		return *(pte->ptr + addr);
	}
	else //if (pte->flag & MEMORY_PAGE_REMAPPED) 
	{
		return reinterpret_cast<memory_ext_interface *>(pte->ptr)->
				read_byte(addr, f);
	}
}

void memory::write_byte_slow(target_addr_t addr, byte_t value,
		memory_fault_info_t *f)
{
	memory_page_table_entry_t *pte = get_page(addr);
	if (check_page_permission(addr, MEMORY_PAGE_WRITABLE, f)) return;

	// check storage allocation
	if (pte->flag & MEMORY_PAGE_EMPTY) 
	{
		allocate_page(pte);
		*(pte->ptr + addr) = value;
	}
	else //if (pte->flag & MEMORY_PAGE_REMAPPED) 
	{
		reinterpret_cast<memory_ext_interface *>(pte->ptr)->
			write_byte(addr, value, f);
	}
}

halfword_t memory::read_halfword_slow(target_addr_t addr,
		memory_fault_info_t *f)
{
	halfword_t value;

	// check page boundary
	if (cross_page_boundary(addr, sizeof(halfword_t)))
	{
		read_block(reinterpret_cast<void *>(&value), addr,
			sizeof(halfword_t), f);
	}
	else
	{
		memory_page_table_entry_t *pte = get_page(addr);
		if (check_page_permission(addr, MEMORY_PAGE_READABLE, f))
			return 0;

		// check storage allocation
		if (pte->flag & MEMORY_PAGE_EMPTY) 
		{
			allocate_page(pte);
			value = *reinterpret_cast<halfword_t *>(pte->ptr + addr);
		}
		else //if (pte->flag & MEMORY_PAGE_REMAPPED) 
		{
			return reinterpret_cast<memory_ext_interface *>(pte->ptr)->
					read_halfword(addr, f);
		}
	}
#if WORDS_BIGENDIAN==TARGET_LITTLE_ENDIAN
	return swap_halfword(value);
#else
	return value;
#endif
}

void memory::write_halfword_slow(target_addr_t addr, halfword_t value,
		memory_fault_info_t *f)
{
	word_t val;

#if WORDS_BIGENDIAN==TARGET_LITTLE_ENDIAN
	val = swap_word(value);
#else
	val = value;
#endif

	// check page boundary
	if (cross_page_boundary(addr, sizeof(halfword_t)))
	{
		write_block(addr, &val, sizeof(halfword_t), f);
	}
	else
	{
		memory_page_table_entry_t *pte = get_page(addr);
		if (check_page_permission(addr, MEMORY_PAGE_WRITABLE, f)) return;

		// check storage allocation
		if (pte->flag & MEMORY_PAGE_EMPTY)
		{
			allocate_page(pte);
			*reinterpret_cast<halfword_t *>(pte->ptr + addr) = val;
		}
		else //if (pte->flag & MEMORY_PAGE_REMAPPED) 
		{
			return reinterpret_cast<memory_ext_interface *>(pte->ptr)->
					write_halfword(addr, value, f);
		}
	}
}

word_t memory::read_word_slow(target_addr_t addr,
		memory_fault_info_t *f)
{
	word_t value;

	// check page boundary
	if (cross_page_boundary(addr, sizeof(word_t)))
	{
		read_block(reinterpret_cast<void *>(&value), addr, sizeof(word_t), f);
	}
	else
	{
		memory_page_table_entry_t *pte = get_page(addr);
		if (check_page_permission(addr, MEMORY_PAGE_READABLE, f))
			return 0;

		// check storage allocation
		if (pte->flag & MEMORY_PAGE_EMPTY) 
		{
			allocate_page(pte);
			value = *reinterpret_cast<word_t *>(pte->ptr + addr);
		}
		else //if (pte->flag & MEMORY_PAGE_REMAPPED) 
		{
			return reinterpret_cast<memory_ext_interface *>(pte->ptr)->
					read_word(addr, f);
		}
	}
#if WORDS_BIGENDIAN==TARGET_LITTLE_ENDIAN
	return swap_word(value);
#else
	return value;
#endif
}

void memory::write_word_slow(target_addr_t addr, word_t value,
		memory_fault_info_t *f)
{
	word_t val;

#if WORDS_BIGENDIAN==TARGET_LITTLE_ENDIAN
	val = swap_word(value);
#else
	val = value;
#endif

	// check page boundary
	if (cross_page_boundary(addr, sizeof(word_t)))
	{
		write_block(addr, &val, sizeof(word_t), f);
	}
	else
	{
		memory_page_table_entry_t *pte = get_page(addr);
		if (check_page_permission(addr, MEMORY_PAGE_WRITABLE, f)) return;

		// check storage allocation
		if (pte->flag & MEMORY_PAGE_EMPTY)
		{
			allocate_page(pte);
			*reinterpret_cast<word_t *>(pte->ptr + addr) = val;
		}
		else //if (pte->flag & MEMORY_PAGE_REMAPPED) 
		{
			return reinterpret_cast<memory_ext_interface *>(pte->ptr)->
					write_word(addr, value, f);
		}
	}
}

dword_t memory::read_dword_slow(target_addr_t addr,
		memory_fault_info_t *f)
{
	dword_t value;

	// check page boundary
	if (cross_page_boundary(addr, sizeof(dword_t)))
	{
		read_block(reinterpret_cast<void *>(&value), addr, sizeof(dword_t), f);
	}
	else
	{
		memory_page_table_entry_t *pte = get_page(addr);
		if (check_page_permission(addr, MEMORY_PAGE_READABLE, f))
			return 0;

		// check storage allocation
		if (pte->flag & MEMORY_PAGE_EMPTY)
		{
			allocate_page(pte);
			value = *reinterpret_cast<dword_t *>(pte->ptr + addr);
		}
		else //if (pte->flag & MEMORY_PAGE_REMAPPED) 
		{
			return reinterpret_cast<memory_ext_interface *>(pte->ptr)->
					read_dword(addr, f);
		}
	}
#if WORDS_BIGENDIAN==TARGET_LITTLE_ENDIAN
	return swap_dword(value);
#else
	return value;
#endif
}

void memory::write_dword_slow(target_addr_t addr, dword_t value,
		memory_fault_info_t *f)
{
	dword_t val;
                                                              
#if WORDS_BIGENDIAN==TARGET_LITTLE_ENDIAN                     
	val = swap_dword(value);                           
#else                                                         
	val = value;                                      
#endif                                                        

	// check page boundary
	if (cross_page_boundary(addr, sizeof(dword_t)))
	{
		write_block(addr, &val, sizeof(dword_t), f);
	}
	else
	{
		memory_page_table_entry_t *pte = get_page(addr);
		if (check_page_permission(addr, MEMORY_PAGE_WRITABLE, f))
			return;

		// check storage allocation
		if (pte->flag & MEMORY_PAGE_EMPTY)
		{
			allocate_page(pte);
			*reinterpret_cast<dword_t *>(pte->ptr + addr) = val;
		}
		else //if (pte->flag & MEMORY_PAGE_REMAPPED) 
		{
			return reinterpret_cast<memory_ext_interface *>(pte->ptr)->
					write_dword(addr, value, f);
		}
	}
}


#ifdef TEST_MEMORY
bool memory::test()
{
	unsigned int i;
	bool ret = true;

	/* test half_word */
	halfword_t hw;
	for (i=0; i<1024;i+=2)
		write_halfword(i, (halfword_t)i);

	for (i=0; i<1024;i+=2)
		if ((hw=read_halfword(i))!=(halfword_t)i ||
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
		write_word(MEMORY_PAGE_SIZE-i, 0xAABBCCDD);
		w = read_word(MEMORY_PAGE_SIZE-i);
		if (w != 0xAABBCCDD) {
			std::cerr << "word alignment test failed at " << i << ", get " << w
				<< std::endl;
		}
	}


	/* alignment test at page boundary*/
	for (i=0; i<16; i++) {
		write_dword(MEMORY_PAGE_SIZE-i, 0x66778899AABBCCDDULL);
		dw = read_dword(MEMORY_PAGE_SIZE-i);
		if (dw != 0x66778899AABBCCDDULL) {
			std::cerr << "dword alignment test failed at " << i << ", get "
				<< dw << std::endl;
		}
	}

	/* alignment test at page boundary*/
	for (i=0; i<4; i++) {
		write_halfword(MEMORY_PAGE_SIZE-i, 0x6677);
		hw = read_halfword(MEMORY_PAGE_SIZE-i);
		if (hw != 0x6677) {
			std::cerr << "hword alignment test failed at " << i << ", get "
				<< hw << std::endl;
		}
	}

	/* test block */
	char hello[] = "hello world!\n";
	char bufff[sizeof(hello)];
	

	write_block(MEMORY_PAGE_SIZE-1, hello, sizeof(hello));
	read_block(bufff, MEMORY_PAGE_SIZE-1, sizeof(hello));

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
	printf(".");
	printf("%d", amem.read_word(0));
	if (amem.test())
		std::cerr << "memory test passed!" << std::endl;
	else
		std::cerr << "memory test failed!" << std::endl;
}
#endif

