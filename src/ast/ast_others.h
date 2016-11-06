/*
 * ast_others.h
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef AST_OTHERS_H
#define AST_OTHERS_H

#include "ast_common.h"
#include "ast_type.h"
#include "ast_def.h"
#include "ast_expr.h"

/*
 * @implements: formal_t
 */
typedef struct formal {
    yyltype loc;
    scope_t env;
    type_t type;
    string id;
} *formal_t;

/*
 * @implements: actual_t
 */
typedef struct actual {
    yyltype loc;
    scope_t env;
    expr_t expr;
} *actual_t;

/*
 * @brief: kind of field
 */
typedef enum field_kind {
    FIELD_VAR = 1,
    FIELD_FUNC
} field_kind_t;

/*
 * @interface: field_t
 */
typedef struct field {
    field_kind_t kind;
    yyltype loc;
    scope_t scope;
} *field_t;

/*
 * @implements: field_t
 */
typedef struct field_var {
    field_kind_t kind;
    yyltype loc;
    scope_t scope;
    var_def_t var_def;
} *field_var_t;

/*
 * @implements: field_t
 */
typedef struct field_func {
    field_kind_t kind;
    yyltype loc;
    scope_t scope;
    func_def_t func_def;
} *field_func_t;

/*
 * @implements: prog_t
 */
typedef struct prog {
    yyltype loc;
    scope_t scope;
    list_t class_defs;      ///< list_t <class_def_t>
} *prog_t;

/*
 * @brief: create formal argument node
 */
formal_t formal_new(yyltype loc, type_t type, string id);

/*
 * @brief: create actual argument node
 */
actual_t actual_new(yyltype loc, expr_t expr);

/*
 * @brief: create variable field node
 */
field_t field_var_new(field_kind_t kind, yyltype loc, var_def_t var_def);

/*
 * @brief: create function field node
 */
field_t field_func_new(field_kind_t kind, yyltype loc, func_def_t func_def);

/*
 * @brief: create program node(root node)
 */
prog_t prog_new(yyltype loc, list_t class_defs);

#endif /* !AST_OTHERS_H */
