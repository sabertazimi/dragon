/*
 * sema_typechk.h
 * Copyright (C) 2016 sabertazimi <sabertazimi@avalon>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef SEMA_TYPECHK_H
#define SEMA_TYPECHK_H

#include "sema_common.h"
#include "ast.h"

/*
 * @brief: check equality of two type nodes
 * @return: 0 not equal; 1 equal
 */
int typechk(type_t left, type_t right);

/*
 * @brief: get type name(string)
 */
char *type_name(type_t node);

/*
 * @brief: get type of AST node
 */
type_t const_typechk(const_t node);

/*
 * @brief: check type on def nodes
 */
type_t var_def_typechk(var_def_t node);
type_t func_def_typechk(func_def_t node);
type_t class_def_typechk(class_def_t node);
type_t class_defs_typechk(list_t class_defs);

/*
 * @brief: check type on expression nodes
 */
type_t expr_bool_typechk(expr_bool_t node);
type_t expr_assign_typechk(expr_assign_t node);
type_t expr_left_typechk(expr_left_t node);
type_t expr_typechk(expr_t node);
type_t assigns_typechk(list_t assigns);

/*
 * @brief: check type on statement nodes
 */
type_t stmt_typechk(stmt_t node);
type_t stmts_typechk(list_t stmts);

/*
 * @brief: check type on argument nodes
 */
type_t formal_typechk(formal_t node);
type_t formals_typechk(list_t formals);
type_t actual_typechk(actual_t node);
type_t actuals_typechk(list_t actuals);

/*
 * @brief: check_type on field nodes
 */
type_t field_typechk(field_t node);
type_t fields_typechk(list_t fields);

/*
 * @brief: top type check function
 */
int prog_typechk(prog_t prog);

#endif /* !SEMA_TYPECHK_H */
