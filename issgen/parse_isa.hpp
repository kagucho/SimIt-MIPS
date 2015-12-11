/* A Bison parser, made by GNU Bison 1.875c.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TK_OP = 258,
     TK_GRP = 259,
     TK_VAR = 260,
     TK_FIELD = 261,
     TK_IDENT = 262,
     TK_NUM = 263,
     TK_PAT = 264,
     TK_STR = 265
   };
#endif
#define TK_OP 258
#define TK_GRP 259
#define TK_VAR 260
#define TK_FIELD 261
#define TK_IDENT 262
#define TK_NUM 263
#define TK_PAT 264
#define TK_STR 265




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 27 "parse_isa.y"
typedef union YYSTYPE {

	char *strval;

	unsigned uint;
	Symbol sym_t;

	VAR_ENV *venv_t;
	FIELD_ENV *fenv_t;

	OP_CON_T *op_con_t;
	OP_CON_ENV *op_con_env_t;

	class oper_base *oper_t;
	vector<class oper_base *> *oper_list_t;

	vector<bin_code *> *code_list_t;
} YYSTYPE;
/* Line 1275 of yacc.c.  */
#line 76 "parse_isa.hpp"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE isa_lval;



