/*
 * sema_symtab.h
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef SEMA_SYMTAB_H
#define SEMA_SYMTAB_H

#include "sema_common.h"

int symtab_failed = 0;

/*
 * @brief: symbol_t , to store symbol name, def_t and offset(other information)
 */
typedef struct _symbol_ *symbol_t;

struct _symbol_ {
    const char *id;
    yyltype loc;
    void *def;      // def_t
    int offset;
};

/*
 * @brief: kind of symbol table
 */
/* typedef enum sym_kind { */
/*     SYMTAB_LOCALVARDEF, */
/*     SYMTAB_CLASSVARDEF, */
/*     SYMTAB_FUNCDEF, */
/*     SYMTAB_CLASSDEF */
/* } symtab_kind_t; */

/*
 * @brief: symbol table
 */
typedef _symtab_ *symtab_t;

struct _symtab_ {
    // symtab_kind_t kind;
    stack_t table;      ///< stack_t <symbol_t>
    int num_symbols;
};

/*
 * @mock: temporary for testing
 * @TODO: implements truly symtab_lookup function
 */
sym_t symtab_lookup(symtab_t symtab, const char *id);

#endif /* !SEMA_SYMTAB_H */
