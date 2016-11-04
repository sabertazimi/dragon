/*
 * ast_def.h
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef AST_DEF_H
#define AST_DEF_H

#include "ast_common.h"
#include "ast_type.h"

// pre-defination to eliminate defination circle dependencies
typedef struct expr_assign *expr_assign_t;

/*
 * @implements: var_def_t
 */
typedef struct var_def {
    yyltype loc;
    type_t type;
    string id;
    expr_assign_t initializer;
} *var_def_t;

/*
 * @brief: kind of func_def_t
 */
typedef enum func_kind {
    FUNC_NORMAL_DEF = 11,
    FUNC_ANONY_DEF
} func_kind_t;

/*
 * @interface: func_def_t
 */
typedef struct func_def {
    func_kind_t kind;
    yyltype loc;
} *func_def_t;

/*
 * @implements: func_normal_def_t
 */
typedef struct func_normal_def {
    func_kind_t kind;
    yyltype loc;
    type_t type;
    list_t formals;         ///< list_t <formal_t>
    list_t stmts;           ///< list_t <stmt_t>
    string id;
} *func_normal_def_t;

/*
 * @implements: func_anony_def_t
 */
typedef struct func_anony_def {
    func_kind_t kind;
    yyltype loc;
    type_t type;
    list_t formals;         ///< list_t <formal_t>
    list_t stmts;           ///< list_t <stmt_t>
} *func_anony_def_t;

/*
 * @implements: class_def_t
 */
typedef struct class_def {
    yyltype loc;
    string id;
    string super;
    list_t fields;          ///< list_t <field_t>
} *class_def_t;

/*
 * @brief: create defination node
 */
var_def_t var_def_new(type_t type, string id, expr_assign_t initializer);
func_def_t func_normal_def_new(func_kind_t kind, type_t type, list_t formals, list_t stmts, string id);
func_def_t func_anony_def_new(func_kind_t kind, type_t type, list_t formals, list_t stmts);
class_def_t class_def_new(string id, string super, list_t fields);

#endif /* !AST_DEF_H */
