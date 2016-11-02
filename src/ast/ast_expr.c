/*
 * ast_expr.c
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdlib.h>
#include "ast.h"

expr_t expr_prim_ident_new(expr_kind_t kind, expr_prim_kind_t sub_kind, string id) {
    expr_prim_ident_t p = (expr_prim_ident_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->id = cpystr(id);
    return (expr_t)p;
}

expr_t expr_prim_const_new(expr_kind_t kind, expr_prim_kind_t sub_kind, const_t const_val) {
    expr_prim_const_t p = (expr_prim_const_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->const_val = const_val;
    return (expr_t)p;
}

expr_t expr_prim_read_new(expr_kind_t kind, expr_prim_kind_t sub_kind) {
    expr_prim_read_t p = (expr_prim_read_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    return (expr_t)p;
}

expr_t expr_prim_newclass_new(expr_kind_t kind, expr_prim_kind_t sub_kind, string id, list_t actuals) {
    expr_prim_newclass_t p = (expr_prim_newclass_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->id = cpystr(id);
    p->actuals = actuals;
    return (expr_t)p;
}

expr_t expr_prim_newarray_new(expr_kind_t kind, expr_prim_kind_t sub_kind, type_t type, expr_t length) {
    expr_prim_newarray_t p = (expr_prim_newarray_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->type = type;
    p->length = length;
    return (expr_t)p;
}

expr_t expr_left_index_new(expr_kind_t kind, expr_left_kind_t sub_kind, expr_left_t array, expr_t index) {
    expr_left_index_t p = (expr_left_index_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->array = array;
    p->index = index;
    return (expr_t)p;
}

expr_t expr_left_class_field_new(expr_kind_t kind, expr_left_kind_t sub_kind, expr_left_t left, string field_id) {
    expr_left_class_field_t p = (expr_left_class_field_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->left = left;
    p->field_id = cpystr(field_id);
    return (expr_t)p;
}

expr_t expr_left_class_call_new(expr_kind_t kind, expr_left_kind_t sub_kind, expr_left_t left, string field_id, list_t actuals) {
    expr_left_class_call_t p = (expr_left_class_call_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->left = left;
    p->field_id = cpystr(field_id);
    p->actuals = actuals;
    return (expr_t)p;
}

expr_t expr_left_func_call_new(expr_kind_t kind, expr_left_kind_t sub_kind, expr_left_t left, list_t actuals) {
    expr_left_func_call_t p = (expr_left_func_call_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->left = left;
    p->actuals = actuals;
    return (expr_t)p;
}

expr_t expr_left_anony_call_new(expr_kind_t kind, expr_left_kind_t sub_kind, func_anony_def_t func_body, list_t actuals) {
    expr_left_anony_call_t p = (expr_left_anony_call_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->func_body = func_body;
    p->actuals = actuals;
    return (expr_t)p;
}

expr_t expr_unary_new(expr_kind_t kind, expr_unary_kind_t sub_kind, expr_unary_t body) {
    expr_unary_t p = (expr_unary_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->body = body;
    return (expr_t)p;
}

expr_t expr_mul_new(expr_kind_t kind, expr_mul_kind_t sub_kind, expr_mul_t left, expr_unary_t right) {
    expr_mul_t p = (expr_mul_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->left = left;
    p->right = right;
    return (expr_t)p;
}

expr_t expr_add_new(expr_kind_t kind, expr_add_kind_t sub_kind, expr_add_t left, expr_mul_t right) {
    expr_add_t p = (expr_add_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->left = left;
    p->right = right;
    return (expr_t)p;
}

expr_t expr_cmp_new(expr_kind_t kind, expr_cmp_kind_t sub_kind, expr_cmp_t left, expr_add_t right) {
    expr_cmp_t p = (expr_cmp_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->left = left;
    p->right = right;
    return (expr_t)p;
}

expr_t expr_eq_new(expr_kind_t kind, expr_eq_kind_t sub_kind, expr_eq_t left, expr_cmp_t right) {
    expr_eq_t p = (expr_eq_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->left = left;
    p->right = right;
    return (expr_t)p;
}

expr_t expr_and_new(expr_kind_t kind, expr_and_t left, expr_eq_t right) {
    expr_and_t p = (expr_and_t)malloc(sizeof(*p));
    p->kind = kind;
    p->left = left;
    p->right = right;
    return (expr_t)p;
}

expr_t expr_or_new(expr_kind_t kind, expr_or_t left, expr_and_t right) {
    expr_or_t p = (expr_or_t)malloc(sizeof(*p));
    p->kind = kind;
    p->left = left;
    p->right = right;
    return (expr_t)p;
}

expr_t expr_assign_new(expr_kind_t kind, expr_left_t left, expr_assign_t right) {
    expr_assign_t p = (expr_assign_t)malloc(sizeof(*p));
    p->kind = kind;
    p->left = left;
    p->right = right;
    return (expr_t)p;
}

expr_bool_t expr_bool_new(expr_kind_t kind, expr_t body) {
    expr_bool_t p = (expr_bool_t)malloc(sizeof(*p));
    p->kind = kind;
    p->body = body;
    return p;
}

