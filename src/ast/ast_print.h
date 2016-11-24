/*!
 * \file ast_print.h
 * \brief
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#ifndef AST_PRINT_H
#define AST_PRINT_H

#include "ast_common.h"
#include "ast_type.h"
#include "ast_const.h"
#include "ast_def.h"
#include "ast_expr.h"
#include "ast_stmt.h"
#include "ast_others.h"

/*
 * @brief: functions for print ast tree
 */
void type_print(type_t node, int num_space);
void const_print(Const node, int num_space);
void var_def_print(var_def_t node, int num_space);
void func_def_print(func_def_t node, int num_space);
void class_def_print(class_def_t node, int num_space);
void class_defs_print(list_t class_defs, int num_space);
void expr_print(expr_t node, int num_space);
void assigns_print(list_t assigns, int num_space);
void stmt_print(stmt_t node, int num_space);
void stmts_print(list_t stmts, int num_space);
void formal_print(formal_t node, int num_space);
void formals_print(list_t formals, int num_space);
void actual_print(actual_t node, int num_space);
void actuals_print(list_t actuals, int num_space);
void field_print(field_t node, int num_space);
void fields_print(list_t fields, int num_space);
void prog_print(prog_t prog);

#endif /* !AST_PRINT_H */
