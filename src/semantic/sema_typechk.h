/*
 * sema_typechk.h
 * Copyright (C) 2016 sabertazimi <sabertazimi@avalon>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef SEMA_TYPECHK_H
#define SEMA_TYPECHK_H

#include "sema_common.h"

type_t type_typechk(type_t node);
type_t const_typechk(const_t node);
type_t var_def_typechk(var_def_t node);
type_t func_def_typechk(func_def_t node);
type_t class_def_typechk(class_def_t node);
type_t class_defs_typechk(list_t class_defs);
type_t expr_typechk(expr_t node);
type_t assigns_typechk(list_t assigns);
type_t stmt_typechk(stmt_t node);
type_t stmts_typechk(list_t stmts);
type_t formal_typechk(formal_t node);
type_t formals_typechk(list_t formals);
type_t actual_typechk(actual_t node);
type_t actuals_typechk(list_t actuals);
type_t field_typechk(field_t node);
type_t fields_typechk(list_t fields);
type_t prog_typechk(prog_t prog);

#endif /* !SEMA_TYPECHK_H */
