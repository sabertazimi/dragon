/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_SRC_PARSER_HH_INCLUDED
# define YY_YY_SRC_PARSER_HH_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    END = 258,
    NIL = 259,
    BOOL = 260,
    INT = 261,
    STRING = 262,
    FUNCTION = 263,
    VOID = 264,
    OP_AND = 265,
    OP_OR = 266,
    OP_LE = 267,
    OP_GE = 268,
    OP_EQ = 269,
    OP_NE = 270,
    OP_ARROW = 271,
    CLASS = 272,
    EXTENDS = 273,
    NEW = 274,
    THIS = 275,
    IF = 276,
    ELSE = 277,
    FOR = 278,
    WHILE = 279,
    RETURN = 280,
    PRINT = 281,
    READINTEGER = 282,
    READLINE = 283,
    CONSTANT_BOOL = 284,
    CONSTANT_INT = 285,
    CONSTANT_STRING = 286,
    IDENTIFIER = 287,
    UNEG = 288,
    NOELSE = 289
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 33 "src/parser.yy" /* yacc.c:1909  */

    int num_val;
    char *str_val;
    TypeLiteral *type_val;
    Expr *expr_val;
    List <Expr *> *exprs_val;
    LValue *Lvalue_val;
    List <VarDef *> *formals_val;
    List <Expr *> *actuals_val;
    VarDef *var_def_val;
    List <VarDef *> *vars_val;
    FuncDef *func_def_val;
    Node *field_val;
    List <Node *>* fields_val;
    Node *stmt_val;
    List <Node *> *stmts_val;
    ClassDef* class_def_val;
    List <ClassDef *>* class_defs_val;
    Program *prog_val;

#line 110 "src/parser.hh" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_SRC_PARSER_HH_INCLUDED  */
