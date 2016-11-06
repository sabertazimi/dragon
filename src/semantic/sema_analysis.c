/*
 * sema_analysis.c
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "sema_analysis.h"

extern int symtab_failed;
extern int typechk_failed;

scope_t glb_scope;

int sema_analysis(prog_t prog) {
    scope_setup(prog);
    prog_typechk(prog);

    if (symtab_failed == 1 || typechk_failed == 1) {
        return 0;
    } else {
        return 1;
    }
}

static void scope_setup_glb(prog_t prog);
static void scope_setup_class_def(class_def_t class_def);

/*
 * @TODO: add defs to scope
 * @TODO: re-direct env and env->parent
 * @TODO: re-direct scope->parent and scope->super
 */

void scope_setup(prog_t prog) {
    scope_setup_glb(prog);

    for (list_t class_defs = prog->class_defs; class_defs != NULL; class_defs = class_defs->next) {
        class_def_t class_def = (class_def_t)class_defs->data;
        scope_setup_class_def(class_def);
        class_def->scope->parent = glb_scope;

        // has super class
        if (strcmp(class_def->super, "\0")) {
            for (list_t super_defs = prog->class_defs; super_defs != NULL; super_defs = super_defs->next) {
                class_def_t super_def = (class_def_t)super_defs->data;

                if (!strcmp(class_def->super, super_def->id)) {
                    class_def->scope->super = class_def->scope;
                }
            }
        }
    }
}

static void scope_setup_glb(prog_t prog) {
    // set up global scope: add all class_def_t to global scope
    glb_scope = scope_new(NULL, NULL, symtab_new(), NULL, NULL, NULL);
    for (list_t class_defs = prog->class_defs; class_defs != NULL; class_defs = class_defs->next) {
        class_def_t class_def = (class_def_t)class_defs->data;
        scope_enter(glb_scope, symbol_new(SYMBOL_CLASS_DEF, class_def->loc, class_def->id, class_def));
    }
}

static void scope_setup_class_def(class_def_t class_def) {
    for (list_t fields = class_def->fields; fields != NULL; fields = fields->next) {
        field_t field = (field_t)fields->data;
        if (field->kind == FIELD_VAR) {
            // scope_setup_var_def((var_def_t)field);
            // field->env->parent;
        }
    }
}
