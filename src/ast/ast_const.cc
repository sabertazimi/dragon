/*!
 * \file ast_const.cc
 * \brief
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#include "ast_const.h"

const_t const_num_new(const_kind_t kind, yyltype loc, int value) {
    const_num_t p = (const_num_t)malloc(sizeof(*p));
    p->kind = kind;
    p->loc = loc;
    p->value = value;
    return (const_t)p;
}

const_t const_string_new(const_kind_t kind, yyltype loc, string text) {
    const_string_t p = (const_string_t)malloc(sizeof(*p));
    p->kind = kind;
    p->loc = loc;
    p->text = strdup(text);
    return (const_t)p;
}

const_t const_nil_new(const_kind_t kind, yyltype loc) {
    const_nil_t p = (const_nil_t)malloc(sizeof(*p));
    p->kind = kind;
    p->loc = loc;
    return (const_t)p;
}
