/*
 * sema_symtab.c
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "sema_symtab.h"

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

