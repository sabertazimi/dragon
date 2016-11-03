/*
 * ast_const.c
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdlib.h>
#include <string.h>
#include "ast.h"

const_t const_num_new(const_kind_t kind, int value) {
    const_num_t p = (const_num_t)malloc(sizeof(*p));
    p->kind = kind;
    p->value = value;
    return (const_t)p;
}

const_t const_string_new(const_kind_t kind, string text) {
    const_string_t p = (const_string_t)malloc(sizeof(*p));
    p->kind = kind;
    p->text = strdup(text);
    return (const_t)p;
}

const_t const_nil_new(const_kind_t kind) {
    const_nil_t p = (const_nil_t)malloc(sizeof(*p));
    p->kind = kind;
    return (const_t)p;
}
