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
#include "mips_gen.hpp"
#include "auto_emitc.h"
#include "mips_dec.h"

using namespace emulator;

void decomp_block(FILE *outfile, 
	emulator_t *emm, mips_addr_t fstart, mips_addr_t fend, unsigned ind)
{
	unsigned int instcount;
	char buf[4096];

	/*print preamble of a function*/
	fprintf(outfile,
	"extern \"C\" void compiled_%u(mips_emul_t *emm, "
		"mips_inst_t start_addr){\n", ind);

	/*define variables*/
	fprintf(outfile,
		"dword_t product;\n"
		"target_addr_t addr;\n"
		"target_addr_t addr2;\n"
		"word_t offr;\n"
		"word_t offm;\n"
		"word_t fixed_word;\n"
		"bool less;\n"
		"bool equal;\n"
		"bool unordered;\n"

		"target_addr_t jpc;\n"
		"#ifdef COUNT_COMPILED\n"
		"u_word_t _lpc;\n"
		"#endif\n");

	/*label table*/
	fprintf(outfile,
		"static void *labels[%u] = {\n\t&&L%x",
			(fend-fstart)/4, fstart);

	for (mips_addr_t kk = fstart+4; kk < fend; kk += 4) {
		fprintf(outfile, ", &&L%x", kk);
		if ((kk-fstart)%16==0) fprintf(outfile, "\n\t");
	}
     
	fprintf(outfile, "};\n");

	/*goto start*/
	fprintf(outfile,
		"#ifdef COUNT_COMPILED\n"                             
		"_lpc = start_addr>>2;\n"                             
		"#endif\n"
		"goto *labels[(start_addr-%u)/4];\n", fstart);

	for (mips_addr_t curpc = fstart; curpc < fend; curpc+=4, instcount++) {

		/*labels*/
		fprintf(outfile, "L%x:\t", curpc);

		emit_code(buf, emm,  curpc, fstart, fend, false);

		fprintf(outfile, "%s", buf);
		/* end of instruction */
	}

	/* print the tail of a function */
	/* should have been fend-4, but use fend-8 for counting -- 
	   no delay slot should be included in this case.
	*/
	fprintf(outfile, "LONG_JUMP(%u,%u);\n}\n", fend-8, fend);
}

char *emitc_default(char *buf, emulator_t *emm, target_addr_t curpc, target_addr_t fstart, target_addr_t fend, bool n){
    buf += sprintf(buf, "fputs(\"BAD OPDCODE!!!\\n\",stderr);\n");
    return buf;
}
