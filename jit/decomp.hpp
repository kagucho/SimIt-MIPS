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
#ifndef DECOMP_HPP
#define DECOMP_HPP

#include "decomp_common.hpp"
#include <cstdio>

void decomp(const char *filename, int argc, char *argv[], char *envp[],
	emulator_t *emm, unsigned ipf, bool tocount, bool verbose);

#endif
