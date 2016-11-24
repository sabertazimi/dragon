/*!
 * \file Stmt.h
 * \brief
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#ifndef AST_STMT_H
#define AST_STMT_H

#include "ast/common.h"
#include "ast/Def.h"
#include "ast/Expr.h"

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
    yyltype loc;
    scope_t env;
} *stmt_t;

/*
 * @implements: stmt_var_def_t
 */
typedef struct stmt_var_def {
    stmt_kind_t kind;
    yyltype loc;
    scope_t env;
    var_def_t var_def;
} *stmt_var_def_t;

/*
 * @implements: stmt_expr_t
 */
typedef struct stmt_expr {
    stmt_kind_t kind;
    yyltype loc;
    scope_t env;
    expr_t expr;
} *stmt_expr_t;

/*
 * @implements: stmt_if_t
 */
typedef struct stmt_if {
    stmt_kind_t kind;
    yyltype loc;
    scope_t env;
    expr_bool_t cond;
    List<stmt_t> body_then;         ///< list_t <stmt_t>
    List<stmt_t> body_else;         ///< list_t <stmt_t>
} *stmt_if_t;

/*
 * @implements: stmt_while_t
 */
typedef struct stmt_while {
    stmt_kind_t kind;
    yyltype loc;
    scope_t env;
    expr_bool_t cond;
    List<stmt_t> body;            ///< list_t <stmt_t>
} *stmt_while_t;

/*
 * @implements: stmt_for_t
 */
typedef struct stmt_for {
    stmt_kind_t kind;
    yyltype loc;
    scope_t env;
    List<expr_assign_t> initializer;     ///< list_t <expr_assign_t>
    expr_bool_t cond;
    List<expr_assign_t> assigner;        ///< list_t <expr_assign_t>
    List<stmt_t> body;            ///< list_t <stmt_t>
} *stmt_for_t;

/*
 * @implements: stmt_return_t
 */
typedef struct stmt_return {
    stmt_kind_t kind;
    yyltype loc;
    scope_t env;
    expr_t  ret_val;
} *stmt_return_t;

/*
 * @implements: stmt_print_t
 */
typedef struct stmt_print {
    stmt_kind_t kind;
    yyltype loc;
    scope_t env;
    expr_t  out;
} *stmt_print_t;

/*
 * @brief: create statement node
 */
stmt_t stmt_var_def_new(stmt_kind_t kind, yyltype loc, var_def_t var_def);
stmt_t stmt_expr_new(stmt_kind_t kind, yyltype loc, expr_t expr);
stmt_t stmt_if_new(stmt_kind_t kind, yyltype loc, expr_bool_t cond, List<stmt_t> body_then, List<stmt_t> body_else);
stmt_t stmt_while_new(stmt_kind_t kind, yyltype loc, expr_bool_t cond, List<stmt_t> body);
stmt_t stmt_for_new(stmt_kind_t kind, yyltype loc, List<expr_assign_t> initializer, expr_bool_t cond, List<expr_assign_t> assigner, List<stmt_t> body);
stmt_t stmt_return_new(stmt_kind_t kind, yyltype loc, expr_t ret_val);
stmt_t stmt_print_new(stmt_kind_t kind, yyltype loc, expr_t out);

#endif /* !AST_STMT_H */
