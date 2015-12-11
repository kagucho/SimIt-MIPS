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

#ifndef AUTO_EMITC
#define AUTO_EMITC


extern char* emitc_default(EMITC_FORMALS);

#define emitc_null emitc_default
#define _STUB_DEC(a) char* estub_##a(EMITC_FORMALS);

#define _TABLE_DEF_BEGIN(a,b) char* (*etable_## a [b])(EMITC_FORMALS) = {
#define _TABLE_DEF_END };

#define _STUB_ENTRY(a) char* estub_##a(EMITC_FORMALS)

#define _FUNC_CALL(a) return emitc_##a(EMITC_ARGS)
#define _FUNC_NAME(a) emitc_##a
#define _STUB_NAME(a) estub_##a
#define _FUNC_DEFAULT emitc_default

#define EINST emm->mem->read_word_fast(curpc)
#define _TABLE_JUMP(a,b,c) return etable_##a[(EINST>>c)&b](EMITC_ARGS)
#define _PATTERN_TRUE(a,b) ((EINST&a)==b)

#define _MAIN_DECODE_ENTRY char* emit_code(EMITC_FORMALS)

#endif
