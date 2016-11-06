/*
 * sema_scope.c
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "sema_scope.h"

scope_t scope_new(scope_t super, scope_t parent,
        symtab_t class_defs, symtab_t var_defs, symtab_t formal_defs,
        symtab_t func_normal_defs, symtab_t func_anony_defs) {
    scope_t scope = (scope_t)malloc(sizeof(*scope));
    scope->super = super;
    scope->parent = parent;
    scope->class_defs = class_defs;
    scope->var_defs = var_defs;
    scope->formal_defs = formal_defs;
    scope->func_normal_defs = func_normal_defs;
    scope->func_anony_defs = func_anony_defs;
    return scope;
}

symbol_t scope_lookup(scope_t scope, const char *id) {
    symbol_t symbol;

    if ((symbol = symtab_lookup(scope->var_defs, id)) != NULL) {
        return symbol;
    } else if ((symbol = symtab_lookup(scope->formal_defs, id)) != NULL) {
        return symbol;
    } else if ((symbol = symtab_lookup(scope->func_normal_defs, id)) != NULL) {
        return symbol;
    } else if ((symbol = symtab_lookup(scope->class_defs, id)) != NULL) {
        return symbol;
    } else if (scope->super != NULL) {
        symbol = scope_lookup(scope->super, id);
        return symbol;
    } else if (scope->parent != NULL) {
        symbol = scope_lookup(scope->parent, id);
        return symbol;
    } else {
        return NULL;
    }
}

scope_t scope_enter(scope_t scope, symbol_t symbol) {
    switch (symbol->kind) {
        case SYMBOL_VAR_DEF:
            if (symtab_enter(scope->var_defs, symbol)) {
                return scope;
            } else {
                return NULL;
            }
        case SYMBOL_FORMAL_DEF:
            if (symtab_enter(scope->formal_defs, symbol)) {
                return scope;
            } else {
                return NULL;
            }
        case SYMBOL_FUNC_NORMAL_DEF:
            if (symtab_enter(scope->func_normal_defs, symbol)) {
                return scope;
            } else {
                return NULL;
            }
        case SYMBOL_FUNC_ANONY_DEF:
            stack_push(scope->func_anony_defs->table, symbol);
            return scope;
        case SYMBOL_CLASS_DEF:
            if (symtab_enter(scope->class_defs, symbol)) {
                return scope;
            } else {
                return NULL;
            }
        default:
            return NULL;
    }
}
