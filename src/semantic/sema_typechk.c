/*
 * sema_typechk.c
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed underf terms of the MIT license.
 */

#include "sema_typechk.h"
#include "sema_symtab.h"

int typechk_failed = 0;

extern scope_t glb_scope;

char *type_name(type_t node) {
    char *typestr = (char *)malloc(sizeof(char) * 80);
    memset(typestr, '\0', 80);

    if (node == NULL) {
        return typestr;
    }

    switch (node->kind) {
        case TYPE_INT:
            strcat(typestr, "int");
            break;
        case TYPE_BOOL:
            strcat(typestr, "bool");
            break;
        case TYPE_STRING:
            strcat(typestr, "string");
            break;
        case TYPE_VOID:
            strcat(typestr, "void");
            break;
        case TYPE_CLASS:
        {
            type_class_t p = (type_class_t)node;
            strcat(typestr, "class ");
            strcat(typestr, p->class_id);
            break;
        }
        case TYPE_ARRAY:
        {
            type_array_t p = (type_array_t)node;
            char *arr_type = type_name(p->type);
            strcat(typestr, "array of ");
            strcat(typestr, arr_type);
            break;
        }
        default:
            typechk_failed = 1;
            dragon_report(node->loc, "unkown type");
            break;
    }

    return typestr;
}

int typechk(type_t left, type_t right) {
    int equality;

    if (left == NULL || right == NULL) {
        equality = 0;
        return equality;
    }

    if (left->kind != right->kind) {
        equality = 0;
    } else if (left->kind == TYPE_INT ||
                left->kind == TYPE_BOOL ||
                left->kind == TYPE_STRING ||
                left->kind == TYPE_VOID) {
        equality = 1;
    } else if (left->kind == TYPE_CLASS) {
        type_class_t l = (type_class_t)left;
        type_class_t r = (type_class_t)right;
        equality = !strcmp(l->class_id, r->class_id);
    } else if (left->kind == TYPE_ARRAY) {
        type_array_t l = (type_array_t)left;
        type_array_t r = (type_array_t)right;
        equality = typechk(l->type, r->type);
    } else {
        equality = 0;
        typechk_failed = 1;
        dragon_report(left->loc, "unkown type");
    }

    return equality;
}

type_t type_typechk(type_t node) {
    if (node == NULL) {
        return NULL;
    }

    if (node->kind == TYPE_CLASS) {
        type_class_t p = (type_class_t)node;
        symbol_t class_def = scope_lookup(glb_scope, p->class_id);

        if (class_def == NULL) {
            typechk_failed = 1;
            dragon_report(node->loc, "undefined class '%s'", p->class_id);
        }
    } else if (node->kind == TYPE_ARRAY) {
        type_array_t p = (type_array_t)node;
        p->type = type_typechk(p->type);
    }

    return node;
}

type_t const_typechk(const_t node) {
    type_t ret;   ///< store result of type check

    switch (node->kind) {
        case CONST_INT:
            ret = (type_t)type_basic_new(TYPE_INT, node->loc);
            ret->env = node->env;
            break;
        case CONST_BOOL:
            ret = (type_t)type_basic_new(TYPE_BOOL, node->loc);
            ret->env = node->env;
            break;
        case CONST_STRING:
            ret = (type_t)type_basic_new(TYPE_STRING, node->loc);
            ret->env = node->env;
            break;
        case CONST_NIL:
            ret = (type_t)type_basic_new(TYPE_VOID, node->loc);
            ret->env = node->env;
            break;
        default:
            ret = (type_t)type_basic_new(TYPE_VOID, node->loc);
            ret->env = node->env;
            typechk_failed = 1;
            dragon_report(node->loc, "unkown const");
            break;
    }

    return ret;
}

type_t var_def_typechk(var_def_t node) {
    type_t left = type_typechk((type_t)node->type);

    if (node->initializer) {
        type_t right = expr_typechk((expr_t)node->initializer);

        if (!typechk(left, right)) {
            typechk_failed = 1;
            dragon_report(node->loc, "incompatible types when assigning to type '%s' from type '%s'", type_name(left), type_name(right));
        }
    }

    return left;
}

type_t func_normal_def_typechk(func_normal_def_t node) {
    type_t ret_def = type_typechk((type_t)node->type);
    type_t ret_stmt = NULL;

    list_t stmts = node->stmts;
    stmt_t stmt = NULL;

    // search return statement node
    while (stmts) {
        stmt = (stmt_t)stmts->data;

        if (stmt->kind == STMT_RETURN) {
            ret_stmt = stmt_typechk(stmt);
            break;
        }

        stmts = stmts->next;
    }

    if (stmt == NULL || ret_stmt == NULL) {
        typechk_failed = 1;
        dragon_report(node->loc, "missing return statement in function '%s'", node->id);
        ret_stmt = (type_t)type_basic_new(TYPE_VOID, node->loc);
        ret_stmt->env = node->scope;
        stmt = (stmt_t)ret_stmt;
    }

    if (!typechk(ret_def, ret_stmt)) {
        typechk_failed = 1;
        dragon_report(stmt->loc, "incompatible types when returning type '%s' but '%s' was expected in function '%s'",
                type_name(ret_stmt), type_name(ret_def), node->id);
    }

    stmts_typechk(node->stmts);

    return ret_def;
}

void class_def_typechk(class_def_t node) {
    fields_typechk(node->fields);
}

void class_defs_typechk(list_t class_defs) {
    for (list_t list = class_defs; list != NULL; list = list->next) {
        class_def_t c = (class_def_t)list->data;
        class_def_typechk(c);
    }
}

type_t expr_bool_typechk(expr_bool_t node) {
    type_t ret = expr_typechk((expr_t)node->body);
    return ret;
}

type_t expr_assign_typechk(expr_assign_t node) {
    type_t left = expr_typechk((expr_t)node->left);
    type_t right = expr_typechk((expr_t)node->right);

    if (!typechk(left, right)) {
        typechk_failed = 1;
        dragon_report(node->left->loc, "incompatible types when assigning to type '%s' from type '%s'", type_name(left), type_name(right));
    }

    return left;
}

type_t expr_or_typechk(expr_or_t node) {
    type_t left = expr_typechk((expr_t)node->left);
    type_t right = expr_typechk((expr_t)node->right);

    if (!typechk(left, right)) {
        typechk_failed = 1;
        dragon_report(node->loc, "incompatible logical types between type '%s' and type '%s'", type_name(left), type_name(right));
    } else if (left->kind == TYPE_CLASS || left->kind == TYPE_ARRAY) {
        typechk_failed = 1;
        dragon_report(node->loc, "used '%s' type where scalar is required", type_name(left));
    }

    return left;
}

type_t expr_and_typechk(expr_and_t node) {
    type_t left = expr_typechk((expr_t)node->left);
    type_t right = expr_typechk((expr_t)node->right);

    if (!typechk(left, right)) {
        typechk_failed = 1;
        dragon_report(node->loc, "incompatible logical types between type '%s' and type '%s'", type_name(left), type_name(right));
    } else if (left->kind == TYPE_CLASS || left->kind == TYPE_ARRAY) {
        typechk_failed = 1;
        dragon_report(node->loc, "used '%s' type where scalar is required", type_name(left));
    }

    return left;
}

type_t expr_eq_typechk(expr_eq_t node) {
    type_t left = expr_typechk((expr_t)node->left);
    type_t right = expr_typechk((expr_t)node->right);

    if (!typechk(left, right)) {
        typechk_failed = 1;
        dragon_report(node->loc, "incompatible logical types between type '%s' and type '%s'", type_name(left), type_name(right));
    } else if (left->kind == TYPE_CLASS || left->kind == TYPE_ARRAY) {
        typechk_failed = 1;
        dragon_report(node->loc, "used '%s' type where scalar is required", type_name(left));
    }

    return left;
}

type_t expr_cmp_typechk(expr_cmp_t node) {
    type_t left = expr_typechk((expr_t)node->left);
    type_t right = expr_typechk((expr_t)node->right);

    if (!typechk(left, right)) {
        typechk_failed = 1;
        dragon_report(node->loc, "incompatible logical types between type '%s' and type '%s'", type_name(left), type_name(right));
    } else if (left->kind == TYPE_CLASS || left->kind == TYPE_ARRAY) {
        typechk_failed = 1;
        dragon_report(node->loc, "used '%s' type where scalar is required", type_name(left));
    }

    return left;
}

type_t expr_add_typechk(expr_add_t node) {
    type_t left = expr_typechk((expr_t)node->left);
    type_t right = expr_typechk((expr_t)node->right);

    if (!typechk(left, right) || left->kind != TYPE_INT) {
        typechk_failed = 1;
        dragon_report(node->loc, "incompatible arithmetic types between type '%s' and type '%s', expected type 'int'", type_name(left), type_name(right));
    }

    return left;
}

type_t expr_mul_typechk(expr_mul_t node) {
    type_t left = expr_typechk((expr_t)node->left);
    type_t right = expr_typechk((expr_t)node->right);

    if (!typechk(left, right) || left->kind != TYPE_INT) {
        typechk_failed = 1;
        dragon_report(node->loc, "incompatible arithmetic types between type '%s' and type '%s', expected type 'int'", type_name(left), type_name(right));
    }

    return left;
}

type_t expr_unary_typechk(expr_unary_t node) {
    type_t ret = expr_typechk((expr_t)node->body);

    switch (node->sub_kind) {
        case EXPR_UNARY_PLUS:
        case EXPR_UNARY_MINUS:
            if (ret->kind != TYPE_INT) {
                typechk_failed = 1;
                dragon_report(node->loc, "wrong type argument to unary plus/minus");
            }
            break;
        case EXPR_UNARY_NOT:
            if (ret->kind == TYPE_CLASS || ret->kind == TYPE_ARRAY) {
                typechk_failed = 1;
                dragon_report(node->loc, "used '%s' type where scalar is required", type_name(ret));
            }
            break;
        default:
            typechk_failed = 1;
            dragon_report(node->loc, "unkown unary expression");
            break;
    }

    return ret;
}

type_t expr_left_typechk(expr_left_t node) {
    type_t ret;

    switch (node->sub_kind) {
        case EXPR_LEFT_INDEX:
        {
            expr_left_index_t p = (expr_left_index_t)node;
            type_t array = expr_typechk((expr_t)p->array);
            type_t index = expr_typechk((expr_t)p->index);

            if (array->kind != TYPE_ARRAY) {
                ret = (type_t)type_basic_new(TYPE_VOID, p->loc);
                ret->env = p->env;
                typechk_failed = 1;
                dragon_report(p->array->loc, "subscripted value is neither array nor vector");
            } else {
                type_array_t arr = (type_array_t)array;
                ret = type_typechk(arr->type);
            }

            if (index->kind != TYPE_INT) {
                typechk_failed = 1;
                dragon_report(p->index->loc, "array subscript is not an integer");
            }

            break;
        }
        case EXPR_LEFT_CLASS_FIELD:
        {
            expr_left_class_field_t p = (expr_left_class_field_t)node;

            if (p->left->sub_kind != EXPR_LEFT_THIS) {
                ret = (type_t)type_basic_new(TYPE_VOID, p->loc);
                ret->env = p->env;
                typechk_failed = 1;
                dragon_report(p->loc, "invalid access to private class field");
            } else {
                symbol_t symbol = scope_lookup(p->env->parent, p->field_id);

                if (symbol == NULL) {
                    ret = (type_t)type_basic_new(TYPE_VOID, p->loc);
                    ret->env = p->env;
                    typechk_failed = 1;
                    dragon_report(p->loc, "invalid access to non-exist class field");
                } else {
                    if (symbol->kind == SYMBOL_CLASS_DEF) {
                        ret = (type_t)type_basic_new(TYPE_VOID, p->loc);
                        ret->env = p->env;
                        typechk_failed = 1;
                        dragon_report(p->loc, "invalid access to non-exist class field");
                    } else {
                        ret = symbol->type;
                    }
                }
            }

            break;
        }
        case EXPR_LEFT_CLASS_CALL:
        {
            expr_left_class_call_t p = (expr_left_class_call_t)node;
            type_t _left = expr_typechk((expr_t)p->left);

            if (_left->kind == TYPE_CLASS) {
                type_class_t left = (type_class_t)_left;
                symbol_t class_def = scope_lookup(glb_scope, left->class_id);

                // class not exist
                if (class_def == NULL) {
                    ret = (type_t)type_basic_new(TYPE_VOID, p->loc);
                    ret->env = p->env;
                    typechk_failed = 1;
                    dragon_report(p->left->loc, "undefined class '%s'", left->class_id);
                    break;
                }

                class_def_t _class_def = (class_def_t)class_def->def;
                symbol_t symbol = scope_lookup(_class_def->scope, p->field_id);

                // field not exist
                if (symbol == NULL) {
                    ret = (type_t)type_basic_new(TYPE_VOID, p->loc);
                    ret->env = p->env;
                    typechk_failed = 1;
                    dragon_report(p->loc, "invalid access to non-exist class field");
                } else {
                    func_normal_def_t func = (func_normal_def_t)symbol->def;

                    // this is a class_def symbol(not a variable)
                    if (symbol->kind == SYMBOL_CLASS_DEF) {
                        ret = (type_t)type_basic_new(TYPE_VOID, p->loc);
                        ret->env = p->env;
                        typechk_failed = 1;
                        dragon_report(p->left->loc, "invalid access to non-exist class field");
                    } else if (!arguments_typechk(func->formals, p->actuals)) {
                        ret = func->type;
                        typechk_failed = 1;
                        dragon_report(((actual_t)p->actuals->data)->loc, "incompatible arguments when call '%s'", func->id);
                    } else {
                        ret = func->type;
                    }
                }
            } else {
                // left is not class
                ret = (type_t)type_basic_new(TYPE_VOID, p->loc);
                ret->env = p->env;
                typechk_failed = 1;
                dragon_report(p->left->loc, "invalid access to field of a non-class variable");
            }

            break;
        }
        case EXPR_LEFT_FUNC_CALL:
        {
            expr_left_func_call_t p = (expr_left_func_call_t)node;
            symbol_t symbol = scope_lookup(p->env->parent, p->id);

            // function not exist in this scope
            if (symbol == NULL) {
                ret = (type_t)type_basic_new(TYPE_VOID, p->loc);
                ret->env = p->env;
                typechk_failed = 1;
                dragon_report(p->loc, "invalid access to non-exist class field");
            } else {
                ret = symbol->type;
                func_normal_def_t func = (func_normal_def_t)symbol->def;

                // this is a class_def symbol(not a function)
                if (symbol->kind == SYMBOL_CLASS_DEF) {
                    ret = (type_t)type_basic_new(TYPE_VOID, p->loc);
                    ret->env = p->env;
                    typechk_failed = 1;
                    dragon_report(p->loc, "invalid access to non-exist class field");
                } else if (!arguments_typechk(func->formals, p->actuals)) {
                    ret = func->type;
                    typechk_failed = 1;
                    dragon_report(((actual_t)p->actuals->data)->loc, "incompatible arguments when call '%s'", func->id);
                } else {
                    ret = func->type;
                }
            }

            break;
        }
        case EXPR_LEFT_ANONY_CALL:
        {
            expr_left_anony_call_t p = (expr_left_anony_call_t)node;
            func_anony_def_t func = p->func_body;

            // function type check
            ret = func_normal_def_typechk((func_normal_def_t)func);
            // actual arguments type check
            actuals_typechk(p->actuals);

            // type check between formal and actual arguments
            if (!arguments_typechk(func->formals, p->actuals)) {
                    typechk_failed = 1;
                    dragon_report(((actual_t)p->actuals->data)->loc, "incompatible arguments when call this anonymous function");
            }

            break;
        }
        default:
            ret = (type_t)type_basic_new(TYPE_VOID, node->loc);
            ret->env = node->env;
            typechk_failed = 1;
            dragon_report(node->loc, "unkown expression");
            break;
    }

    return ret;
}

type_t expr_prim_typechk(expr_prim_t p) {
    type_t ret;

    switch (p->sub_kind) {
        case EXPR_PRIM_IDENT:
        {
            expr_prim_ident_t pp = (expr_prim_ident_t)p;
            symbol_t symbol = scope_lookup(pp->env, pp->id);

            if (symbol == NULL) {
                ret = (type_t)type_basic_new(TYPE_VOID, pp->loc);
                ret->env = pp->env;
                typechk_failed = 1;
                dragon_report(pp->loc, "undefined identifier '%s'", pp->id);
            } else {
                ret = symbol->type;
            }
            break;
        }
        case EXPR_PRIM_CONST:
        {
            expr_prim_const_t pp = (expr_prim_const_t)p;
            ret = const_typechk(pp->const_val);
            break;
        }
        case EXPR_PRIM_READINT:
        {
            expr_prim_read_t pp = (expr_prim_read_t)p;
            ret = type_basic_new(TYPE_INT, pp->loc);
            ret->env = pp->env;
            break;
        }
        case EXPR_PRIM_READLINE:
        {
            expr_prim_read_t pp = (expr_prim_read_t)p;
            ret = type_basic_new(TYPE_STRING, pp->loc);
            ret->env = pp->env;
            break;
        }
        case EXPR_PRIM_NEWCLASS:
        {
            expr_prim_newclass_t pp = (expr_prim_newclass_t)p;

            symbol_t class_def = scope_lookup(glb_scope, pp->id);

            if (class_def == NULL) {
                ret = (type_t)type_basic_new(TYPE_VOID, pp->loc);
                ret->env = pp->env;
                typechk_failed = 1;
                dragon_report(p->loc, "undefined class '%s'", pp->id);
            } else {
                ret = type_class_new(TYPE_CLASS, pp->loc, pp->id);
                ret->env = pp->env;
            }

            break;
        }
        case EXPR_PRIM_NEWARRAY:
        {
            expr_prim_newarray_t pp = (expr_prim_newarray_t)p;

            type_t length = expr_typechk(pp->length);

            if (length->kind != TYPE_INT) {
                typechk_failed = 1;
                dragon_report(pp->length->loc, "array subscript is not an integer");
            }

            type_t arr_type = type_typechk(pp->type);
            ret = type_array_new(TYPE_ARRAY, arr_type->loc, arr_type);
            ret->env = arr_type->env;

            break;
        }
        default:
            ret = (type_t)type_basic_new(TYPE_VOID, p->loc);
            ret->env = p->env;
            typechk_failed = 1;
            dragon_report(p->loc, "unkown unary expression");
    }

    return ret;
}

type_t expr_typechk(expr_t node) {
    type_t ret;

    switch (node->kind) {
        case EXPR_BOOL:
        {
            expr_bool_t p = (expr_bool_t)node;
            ret = expr_bool_typechk(p);
            break;
        }
        case EXPR_ASSIGN:
        {
            expr_assign_t p = (expr_assign_t)node;
            ret = expr_assign_typechk(p);
            break;
        }
        case EXPR_OR:
        {
            expr_or_t p = (expr_or_t)node;
            ret = expr_or_typechk(p);
            break;
        }
        case EXPR_AND:
        {
            expr_and_t p = (expr_and_t)node;
            ret = expr_and_typechk(p);
            break;
        }
        case EXPR_EQ:
        {
            expr_eq_t p = (expr_eq_t)node;
            ret = expr_eq_typechk(p);
            break;
        }
        case EXPR_CMP:
        {
            expr_cmp_t p = (expr_cmp_t)node;
            ret = expr_cmp_typechk(p);
            break;
        }
        case EXPR_ADD:
        {
            expr_add_t p = (expr_add_t)node;
            ret = expr_add_typechk(p);
            break;
        }
        case EXPR_MUL:
        {
            expr_mul_t p = (expr_mul_t)node;
            ret = expr_mul_typechk(p);
            break;
        }
        case EXPR_UNARY:
        {
            expr_unary_t p = (expr_unary_t)node;
            ret = expr_unary_typechk(p);
            break;
        }
        case EXPR_LEFT:
        {
            expr_left_t p = (expr_left_t)node;
            ret = expr_left_typechk(p);
            break;
        }
        case EXPR_PRIM:
        {
            expr_prim_t p = (expr_prim_t)node;
            ret = expr_prim_typechk(p);
            break;
        }
        default:
            ret = (type_t)type_basic_new(TYPE_VOID, node->loc);
            ret->env = node->env;
            typechk_failed = 1;
            dragon_report(node->loc, "unkown expression");
            break;
    }

    return ret;
}

void assigns_typechk(list_t assigns) {
    for (list_t list = assigns; list != NULL; list = list->next) {
        expr_t p = (expr_t)list->data;
        expr_typechk(p);
    }
}

type_t stmt_typechk(stmt_t node) {
    type_t ret;

    switch (node->kind) {
        case STMT_VAR_DEF:
        {
            stmt_var_def_t p = (stmt_var_def_t)node;
            ret = var_def_typechk(p->var_def);
            break;
        }
        case STMT_EXPR:
        {
            stmt_expr_t p = (stmt_expr_t)node;

            if (p->expr) {
                ret = expr_typechk(p->expr);
            } else {
                ret = (type_t)type_basic_new(TYPE_VOID, p->loc);
                ret->env = p->env;
            }

            break;
        }
        case STMT_IF:
        {
            stmt_if_t p = (stmt_if_t)node;

            expr_typechk((expr_t)p->cond);
            stmts_typechk(p->body_then);

            if (p->body_else) {
                stmts_typechk(p->body_else);
            }

            ret = (type_t)type_basic_new(TYPE_VOID, p->loc);
            ret->env = p->env;
            break;
        }
        case STMT_WHILE:
        {
            stmt_while_t p = (stmt_while_t)node;
            expr_typechk((expr_t)p->cond);
            stmts_typechk(p->body);

            ret = (type_t)type_basic_new(TYPE_VOID, p->loc);
            ret->env = p->env;
            break;
        }
        case STMT_FOR:
        {
            stmt_for_t p = (stmt_for_t)node;

            assigns_typechk(p->initializer);
            assigns_typechk(p->assigner);
            expr_typechk((expr_t)p->cond);
            stmts_typechk(p->body);

            ret = (type_t)type_basic_new(TYPE_VOID, p->loc);
            ret->env = p->env;
            break;
        }
        case STMT_RETURN:
        {
            stmt_return_t p = (stmt_return_t)node;

            if (p->ret_val) {
                ret = expr_typechk(p->ret_val);
            } else {
                ret = (type_t)type_basic_new(TYPE_VOID, p->loc);
                ret->env = p->env;
            }

            break;
        }
        case STMT_PRINT:
        {
            stmt_print_t p = (stmt_print_t)node;
            ret = expr_typechk(p->out);
            break;
        }
        default:
            ret = (type_t)type_basic_new(TYPE_VOID, node->loc);
            ret->env = node->env;
            break;
    }

    return ret;
}

void stmts_typechk(list_t stmts) {
    for (list_t list = stmts; list != NULL; list = list->next) {
        stmt_t stmt = (stmt_t)list->data;
        stmt_typechk(stmt);
    }
}

type_t formal_typechk(formal_t node) {
    return type_typechk(node->type);
}

int arguments_typechk(list_t formals, list_t actuals) {
    while (formals != NULL && actuals != NULL) {
        formal_t formal = (formal_t)formals->data;
        actual_t actual = (actual_t)actuals->data;

        if (!typechk(formal_typechk(formal) , actual_typechk(actual))) {
            return 0;
        }

        formals = formals->next;
        actuals = actuals->next;
    }

    if (formals != NULL || actuals != NULL) {
        return 0;
    }

    return 1;
}

void formals_typechk(list_t formals) {
    for (list_t list = formals; list != NULL; list = list->next) {
        formal_t formal = (formal_t)list->data;
        formal_typechk(formal);
    }
}

type_t actual_typechk(actual_t node) {
    return expr_typechk(node->expr);
}

void actuals_typechk(list_t actuals) {
    for (list_t list = actuals; list != NULL; list = list->next) {
        actual_t actual = (actual_t)list->data;
        actual_typechk(actual);
    }
}

type_t field_typechk(field_t node) {
    type_t ret;

    switch (node->kind) {
        case FIELD_VAR:
        {
            field_var_t p = (field_var_t)node;
            ret = var_def_typechk(p->var_def);

            // field should be initialized when defined
            if (p->var_def->initializer == NULL) {
                typechk_failed = 1;
                dragon_report(p->var_def->loc, "field member should be initialized when defined");
            } else if (p->var_def->initializer->kind != EXPR_PRIM){
                typechk_failed = 1;
                dragon_report(p->var_def->loc, "field member should be initialized only by constant creator");
            } else {
                expr_prim_t pp = (expr_prim_t)p->var_def->initializer;

                if (pp->sub_kind != EXPR_PRIM_CONST && pp->sub_kind != EXPR_PRIM_NEWCLASS && pp->sub_kind != EXPR_PRIM_NEWARRAY) {
                    typechk_failed = 1;
                    dragon_report(p->var_def->loc, "field member should be initialized only by constant creator");
                }
            }

            break;
        }
        case FIELD_FUNC:
        {
            field_func_t p = (field_func_t)node;

            if (p->func_def->kind == FUNC_NORMAL_DEF) {
                func_normal_def_t pp = (func_normal_def_t)p->func_def;
                ret = func_normal_def_typechk(pp);
            } else {
                ret = (type_t)type_basic_new(TYPE_VOID, p->loc);
                ret->env = p->env;
            }

            break;
        }
        default:
            ret = (type_t)type_basic_new(TYPE_VOID, node->loc);
            ret->env = node->env;
            break;
    }

    return ret;
}

void fields_typechk(list_t fields) {
    for (list_t list = fields; list != NULL; list = list->next) {
        field_t field = (field_t)list->data;
        field_typechk(field);
    }
}

void prog_typechk(prog_t prog) {
    class_defs_typechk(prog->class_defs);
}
