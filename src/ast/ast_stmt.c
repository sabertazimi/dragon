/*
 * ast_stmt.c
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "ast_stmt.h"

stmt_t stmt_var_def_new(stmt_kind_t kind, var_def_t var_def) {
    stmt_var_def_t p = (stmt_var_def_t)malloc(sizeof(*p));
    p->kind = kind;
    p->var_def = var_def;
    return (stmt_t)p;
}

stmt_t stmt_expr_new(stmt_kind_t kind, expr_t expr) {
    stmt_expr_t p = (stmt_expr_t)malloc(sizeof(*p));
    p->kind = kind;
    p->expr = expr;
    return (stmt_t)p;
}

stmt_t stmt_if_new(stmt_kind_t kind, expr_bool_t cond, list_t body_then, list_t body_else) {
    stmt_if_t p = (stmt_if_t)malloc(sizeof(*p));
    p->kind = kind;
    p->cond = cond;
    p->body_then = body_then;
    p->body_else = body_else;
    return (stmt_t)p;
}

stmt_t stmt_while_new(stmt_kind_t kind, expr_bool_t cond, list_t body) {
    stmt_while_t p = (stmt_while_t)malloc(sizeof(*p));
    p->kind = kind;
    p->cond = cond;
    p->body = body;
    return (stmt_t)p;
}

stmt_t stmt_for_new(stmt_kind_t kind, list_t initializer, expr_bool_t cond, list_t assigner, list_t body) {
    stmt_for_t p = (stmt_for_t)malloc(sizeof(*p));
    p->kind = kind;
    p->initializer = initializer;
    p->cond = cond;
    p->assigner = assigner;
    p->body = body;
    return (stmt_t)p;
}

stmt_t stmt_return_new(stmt_kind_t kind, expr_t ret_val) {
    stmt_return_t p = (stmt_return_t)malloc(sizeof(*p));
    p->kind = kind;
    p->ret_val = ret_val;
    return (stmt_t)p;
}

stmt_t stmt_print_new(stmt_kind_t kind, expr_t out) {
    stmt_print_t p = (stmt_print_t)malloc(sizeof(*p));
    p->kind = kind;
    p->out = out;
    return (stmt_t)p;
}
