/*!
 * \file Type.h
 * \brief
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#ifndef AST_TYPE_H
#define AST_TYPE_H

#include "ast/common.h"

/*
 * @brief: kind of type_t
 */
typedef enum type_kind {
    TYPE_INT = 21,
    TYPE_BOOL,
    TYPE_STRING,
    TYPE_VOID,
    TYPE_CLASS,
    TYPE_ARRAY
} type_kind_t;

/*
 * @interface: type_t
 */
typedef struct type {
    type_kind_t kind;
    yyltype loc;
    scope_t env;
} *type_t;

/*
 * @implements: type_int_t/type_bool_t/type_string_t/type_void_t
 */
typedef struct type_basic {
    type_kind_t kind;
    yyltype loc;
    scope_t env;
} *type_basic_t;

/*
 * @implements: type_class_t
 */
typedef struct type_class {
    type_kind_t kind;
    yyltype loc;
    scope_t env;
    string class_id;
} *type_class_t;

/*
 * @implements: type_array_t
 */
typedef struct type_array {
    type_kind_t kind;
    yyltype loc;
    scope_t env;
    type_t type;
    int length;
} *type_array_t;

/*
 * @brief: create basic type node(int/bool/string/void)
 */
type_t type_basic_new(type_kind_t kind, yyltype loc);

/*
 * @brief: create class type node
 */
type_t type_class_new(type_kind_t kind, yyltype loc, string class_id);

/*
 * @brief: create array type node
 */
type_t type_array_new(type_kind_t kind, yyltype loc, type_t type);

#endif /* !AST_TYPE_H */
