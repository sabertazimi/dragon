/*!
 * \file typechk.h
 * \brief
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#ifndef SEMA_TYPECHK_H
#define SEMA_TYPECHK_H

#include "semantic/common.h"
#include "errors/errors.h"
#include "ast/ast.h"

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
type_t const_typechk(Const *node);

/*
 * @brief: check type on def nodes
 */
type_t var_def_typechk(var_def_t node);
type_t func_def_typechk(func_def_t node);
void class_def_typechk(class_def_t node);
void class_defs_typechk(list_t class_defs);

/*
 * @brief: check type on expression nodes
 */
type_t expr_bool_typechk(expr_bool_t node);
type_t expr_assign_typechk(expr_assign_t node);
type_t expr_left_typechk(expr_left_t node);
type_t expr_typechk(expr_t node);
void assigns_typechk(list_t assigns);

/*
 * @brief: check type on statement nodes
 */
type_t stmt_typechk(stmt_t node);
void stmts_typechk(list_t stmts);

/*
 * @brief: check type on argument nodes
 */
type_t formal_typechk(formal_t node);
void formals_typechk(list_t formals);
type_t actual_typechk(actual_t node);
void actuals_typechk(list_t actuals);
int arguments_typechk(list_t formals, list_t actuals);

/*
 * @brief: check_type on field nodes
 */
type_t field_typechk(field_t node);
void fields_typechk(list_t fields);

/*
 * @brief: top type check function
 */
void prog_typechk(prog_t prog);

#endif /* !SEMA_TYPECHK_H */
