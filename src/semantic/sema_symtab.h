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
typedef enum sym_kind {
    SYM_LOCALVARDEF,
    SYM_CLASSVARDEF,
    SYM_FUNCDEF,
    SYM_CLASSDEF
} sym_kind_t;

/*
 * @interface: sym_t
 */
typedef struct sym *sym_t;

/*
 * @implements: sym_vardef_t
 */
// @TODO: seperate vardef to local vardef and field vardef
// @FIXME
typedef struct sym_vardef *sym_vardef_t;

/*
 * @implements: sym_funcdef_t
 */
typedef struct sym_funcdef *sym_funcdef_t;

/*
 * @implements: sym_classdef_t
 */
typedef struct sym_classdef *sym_classdef_t;

struct sym {
    sym_kind_t kind;
};


struct sym_vardef {
    sym_kind_t kind;
    yyltype loc;
    var_def_t vardef;
    type_t type;
    string id;
    sym_classdef_t classdef;
};

struct sym_funcdef {
    sym_kind_t kind;
    yyltype loc;
    func_normal_def_t funcdef;
    type_t type;
    list_t formals;
    list_t stmts;
    sym_classdef_t classdef;
};

// @TODO: symbol table generation
// 第一次遍历语法树: 查询 var_def_t/func_def_t/class_def_t, 构造符号表
// 先 sym_classdef_new(), 对于所有 sym_vardef_new/sym_funcdef_new, 将生成的结点插入 classdef->sym_vardef_t/sym_funcdef_t 链表
// 遍历完一个 classdef 中所有的 var_def_t/func_def_t 后, 再遍历 sym_vardef_t/sym_funcdef_t 链表, 将所有 sym_vardef/sym_funcdef 结点的 symclassdef 指针指向 classdef 结点

struct sym_classdef {
    sym_kind_t kind;
    yyltype loc;
    class_def_t classdef;
    string id;
    list_t vardefs;     ///< list_t <sym_vardef_t>
    list_t funcdefs;    ///< list_t <sym_funcdef_t>
    // @TODO: scope_t class_scope;
};

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
sym_t sym_vardef_new(sym_kind_t kind, type_t type);

/*
 * @mock: temporary for testing
 * @TODO: implements truly symtab_lookup function
 */
sym_t symtab_lookup(sym_kind_t kind, string id);

#endif /* !SEMA_SYMTAB_H */
