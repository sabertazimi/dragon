/*
 * sema_analysis.c
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "sema_analysis.h"

extern int symtab_failed;
extern int typechk_failed;
extern void dragon_report(yyltype, const char *, ...);

static void scope_setup_glb(prog_t prog);
static void scope_setup_type(type_t node);
static void scope_setup_expr(expr_t node);
static void scope_setup_stmt(stmt_t node);
static void scope_setup_func_normal_def(func_normal_def_t func_def);
static void scope_setup_func_anony_def(func_anony_def_t func_def);
static void scope_setup_class_def(class_def_t class_def);
static void scope_setup_class_defs(list_t class_defs);

scope_t glb_scope;  ///< top scope

int sema_analysis(prog_t prog) {
    scope_setup(prog);
    prog_typechk(prog);

    if (symtab_failed == 1 || typechk_failed == 1) {
        return 0;
    } else {
        return 1;
    }
}

void scope_setup(prog_t prog) {
    scope_setup_glb(prog);
    scope_setup_class_defs(prog->class_defs);
}

static void scope_setup_glb(prog_t prog) {
    // set up global scope: add all class_def_t to global scope
    glb_scope = scope_new(NULL, NULL, symtab_new(), NULL, NULL, NULL, NULL);

    // record Main class exist whether or not
    static int main_class_exist = 0;

    for (list_t class_defs = prog->class_defs; class_defs != NULL; class_defs = class_defs->next) {
        class_def_t class_def = (class_def_t)class_defs->data;
        scope_enter(glb_scope, symbol_new(SYMBOL_CLASS_DEF, class_def->loc, class_def->id, type_class_new(TYPE_CLASS, class_def->loc, class_def->id), class_def));

        if (!strcmp(class_def->id, "Main")) {
            main_class_exist = 1;
        }
    }

    // Main class not exist
    if (main_class_exist == 0) {
        symtab_failed = 1;
        dragon_report(prog->loc, "missing 'Main' class");
    }
}

static void scope_setup_type(type_t node) {
    if (node->kind == TYPE_ARRAY) {
        type_array_t p = (type_array_t)node;
        p->type->env = p->env;
        scope_setup_type(p->type);
    }
}

static void scope_setup_expr(expr_t node) {
    switch (node->kind) {
        case EXPR_BOOL:
        {
            expr_bool_t p = (expr_bool_t)node;
            p->body->env = p->env;
            scope_setup_expr(p->body);
            break;
        }
        case EXPR_ASSIGN:
        {
            expr_assign_t p = (expr_assign_t)node;
            p->left->env = p->env;
            p->right->env = p->env;
            scope_setup_expr((expr_t)p->left);
            scope_setup_expr((expr_t)p->right);
            break;
        }
        case EXPR_OR:
        {
            expr_or_t p = (expr_or_t)node;
            p->left->env = p->env;
            p->right->env = p->env;
            scope_setup_expr((expr_t)p->left);
            scope_setup_expr((expr_t)p->right);
            break;
        }
        case EXPR_AND:
        {
            expr_and_t p = (expr_and_t)node;
            p->left->env = p->env;
            p->right->env = p->env;
            scope_setup_expr((expr_t)p->left);
            scope_setup_expr((expr_t)p->right);
            break;
        }
        case EXPR_EQ:
        {
            expr_eq_t p = (expr_eq_t)node;
            p->left->env = p->env;
            p->right->env = p->env;
            scope_setup_expr((expr_t)p->left);
            scope_setup_expr((expr_t)p->right);
            break;
        }
        case EXPR_CMP:
        {
            expr_cmp_t p = (expr_cmp_t)node;
            p->left->env = p->env;
            p->right->env = p->env;
            scope_setup_expr((expr_t)p->left);
            scope_setup_expr((expr_t)p->right);
            break;
        }
        case EXPR_ADD:
        {
            expr_add_t p = (expr_add_t)node;
            p->left->env = p->env;
            p->right->env = p->env;
            scope_setup_expr((expr_t)p->left);
            scope_setup_expr((expr_t)p->right);
            break;
        }
        case EXPR_MUL:
        {
            expr_mul_t p = (expr_mul_t)node;
            p->left->env = p->env;
            p->right->env = p->env;
            scope_setup_expr((expr_t)p->left);
            scope_setup_expr((expr_t)p->right);
            break;
        }
        case EXPR_UNARY:
        {
            expr_unary_t p = (expr_unary_t)node;
            p->body->env = p->env;
            scope_setup_expr((expr_t)p->body);
            break;
        }
        case EXPR_LEFT:
        {
            expr_left_t p = (expr_left_t)node;

            switch (p->sub_kind) {
                case EXPR_LEFT_THIS:
                    break;
                case EXPR_LEFT_INDEX:
                {
                    expr_left_index_t pp = (expr_left_index_t)p;
                    pp->array->env = pp->env;
                    pp->index->env = pp->env;
                    scope_setup_expr((expr_t)pp->array);
                    scope_setup_expr(pp->index);
                    break;
                }
                case EXPR_LEFT_CLASS_FIELD:
                {
                    expr_left_class_field_t pp = (expr_left_class_field_t)p;
                    pp->left->env = pp->env;
                    scope_setup_expr((expr_t)pp->left);
                    break;
                }
                case EXPR_LEFT_CLASS_CALL:
                {
                    expr_left_class_call_t pp = (expr_left_class_call_t)p;

                    pp->left->env = pp->env;
                    scope_setup_expr((expr_t)pp->left);

                    for (list_t list = pp->actuals; list != NULL; list = list->next) {
                        actual_t actual = (actual_t)list->data;
                        actual->env = pp->env;
                        actual->expr->env = pp->env;
                        scope_setup_expr(actual->expr);
                    }

                    break;
                }
                case EXPR_LEFT_FUNC_CALL:
                {
                    expr_left_func_call_t pp = (expr_left_func_call_t)p;

                    for (list_t list = pp->actuals; list != NULL; list = list->next) {
                        actual_t actual = (actual_t)list->data;
                        actual->env = pp->env;
                        actual->expr->env = pp->env;
                        scope_setup_expr(actual->expr);
                    }

                    break;
                }
                case EXPR_LEFT_ANONY_CALL:
                {
                    expr_left_anony_call_t pp = (expr_left_anony_call_t)p;

                    for (list_t list = pp->actuals; list != NULL; list = list->next) {
                        actual_t actual = (actual_t)list->data;
                        actual->env = pp->env;
                        actual->expr->env = pp->env;
                        scope_setup_expr(actual->expr);
                    }

                    // insert a new def symbol
                    symbol_t symbol = symbol_new(SYMBOL_FUNC_ANONY_DEF, pp->func_body->loc, "\0", pp->func_body->type, pp->func_body);
                    char str[100];
                    sprintf(str, "%d", symbol->offset);
                    symbol->id = strdup(str);
                    scope_enter(pp->env, symbol);

                    pp->func_body->type->env = pp->env;
                    scope_setup_func_anony_def(pp->func_body);

                    // dragon_log("anony func symbol id: %s", symbol->id);

                    break;
                }
            }

            break;
        }
        case EXPR_PRIM:
        {
            expr_prim_t p = (expr_prim_t)node;

            switch (p->sub_kind) {
                case EXPR_PRIM_CONST:
                {
                    expr_prim_const_t pp = (expr_prim_const_t)p;
                    pp->const_val->env = pp->env;
                    break;
                }
                case EXPR_PRIM_NEWCLASS:
                {
                    expr_prim_newclass_t pp = (expr_prim_newclass_t)p;

                    for (list_t list = pp->actuals; list != NULL; list = list->next) {
                        actual_t actual = (actual_t)list->data;
                        actual->env = pp->env;
                        actual->expr->env = pp->env;
                        scope_setup_expr(actual->expr);
                    }

                    break;
                }
                case EXPR_PRIM_NEWARRAY:
                {
                    expr_prim_newarray_t pp = (expr_prim_newarray_t)p;
                    pp->type->env = pp->env;
                    pp->length->env = pp->env;
                    scope_setup_type(pp->type);
                    scope_setup_expr(pp->length);
                    break;
                }
                default:
                    break;
            }

            break;
        }
    }
}

static void scope_setup_stmt(stmt_t node) {
    switch (node->kind) {
        case STMT_EXPR:
        {
            stmt_expr_t p = (stmt_expr_t)node;

            if (p->expr) {
                p->expr->env = p->env;
                scope_setup_expr(p->expr);
            }

            break;
        }
        case STMT_IF:
        {
            stmt_if_t p = (stmt_if_t)node;

            // set up scope list
            p->cond->env = p->env;
            scope_setup_expr((expr_t)p->cond);

            // set up scope list
            for (list_t body = p->body_then; body != NULL; body = body->next) {
                stmt_t s = (stmt_t)body->data;

                if (s->kind == STMT_VAR_DEF) {
                    symtab_failed = 1;
                    dragon_report(s->loc, "invalid variable defination in if statement");
                } else {
                    s->env = p->env;
                    scope_setup_stmt(s);
                }
            }

            // set up scope list
            for (list_t body = p->body_else; body != NULL; body = body->next) {
                stmt_t s = (stmt_t)body->data;

                if (s->kind == STMT_VAR_DEF) {
                    symtab_failed = 1;
                    dragon_report(s->loc, "invalid variable defination in if statement");
                } else {
                    s->env = p->env;
                    scope_setup_stmt(s);
                }
            }

            break;
        }
        case STMT_WHILE:
        {
            stmt_while_t p = (stmt_while_t)node;

            // set up scope list
            p->cond->env = p->env;
            scope_setup_expr((expr_t)p->cond);

            // set up scope list
            for (list_t body = p->body; body != NULL; body = body->next) {
                stmt_t s = (stmt_t)body->data;

                if (s->kind == STMT_VAR_DEF) {
                    symtab_failed = 1;
                    dragon_report(s->loc, "invalid variable defination in if statement");
                } else {
                    s->env = p->env;
                    scope_setup_stmt(s);
                }
            }

            break;
        }
        case STMT_FOR:
        {
            stmt_for_t p = (stmt_for_t)node;

            // set up scope list
            p->cond->env = p->env;
            scope_setup_expr((expr_t)p->cond);

            // set up scope list
            for (list_t list = p->initializer; list != NULL; list = list->next) {
                expr_t e = (expr_t)list->data;
                e->env = p->env;
                scope_setup_expr(e);
            }

            // set up scope list
            for (list_t list = p->assigner; list != NULL; list = list->next) {
                expr_t e = (expr_t)list->data;
                e->env = p->env;
                scope_setup_expr(e);
            }

            // set up scope list
            for (list_t body = p->body; body != NULL; body = body->next) {
                stmt_t s = (stmt_t)body->data;

                if (s->kind == STMT_VAR_DEF) {
                    symtab_failed = 1;
                    dragon_report(s->loc, "invalid variable defination in if statement");
                } else {
                    s->env = p->env;
                    scope_setup_stmt(s);
                }
            }

            break;
        }
        case STMT_RETURN:
        {
            stmt_return_t p = (stmt_return_t)node;

            if (p->ret_val) {
                p->ret_val->env = p->env;
                scope_setup_expr(p->ret_val);
            }

            break;
        }
        case STMT_PRINT:
        {
            stmt_print_t p = (stmt_print_t)node;
            p->out->env = p->env;
            scope_setup_expr(p->out);
            break;
        }
        default:
            break;
    }
}

static void scope_setup_func_normal_def(func_normal_def_t func_def) {
    for (list_t formals = func_def->formals; formals != NULL; formals = formals->next) {
        formal_t formal = (formal_t)formals->data;
        scope_enter(func_def->scope, symbol_new(SYMBOL_FORMAL_DEF, formal->loc, formal->id, formal->type, formal));
        formal->env = func_def->scope;
        formal->type->env = func_def->scope;
        scope_setup_type(formal->type);
    }

    for (list_t stmts = func_def->stmts; stmts != NULL; stmts = stmts->next) {
        stmt_t s = (stmt_t)stmts->data;

        if (s->kind == STMT_VAR_DEF) {
            stmt_var_def_t ss = (stmt_var_def_t)s;
            var_def_t var_def = ss->var_def;

            // insert a new def symbol
            scope_enter(func_def->scope, symbol_new(SYMBOL_VAR_DEF, var_def->loc, var_def->id, var_def->type, var_def));

            // set up scope list
            var_def->env = func_def->scope;
            var_def->type->env = func_def->scope;
            scope_setup_type(var_def->type);

            if (var_def->initializer) {
                var_def->initializer->env = func_def->scope;
                scope_setup_expr((expr_t)var_def->initializer);
            }
        }

        // set up scope list
        s->env = func_def->scope;

        // set up scope of stmt
        scope_setup_stmt(s);
    }
}

static void scope_setup_func_anony_def(func_anony_def_t func_def) {
    for (list_t formals = func_def->formals; formals != NULL; formals = formals->next) {
        formal_t formal = (formal_t)formals->data;
        scope_enter(func_def->scope, symbol_new(SYMBOL_FORMAL_DEF, formal->loc, formal->id, formal->type, formal));
        formal->env = func_def->scope;
        formal->type->env = func_def->scope;
        scope_setup_type(formal->type);
    }

    for (list_t stmts = func_def->stmts; stmts != NULL; stmts = stmts->next) {
        stmt_t s = (stmt_t)stmts->data;

        if (s->kind == STMT_VAR_DEF) {
            stmt_var_def_t ss = (stmt_var_def_t)s;
            var_def_t var_def = ss->var_def;

            // insert a new def symbol
            scope_enter(func_def->scope, symbol_new(SYMBOL_VAR_DEF, var_def->loc, var_def->id, var_def->type, var_def));

            // set up scope list
            var_def->env = func_def->scope;
            var_def->type->env = func_def->scope;
            scope_setup_type(var_def->type);

            if (var_def->initializer) {
                var_def->initializer->env = func_def->scope;
                scope_setup_expr((expr_t)var_def->initializer);
            }
        }

        // set up scope list
        s->env = func_def->scope;

        // set up scope of stmt
        scope_setup_stmt(s);
    }
}

static void scope_setup_class_def(class_def_t class_def) {
    // search for main method of Main class
    static int main_method_exist = 0;

    for (list_t fields = class_def->fields; fields != NULL; fields = fields->next) {
        field_t field = (field_t)fields->data;

        switch (field->kind) {
            case FIELD_VAR:
            {
                field_var_t p = (field_var_t)field;

                // insert new def symbol
                scope_enter(class_def->scope, symbol_new(SYMBOL_VAR_DEF, p->var_def->loc, p->var_def->id, p->var_def->type, p->var_def));

                // set up scope list
                p->env = class_def->scope;
                p->var_def->env = class_def->scope;
                p->var_def->type->env = class_def->scope;
                scope_setup_type(p->var_def->type);

                if (p->var_def->initializer) {
                    p->var_def->initializer->env = class_def->scope;
                    scope_setup_expr((expr_t)p->var_def->initializer);
                }

                break;
            }
            case FIELD_FUNC:
            {
                field_func_t p = (field_func_t)field;

                // ignore anonymous function defination as class field
                if (p->func_def->kind == FUNC_NORMAL_DEF) {
                    func_normal_def_t func_def = (func_normal_def_t)p->func_def;

                    if (!strcmp(class_def->id, "Main")) {
                        if (!strcmp(func_def->id, "main")) {
                            main_method_exist = 1;
                        }
                    }

                    // insert new def symbol
                    scope_enter(class_def->scope, symbol_new(SYMBOL_FUNC_NORMAL_DEF, func_def->loc, func_def->id, func_def->type, func_def));

                    // set up scope list
                    p->env = func_def->scope;
                    func_def->scope->parent = class_def->scope;
                    func_def->type->env = func_def->scope;
                    scope_setup_type(func_def->type);

                    // set up scope of normal function
                    scope_setup_func_normal_def(func_def);
                }

                break;
            }
        }
    }

    // main method not exist in Main class
    if (!strcmp(class_def->id, "Main")) {
        if (main_method_exist == 0) {
            symtab_failed = 1;
            dragon_report(class_def->loc, "missing 'main' method in 'Main' class");
        }
    }
}

static void scope_setup_class_defs(list_t class_defs) {
    for (list_t _class_defs = class_defs; _class_defs != NULL; _class_defs = _class_defs->next) {
        class_def_t class_def = (class_def_t)_class_defs->data;
        class_def->scope->parent = glb_scope;
        scope_setup_class_def(class_def);
    }

    // set up scope link between super class and extends class
    for (list_t _class_defs = class_defs; _class_defs != NULL; _class_defs = _class_defs->next) {
        class_def_t class_def = (class_def_t)_class_defs->data;

        // has super class
        if (strcmp(class_def->super, "\0")) {
            for (list_t super_defs = class_defs; super_defs != NULL; super_defs = super_defs->next) {
                class_def_t super_def = (class_def_t)super_defs->data;

                if (!strcmp(class_def->super, super_def->id)) {
                    class_def->scope->super = super_def->scope;
                    break;
                }
            }
        }
    }

}
