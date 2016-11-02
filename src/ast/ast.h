/*
 * ast.h
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef AST_H
#define AST_H

#include "list.h"
#include "ast_type.h"
#include "ast_const.h"
#include "ast_def.h"
#include "ast_expr.h"
#include "ast_stmt.h"
#include "ast_others.h"
#include "ast_print.h"

///< space step when print ast tree
#define SPACE_STEP 2

/*
 * @brief: clone string text from stack to heap
 */
string cpystr(string text);

/*
 * @brief: print space(and level number)
 */
void space_print(int num_space);

#endif /* !AST_H */
