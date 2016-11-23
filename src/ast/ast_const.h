/*!
 * \file ast_const.h
 * \brief
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#ifndef AST_CONST_H
#define AST_CONST_H

#include "ast_common.h"

///< kind of ast node
typedef enum __ast_kind__ {
    CONST_INT = 151,
    CONST_BOOL,
    CONST_STRING,
    CONST_NIL
} ast_kind;

/*
 * @interface: const_t
 */
typedef struct _const_ {
    const_kind_t kind;
    yyltype loc;
    scope_t env;
} *const_t;

/*
 * @implements: const_int_t/const_bool_t
 */
typedef struct _const_num_ {
    const_kind_t kind;
    yyltype loc;
    scope_t env;
    int value;
} *const_num_t;

/*
 * @implements: const_string_t
 */
typedef struct _const_string_ {
    const_kind_t kind;
    yyltype loc;
    scope_t env;
    string text;
} *const_string_t;

/*
 * @implements: const_nil_t
 */
typedef struct _const_nil_ {
    const_kind_t kind;
    yyltype loc;
    scope_t env;
} *const_nil_t;

/*
 * @brief: create number const node(int/bool)
 */
const_t const_num_new(const_kind_t kind, yyltype loc, int value);

/*
 * @brief: create string const node
 */
const_t const_string_new(const_kind_t kind, yyltype loc, string text);

/*
 * @brief: create nil const node
 */
const_t const_nil_new(const_kind_t kind, yyltype loc);

#endif /* !AST_CONST_H */
