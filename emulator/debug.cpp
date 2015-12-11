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
#include "mips_emul.hpp"
#include "misc.hpp"
#include "debug_disasm.hpp"

static void debug_help(FILE *fp);
bool get_addr(char *s, mips_addr_t *addr);
char *my_gets(char *p, int size);

using namespace emulator;

void mips_emulator::debug()
{
	mips_addr_t disasm_addr = ReadPC();
	mips_addr_t dump_addr = ReadPC();
	mips_addr_t addr;
	unsigned int reg_num;
	int nparms;
	int count;
	char line[256];
	char last_line[256];
	char parm[8][32];
	
	
	strcpy(last_line, "");
	strcpy(line, "");
	
	do
	{	
	 	if(strcmp(line, "") == 0)
	 	{
	 		strcpy(line, last_line);
	 	}
		
		nparms = sscanf(line, "%s %s %s %s %s %s %s %s",
			parm[0], parm[1], parm[2], parm[3], parm[4], parm[5],
			parm[6], parm[7]);
		
		switch(nparms)
		{
			case 1:
				if (strcmp(parm[0], "h") == 0 || strcmp(parm[0], "?") == 0) //ok
				{
					debug_help(stdout);
					break;
				}
				if(strcmp(parm[0], "u") == 0)  //pending disassemble
				{
					debug_disasm(stdout, disasm_addr);
					disasm_addr += 10 * 4;
					break;
				}
				else if(strcmp(parm[0], "d") == 0) //ok
				{
					debug_dump(stdout, dump_addr);
					dump_addr += 16 * 16;
					break;
				}
				else if(strcmp(parm[0], "g") == 0) //pending disassemble
				{
					debug_go_to(0);
					break;
				}
				else if(strcmp(parm[0], "pc") == 0) //ok
				{
					printf("PC = 0x%08x\n", ReadPC());
					break;
				}
				else if(strcmp(parm[0], "hi") == 0) //ok
				{
					printf("HI = 0x%08x\n", ReadHI());
					break;
				}
				else if(strcmp(parm[0], "lo") == 0) //ok
				{
					printf("LO = 0x%08x\n", ReadLO());
					break;
				}
				else if(strcmp(parm[0], "fcsr") == 0) //ok
				{
					printf("FCSR = 0x%08x\n", ReadFCSR());
					break;
				}
				else if(strcmp(parm[0], "ra") == 0) //remove
				{
					printf("RA = 0x%08x\n", ReadGPR(31));
					break;
				}
				else if(strcmp(parm[0], "r") == 0) //ok
				{
					debug_dump_registers(stdout,1);
					break;
				}
				else if(sscanf(parm[0], "r%u", &reg_num) == 1)//ok
				{
					if (reg_num<32)
						printf("r%u = 0x%08x\n", reg_num, ReadGPR(reg_num));
					break;
				}
				else if(strcmp(parm[0], "rf") == 0) //ok
				{
					debug_dump_registers(stdout,2);
					break;
				}
				else if(sscanf(parm[0], "rf%u", &reg_num) == 1)//ok
				{
					if (reg_num<32)
						printf("f%u = %+g\n", reg_num, ReadSFP(reg_num));
					break;
				}
				else if(strcmp(parm[0], "rd") == 0) //ok
				{
					debug_dump_registers(stdout,3);
					break;
				}
				else if(sscanf(parm[0], "rd%u", &reg_num) == 1)//ok
				{
					if (reg_num<32 && !(reg_num%2))
						printf("f%u = %+g\n", reg_num, ReadDFP(reg_num));
					break;
				}
				
				else if(strcmp(parm[0], "t") == 0) //pending disassemble
				{
					debug_trace(1);
					break;
				}
				else if(strcmp(parm[0], "q") == 0)
				{
					return;
				}
				//else if(strcmp(parm[0], "c") == 0)
				//{
			//		dump_instruction_counters(stdout);
			//		break;
			//	}
			//	else if(strcmp(parm[0], "cc") == 0)
			//	{
			//		reset_instruction_counters();
			//		break;
			//	}
				else
				{
					fprintf(stderr, "Unknown debugging command!\n");
					debug_help(stderr);
				}
				break;
				
			case 2:
				if(strcmp(parm[0], "u") == 0 && get_addr(parm[1], &disasm_addr)) //pending disassemble
				{
					debug_disasm(stdout, disasm_addr);
					disasm_addr += 10 * 4;
					break;
				}
				else if(strcmp(parm[0], "d") == 0 &&
					get_addr(parm[1], &dump_addr)) //pending disassemble
				{
					debug_dump(stdout, dump_addr);
					dump_addr += 16 * 16;
					break;
				}
				else if(strcmp(parm[0], "u") == 0 && strcmp(parm[1], "pc") == 0) //pending disassemble
				{
					disasm_addr = ReadPC();
					debug_disasm(stdout, disasm_addr);
					disasm_addr += 10 * 4;
					break;
				}
				else if(strcmp(parm[0], "g") == 0 && get_addr(parm[1], &addr)) //pending disassemble
				{
					debug_go_to(addr);
					break;
				}
				else if(strcmp(parm[0], "t") == 0 &&
					sscanf(parm[1], "%d", &count) == 1) //pendng disassemble
				{
					debug_trace(count);
					break;
				}
				else
				{
					fprintf(stderr,"Unknown debugging command!\n");
					debug_help(stderr);
				}
				break;
		}
	
		strcpy(last_line, line);
		
		printf("> ");
	} while(my_gets(line, sizeof(line)));

}

static void debug_help(FILE *fp)
{
	fprintf(fp, " Debug commands:\n"
				"	h		print this message\n"
				"	u [addr]	disassemble 10 instructions\n"
				"	d [addr]	dump 256 bytes from memory\n"
				"	g [addr]	run until addr\n"
				"	t [num]		step num instruction(s)\n"
				"	r[n]		dump gpr and fpr value(s)\n"
				"	rf[n]		same as 'r' but fpr shown as float\n"
				"	rd[n]		same as 'r' but fpr shown as double\n"
				"	pc		dump program counter\n"
				"	hi		dump HI\n"
				"	lo		dump LO\n"
				"	fcsr		dump FCSR\n"
				"	ra		dump ra (r31)\n"
			//	"	c		dump instruction counters\n"
			//	"	cc		reset instruction counters\n"
				"	q		quit\n");
}

bool get_addr(char *s, mips_addr_t *addr) //ok
{
	return sscanf(s, "%x", addr) == 1 || sscanf(s, "0x%x", addr) == 1;
}

char *my_gets(char *p, int size) //ok
{
	char *ret = fgets(p, size, stdin);
	if(ret)
	{
		int l = strlen(p);
		if(l > 0) p[l - 1] = 0;
	}
	return ret;
}

void mips_emulator::debug_disasm(FILE *stream, mips_addr_t addr) //pending disassemble
{
	int i;
	mips_inst_t inst;
	char disasm[256];
	
	for(i = 0; i < 10; i++, addr += 4)
	{
		inst = mem->read_word(addr);
		mips_disassemble(inst, addr, disasm);
		fprintf(stream, "0x%08x : 0x%08x	%s", addr, inst, disasm);
	}
}

void mips_emulator::debug_dump(FILE *stream, mips_addr_t addr) //ok
{
	int i, j;
	
	fprintf(stream,
		"   address   0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\n");
	for(i = 0; i < 16; i++)
	{
		fprintf(stream, "0x%08x: ", addr);
		for(j = 0; j < 16; j++, addr++)
		{
			fprintf(stream, "%02x", mem->read_byte(addr) & 0xFF);
			if(j < 15) fprintf(stream, " ");
		}
		fprintf(stream, "\n");
	}
}

void mips_emulator::debug_trace(int count) //pending disassemble
{
	mips_inst_t inst;
	char disasm[256];

	status = ST_DEBUGGING;
	while(status==ST_DEBUGGING && count > 0)
	{
		inst = mem->read_word_fast(ReadPC());
		execute(inst);
		icount++;
		count--;
	}
	
	inst = mem->read_word_fast(ReadPC());
	mips_disassemble(inst, ReadPC(), disasm);
	printf("0x%08x : 0x%08x	%s", ReadPC(), inst, disasm);
}

void mips_emulator::debug_dump_registers(FILE *stream, int floatmode) //ok
{
	int n=0;

	for (int i=0; i<8; i++) {

		// aligning
		if (i>0) fprintf(stream, "  ");

		for (int j=0; j<4; j++, n++) 
			fprintf(stream, "%s  = 0x%08x ", mips_gpr_names[n], ReadGPR(n));

		fprintf(stream, "\n");
	}
	n=0;
	if(floatmode == 3){
	for (int i=0; i<4; i++){
			fprintf(stream, "\n  ");
			for (int j=0; j<8; j+=2, n+=2){
				if(n>9)
					fprintf(stream, "f%u = %+e	", n, ReadDFP(n));
				else
					fprintf(stream, "f%u  = %+e	", n, ReadDFP(n));
			}
	}}
	else{
	for (int i=0; i<8; i++) {
		
		fprintf(stream, "\n  ");
		for (int j=0; j<4; j++, n++){ 
			if(n>9){
				if(floatmode == 2){
				fprintf(stream, "f%u = %+e	", n, ReadSFP(n));
				}
				else {
				fprintf(stream, "f%u = 0x%08x ", n, ReadFixedW(n));
				}
			}
			else{
				if(floatmode == 2){
				fprintf(stream, "f%u  = %+e	", n, ReadSFP(n));
				}
				else {
				fprintf(stream, "f%u  = 0x%08x ", n, ReadFixedW(n));
		}}}
	}
	}
	
		fprintf(stream, "\n");
}

void mips_emulator::debug_go_to(mips_addr_t addr) //pending disassemble
{
	mips_inst_t inst;
	char disasm[256];
	
	status = ST_DEBUGGING;
	
	do	
	{
		inst = mem->read_word_fast(ReadPC());
		execute(inst);
		icount++;
	}
	while(status==ST_DEBUGGING && ReadPC() != addr);
	
	if(is_done())
		printf("Program exited with code %d.\n", retcode);
	else{
		inst = mem->read_word_fast(ReadPC());
		mips_disassemble(inst, ReadPC(), disasm);
		printf("0x%08x : 0x%08x	%s", ReadPC(), inst, disasm);
	}
}
