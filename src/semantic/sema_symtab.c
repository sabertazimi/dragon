/*
 * sema_symtab.c
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "sema_symtab.h"

/*
 * @TODO: get inspiration from cs143
 * relationships between ast node, scope_t and symtab_t
 * ast node(class_def and func_def) has pointer member pointing to a scope_t variable, to store their scope
 * scope_t has a symtab_t member ,to store all symbol valid in this scope
 * symtab_t has a stack_t/list_t (<stack_t/list_t <symbol_t>) member, to store all defs binding to symbols
 * typedef struct _symbol_ {
 *  const char* id;     // key
 *  def_t def;          // value
 * } *symbol_t;
 *
 * when travel ast tree first time, set up all scope_t in class_def_t or func_def_t
 * 1. create empty scope
 * 2. bind a specific def_t to a symbol_t (set up id -> def_t mapping)
 * 3. add symbol_t to scope->symtab_t
 *
 * when travel ast tree second time, start to truly semantic analysis(e.g type check)
 *
 * @TODO: change ast node <class_def_t> <func_def_t> , add scope_t member
 * @TODO: change ast node <without scope_t>, add parent member
 * @TODO: change parser.y and new ast node function <class_def_t, func_def_t>, bind all children of them to them(children->parent = this/them)
 * @TODO: implement data structure symbol_t, symtab_t and scope_t and operations on them.
 */

static yyltype mock_loc = {233, 233, 233, 234};

// scope_t
// sym_classdef -> ... -> ... -> sym_classdef_main

// @FIXME
/* sym_t sym_vardef_new(sym_kind_t kind, var_def_t var_def) { */
/*     sym_vardef_t p = (sym_vardef_t)malloc(sizeof(*p)); */
/*     p->kind = kind; */
/*     p->type = var_def->type; */
/*     p->id = var_def->id; */
/*     return (sym_t)p; */
/* } */

// @TODO: this is a mock function
sym_t sym_vardef_new(sym_kind_t kind, type_t type) {
    sym_vardef_t p = (sym_vardef_t)malloc(sizeof(*p));
    p->kind = kind;
    p->type = type;
    return (sym_t)p;
}

/*
 * @mock: temporary for testing
 * @TODO: implements truly symtab_lookup function
 */
sym_t symtab_lookup(sym_kind_t kind, string id) {
    switch (kind) {
        case SYM_LOCALVARDEF:
        {
            // sym_vardef_t p = sym_vardef_new(SYM_VARDEF, （type_t)type_basic_new(TYPE_INT));
            break;
        }
        case SYM_CLASSVARDEF:
        {
            // sym_vardef_t p = sym_vardef_new(SYM_VARDEF, （type_t)type_basic_new(TYPE_INT));
            break;
        }
        case SYM_FUNCDEF:
        {

            break;
        }
        case SYM_CLASSDEF:
        {

            break;
        }
    }

    sym_vardef_t p = sym_vardef_new(SYM_LOCALVARDEF, (type_t)type_basic_new(TYPE_INT, mock_loc));
    return (sym_t)p;
}

