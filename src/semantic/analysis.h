/*!
 * \file analysis.h
 * \brief
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#ifndef SEMA_ANALYSIS_H
#define SEMA_ANALYSIS_H

#include "semantic/common.h"
#include "semantic/Symtab.h"
#include "semantic/Scope.h"
#include "semantic/typechk.h"

/*
 * @brief: top function in semantic analysis module
 * @return: 0 false; 1 success
 */
int sema_analysis(prog_t prog);

/*
 * @brief: set up scope for ast tree
 */
void scope_setup(prog_t prog);

/*
 * @brief: print symbol tables
 */
void symtabs_print(prog_t prog);

#endif /* !SEMA_ANALYSIS_H */
