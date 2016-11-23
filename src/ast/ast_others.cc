/*!
 * \file ast_others.cc
 * \brief
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#include "ast_others.h"

formal_t formal_new(yyltype loc, type_t type, string id) {
    formal_t p = (formal_t)malloc(sizeof(*p));
    p->loc = loc;
    p->type = type;
    p->id = strdup(id);
    return p;
}

actual_t actual_new(yyltype loc, expr_t expr) {
    actual_t p = (actual_t)malloc(sizeof(*p));
    p->loc = loc;
    p->expr = expr;
    return p;
}

field_t field_var_new(field_kind_t kind, yyltype loc, var_def_t var_def) {
    field_var_t p = (field_var_t)malloc(sizeof(*p));
    p->kind = kind;
    p->loc = loc;
    p->var_def = var_def;
    return (field_t)p;
}

field_t field_func_new(field_kind_t kind, yyltype loc, func_def_t func_def) {
    field_func_t p = (field_func_t)malloc(sizeof(*p));
    p->kind = kind;
    p->loc = loc;
    p->func_def = func_def;
    return (field_t)p;
}

prog_t prog_new(yyltype loc, list_t class_defs) {
    prog_t p = (prog_t)malloc(sizeof(*p));
    p->loc = loc;
    p->class_defs = class_defs;
    return p;
}
