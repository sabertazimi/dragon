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

type_t type_basic_new(type_kind_t kind) {
    type_basic_t p = (type_basic_t)malloc(sizeof(*p));
    p->kind = kind;
    return (type_t)p;
}

type_t type_class_new(type_kind_t kind, string class_id) {
    type_class_t p = (type_class_t)malloc(sizeof(*p));
    p->kind = kind;
    p->class_id = cpystr(class_id);
    return (type_t)p;
}

type_t type_array_new(type_kind_t kind, type_t type) {
    type_array_t p = (type_array_t)malloc(sizeof(*p));
    p->kind = kind;
    p->type = type;
    return (type_t)p;
}

const_t const_num_new(const_kind_t kind, int value) {
    const_num_t p = (const_num_t)malloc(sizeof(*p));
    p->kind = kind;
    p->value = value;
    return (const_t)p;
}

const_t const_string_new(const_kind_t kind, string text) {
    const_string_t p = (const_string_t)malloc(sizeof(*p));
    p->kind = kind;
    p->text = cpystr(text);
    return (const_t)p;
}

const_t const_nil_new(const_kind_t kind) {
    const_nil_t p = (const_nil_t)malloc(sizeof(*p));
    p->kind = kind;
    return (const_t)p;
}

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

expr_t expr_prim_nested_new(expr_kind_t kind, expr_prim_kind_t sub_kind, expr_t expr) {
    expr_prim_nested_t p = (expr_prim_nested_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->expr = expr;
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

expr_t expr_and_new(expr_kind_t kind, expr_and_kind_t sub_kind, expr_and_t left, expr_eq_t right) {
    expr_and_t p = (expr_and_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->left = left;
    p->right = right;
    return (expr_t)p;
}

expr_t expr_or_new(expr_kind_t kind, expr_or_kind_t sub_kind, expr_or_t left, expr_and_t right) {
    expr_or_t p = (expr_or_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->left = left;
    p->right = right;
    return (expr_t)p;
}

expr_t expr_assign_new(expr_kind_t kind, expr_assign_kind_t sub_kind, expr_left_t left, expr_assign_t right) {
    expr_assign_t p = (expr_assign_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
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

var_def_t var_def_new(type_t type, string id, expr_assign_t initializer) {
    var_def_t p = (var_def_t)malloc(sizeof(*p));
    p->type = type;
    p->id = cpystr(id);
    p->initializer = initializer;
    return p;
}

func_def_t func_normal_def_new(func_kind_t kind, type_t type, list_t formals, list_t stmts, string id) {
    func_normal_def_t p = (func_normal_def_t)malloc(sizeof(*p));
    p->kind = kind;
    p->type = type;
    p->formals = formals;
    p->stmts = stmts;
    p->id = cpystr(id);
    return (func_def_t)p;
}

func_def_t func_anony_def_new(func_kind_t kind, type_t type, list_t formals, list_t stmts) {
    func_anony_def_t p = (func_anony_def_t)malloc(sizeof(*p));
    p->kind = kind;
    p->type = type;
    p->formals = formals;
    p->stmts = stmts;
    return (func_def_t)p;
}

field_t field_var_new(field_kind_t kind, var_def_t var_def) {
    field_var_t p = (field_var_t)malloc(sizeof(*p));
    p->kind = kind;
    p->var_def = var_def;
    return (field_t)p;
}

field_t field_func_new(field_kind_t kind, func_def_t func_def) {
    field_func_t p = (field_func_t)malloc(sizeof(*p));
    p->kind = kind;
    p->func_def = func_def;
    return (field_t)p;
}

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

class_def_t class_def_new(string id, string super, list_t fields) {
    class_def_t p = (class_def_t)malloc(sizeof(*p));
    p->id = cpystr(id);
    p->super = cpystr(super);
    p->fields = fields;
    return p;
}

prog_t prog_new(list_t class_defs) {
    prog_t p = (prog_t)malloc(sizeof(*p));
    p->class_defs = class_defs;
    return p;
}
