/*
 * ast_stmt.h
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef AST_STMT_H
#define AST_STMT_H

#include "ast_common.h"
#include "ast_def.h"
#include "ast_expr.h"

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

/*
 * @brief: create statement node
 */
stmt_t stmt_var_def_new(stmt_kind_t kind, var_def_t var_def);
stmt_t stmt_expr_new(stmt_kind_t kind, expr_t expr);
stmt_t stmt_if_new(stmt_kind_t kind, expr_bool_t cond, list_t body_then, list_t body_else);
stmt_t stmt_while_new(stmt_kind_t kind, expr_bool_t cond, list_t body);
stmt_t stmt_for_new(stmt_kind_t kind, list_t initializer, expr_bool_t cond, list_t assigner, list_t body);
stmt_t stmt_return_new(stmt_kind_t kind, expr_t ret_val);
stmt_t stmt_print_new(stmt_kind_t kind, expr_t out);

#endif /* !AST_STMT_H */
