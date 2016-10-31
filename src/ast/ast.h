/*
 * ast.h
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef AST_H
#define AST_H

#include "list.h"

typedef char *string;

/********** start of type_t **********/
/*
 * @brief: kind of type_t
 */
typedef enum type_kind {
    TYPE_INT = 21,
    TYPE_BOOL,
    TYPE_STRING,
    TYPE_VOID,
    TYPE_CLASS,
    TYPE_ARRAY
} type_t;
/********** end of type_t **********/

/********** start of const_t **********/
/*
 * @brief: kind of constant
 */
typedef enum const_kind {
    CONST_INT = 151,
    CONST_BOOL,
    CONST_STRING,
    CONST_NIL
} const_kind_t;

/*
 * @implements: const_t
 */
typedef struct const_t {
    const_kind_t kind;
    int value;
    string text;
} *const_t;
/********** end of const_t **********/

/********** start of func_def_t **********/
/*
 * @brief: kind of func_def_t
 */
typedef enum func_kind {
    FUNC_NORMAL_DEF = 11,
    FUNC_ANONY_DEF
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
    string id;
} *func_normal_def_t;

/*
 * @implements: func_anony_def_t
 */
typedef struct func_anony_def {
    func_kind_t kind;
    type_t type;
    list_t formals;         ///< list_t <formal_t>
    list_t stmts;           ///< list_t <stmt_t>
} *func_anony_def_t;
/********** end of func_def_t **********/

/********** start of expr_t **********/
/*
 * @brief: kind of expr_t
 */
typedef enum expr_kind {
    EXPR_BOOL = 41,
    EXPR_BASIC,
    EXPR_ASSIGN,
    EXPR_OR,
    EXPR_AND,
    EXPR_EQ,
    EXPR_CMP,
    EXPR_ADD,
    EXPR_MUL,
    EXPR_UNARY,
    EXPR_LEFT,
    EXPR_PRIM,
} expr_kind_t;

// pre-defination to solve defination dependencies error
typedef struct expr_assign_t *expr_assign_t;

/*
 * @interface: expr_t
 */
typedef struct expr {
    expr_kind_t kind;           ///< EXPR_BASIC
    expr_kind_t sub_kind;       ///< 0
    expr_assign_t body;
} *expr_t;

/*
 * @brief: kind of expr_prim_t
 */
typedef enum expr_prim_kind {
    EXPR_PRIM_IDENT = 141,
    EXPR_PRIM_CONST,
    EXPR_PRIM_NESTED,
    EXPR_PRIM_READINT,
    EXPR_PRIM_READLINE,
    EXPR_PRIM_NEWCLASS,
    EXPR_PRIM_NEWARRAY
} expr_prim_kind_t;

/*
 * @interface: expr_prim_t
 */
typedef struct expr_prim {
    expr_kind_t kind;
    expr_prim_kind_t sub_kind;
} *expr_prim_t;

/*
 * @implements: expr_prim_ident_t
 */
typedef struct expr_prim_ident {
    expr_kind_t kind;
    expr_prim_kind_t sub_kind;
    string id;
} *expr_prim_ident_t;

/*
 * @implements: expr_prim_const_t
 */
typedef struct expr_prim_const {
    expr_kind_t kind;
    expr_prim_kind_t sub_kind;
    const_t const_val;
} *expr_prim_const_t;

/*
 * @implements: expr_prim_nested_t
 */
typedef struct expr_prim_nested_t {
    expr_kind_t kind;
    expr_prim_kind_t sub_kind;
    expr_t expr;
} *expr_prim_nested_t;

/*
 * @implements: expr_prim_readint_t
 */
typedef struct expr_prim_readint_t {
    expr_kind_t kind;
    expr_prim_kind_t sub_kind;
} *expr_prim_readint_t;

/*
 * @implements: expr_prim_readline_t
 */
typedef struct expr_prim_readline_t {
    expr_kind_t kind;
    expr_prim_kind_t sub_kind;
} *expr_prim_readline_t;

/*
 * @implements: expr_prim_newclass_t
 */
typedef struct expr_prim_newclass_t {
    expr_kind_t kind;
    expr_prim_kind_t sub_kind;
    string id;
    list_t actuals;             ///< list_t <actual_t>
} *expr_prim_newclass_t;

/*
 * @implements: expr_prim_newarray_t
 */
typedef struct expr_prim_newarray_t {
    expr_kind_t kind;
    expr_prim_kind_t sub_kind;
    type_t type;
    expr_t length;
} *expr_prim_newarray_t;

/*
 * @brief: kind of expr_left_t
 */
typedef enum expr_left_kind {
    EXPR_LEFT_PRIM = 0,
    EXPR_LEFT_INDEX = 131,
    EXPR_LEFT_CLASS_FIELD,
    EXPR_LEFT_CLASS_CALL,
    EXPR_LEFT_FUNC_CALL,
    EXPR_LEFT_ANONY_CALL
} expr_left_kind_t;

/*
 * @interface: expr_left_t
 */
typedef struct expr_left {
    expr_kind_t kind;
    expr_left_kind_t sub_kind;
} *expr_left_t;

/*
 * @implements: expr_left_prim_t
 */
typedef struct expr_left_prim {
    expr_kind_t kind;
    expr_left_kind_t sub_kind;
    expr_prim_t body;
} *expr_left_prim_t;

/*
 * @implements: expr_left_index_t
 */
typedef struct expr_left_index {
    expr_kind_t kind;
    expr_left_kind_t sub_kind;
    expr_left_t array;
    expr_t index;
} *expr_left_index_t;

/*
 * @implements: expr_left_class_field_t
 */
typedef struct expr_left_class_field {
    expr_kind_t kind;
    expr_left_kind_t sub_kind;
    expr_left_t left;
    string field_id;
} *expr_left_class_field_t;

/*
 * @implements: expr_left_class_call_t
 */
typedef struct expr_left_class_call {
    expr_kind_t kind;
    expr_left_kind_t sub_kind;
    expr_left_t left;
    string field_id;
    list_t actuals;         ///< list_t <actual_t>
} *expr_left_class_call_t;

/*
 * @implements: expr_left_func_call_t
 */
typedef struct expr_left_func_call {
    expr_kind_t kind;
    expr_left_kind_t sub_kind;
    expr_left_t left;
    list_t actuals;         ///< list_t <actual_t>
} *expr_left_func_call_t;

/*
 * @implements: expr_left_anony_call_t
 */
typedef struct expr_left_anony_call {
    expr_kind_t kind;
    expr_left_kind_t sub_kind;
    func_anony_def_t func_body;
    list_t actuals;         ///< list_t <actual_t>
} *expr_left_anony_call_t;

/*
 * @brief: kind of expr_unary_t
 */
typedef enum expr_unary_kind {
    EXPR_UNARY_LEFT = 0,
    EXPR_UNARY_THIS = 121,
    EXPR_UNARY_PLUS,
    EXPR_UNARY_MINUS,
    EXPR_UNARY_NOT
} expr_unary_kind_t;

/*
 * @interface: expr_unary_t
 */
typedef struct expr_unary {
    expr_kind_t kind;
    expr_unary_kind_t sub_kind;
} *expr_unary_t;

/*
 * @implements: expr_unary_left_t
 */
typedef struct expr_unary_left {
    expr_kind_t kind;
    expr_unary_kind_t sub_kind;
    expr_left_t body;
} *expr_unary_left_t;

/*
 * @implements: expr_unary_this_t/expr_unary_plus_t/expr_unary_minus_t/expr_unary_not_t
 */
typedef struct expr_unary_normal {
    expr_kind_t kind;
    expr_unary_kind_t sub_kind;
    expr_unary_t body;
} *expr_unary_normal_t;

/*
 * @brief: kind of expr_mul_t
 */
typedef enum expr_mul_kind {
    EXPR_MUL_UNARY = 0,
    EXPR_MUL_MUL = 111,
    EXPR_MUL_DIV,
    EXPR_MUL_MOD
} expr_mul_kind_t;

/*
 * @interface: expr_mul_t
 */
typedef struct expr_mul {
    expr_kind_t kind;
    expr_mul_kind_t sub_kind;
} *expr_mul_t;

/*
 * @implements: expr_mul_unary_t
 */
typedef struct expr_mul_unary {
    expr_kind_t kind;
    expr_mul_kind_t sub_kind;
    expr_unary_t body;
} *expr_mul_unary_t;

/*
 * @implements: expr_mul_mul_t/expr_mul_sub_t/expr_mul_mod_t
 */
typedef struct expr_mul_normal {
    expr_kind_t kind;
    expr_mul_kind_t sub_kind;
    expr_mul_t left;
    expr_unary_t right;
} *expr_mul_normal_t;

/*
 * @brief: kind of expr_add_t
 */
typedef enum expr_add_kind {
    EXPR_ADD_MUL = 0,
    EXPR_ADD_ADD = 101,
    EXPR_ADD_SUB
} expr_add_kind_t;

/*
 * @interface: expr_add_t
 */
typedef struct expr_add {
    expr_kind_t kind;
    expr_add_kind_t sub_kind;
} *expr_add_t;

/*
 * @implements: expr_add_mul_t
 */
typedef struct expr_add_mul {
    expr_kind_t kind;
    expr_add_kind_t sub_kind;
    expr_mul_t body;
} *expr_add_mul_t;

/*
 * @implements: expr_add_add_t/expr_add_sub_t
 */
typedef struct expr_add_normal {
    expr_kind_t kind;
    expr_add_kind_t sub_kind;
    expr_add_t left;
    expr_mul_t right;
} *expr_add_normal_t;

/*
 * @brief: kind of expr_cmp_t
 */
typedef enum expr_cmp_kind {
    EXPR_CMP_ADD = 0,
    EXPR_CMP_L = 91,
    EXPR_CMP_G,
    EXPR_CMP_LE,
    EXPR_CMP_GE
} expr_cmp_kind_t;

/*
 * @interface: expr_cmp_t
 */
typedef struct expr_cmp {
    expr_kind_t kind;
    expr_cmp_kind_t sub_kind;
} *expr_cmp_t;

/*
 * @implements: expr_cmp_add_t
 */
typedef struct expr_cmp_add {
    expr_kind_t kind;
    expr_cmp_kind_t sub_kind;
    expr_add_t body;
} *expr_cmp_add_t;

/*
 * @implements: expr_cmp_l_t/expr_cmp_g_t/expr_cmp_le_t/expr_cmp_ge_t
 */
typedef struct expr_cmp_normal {
    expr_kind_t kind;
    expr_cmp_kind_t sub_kind;
    expr_cmp_t left;
    expr_add_t right;
} *expr_cmp_normal_t;

/*
 * @brief: kind of expr_eq_t
 */
typedef enum expr_eq_kind {
    EXPR_EQ_CMP = 0,
    EXPR_EQ_EQ = 81,
    EXPR_EQ_NE
} expr_eq_kind_t;

/*
 * @interface: expr_eq_t
 */
typedef struct expr_eq {
    expr_kind_t kind;
    expr_eq_kind_t sub_kind;
} *expr_eq_t;

/*
 * @implements: expr_eq_cmp_t
 */
typedef struct expr_eq_cmp {
    expr_kind_t kind;
    expr_eq_kind_t sub_kind;
    expr_cmp_t body;
} *expr_eq_cmp_t;

/*
 * @implements: expr_eq_eq_t/expr_eq_ne_t
 */
typedef struct expr_eq_normal {
    expr_kind_t kind;
    expr_eq_kind_t sub_kind;
    expr_eq_t left;
    expr_cmp_t right;
} *expr_eq_normal_t;

/*
 * @brief: kind of expr_and_t
 */
typedef enum expr_and_kind {
    EXPR_AND_EQ = 0,
    EXPR_AND_NORMAL = 71
} expr_and_kind_t;

/*
 * @interface: expr_and_t
 */
typedef struct expr_and {
    expr_kind_t kind;
    expr_and_kind_t sub_kind;
} *expr_and_t;

/*
 * @implements: expr_and_eq_t
 */
typedef struct expr_and_eq {
    expr_kind_t kind;
    expr_and_kind_t sub_kind;
    expr_eq_t body;
} *expr_and_eq_t;

/*
 * @implements: expr_and_normal_t
 */
typedef struct expr_and_normal {
    expr_kind_t kind;
    expr_and_kind_t sub_kind;
    expr_and_t left;
    expr_eq_t right;
} *expr_and_normal_t;

/*
 * @brief: kind of expr_or_t
 */
typedef enum expr_or_kind {
    EXPR_OR_AND = 0,
    EXPR_OR_NORMAL = 61
} expr_or_kind_t;

/*
 * @interface: expr_or_t
 */
typedef struct expr_or {
    expr_kind_t kind;
    expr_or_kind_t sub_kind;
} *expr_or_t;

/*
 * @implements: expr_or_and_t
 */
typedef struct expr_or_and {
    expr_kind_t kind;
    expr_or_kind_t sub_kind;
    expr_and_t body;
} *expr_or_and_t;

/*
 * @implements: expr_or_normal_t
 */
typedef struct expr_or_normal {
    expr_kind_t kind;
    expr_or_kind_t sub_kind;
    expr_or_t left;
    expr_and_t right;
} *expr_or_normal_t;

/*
 * @brief: kind of expr_assign_t
 */
typedef enum expr_assign_kind {
    EXPR_ASSIGN_OR = 0,
    EXPR_ASSIGN_NORMAL = 51
} expr_assign_kind_t;

/*
 * @interface: expr_assign_t
 */
struct expr_assign_t {
    expr_kind_t kind;
    expr_assign_kind_t sub_kind;
};

/*
 * @implements: expr_assign_or_t
 */
typedef struct expr_assign_or {
    expr_kind_t kind;
    expr_assign_kind_t sub_kind;
    expr_or_t body;
} *expr_assign_or_t;

/*
 * @implements: expr_assign_normal_t
 */
typedef struct expr_assign_normal {
    expr_kind_t kind;
    expr_assign_kind_t sub_kind;
    expr_left_t left;
    expr_assign_t right;
} *expr_assign_normal_t;

/*
 * @interface: expr_bool_t
 */
typedef struct expr_bool {
    expr_kind_t kind;           ///< EXPR_BOOL
    expr_kind_t sub_kind;       ///< 0
    expr_t body;
} *expr_bool_t;
/********** end of expr_t **********/

/********** start of formal_t **********/
/*
 * @implements: formal_t
 */
typedef struct formal {
    type_t type;
    string id;
} *formal_t;
/********** end of formal_t **********/

/********** start of actual_t **********/
typedef struct actual {
    expr_t expr;
} *actual_t;
/********** end of actual_t **********/

/********** start of var_def_t **********/
/*
 * @implements: var_def_t
 */
typedef struct var_def {
    type_t type;
    string id;
    expr_assign_t initializer;
} *var_def_t;
/********** end of var_def_t **********/

/********** start of field_t **********/
/*
 * @brief: kind of field
 */
typedef enum field_kind {
    FIELD_VAR = 1,
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

/********** start of stmt_t **********/
/*
 * @brief: kind of stmt_t
 */
typedef enum stmt_kind {
    STMT_VAR_DEF = 31,
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
} *stmt_var_def_t;

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

/********** start of class_def_t **********/
/*
 * @implements: class_def_t
 */
typedef struct class_def {
    string id;
    string super;
    list_t fields;          ///< list_t <field_t>
} *class_def_t;
/********** end of class_def_t **********/

/********** start of prog_t **********/
/*
 * @implements: prog_t
 */
typedef struct prog {
    list_t class_defs;      ///< list_t <class_def_t>
} *prog_t;
/********** end of prog_t **********/

#endif /* !AST_H */
