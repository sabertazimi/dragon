/*
 * sema_analysis.h
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef SEMA_ANALYSIS_H
#define SEMA_ANALYSIS_H

#include "sema_common.h"
#include "sema_symtab.h"
#include "sema_scope.h"
#include "sema_typechk.h"

/*
 * @brief: top function in semantic analysis module
 * @return: 0 false; 1 success
 */
int sema_analysis(prog_t prog);

/*
 * @brief: set up scope for ast tree
 */
void scope_setup(prog_t prog);

#endif /* !SEMA_ANALYSIS_H */
