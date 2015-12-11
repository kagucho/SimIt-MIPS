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
#include <mips_emul.hpp>

//sbasu
#include <pthread.h>

//#define MAXFUNS 262144
namespace emulator {

class decomp_server {


  public:

	/* constructor */
	decomp_server(bool,  uint32_t, bool);

	/* destructor */
	~decomp_server();

	/* to run the server */
	uint32_t run(const char *path);

	uint32_t get_count() const {return decomp_count;}

  private:

	bool compile_block(uint32_t address, uint32_t size, unsigned ind,
		bool tocount, bool selfmod, const char *path);

	/* emulator */
	mips_emulator *emu;
	bool verbose;
	uint32_t portnum;
	bool tolink;
	uint32_t decomp_count;


};


    
}


#endif
