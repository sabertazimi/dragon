/*
 * ast_type.h
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef AST_TYPE_H
#define AST_TYPE_H

#include "list.h"

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
} *type_t;

/*
 * @implements: type_int_t/type_bool_t/type_string_t/type_void_t
 */
typedef struct type_basic {
    type_kind_t kind;
} *type_basic_t;

/*
 * @implements: type_class_t
 */
typedef struct type_class {
    type_kind_t kind;
    string class_id;
} *type_class_t;

/*
 * @implements: type_array_t
 */
typedef struct type_array {
    type_kind_t kind;
    type_t type;
} *type_array_t;

/*
 * @brief: create basic type node(int/bool/string/void)
 */
type_t type_basic_new(type_kind_t kind);

/*
 * @brief: create class type node
 */
type_t type_class_new(type_kind_t kind, string class_id);

/*
 * @brief: create array type node
 */
type_t type_array_new(type_kind_t kind, type_t type);

#endif /* !AST_TYPE_H */
