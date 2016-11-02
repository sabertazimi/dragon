/*
 * ast_others.c
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdlib.h>
#include "ast.h"

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

prog_t prog_new(list_t class_defs) {
    prog_t p = (prog_t)malloc(sizeof(*p));
    p->class_defs = class_defs;
    return p;
}
