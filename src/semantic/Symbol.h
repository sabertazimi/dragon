/*!
 * \file Symtab.h
 * \brief
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#ifndef SEMA_SYMTAB_H
#define SEMA_SYMTAB_H

#include "semantic/common.h"

/*
 * @brief: kind of symbol
 */
typedef enum symbol_kind {
    SYMBOL_VAR_DEF,
    SYMBOL_FORMAL_DEF,
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
    void *type;     ///< type_t
    void *def;      ///< def_t
    int offset;
};

/*
 * @brief: symbol table
 */
typedef struct _symtab_ *symtab_t;

struct _symtab_ {
    stack_t table;      ///< stack_t <symbol_t>
    int num_symbols;
};

/*
 * @brief: create a new symbol
 */
symbol_t symbol_new(symbol_kind_t kind, yyltype loc, const char *id, void *type, void *def);

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

/*
 * @brief: print symbol
 */
void symbol_print(symbol_t symbol);

/*
 * @brief: print symbol table
 */
void symtab_print(symtab_t symtab);

#endif /* !SEMA_SYMTAB_H */
