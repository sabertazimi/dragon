/*
 * sema_symtab.c
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "sema_symtab.h"

/*
 * @brief: for error report to users
 */
extern void dragon_report(yyltype, const char *, ...);

/*
 * @brief: for get name of type
 */
// extern char *type_name(type_t node);

int symtab_failed = 0;

/*
 * @brief: for offset address of symbol
 */
int field_var_offset = 0;
int var_def_offset = 0;
int formal_def_offset = 0;
int func_normal_def_offset = 0;
int class_def_offset = 0;
int cnt_offset = 0;

symbol_t symbol_new(symbol_kind_t kind, yyltype loc, const char *id, void *type, void *def) {
    symbol_t symbol = (symbol_t)malloc(sizeof(*symbol));
    symbol->kind = kind;
    symbol->loc = loc;
    symbol->id = strdup(id);
    symbol->type = type;
    symbol->def = def;

    switch (kind) {
        case SYMBOL_VAR_DEF:
            symbol->offset = var_def_offset++;
            break;
        case SYMBOL_FORMAL_DEF:
            symbol->offset = formal_def_offset++;
            break;
        case SYMBOL_FUNC_NORMAL_DEF:
            symbol->offset = func_normal_def_offset++;
            break;
        case SYMBOL_CLASS_DEF:
            symbol->offset = class_def_offset++;
            break;
        default:
            symbol->offset = cnt_offset++;
            break;
    }

    return symbol;
}

symtab_t symtab_new(void) {
    symtab_t symtab = (symtab_t)malloc(sizeof(*symtab));
    symtab->table = stack_new();
    symtab->num_symbols = 0;
    return symtab;
}

symbol_t symtab_lookup(symtab_t symtab, const char *id) {
    if (symtab == NULL) return NULL;

    for (int i = 0; i < symtab->num_symbols; i++) {
        symbol_t symbol = (symbol_t)stack_get(symtab->table, i);

        if (!strcmp(symbol->id, id)) {
            return symbol;
        }
    }

    return NULL;
}

symtab_t symtab_enter(symtab_t symtab, symbol_t symbol) {
    if (symtab == NULL) return NULL;

    symbol_t exist = symtab_lookup(symtab, symbol->id);

    if (exist != NULL) {
        symtab_failed = 1;
        dragon_report(symbol->loc, "redefined '%s'", symbol->id);
        return NULL;
    } else {
        stack_push(symtab->table, symbol);
        symtab->num_symbols += 1;
        return symtab;
    }
}

void symbol_print(symbol_t symbol) {
    if (symbol == NULL) return;

    fprintf(stdout, ">>> kind: %d, id: %s, type: %s, offset: %d\n", symbol->kind, symbol->id, type_name(symbol->type), symbol->offset);
}

void symtab_print(symtab_t symtab) {
    if (symtab == NULL) return;

    for (int i = 0; i < symtab->num_symbols; i++) {
        symbol_print((symbol_t)stack_get(symtab->table, i));
    }
}
