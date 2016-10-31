/*
 * ast.h
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef AST_H
#define AST_H

#include "list.h"

/* class_defs */
/*     : class_defs class_def */
/*     | class_def */
/*     ; */

/* class_def */
/*     : CLASS IDENTIFIER '{' fields '}' */
/*     | CLASS IDENTIFIER EXTENDS IDENTIFIER '{' fields '}' */
/*     ; */

/* fields */
/*     : fields field */
/*     | field */
/*     ; */

/* field */
/*     : var_def */
/*     | func_def */
/*     ; */

/* var_def */
/*     : type IDENTIFIER ';' */
/*     | type IDENTIFIER '=' assign_expr ';' */
/*     ; */

/* type */
/*     : INT */
/*     | BOOL */
/*     | STRING */
/*     | VOID */
/*     | CLASS IDENTIFIER */
/*     | type '[' ']' */
/*     ; */

/* func_def */
/*     : func_normal_def */
/*     | func_anonymous_def */
/*     ; */

/* func_normal_def */
/*     : type IDENTIFIER '=' '(' formals ')' OP_ARROW '{' stmts '}' ';' */
/*     ; */

/* func_anonymous_def */
/*     : type '(' formals ')' OP_ARROW '{' stmts '}' */
/*     ; */

/* formals */
/*     : formals_body */
/*     | VOID */
/*     ; */

/* formals_body */
/*     : formals_body ',' type IDENTIFIER */
/*     | type IDENTIFIER */
/*     ; */

/* stmts */
/*     : stmts stmt */
/*     | /1* empty *1/ */
/*     ; */

/* stmt */
/*     : var_def */
/*     | expr_stmt */
/*     | if_stmt */
/*     | while_stmt */
/*     | for_stmt */
/*     | return_stmt */
/*     | print_stmt */
/*     ; */

/* expr_stmt */
/*     : expr ';' */
/*     | ';' */
/*     ; */

/* if_stmt */
/*     : IF '(' bool_expr ')' '{' stmts '}' %prec NOELSE */
/*     | IF '(' bool_expr ')' '{' stmts '}' ELSE '{' stmts '}' */
/*     ; */

/* while_stmt */
/*     : WHILE '(' bool_expr ')' '{' stmts '}' */
/*     ; */

/* for_stmt */
/*     : FOR '(' assign_list ';' bool_expr ';' assign_list ')' '{' stmts '}' */
/*     ; */

/* return_stmt */
/*     : RETURN ';' */
/*     | RETURN VOID ';' */
/*     | RETURN expr ';' */
/*     ; */

/* print_stmt */
/*     : PRINT '(' expr ')' ';' */
/*     ; */

/* actuals */
/*     : actuals_body */
/*     | /1* empty *1/ */
/*     ; */

/* actuals_body */
/*     : actuals_body ',' expr */
/*     | expr */
/*     ; */

/* bool_expr */
/*     : expr */
/*     ; */

/* expr */
/*     : assign_expr */
/*     ; */

/* assign_expr */
/* 	: or_expr */
/* 	| left_expr '=' assign_expr */
/* 	; */

/* assign_list */
/*     : assign_list_body */
/*     | VOID */
/*     ; */

/* assign_list_body */
/*     : assign_list_body ',' assign_expr */
/*     | assign_expr */
/*     ; */

/* or_expr */
/* 	: and_expr */
/* 	| or_expr OP_OR and_expr */
/* 	; */

/* and_expr */
/* 	: eq_expr */
/* 	| and_expr OP_AND eq_expr */
/* 	; */

/* eq_expr */
/* 	: cmp_expr */
/* 	| eq_expr OP_EQ cmp_expr */
/* 	| eq_expr OP_NE cmp_expr */
/* 	; */

/* cmp_expr */
/* 	: add_expr */
/* 	| cmp_expr '<' add_expr */
/* 	| cmp_expr '>' add_expr */
/* 	| cmp_expr OP_LE add_expr */
/* 	| cmp_expr OP_GE add_expr */
/* 	; */

/* add_expr */
/* 	: mul_expr */
/* 	| add_expr '+' mul_expr */
/* 	| add_expr '-' mul_expr */
/* 	; */

/* mul_expr */
/* 	: unary_expr */
/* 	| mul_expr '*' unary_expr */
/* 	| mul_expr '/' unary_expr */
/* 	| mul_expr '%' unary_expr */
/* 	; */

/* unary_expr */
/*     : left_expr */
/*     | THIS */
/*     | '+' unary_expr */
/*     | '-' unary_expr */
/*     | '!' unary_expr */
/*     ; */

/* left_expr */
/* 	: prim_expr */
/* 	| left_expr '[' expr ']' */
/* 	| left_expr '.' IDENTIFIER %prec CLASS_MEMBER */
/*     | left_expr '.' IDENTIFIER '(' actuals ')' */
/* 	| left_expr '(' actuals ')' */
/*     | func_anonymous_def '(' actuals ')' */
/* 	; */

/* prim_expr */
/* 	: IDENTIFIER */
/* 	| constant */
/* 	| '(' expr ')' */
/*     | READINTEGER '(' ')' */
/*     | READLINE '(' ')' */
/*     | NEW IDENTIFIER '(' actuals ')' */
/*     | NEW type '[' expr ']' */
/* 	; */

/* constant */
/*     : CONSTANT_INT */
/*     | CONSTANT_BOOL */
/*     | CONSTANT_STRING */
/*     | NIL */
/*     ; */

typedef struct prog_t {
    list_t class_defs;      ///< list_t <class_def_t>
} *prog_t;

typedef struct class_def_t {
    ident_t id;
    ident_t super;
    list_t fields;          ///< list_t <field_t>
} *class_def_t;

typedef struct ident_t {
    char *id;
} *ident_t;

/* p = (ident_t)malloc(sizeof(*p)); */
/* p->id = (char *)malloc(sizeof(char) * (strlen(str) + 1)); */
/* strcpy(p->id, str); */


#endif /* !AST_H */
