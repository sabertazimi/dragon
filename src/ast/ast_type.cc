/*!
 * \file ast_type.cc
 * \brief
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#include "ast_type.h"

type_t type_basic_new(type_kind_t kind, yyltype loc) {
    type_basic_t p = (type_basic_t)malloc(sizeof(*p));
    p->kind = kind;
    p->loc = loc;
    return (type_t)p;
}

type_t type_class_new(type_kind_t kind, yyltype loc, string class_id) {
    type_class_t p = (type_class_t)malloc(sizeof(*p));
    p->kind = kind;
    p->loc = loc;
    p->class_id = strdup(class_id);
    return (type_t)p;
}

type_t type_array_new(type_kind_t kind, yyltype loc, type_t type) {
    type_array_t p = (type_array_t)malloc(sizeof(*p));
    p->kind = kind;
    p->loc = loc;
    p->type = type;
    return (type_t)p;
}

