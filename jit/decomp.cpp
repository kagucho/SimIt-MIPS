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
#include "decomp.hpp"
#include "arch.hpp"
#include "read_elf.h"
#include <cstdlib>
#include <map>

#define GRACE 10

using std::map;
using namespace emulator;


void decomp(const char *filename, 
	int argc, char *argv[], char *envp[], mips_emulator *emm,
	unsigned log2_insts_per_func, bool tocount, bool verbose)
{
	/*code from loader*/
	Elf32_Ehdr *hdr;
	Elf32_Shdr *shdr;
	Elf32_Shdr *shdr_new_section;
	Elf32_Word new_section_size, new_section_type, new_section_flags;
	void *new_section;
	Elf32_Addr new_section_addr;	
	FILE *fobj;

	FILE *out1;
	FILE *out2;
	FILE *outfile;
	mips_addr_t s_start;
	mips_addr_t s_end; 
	unsigned funcount;
	unsigned bytes_per_func = (1<<log2_insts_per_func)<<2;
	map<target_addr_t, target_addr_t> sec_addrs;
	map<target_addr_t, unsigned> func_addrs;
	
	/*code from loader*/
	fobj = fopen(filename, "rb");
	if(fobj == NULL) {
		fprintf(stderr, "Can't open executable: %s\n", filename);
		exit(1);
	}

	hdr = ReadElfHeader(fobj);
	
	if(hdr == NULL) {
		fprintf(stderr,
			"Could not read ELF32 header from file: %s.\n", filename);
		exit(1);
	}
	
	/* check if the file is for MIPS */
	if (hdr->e_type != ET_EXEC ||
		hdr->e_machine != EM_MIPS ||
		hdr->e_ident[EI_DATA] != ELFDATA2LSB) {
		fprintf(stderr, "File is not MIPS LSB executable: %s.\n", filename);
		exit(1);
	}
	
	/*end from loader*/
	
	/*code from loader*/
	shdr = ReadSectionHeaders(hdr, fobj);
	
	if(shdr == NULL) {
		fprintf(stderr, "Can't read section headers from executable\n");
		exit(1);
	}
	//string_table = LoadStringTable(hdr, shdr, fobj);	//need this??
	

	/*begin loader code*/
	for(int i = 0; i < hdr->e_shnum; i++)
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

			if (new_section_size && (new_section_flags & SHF_ALLOC) &&
				(new_section_flags & SHF_EXECINSTR))
			{ 

				new_section = malloc(new_section_size);
 				LoadSection(shdr_new_section, new_section, fobj);
				/*end from loader*/

				s_start = new_section_addr;
				s_end = new_section_addr + new_section_size;

				/*store s_end and s_start for later use*/
				sec_addrs[s_start] = s_end;

				/*code from loader*/
				free(new_section);
			}
		}
	}
	
	free(shdr);
	free(hdr);
	fclose(fobj);
	/*end loader code*/

	/*create cpps*/
	out1 = fopen("Stotal1.cpp", "w");
	if(out1 == NULL) {
		fprintf(stderr, "Can't open file to write");
		exit(1);
	}

	fprintf(out1, "#include \"compiled_run.hpp\"\n");
	fprintf(out1, "using namespace emulator;\n");
	fprintf(out1, "typedef mips_emulator mips_emul_t;\n");
	

	out2 = fopen("Stotal2.cpp", "w");
	if(out2 == NULL) {
		fprintf(stderr, "Can't open file to write");
		exit(1);
	}

	fprintf(out2, "#include \"compiled_run.hpp\"\n");
	fprintf(out2, "using namespace emulator;\n");
	fprintf(out2, "typedef mips_emulator mips_emul_t;\n");


	map<target_addr_t, target_addr_t>::iterator adit;
	adit = sec_addrs.begin(); 


	s_end = 0; 
	funcount = 0;
	while (adit!=sec_addrs.end()) {

		// align addresses
		s_start = (*adit).first - (*adit).first % bytes_per_func;
		if (s_start <= s_end)	// if partially emitted, resume from left off
			s_start = s_end;

		s_end = ((*adit).second+bytes_per_func-1)/bytes_per_func*bytes_per_func;

		for (target_addr_t ii=s_start; ii<s_end; ii+=bytes_per_func) {
			// split output into two files so that we can make -j2
			outfile = funcount%2?out1:out2;
			decomp_block(outfile, emm, ii, ii+bytes_per_func, funcount);
			func_addrs[ii] = funcount;
			funcount++;
		}

		// skip the covered section
		while (adit!=sec_addrs.end() && (*adit).second<=s_end)
			adit++;
	}

	fclose(out1);
	fclose(out2);

	/*create header file*/
	outfile = fopen("Scompiled_all.hpp", "w");
	if(outfile == NULL) {
		fprintf(stderr, "Can't open file to write");
		exit(1);
	}
	fprintf(outfile,
		"#ifndef SCOMPILED_ALL_HPP\n"
		"#define SCOMPILED_ALL_HPP\n"
		"#define BIN_PATH \"%s\"\n", filename);

	if (tocount)
		fprintf(outfile, 
			"#define COUNT_COMPILED\n");

	fprintf(outfile, 
		"#define VERBOSE %u\n", verbose?1:0);

	fprintf(outfile,
		"#define SHIFT_VAL %u\n"
		"#define NUM_FUNCS %u\n", log2_insts_per_func+2, funcount);

	fprintf(outfile, 
		"#include \"arch.hpp\"\n");

	fprintf(outfile,
		"typedef void (*fpointer)(emulator_t *, mips_addr_t);\n");

	fprintf(outfile,
		"extern const fpointer compiled_funct[NUM_FUNCS];\n");

	fprintf(outfile,
		"extern const mips_addr_t func_addrs[NUM_FUNCS];\n");

	fprintf(outfile,"#endif\n");	
	fclose(outfile);

	/*create header file*/
	outfile = fopen("Scompiled_all.cpp", "w");
	if(outfile == NULL) {
		fprintf(stderr, "Can't open file to write");
		exit(1);
	}

	fprintf(outfile, "#include \"Scompiled_all.hpp\"\n");
	fprintf(outfile, "extern \"C\" {\n");

	for(unsigned ii=0; ii<funcount; ii++)
		fprintf(outfile,
			"void compiled_%u(emulator_t *emm, "
			"mips_addr_t start_addr);\n", ii);

	fprintf(outfile, "}\n");

	fprintf(outfile,
		"const fpointer compiled_funct[NUM_FUNCS] = {\n");

	for(unsigned ii=0; ii<funcount; ii++) {
		fprintf(outfile, " compiled_%u,", ii);
		if (ii%4==0) fprintf(outfile, "\n");
	}

	fprintf(outfile, "};\n");

	fprintf(outfile,
		"const mips_addr_t func_addrs[NUM_FUNCS] = {\n");

	map<mips_addr_t, unsigned>::iterator fit = func_addrs.begin();
	for (unsigned ii=0; ii<funcount; fit++, ii++) {
		fprintf(outfile, " %u,", (*fit).first);
		if (ii%4==0) fprintf(outfile, "\n");
	}

	fprintf(outfile,"};\n");
	fclose(outfile);
}
