/*
 * sema_symtab.c
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "sema_symtab.h"

static int cnt_offset = 0;

symbol_t symbol_new(const char *id, yyltype loc, void *def) {
    symbol_t symbol = (symbol_t)malloc(sizeof(*symbol));
    symbol->id = strdup(id);
    symbol->loc = loc;
    symbol->def = def;
    symbol->offset = cnt_offset++;
}

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

/*
 * @brief: search symbol in symbol table with id
 * @return: NULL/symbol_t
 */
symbol_t symtab_lookup(symtab_t symtab, const char *id) {
    for (int i = 0; i < symtab->num_symbols; i++) {
        symbol_t symbol = (symbol_t)stack_get(symtab->table, i);

        if (!strcmp(symbol->id, id)) {
            return symbol;
        }
    }

    return NULL;
}

/*
 * @brief: insert a new symbol to symbol table
 */
symtab_t symtab_enter(symtab_t symtab, symbol_t symbol) {
    symbol_t exist = symtab_lookup(symtab, symbol->id)

    if (symtab_lookup(symtab, symbol->id) != NULL) {
        symtab_failed = 1;
        dragon_report(symbol->loc, "redefined %s", symbol->id);
        return NULL;
    } else {
        stack_push(symtab->table, symbol);
        return symtab;
    }
}
