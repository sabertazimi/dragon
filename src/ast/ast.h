/*
 * ast.h
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef AST_H
#define AST_H

#include "list.h"

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

/********** start of prog_t **********/
/*
 * @implements: prog_t
 */
typedef struct prog {
    list_t class_defs;      ///< list_t <class_def_t>
} *prog_t;
/********** end of prog_t **********/

/********** start of class_def_t **********/
/*
 * @implements: class_def_t
 */
typedef struct class_def {
    char *id;
    char *super;
    list_t fields;          ///< list_t <field_t>
} *class_def_t;
/********** end of class_def_t **********/

/********** start of field_t **********/
/*
 * @brief: kind of field
 */
typedef enum field_kind {
    FIELD_VAR,
    FIELD_FUNC
} field_kind_t;

/*
 * @interface: field_t
 */
typedef struct field {
    field_kind_t kind;
} *field_t;

/*
 * @implements: field_t
 */
typedef struct field_var {
    field_kind_t kind;
    var_def_t var_def;
} *field_var_t;

/*
 * @implements: field_t
 */
typedef struct field_func {
    field_kind_t kind;
    func_def_t func_def;
} *field_func_t;
/********** end of field_t **********/

/********** start of var_def_t **********/
/*
 * @implements: var_def_t
 */
typedef struct var_def {
    type_t type;
    char *id;
    expr_assign_t initializer;
} *var_def_t;
/********** end of var_def_t **********/

/********** start of func_def_t **********/
/*
 * @brief: kind of func_def_t
 */
typedef enum func_kind {
    FUNC_NORMAL_DEF,
    FUNC_ANONYMOUS_DEF
} func_kind_t;


/*
 * @interface: func_def_t
 */
typedef struct func_def {
    func_kind_t kind;
} *func_def_t;

/*
 * @implements: func_normal_def_t
 */
typedef struct func_normal_def {
    func_kind_t kind;
    type_t type;
    list_t formals;         ///< list_t <formal_t>
    list_t stmts;           ///< list_t <stmt_t>
    char *id;
} *func_normal_def_t;

/*
 * @implements: func_anonymous_def_t
 */
typedef struct func_anonymous_def {
    func_kind_t kind;
    type_t type;
    list_t formals;         ///< list_t <formal_t>
    list_t stmts;           ///< list_t <stmt_t>
} *func_anonymous_def_t;
/********** end of func_def_t **********/

/********** start of type_t **********/
/*
 * @brief: kind of type_t
 */
typedef enum type_kind {
    TYPE_INT,
    TYPE_BOOL,
    TYPE_STRING,
    TYPE_VOID,
    TYPE_CLASS,
    TYPE_ARRAY
} type_t;
/********** end of type_t **********/

/********** start of formal_t **********/
/*
 * @implements: formal_t
 */
typedef struct formal {
    type_t type;
    cahr *id;
} *formal_t;
/********** end of formal_t **********/

/********** start of stmt_t **********/
/*
 * @brief: kind of stmt_t
 */
typedef enum stmt_kind {
    STMT_VAR_DEF,
    STMT_EXPR,
    STMT_IF,
    STMT_WHILE,
    STMT_FOR,
    STMT_RETURN,
    STMT_PRINT
} stmt_kind_t;

/*
 * @interface: stmt_t
 */
typedef struct stmt {
    stmt_kind_t kind;
} *stmt_t;

/*
 * @implements: stmt_var_def_t
 */
typedef struct stmt_var_def {
    stmt_kind_t kind;
    var_def_t var_def;
} *stmt_var_def_t

/*
 * @implements: stmt_expr_t
 */
typedef struct stmt_expr {
    stmt_kind_t kind;
    expr_t expr;
} *stmt_expr_t;

/*
 * @implements: stmt_if_t
 */
typedef struct stmt_if {
    stmt_kind_t kind;
    expr_bool_t cond;
    list_t body_then;         ///< list_t <stmt_t>
    list_t body_else;         ///< list_t <stmt_t>
} *stmt_if_t;

/*
 * @implements: stmt_while_t
 */
typedef struct stmt_while {
    stmt_kind_t kind;
    expr_bool_t cond;
    list_t body;            ///< list_t <stmt_t>
} *stmt_while_t;

/*
 * @implements: stmt_for_t
 */
typedef struct stmt_for {
    stmt_kind_t kind;
    list_t initializer;     ///< list_t <expr_assign_t>
    expr_bool_t cond;
    list_t assigner;        ///< list_t <expr_assign_t>
    list_t body;            ///< list_t <stmt_t>
} *stmt_for_t;

/*
 * @implements: stmt_return_t
 */
typedef struct stmt_return {
    stmt_kind_t kind;
    expr_t  ret_val;
} *stmt_return_t;

/*
 * @implements: stmt_print_t
 */
typedef struct stmt_print {
    stmt_kind_t kind;
    expr_t  out;
} *stmt_print_t;
/********** end of stmt_t **********/

/********** start of actual_t **********/
typedef struct actual {
    expr_t expr;
} actual_t;
/********** end of actual_t **********/

/********** start of expr_t **********/
/********** end of expr_t **********/

/********** start of type_t **********/
/********** end of type_t **********/

/********** start of type_t **********/
/********** end of type_t **********/

/********** start of type_t **********/
/********** end of type_t **********/

/********** start of type_t **********/
/********** end of type_t **********/

/********** start of type_t **********/
/********** end of type_t **********/

/********** start of type_t **********/
/********** end of type_t **********/

/* char *id */
/* p->id = (char *)malloc(sizeof(char) * (strlen(str) + 1)); */
/* strcpy(p->id, str); */

#endif /* !AST_H */
