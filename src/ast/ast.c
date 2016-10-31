/*
 * ast.c
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

static string cpystr(string text) {
    string str = (string)malloc(sizeof(char) * (strlen(text) + 1));
    strcpy(str, text);
    return str;
}

const_t const_new(const_kind_t kind, int value, string text) {
    const_t p = (const_t)malloc(sizeof(*p));
    p->kind = kind;
    p->value = value;
    p->text = cpystr(text);
    return p;
}

func_normal_def_t func_normal_def_new(func_kind_t kind, type_t type, list_t formals, list_t stmts, string id) {
    func_normal_def_t p = (func_normal_def_t)malloc(sizeof(*p));
    p->kind = kind;
    p->type = type;
    p->formals = formals;
    p->stmts = stmts;
    p->id = cpystr(id);
    return p;
}

func_anony_def_t func_anony_def_new(func_kind_t kind, type_t type, list_t formals, list_t stmts) {
    func_anony_def_t p = (func_anony_def_t)malloc(sizeof(*p));
    p->kind = kind;
    p->type = type;
    p->formals = formals;
    p->stmts = stmts;
    return p;
}

expr_t expr_new(expr_kind_t kind, expr_kind_t sub_kind, expr_assign_t body) {
    expr_t p = (expr_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->body = body;
    return p;
}

expr_prim_ident_t expr_prim_ident_new(expr_kind_t kind, expr_prim_kind_t sub_kind, string id) {
    expr_prim_ident_t p = (expr_prim_ident_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->id = cpystr(id);
    return p;
}

expr_prim_const_t expr_prim_const_new(expr_kind_t kind, expr_prim_kind_t sub_kind, const_t const_val) {
    expr_prim_const_t p = (expr_prim_const_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->const_val = const_val;
    return p;
}

expr_prim_nested_t expr_prim_nested_new(expr_kind_t kind, expr_prim_kind_t sub_kind, expr_t expr) {
    expr_prim_nested_t p = (expr_prim_nested_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->expr = expr;
    return p;
}

expr_prim_readint_t expr_prim_readint_new(expr_kind_t kind, expr_prim_kind_t sub_kind) {
    expr_prim_readint_t p = (expr_prim_readint_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    return p;
}

expr_prim_readline_t expr_prim_readline_new(expr_kind_t kind, expr_prim_kind_t sub_kind) {
    expr_prim_readline_t p = (expr_prim_readline_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    return p;
}

expr_prim_newclass_t expr_prim_newclass_new(expr_kind_t kind, expr_prim_kind_t sub_kind, string id, list_t actuals) {
    expr_prim_newclass_t p = (expr_prim_newclass_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->id = cpystr(id);
    p->actuals = actuals;
    return p;
}

expr_prim_newarray_t expr_prim_newarray_new(expr_kind_t kind, expr_prim_kind_t sub_kind, type_t type, expr_t length) {
    expr_prim_newarray_t p = (expr_prim_newarray_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->type = type;
    p->length = length;
    return p;
}

expr_left_prim_t expr_left_prim_new(expr_kind_t kind, expr_left_kind_t sub_kind, expr_prim_t body) {
    expr_left_prim_t p = (expr_left_prim_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->body = body;
    return p;
}

expr_left_index_t expr_left_index_new(expr_kind_t kind, expr_left_kind_t sub_kind, expr_left_t array, expr_t index) {
    expr_left_index_t p = (expr_left_index_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->array = array;
    p->index = index;
    return p;
}

expr_left_class_field_t expr_left_class_field_new(expr_kind_t kind, expr_left_kind_t sub_kind, expr_left_t left, string field_id) {
    expr_left_class_field_t p = (expr_left_class_field_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->left = left;
    p->field_id = cpystr(field_id);
    return p;
}

expr_left_class_call_t expr_left_class_call_new(expr_kind_t kind, expr_left_kind_t sub_kind, expr_left_t left, string field_id, list_t actuals) {
    expr_left_class_call_t p = (expr_left_class_call_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->left = left;
    p->field_id = cpystr(field_id);
    p->actuals = actuals;
    return p;
}

expr_left_func_call_t expr_left_func_call_new(expr_kind_t kind, expr_left_kind_t sub_kind, expr_left_t left, list_t actuals) {
    expr_left_func_call_t p = (expr_left_func_call_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->left = left;
    p->actuals = actuals;
    return p;
}

expr_left_anony_call_t expr_left_anony_call_new(expr_kind_t kind, expr_left_kind_t sub_kind, func_anony_def_t func_body, list_t actuals) {
    expr_left_anony_call_t p = (expr_left_anony_call_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->func_body = func_body;
    p->actuals = actuals;
    return p;
}

expr_unary_left_t expr_unary_left_new(expr_kind_t kind, expr_unary_kind_t sub_kind, expr_left_t body) {
    expr_unary_left_t p = (expr_unary_left_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->body = body;
    return p;
}

expr_unary_normal_t expr_unary_normal_new(expr_kind_t kind, expr_unary_kind_t sub_kind, expr_unary_t body) {
    expr_unary_normal_t p = (expr_unary_normal_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->body = body;
    return p;
}

expr_mul_unary_t expr_mul_unary_new(expr_kind_t kind, expr_mul_kind_t sub_kind, expr_unary_t body) {
    expr_mul_unary_t p = (expr_mul_unary_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->body = body;
    return p;
}

expr_mul_normal_t expr_mul_normal_new(expr_kind_t kind, expr_mul_kind_t sub_kind, expr_mul_t left, expr_unary_t right) {
    expr_mul_normal_t p = (expr_mul_normal_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->left = left;
    p->right = right;
    return p;
}

expr_add_mul_t expr_add_mul_new(expr_kind_t kind, expr_add_kind_t sub_kind, expr_mul_t body) {
    expr_add_mul_t p = (expr_add_mul_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->body = body;
    return p;
}

expr_add_normal_t expr_add_normal_new(expr_kind_t kind, expr_add_kind_t sub_kind, expr_add_t left, expr_mul_t right) {
    expr_add_normal_t p = (expr_add_normal_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->left = left;
    p->right = right;
    return p;
}

expr_cmp_add_t expr_cmp_add_new(expr_kind_t kind, expr_cmp_kind_t sub_kind, expr_add_t body) {
    expr_cmp_add_t p = (expr_cmp_add_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->body = body;
    return p;
}

expr_cmp_normal_t expr_cmp_normal_new(expr_kind_t kind, expr_cmp_kind_t sub_kind, expr_cmp_t left, expr_add_t right) {
    expr_cmp_normal_t p = (expr_cmp_normal_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->left = left;
    p->right = right;
    return p;
}

expr_eq_cmp_t expr_eq_cmp_new(expr_kind_t kind, expr_eq_kind_t sub_kind, expr_cmp_t body) {
    expr_eq_cmp_t p = (expr_eq_cmp_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->body = body;
    return p;
}

expr_eq_normal_t expr_eq_normal_new(expr_kind_t kind, expr_eq_kind_t sub_kind, expr_eq_t left, expr_cmp_t right) {
    expr_eq_normal_t p = (expr_eq_normal_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->left = left;
    p->right = right;
    return p;
}

expr_and_eq_t expr_and_eq_new(expr_kind_t kind, expr_and_kind_t sub_kind, expr_eq_t body) {
    expr_and_eq_t p = (expr_and_eq_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->body = body;
    return p;
}

expr_and_normal_t expr_and_normal_new(expr_kind_t kind, expr_and_kind_t sub_kind, expr_and_t left, expr_eq_t right) {
    expr_and_normal_t p = (expr_and_normal_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->left = left;
    p->right = right;
    return p;
}

expr_or_and_t expr_or_and_new(expr_kind_t kind, expr_or_kind_t sub_kind, expr_and_t body) {
    expr_or_and_t p = (expr_or_and_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->body = body;
    return p;
}

expr_or_normal_t expr_or_normal_new(expr_kind_t kind, expr_or_kind_t sub_kind, expr_or_t left, expr_and_t right) {
    expr_or_normal_t p = (expr_or_normal_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->left = left;
    p->right = right;
    return p;
}

expr_assign_or_t expr_assign_or_new(expr_kind_t kind, expr_assign_kind_t sub_kind, expr_or_t body) {
    expr_assign_or_t p = (expr_assign_or_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->body = body;
    return p;
}

expr_assign_normal_t expr_assign_normal_new(expr_kind_t kind, expr_assign_kind_t sub_kind, expr_left_t left, expr_assign_t right) {
    expr_assign_normal_t p = (expr_assign_normal_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->left = left;
    p->right = right;
    return p;
}

expr_bool_t expr_bool_new(expr_kind_t kind, expr_or_kind_t sub_kind, expr_t body) {
    expr_bool_t p = (expr_bool_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->body = body;
    return p;
}

formal_t formal_new(type_t type, string id) {
    formal_t p = (formal_t)malloc(sizeof(*p));
    p->type = type;
    p->id = cpystr(id);
    return p;
}

actual_t actual_new(expr_t expr) {
    actual_t p = (actual_t)malloc(sizeof(*p));
    p->expr = expr;
    return p;
}


/* 583 */

/* p->id = (char *)malloc(sizeof(char) * (strlen(str) + 1)); */
/* strcpy(p->id, str); */

/* expr_t *div_into(expr_t *expr) { */
/*     while (expr->sub_kind == 0) { */
/*         expr = expr->body; */
/*     } */
/*     return expr; */
/* } */

/*     switch (expr->kind) { */
/*         case EXPR_AND; */
/*             expr = (expr_and_t)expr; */
/*             ... */
/*             break; */
/*         default: */
/*             break; */
/*     } */

/* expr_ast_prune */
