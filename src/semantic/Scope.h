/*!
 * \file Scope.h
 * \brief
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#ifndef SEMA_SCOPE_H
#define SEMA_SCOPE_H

#include "semantic/common.h"
#include "semantic/Symtab.h"

typedef struct _scope_ *scope_t;

struct _scope_ {
    scope_t parent;             ///< scope from upper ast node
    scope_t super;              ///< scope from super class
    symtab_t class_defs;        ///< for global scope
    symtab_t var_defs;          ///< for class/function scope
    symtab_t formal_defs;       ///< for function scope
    symtab_t func_normal_defs;  ///< for class scope
    symtab_t func_anony_defs;   ///< for function scope(ignore func_anony_defs as class fields)
};

/*
 * @brief: create a new scope
 */
scope_t scope_new(scope_t super, scope_t parent,
        symtab_t class_defs, symtab_t var_defs, symtab_t formal_defs,
        symtab_t func_normal_defs, symtab_t func_anony_defs);

/*
 * @brief: search symbol in scope with id
 * @return: NULL/symbol_t
 */
symbol_t scope_lookup(scope_t scope, const char *id);


/*
 * @brief: insert a new symbol to scope
 */
scope_t scope_enter(scope_t scope, symbol_t symbol);

#endif /* !SEMA_SCOPE_H */
