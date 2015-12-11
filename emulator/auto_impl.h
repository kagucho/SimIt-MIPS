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

#ifndef AUTO_IMPL
#define AUTO_IMPL


extern void impl_default(IMPL_FORMALS);

#define impl_null impl_default
#define _STUB_DEC(a) void stub_##a(IMPL_FORMALS);

#define _TABLE_DEF_BEGIN(a,b) void (*table_## a [b])(IMPL_FORMALS) = {
#define _TABLE_DEF_END };

#define _STUB_ENTRY(a) void stub_##a(IMPL_FORMALS)

#define _FUNC_CALL(a) impl_##a(IMPL_ARGS)
#define _FUNC_NAME(a) impl_##a
#define _STUB_NAME(a) stub_##a
#define _FUNC_DEFAULT impl_default

#define _TABLE_JUMP(a,b,c) table_##a[(inst>>c)&b](IMPL_ARGS)
#define _PATTERN_TRUE(a,b) ((inst&a)==b)

#define _MAIN_DECODE_ENTRY void decode_main(IMPL_FORMALS)

#endif
