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
/***************************************************************************
                          loader.c  -  description
                             -------------------
    begin                : Wed Sep 26 2001
    copyright            : (C) 2001 CEA and Université Paris XI Orsay
    author               : Gilles Mouchard
    email                : gilles.mouchard@lri.fr, gilles.mouchard@cea.fr
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "read_elf.h"
#include "mips_emul.hpp"

#include <cstdlib>
#include <cstring>
#include <csignal>


using namespace emulator;

void mips_emulator::load_program(const char *filename, 
		int argc, char *argv[], char *envp[])
{
	Elf32_Ehdr *hdr;
	Elf32_Phdr *phdr;
	Elf32_Shdr *shdr;
	char *string_table;
	Elf32_Shdr *shdr_new_section;
	Elf32_Word new_section_size, new_section_type, new_section_flags;
	void *new_section;
	Elf32_Addr new_section_addr;
	int i;	
	FILE *fobj;
	uint32_t data_base = 0, prog_base;
	uint32_t data_size = 0;
	uint32_t envAddr, argAddr;
	uint32_t stack_ptr;
	void (*sig_handler)(int);

	fobj = fopen(filename, "rb");
	if(fobj == NULL) {
		fprintf(stderr, "Can't open executable: %s\n", filename);
		exit(1);
	}

	hdr = ReadElfHeader(fobj);

	if(hdr == NULL) {
		fprintf(stderr, "Could not read ELF32 header from file: %s.\n",
			   	filename);
		exit(1);
	}

	/* check if the file is for MIPS */
	if (hdr->e_type != ET_EXEC ||
		hdr->e_machine != EM_MIPS ||
		hdr->e_ident[EI_DATA] != ELFDATA2LSB) {
		fprintf(stderr, "File is not MIPS LSB executable: %s.\n", filename);
		exit(1);
	}

	phdr = ReadProgramHeaders(hdr, fobj);

	for(i=0; i<hdr->e_phnum; i++) {
		/* WEI QIN: MIPS's segment flag seems different from others:
		   we cannot tell data segment from others. So I just find
		   the segment with the largest address here. The address above
		   the segment will be used for heap. */
		if (phdr[i].p_type == PT_LOAD) /* Loadable Program Segment */ {
			if (phdr[i].p_vaddr>data_base) {
				data_base = phdr[i].p_vaddr;
				data_size = phdr[i].p_memsz;
			}
		}
	}
	prog_base = hdr->e_entry;

	shdr = ReadSectionHeaders(hdr, fobj);
	
	if(shdr == NULL) {
		fprintf(stderr, "Can't read section headers from executable\n");
		exit(1);
	}
	string_table = LoadStringTable(hdr, shdr, fobj);

	// turn off memory protection
	sig_handler = signal(SIGUSR1, SIG_IGN);

	for(i = 0; i < hdr->e_shnum; i++)
	{
		shdr_new_section = &shdr[i];

		new_section_type = GetSectionType(shdr_new_section);
		new_section_flags = GetSectionFlags(shdr_new_section);
		if ((new_section_type == SHT_PROGBITS) ||
			(new_section_type == SHT_NOBITS))
		{
			new_section_size =
				shdr_new_section ? GetSectionSize(shdr_new_section) : 0;
			new_section_addr = GetSectionAddr(shdr_new_section);

			if (new_section_size && (new_section_flags & SHF_ALLOC))
			{
				if (verbose)
				fprintf(stderr, "Loading %s (%u bytes) at address 0x%08x\n",
					GetSymbolName(shdr[i].sh_name, string_table),
					new_section_size, new_section_addr);

				new_section = malloc(new_section_size);
				LoadSection(shdr_new_section, new_section, fobj);

				/* unitialized section => write 0s */
				if (new_section_type == SHT_NOBITS) {
					mem->set_block(new_section_addr, 0, new_section_size);
				}
				else {
					/* initialized section => copy from objfile */
					mem->write_block(new_section_addr, new_section, new_section_size);
				}

				if (new_section_flags&SHF_EXECINSTR) {
#ifdef EMUMEM_SAFE
					mem->set_permission(new_section_addr, new_section_size,
						MEMORY_PAGE_READABLE | MEMORY_PAGE_EXECUTABLE);

					if (verbose)
						fprintf(stderr, "Mark memory address %x len %x "
							"as text segment.\n", new_section_addr,
							new_section_size);
#endif
				}
				free(new_section);
			}
		}
		else if (new_section_type == SHT_DYNAMIC ||
			new_section_type == SHT_DYNSYM) {
			fprintf(stderr, "File is dynamically linked,"
				" compile with `-static'.\n");
			signal(SIGUSR1, sig_handler);
			exit(1);
		}
	}
	free(string_table);
	free(phdr);
	free(shdr);
	free(hdr);

	fclose(fobj);

	WritePC(prog_base);
	mem->set_block(STACK_BASE - STACK_SIZE, 0, STACK_SIZE);

	stack_ptr = STACK_BASE - MAX_ENVIRON;
	WriteGPR(stack_ptr, 29);

	/*write argc to stack*/
	mem->write_word(stack_ptr, argc);
	WriteGPR(argc, 4);
	stack_ptr += 4;

	/*skip stack_ptr past argv pointer array*/
	argAddr = stack_ptr;
	WriteGPR(argAddr, 5);
	stack_ptr += (argc+1)*4;

	/*skip env pointer array*/
	envAddr = stack_ptr;
	for (i=0; envp[i]; i++)
		stack_ptr += 4;
	stack_ptr += 4;

	/*write argv to stack*/ 
	for (i=0; i<argc; i++) {
		mem->write_word(argAddr+i*4, stack_ptr);
		mem->write_block(stack_ptr, argv[i], strlen(argv[i]));
		/*0 already at the end of the string as done by initialization*/
		stack_ptr += strlen(argv[i])+1;
	}

	/*0 already at the end argv pointer array*/

	/*write env to stack*/
	for (i=0; envp[i]; i++) {
		mem->write_word(envAddr+i*4, stack_ptr);
		mem->write_block(stack_ptr, envp[i], strlen(envp[i]));
		/*0 already at the end of the string as done by initialization*/
		stack_ptr += strlen(envp[i])+1;
	}

	signal(SIGUSR1, sig_handler);

	/*0 already at the end argv pointer array*/

	/*stack overflow*/
	if (stack_ptr+4>=STACK_BASE) {
		fprintf(stderr,
			"Environment overflow. Need to increase MAX_ENVIRON.\n");
		exit(1);
	}

	/* initialize brk point to 4k byte boundary */
	target_addr_t abrk = data_base+data_size+4096;
	abrk -= abrk % 4096;

	set_brk(abrk);
	set_mmap_brk(MMAP_BASE);

	status = ST_IDLE;

	fname_cache = filename;
	argc_cache = argc;
	argv_cache = argv;
	envp_cache = envp;
}

void mips_emulator::reload()
{
	reset();
	load_program(fname_cache, argc_cache, argv_cache, envp_cache);
}
