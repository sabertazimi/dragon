/*
 * ast_type.c
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "ast_type.h"

type_t type_basic_new(type_kind_t kind) {
    type_basic_t p = (type_basic_t)malloc(sizeof(*p));
    p->kind = kind;
    return (type_t)p;
}

type_t type_class_new(type_kind_t kind, string class_id) {
    type_class_t p = (type_class_t)malloc(sizeof(*p));
    p->kind = kind;
    p->class_id = strdup(class_id);
    return (type_t)p;
}

type_t type_array_new(type_kind_t kind, type_t type) {
    type_array_t p = (type_array_t)malloc(sizeof(*p));
    p->kind = kind;
    p->type = type;
    return (type_t)p;
}




