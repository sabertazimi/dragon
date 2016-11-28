/*!
 * \file ast_def.cc
 * \brief
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#include "ast_def.h"

using namespace std;

var_def_t var_def_new(yyltype loc, type_t type, string id, expr_assign_t initializer) {
    var_def_t p = (var_def_t)malloc(sizeof(*p));
    p->loc = loc;
    p->type = type;
    p->id = string(id);
    p->initializer = initializer;
    return p;
}

func_def_t func_normal_def_new(func_kind_t kind, yyltype loc, type_t type, list_t formals, list_t stmts, string id) {
    func_normal_def_t p = (func_normal_def_t)malloc(sizeof(*p));
    p->kind = kind;
    p->loc = loc;
    // p->scope = scope_new(NULL, NULL, NULL, symtab_new(), symtab_new(), NULL, symtab_new());
    p->type = type;
    p->formals = formals;
    p->stmts = stmts;
    p->id = string(id);
    return (func_def_t)p;
}

func_def_t func_anony_def_new(func_kind_t kind, yyltype loc, type_t type, list_t formals, list_t stmts) {
    func_anony_def_t p = (func_anony_def_t)malloc(sizeof(*p));
    p->kind = kind;
    p->loc = loc;
    // p->scope = scope_new(NULL, NULL, NULL, symtab_new(), symtab_new(), NULL, symtab_new());
    p->type = type;
    p->formals = formals;
    p->stmts = stmts;
    return (func_def_t)p;
}

class_def_t class_def_new(yyltype loc, string id, string super, list_t fields) {
    class_def_t p = (class_def_t)malloc(sizeof(*p));
    p->loc = loc;
    // p->scope = scope_new(NULL, NULL, NULL, symtab_new(), NULL, symtab_new(), NULL);
    p->id = string(id);
    p->super = string(super);
    p->fields = fields;
    return p;
}