/*
 * sema_symtab.h
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef SEMA_SYMTAB_H
#define SEMA_SYMTAB_H

#include "sema_common.h"

/*
 * @brief: kind of symbol
 */
typedef enum symbol_kind {
    SYMBOL_VAR_DEF,
    SYMBOL_FUNC_NORMAL_DEF,
    SYMBOL_FUNC_ANONY_DEF,
    SYMBOL_CLASS_DEF
} symbol_kind_t;

/*
 * @brief: symbol_t , to store symbol name, def_t and offset(other information)
 */
typedef struct _symbol_ *symbol_t;

struct _symbol_ {
    symbol_kind_t kind;
    yyltype loc;
    const char *id;
    void *def;      // def_t
    int offset;
};

/*
 * @brief: symbol table
 */
typedef struct _symtab_ *symtab_t;

struct _symtab_ {
    // symtab_kind_t kind;
    stack_t table;      ///< stack_t <symbol_t>
    int num_symbols;
};

/*
 * @brief: create a empty symbol table
 */
symtab_t symtab_new(void);

/*
 * @brief: search symbol in symbol table with id
 * @return: NULL/symbol_t
 */
symbol_t symtab_lookup(symtab_t symtab, const char *id);


/*
 * @brief: insert a new symbol to symbol table
 */
symtab_t symtab_enter(symtab_t symtab, symbol_t symbol);

#endif /* !SEMA_SYMTAB_H */
