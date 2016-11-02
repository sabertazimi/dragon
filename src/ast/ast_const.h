/*
 * ast_const.h
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef AST_CONST_H
#define AST_CONST_H

#include "list.h"

/*
 * @brief: kind of constant
 */
typedef enum const_kind {
    CONST_INT = 151,
    CONST_BOOL,
    CONST_STRING,
    CONST_NIL
} const_kind_t;

/*
 * @interface: const_t
 */
typedef struct const_t {
    const_kind_t kind;
} *const_t;

/*
 * @implements: const_int_t/const_bool_t
 */
typedef struct const_num_t {
    const_kind_t kind;
    int value;
} *const_num_t;

/*
 * @implements: const_string_t
 */
typedef struct const_string_t {
    const_kind_t kind;
    string text;
} *const_string_t;

/*
 * @implements: const_nil_t
 */
typedef struct const_nil_t {
    const_kind_t kind;
} *const_nil_t;

/*
 * @brief: create number const node(int/bool)
 */
const_t const_num_new(const_kind_t kind, int value);

/*
 * @brief: create string const node
 */
const_t const_string_new(const_kind_t kind, string text);

/*
 * @brief: create nil const node
 */
const_t const_nil_new(const_kind_t kind);

#endif /* !AST_CONST_H */