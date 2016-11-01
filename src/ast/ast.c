/*
 * ast.c
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

///< space step when print ast tree
#define SPACE_STEP 4

static string cpystr(string text) {
    string str = (string)malloc(sizeof(char) * (strlen(text) + 1));
    strcpy(str, text);
    return str;
}

static void space_print(int num_space) {
    for (int i = 0;i < num_space; i++) {
        fprintf(stdout, " ");
    }
}

void type_print(type_t node, int num_space) {
    space_print(num_space);

    switch (node->kind) {
        case TYPE_INT:
            fprintf(stdout, "type_int");
            break;
        case TYPE_BOOL:
            fprintf(stdout, "type_bool");
            break;
        case TYPE_STRING:
            fprintf(stdout, "type_string");
            break;
        case TYPE_VOID:
            fprintf(stdout, "type_void");
            break;
        case TYPE_CLASS:
        {
            type_class_t p = (type_class_t)node;
            fprintf(stdout, "type_class->%s", p->class_id);
            break;
        }
        case TYPE_ARRAY:
        {
            type_array_t p = (type_array_t)node;
            fprintf(stdout, "type_array->\n");
            type_print(p->type, num_space + SPACE_STEP);
            break;
        }
        default:
            fprintf(stdout, "unkown type");
            exit(1);
            break;
    }

    fprintf(stdout, "\n");
}

type_t type_basic_new(type_kind_t kind) {
    type_basic_t p = (type_basic_t)malloc(sizeof(*p));
    p->kind = kind;
    return (type_t)p;
}

type_t type_class_new(type_kind_t kind, string class_id) {
    type_class_t p = (type_class_t)malloc(sizeof(*p));
    p->kind = kind;
    p->class_id = cpystr(class_id);
    return (type_t)p;
}

type_t type_array_new(type_kind_t kind, type_t type) {
    type_array_t p = (type_array_t)malloc(sizeof(*p));
    p->kind = kind;
    p->type = type;
    return (type_t)p;
}

void const_print(const_t node, int num_space) {
    space_print(num_space);

    switch (node->kind) {
        case CONST_INT:
        {
            const_num_t p = (const_num_t)node;
            fprintf(stdout, "const_int->%d", p->value);
            break;
        }
        case CONST_BOOL:
        {
            const_num_t p = (const_num_t)node;
            fprintf(stdout, "const_bool->%d", !!p->value);
            break;
        }
        case CONST_STRING:
        {
            const_string_t p = (const_string_t)node;
            fprintf(stdout, "const_string->%s", p->text);
            break;
        }
        case CONST_NIL:
            fprintf(stdout, "const_void");
            break;
        default:
            fprintf(stdout, "unkown constant");
            exit(1);
            break;
    }

    fprintf(stdout, "\n");
}

const_t const_num_new(const_kind_t kind, int value) {
    const_num_t p = (const_num_t)malloc(sizeof(*p));
    p->kind = kind;
    p->value = value;
    return (const_t)p;
}

const_t const_string_new(const_kind_t kind, string text) {
    const_string_t p = (const_string_t)malloc(sizeof(*p));
    p->kind = kind;
    p->text = cpystr(text);
    return (const_t)p;
}

const_t const_nil_new(const_kind_t kind) {
    const_nil_t p = (const_nil_t)malloc(sizeof(*p));
    p->kind = kind;
    return (const_t)p;
}

void expr_print(expr_t node, int num_space) {
    space_print(num_space);

    switch (node->kind) {
        case EXPR_BOOL:
        {
            expr_bool_t p = (expr_bool_t)node;
            fprintf(stdout, "expr_bool->\n");
            expr_print(p->body,num_space + SPACE_STEP);
            break;
        }
        case EXPR_ASSIGN:
        {
            expr_assign_t p = (expr_assign_t)node;
            fprintf(stdout, "expr_assign->\n");
            expr_print((expr_t)p->left, num_space + SPACE_STEP);
            expr_print((expr_t)p->right, num_space + SPACE_STEP);
            break;
        }
        case EXPR_OR:
        {
            expr_or_t p = (expr_or_t)node;
            fprintf(stdout, "expr_or->\n");
            expr_print((expr_t)p->left, num_space + SPACE_STEP);
            expr_print((expr_t)p->right, num_space + SPACE_STEP);
            break;
        }
        case EXPR_AND:
        {
            expr_and_t p = (expr_and_t)node;
            fprintf(stdout, "expr_and->\n");
            expr_print((expr_t)p->left, num_space + SPACE_STEP);
            expr_print((expr_t)p->right, num_space + SPACE_STEP);
            break;
        }
        case EXPR_EQ:
        {
            expr_eq_t p = (expr_eq_t)node;

            switch (p->sub_kind) {
                case EXPR_EQ_EQ:
                    fprintf(stdout, "expr_eq->\n");
                    expr_print((expr_t)p->left, num_space + SPACE_STEP);
                    expr_print((expr_t)p->right, num_space + SPACE_STEP);
                    break;
                case EXPR_EQ_NE:
                    fprintf(stdout, "expr_ne->\n");
                    expr_print((expr_t)p->left, num_space + SPACE_STEP);
                    expr_print((expr_t)p->right, num_space + SPACE_STEP);
                    break;
                default:
                    fprintf(stdout, "unkown expr");
                    exit(1);
                    break;
            }

            break;
        }
        case EXPR_CMP:
        {
            expr_cmp_t p = (expr_cmp_t)node;

            switch (p->sub_kind) {
                case EXPR_CMP_LT:
                    fprintf(stdout, "expr_cmp_lt->\n");
                    expr_print((expr_t)p->left, num_space + SPACE_STEP);
                    expr_print((expr_t)p->right, num_space + SPACE_STEP);
                    break;
                case EXPR_CMP_GT:
                    fprintf(stdout, "expr_cmp_gt->\n");
                    expr_print((expr_t)p->left, num_space + SPACE_STEP);
                    expr_print((expr_t)p->right, num_space + SPACE_STEP);
                    break;
                case EXPR_CMP_LE:
                    fprintf(stdout, "expr_cmp_le->\n");
                    expr_print((expr_t)p->left, num_space + SPACE_STEP);
                    expr_print((expr_t)p->right, num_space + SPACE_STEP);
                    break;
                case EXPR_CMP_GE:
                    fprintf(stdout, "expr_cmp_ge->\n");
                    expr_print((expr_t)p->left, num_space + SPACE_STEP);
                    expr_print((expr_t)p->right, num_space + SPACE_STEP);
                    break;
                default:
                    fprintf(stdout, "unkown expr");
                    exit(1);
                    break;
            }

            break;
        }
        case EXPR_ADD:
        {
            expr_add_t p = (expr_add_t)node;

            switch (p->sub_kind) {
                case EXPR_ADD_ADD:
                    fprintf(stdout, "expr_add->\n");
                    expr_print((expr_t)p->left, num_space + SPACE_STEP);
                    expr_print((expr_t)p->right, num_space + SPACE_STEP);
                    break;
                case EXPR_ADD_SUB:
                    fprintf(stdout, "expr_sub->\n");
                    expr_print((expr_t)p->left, num_space + SPACE_STEP);
                    expr_print((expr_t)p->right, num_space + SPACE_STEP);
                    break;
                default:
                    fprintf(stdout, "unkown expr");
                    exit(1);
                    break;
            }

            break;
        }
        case EXPR_MUL:
        {
            expr_mul_t p = (expr_mul_t)node;

            switch (p->sub_kind) {
                case EXPR_MUL_MUL:
                    fprintf(stdout, "expr_mul->\n");
                    expr_print((expr_t)p->left, num_space + SPACE_STEP);
                    expr_print((expr_t)p->right, num_space + SPACE_STEP);
                    break;
                case EXPR_MUL_DIV:
                    fprintf(stdout, "expr_div->\n");
                    expr_print((expr_t)p->left, num_space + SPACE_STEP);
                    expr_print((expr_t)p->right, num_space + SPACE_STEP);
                    break;
                case EXPR_MUL_MOD:
                    fprintf(stdout, "expr_mod->\n");
                    expr_print((expr_t)p->left, num_space + SPACE_STEP);
                    expr_print((expr_t)p->right, num_space + SPACE_STEP);
                    break;
                default:
                    fprintf(stdout, "unkown expr");
                    exit(1);
                    break;
            }

            break;
        }
        case EXPR_UNARY:
        {
            expr_unary_t p = (expr_unary_t)node;

            switch (p->sub_kind) {
                case EXPR_UNARY_THIS:
                    fprintf(stdout, "this");
                    break;
                case EXPR_UNARY_PLUS:
                    fprintf(stdout, "expr_unary_plus->\n");
                    expr_print((expr_t)p->body, num_space + SPACE_STEP);
                    break;
                case EXPR_UNARY_MINUS:
                    fprintf(stdout, "expr_unary_minus->\n");
                    expr_print((expr_t)p->body, num_space + SPACE_STEP);
                    break;
                case EXPR_UNARY_NOT:
                    fprintf(stdout, "expr_unary_not->\n");
                    expr_print((expr_t)p->body, num_space + SPACE_STEP);
                    break;
                default:
                    fprintf(stdout, "unkown expr");
                    exit(1);
                    break;
            }

            break;
        }
        case EXPR_LEFT:
        {
            expr_left_t p = (expr_left_t)node;

            switch (p->sub_kind) {
                case EXPR_LEFT_INDEX:
                {
                    expr_left_index_t pp = (expr_left_index_t)p;
                    fprintf(stdout, "expr_left_array_index->\n");
                    expr_print((expr_t)pp->array, num_space + SPACE_STEP);
                    expr_print((expr_t)pp->index, num_space + SPACE_STEP);
                    break;
                }
                case EXPR_LEFT_CLASS_FIELD:
                {
                    expr_left_class_field_t pp = (expr_left_class_field_t)p;
                    fprintf(stdout, "expr_left_class_field->%s\n", pp->field_id);
                    expr_print((expr_t)pp->left, num_space + SPACE_STEP);
                    break;
                }
                case EXPR_LEFT_CLASS_CALL:
                {
                    expr_left_class_call_t pp = (expr_left_class_call_t)p;
                    fprintf(stdout, "expr_left_class_call->%s\n", pp->field_id);
                    expr_print((expr_t)pp->left, num_space + SPACE_STEP);
                    actuals_print(pp->actuals, num_space + SPACE_STEP);
                    break;
                }
                case EXPR_LEFT_FUNC_CALL:
                {
                    expr_left_func_call_t pp = (expr_left_func_call_t)p;
                    fprintf(stdout, "expr_left_func_call->\n");
                    expr_print((expr_t)pp->left, num_space + SPACE_STEP);
                    actuals_print(pp->actuals, num_space + SPACE_STEP);
                    break;
                }
                case EXPR_LEFT_ANONY_CALL:
                {
                    expr_left_anony_call_t pp = (expr_left_anony_call_t)p;
                    fprintf(stdout, "expr_left_anony_call->\n");
                    func_def_print((func_def_t)pp->func_body, num_space + SPACE_STEP);
                    actuals_print(pp->actuals, num_space + SPACE_STEP);
                    break;
                }
                default:
                    fprintf(stdout, "unkown expr");
                    exit(1);
                    break;
            }

            break;
        }
        case EXPR_PRIM:
        {
            expr_prim_t p = (expr_prim_t)node;

            switch (p->sub_kind) {
                case EXPR_PRIM_IDENT:
                {
                    expr_prim_ident_t pp = (expr_prim_ident_t)p;
                    fprintf(stdout, "expr_prim_ident->%s", pp->id);
                    break;
                }
                case EXPR_PRIM_CONST:
                {
                    expr_prim_const_t pp = (expr_prim_const_t)p;
                    fprintf(stdout, "expr_prim_const_t->\n");
                    const_print(pp->const_val, num_space + SPACE_STEP);
                    break;
                }
                case EXPR_PRIM_READINT:
                {
                    fprintf(stdout, "expr_prim_readint");
                    break;
                }
                case EXPR_PRIM_READLINE:
                {
                    fprintf(stdout, "expr_prim_readline");
                    break;
                }
                case EXPR_PRIM_NEWCLASS:
                {
                    expr_prim_newclass_t pp = (expr_prim_newclass_t)p;
                    fprintf(stdout, "expr_prim_newclass->%s\n", pp->id);
                    actuals_print(pp->actuals, num_space + SPACE_STEP);
                    break;
                }
                case EXPR_PRIM_NEWARRAY:
                {
                    expr_prim_newarray_t pp = (expr_prim_newarray_t)p;
                    fprintf(stdout, "expr_prim_newarray->\n");
                    type_print(pp->type, num_space + SPACE_STEP);
                    expr_print(pp->length, num_space + SPACE_STEP);
                    break;
                }
                default:
                    fprintf(stdout, "unkown expr");
                    exit(1);
                    break;
            }

            break;
        }
        default:
            fprintf(stdout, "unkown expr");
            exit(1);
            break;
    }

    fprintf(stdout, "\n");
}

void assigns_print(list_t assigns, int num_space) {
    space_print(num_space);

    fprintf(stdout, "assigns->\n");

    list_t pf = assigns;

    while (pf) {
        expr_assign_t node = (expr_assign_t)pf->data;

        if (node) {
            expr_print((expr_t)node, num_space + SPACE_STEP);
        }

        pf = pf->next;
    }

    fprintf(stdout, "\n");
}

expr_t expr_prim_ident_new(expr_kind_t kind, expr_prim_kind_t sub_kind, string id) {
    expr_prim_ident_t p = (expr_prim_ident_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->id = cpystr(id);
    return (expr_t)p;
}

expr_t expr_prim_const_new(expr_kind_t kind, expr_prim_kind_t sub_kind, const_t const_val) {
    expr_prim_const_t p = (expr_prim_const_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->const_val = const_val;
    return (expr_t)p;
}

expr_t expr_prim_read_new(expr_kind_t kind, expr_prim_kind_t sub_kind) {
    expr_prim_read_t p = (expr_prim_read_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    return (expr_t)p;
}

expr_t expr_prim_newclass_new(expr_kind_t kind, expr_prim_kind_t sub_kind, string id, list_t actuals) {
    expr_prim_newclass_t p = (expr_prim_newclass_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->id = cpystr(id);
    p->actuals = actuals;
    return (expr_t)p;
}

expr_t expr_prim_newarray_new(expr_kind_t kind, expr_prim_kind_t sub_kind, type_t type, expr_t length) {
    expr_prim_newarray_t p = (expr_prim_newarray_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->type = type;
    p->length = length;
    return (expr_t)p;
}

expr_t expr_left_index_new(expr_kind_t kind, expr_left_kind_t sub_kind, expr_left_t array, expr_t index) {
    expr_left_index_t p = (expr_left_index_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->array = array;
    p->index = index;
    return (expr_t)p;
}

expr_t expr_left_class_field_new(expr_kind_t kind, expr_left_kind_t sub_kind, expr_left_t left, string field_id) {
    expr_left_class_field_t p = (expr_left_class_field_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->left = left;
    p->field_id = cpystr(field_id);
    return (expr_t)p;
}

expr_t expr_left_class_call_new(expr_kind_t kind, expr_left_kind_t sub_kind, expr_left_t left, string field_id, list_t actuals) {
    expr_left_class_call_t p = (expr_left_class_call_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->left = left;
    p->field_id = cpystr(field_id);
    p->actuals = actuals;
    return (expr_t)p;
}

expr_t expr_left_func_call_new(expr_kind_t kind, expr_left_kind_t sub_kind, expr_left_t left, list_t actuals) {
    expr_left_func_call_t p = (expr_left_func_call_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->left = left;
    p->actuals = actuals;
    return (expr_t)p;
}

expr_t expr_left_anony_call_new(expr_kind_t kind, expr_left_kind_t sub_kind, func_anony_def_t func_body, list_t actuals) {
    expr_left_anony_call_t p = (expr_left_anony_call_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->func_body = func_body;
    p->actuals = actuals;
    return (expr_t)p;
}

expr_t expr_unary_new(expr_kind_t kind, expr_unary_kind_t sub_kind, expr_unary_t body) {
    expr_unary_t p = (expr_unary_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->body = body;
    return (expr_t)p;
}

expr_t expr_mul_new(expr_kind_t kind, expr_mul_kind_t sub_kind, expr_mul_t left, expr_unary_t right) {
    expr_mul_t p = (expr_mul_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->left = left;
    p->right = right;
    return (expr_t)p;
}

expr_t expr_add_new(expr_kind_t kind, expr_add_kind_t sub_kind, expr_add_t left, expr_mul_t right) {
    expr_add_t p = (expr_add_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->left = left;
    p->right = right;
    return (expr_t)p;
}

expr_t expr_cmp_new(expr_kind_t kind, expr_cmp_kind_t sub_kind, expr_cmp_t left, expr_add_t right) {
    expr_cmp_t p = (expr_cmp_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->left = left;
    p->right = right;
    return (expr_t)p;
}

expr_t expr_eq_new(expr_kind_t kind, expr_eq_kind_t sub_kind, expr_eq_t left, expr_cmp_t right) {
    expr_eq_t p = (expr_eq_t)malloc(sizeof(*p));
    p->kind = kind;
    p->sub_kind = sub_kind;
    p->left = left;
    p->right = right;
    return (expr_t)p;
}

expr_t expr_and_new(expr_kind_t kind, expr_and_t left, expr_eq_t right) {
    expr_and_t p = (expr_and_t)malloc(sizeof(*p));
    p->kind = kind;
    p->left = left;
    p->right = right;
    return (expr_t)p;
}

expr_t expr_or_new(expr_kind_t kind, expr_or_t left, expr_and_t right) {
    expr_or_t p = (expr_or_t)malloc(sizeof(*p));
    p->kind = kind;
    p->left = left;
    p->right = right;
    return (expr_t)p;
}

expr_t expr_assign_new(expr_kind_t kind, expr_left_t left, expr_assign_t right) {
    expr_assign_t p = (expr_assign_t)malloc(sizeof(*p));
    p->kind = kind;
    p->left = left;
    p->right = right;
    return (expr_t)p;
}

expr_bool_t expr_bool_new(expr_kind_t kind, expr_t body) {
    expr_bool_t p = (expr_bool_t)malloc(sizeof(*p));
    p->kind = kind;
    p->body = body;
    return p;
}

void formals_print(list_t formals, int num_space) {
    space_print(num_space);

    fprintf(stdout, "formals->\n");

    list_t pf = formals;

    while (pf) {
        formal_t node = (formal_t)pf->data;

        if (node) {
            formal_print(node, num_space + SPACE_STEP);
        }

        pf = pf->next;
    }

    fprintf(stdout, "\n");
}

void formal_print(formal_t node, int num_space) {
    space_print(num_space);

    fprintf(stdout, "formal->%s\n", node->id);
    type_print(node->type, num_space + SPACE_STEP);

    fprintf(stdout, "\n");
}

formal_t formal_new(type_t type, string id) {
    formal_t p = (formal_t)malloc(sizeof(*p));
    p->type = type;
    p->id = cpystr(id);
    return p;
}

void actuals_print(list_t actuals, int num_space) {
    space_print(num_space);

    fprintf(stdout, "actuals->\n");

    list_t pf = actuals;

    while (pf) {
        actual_t node = (actual_t)pf->data;

        if (node) {
            actual_print(node, num_space + SPACE_STEP);
        }

        pf = pf->next;
    }

    fprintf(stdout, "\n");
}

void actual_print(actual_t node, int num_space) {
    space_print(num_space);

    fprintf(stdout, "actual->\n");
    expr_print(node->expr, num_space + SPACE_STEP);

    fprintf(stdout, "\n");
}

actual_t actual_new(expr_t expr) {
    actual_t p = (actual_t)malloc(sizeof(*p));
    p->expr = expr;
    return p;
}

void var_def_print(var_def_t node, int num_space) {
    space_print(num_space);

    fprintf(stdout, "var_def->%s\n", node->id);

    type_print(node->type, num_space + SPACE_STEP);
    if (node->initializer) {
        expr_print((expr_t)node->initializer, num_space + SPACE_STEP);
    }

    fprintf(stdout, "\n");
}

var_def_t var_def_new(type_t type, string id, expr_assign_t initializer) {
    var_def_t p = (var_def_t)malloc(sizeof(*p));
    p->type = type;
    p->id = cpystr(id);
    p->initializer = initializer;
    return p;
}

void func_def_print(func_def_t node, int num_space) {
    space_print(num_space);

    switch (node->kind) {
        case FUNC_NORMAL_DEF:
        {
            func_normal_def_t p = (func_normal_def_t)node;
            fprintf(stdout, "func_normal_def->%s\n", p->id);
            type_print(p->type, num_space + SPACE_STEP);
            formals_print(p->formals, num_space + SPACE_STEP);
            stmts_print(p->stmts, num_space + SPACE_STEP);
            break;
        }
        case FUNC_ANONY_DEF:
        {
            func_anony_def_t p = (func_anony_def_t)node;
            fprintf(stdout, "func_anony_def\n");
            type_print(p->type, num_space + SPACE_STEP);
            formals_print(p->formals, num_space + SPACE_STEP);
            stmts_print(p->stmts, num_space + SPACE_STEP);
            break;
        }
        default:
            fprintf(stdout, "unkown func_def");
            exit(1);
            break;
    }

    fprintf(stdout, "\n");
}

func_def_t func_normal_def_new(func_kind_t kind, type_t type, list_t formals, list_t stmts, string id) {
    func_normal_def_t p = (func_normal_def_t)malloc(sizeof(*p));
    p->kind = kind;
    p->type = type;
    p->formals = formals;
    p->stmts = stmts;
    p->id = cpystr(id);
    return (func_def_t)p;
}

func_def_t func_anony_def_new(func_kind_t kind, type_t type, list_t formals, list_t stmts) {
    func_anony_def_t p = (func_anony_def_t)malloc(sizeof(*p));
    p->kind = kind;
    p->type = type;
    p->formals = formals;
    p->stmts = stmts;
    return (func_def_t)p;
}

void fields_print(list_t fields, int num_space) {
    space_print(num_space);

    fprintf(stdout, "fields->\n");

    list_t pf = fields;

    while (pf) {
        field_t node = (field_t)pf->data;

        if (node) {
            field_print(node, num_space + SPACE_STEP);
        }

        pf = pf->next;
    }

    fprintf(stdout, "\n");
}

void field_print(field_t node, int num_space) {
    space_print(num_space);

    switch (node->kind) {
        case FIELD_VAR:
        {
            field_var_t p = (field_var_t)node;
            fprintf(stdout, "field_var->\n");
            var_def_print(p->var_def, num_space + SPACE_STEP);
            break;
        }
        case FIELD_FUNC:
        {
            field_func_t p = (field_func_t)node;
            fprintf(stdout, "field_func->\n");
            func_def_print(p->func_def, num_space + SPACE_STEP);
            break;
        }
        default:
            fprintf(stdout, "unkown field");
            exit(1);
            break;
    }

    fprintf(stdout, "\n");
}


field_t field_var_new(field_kind_t kind, var_def_t var_def) {
    field_var_t p = (field_var_t)malloc(sizeof(*p));
    p->kind = kind;
    p->var_def = var_def;
    return (field_t)p;
}

field_t field_func_new(field_kind_t kind, func_def_t func_def) {
    field_func_t p = (field_func_t)malloc(sizeof(*p));
    p->kind = kind;
    p->func_def = func_def;
    return (field_t)p;
}

void stmts_print(list_t stmts, int num_space) {
    space_print(num_space);

    fprintf(stdout, "stmts->\n");

    list_t pf = stmts;

    while (pf) {
        stmt_t node = (stmt_t)pf->data;

        if (node) {
            stmt_print(node, num_space + SPACE_STEP);
        }

        pf = pf->next;
    }

    fprintf(stdout, "\n");
}

void stmt_print(stmt_t node, int num_space) {
    space_print(num_space);

    switch (node->kind) {
        case STMT_VAR_DEF:
        {
            stmt_var_def_t p = (stmt_var_def_t)node;
            fprintf(stdout, "stmt_var_def->\n");
            var_def_print(p->var_def, num_space + SPACE_STEP);
            break;
        }
        case STMT_EXPR:
        {
            stmt_expr_t p = (stmt_expr_t)node;
            fprintf(stdout, "stmt_expr->\n");
            if (p->expr) {
                expr_print(p->expr, num_space + SPACE_STEP);
            }
            break;
        }
        case STMT_IF:
        {
            stmt_if_t p = (stmt_if_t)node;
            fprintf(stdout, "stmt_if->\n");
            expr_print((expr_t)p->cond, num_space + SPACE_STEP);
            stmts_print(p->body_then, num_space + SPACE_STEP);
            stmts_print(p->body_else, num_space + SPACE_STEP);
            break;
        }
        case STMT_WHILE:
        {
            stmt_while_t p = (stmt_while_t)node;
            fprintf(stdout, "stmt_while->\n");
            expr_print((expr_t)p->cond, num_space + SPACE_STEP);
            stmts_print(p->body, num_space + SPACE_STEP);
            break;
        }
        case STMT_FOR:
        {
            stmt_for_t p = (stmt_for_t)node;
            fprintf(stdout, "stmt_for->\n");
            assigns_print(p->initializer, num_space + SPACE_STEP);
            expr_print((expr_t)p->cond, num_space + SPACE_STEP);
            assigns_print(p->assigner, num_space + SPACE_STEP);
            stmts_print(p->body, num_space + SPACE_STEP);
            break;
        }
        case STMT_RETURN:
        {
            stmt_return_t p = (stmt_return_t)node;
            fprintf(stdout, "stmt_return->\n");
            if (p->ret_val) {
                expr_print(p->ret_val, num_space + SPACE_STEP);
            }
            break;
        }
        case STMT_PRINT:
        {
            stmt_print_t p = (stmt_print_t)node;
            fprintf(stdout, "stmt_print->\n");
            expr_print(p->out, num_space + SPACE_STEP);
            break;
        }
        default:
            fprintf(stdout, "unkown stmt");
            exit(1);
            break;
    }

    fprintf(stdout, "\n");
}

stmt_t stmt_var_def_new(stmt_kind_t kind, var_def_t var_def) {
    stmt_var_def_t p = (stmt_var_def_t)malloc(sizeof(*p));
    p->kind = kind;
    p->var_def = var_def;
    return (stmt_t)p;
}

stmt_t stmt_expr_new(stmt_kind_t kind, expr_t expr) {
    stmt_expr_t p = (stmt_expr_t)malloc(sizeof(*p));
    p->kind = kind;
    p->expr = expr;
    return (stmt_t)p;
}

stmt_t stmt_if_new(stmt_kind_t kind, expr_bool_t cond, list_t body_then, list_t body_else) {
    stmt_if_t p = (stmt_if_t)malloc(sizeof(*p));
    p->kind = kind;
    p->cond = cond;
    p->body_then = body_then;
    p->body_else = body_else;
    return (stmt_t)p;
}

stmt_t stmt_while_new(stmt_kind_t kind, expr_bool_t cond, list_t body) {
    stmt_while_t p = (stmt_while_t)malloc(sizeof(*p));
    p->kind = kind;
    p->cond = cond;
    p->body = body;
    return (stmt_t)p;
}

stmt_t stmt_for_new(stmt_kind_t kind, list_t initializer, expr_bool_t cond, list_t assigner, list_t body) {
    stmt_for_t p = (stmt_for_t)malloc(sizeof(*p));
    p->kind = kind;
    p->initializer = initializer;
    p->cond = cond;
    p->assigner = assigner;
    p->body = body;
    return (stmt_t)p;
}

stmt_t stmt_return_new(stmt_kind_t kind, expr_t ret_val) {
    stmt_return_t p = (stmt_return_t)malloc(sizeof(*p));
    p->kind = kind;
    p->ret_val = ret_val;
    return (stmt_t)p;
}

stmt_t stmt_print_new(stmt_kind_t kind, expr_t out) {
    stmt_print_t p = (stmt_print_t)malloc(sizeof(*p));
    p->kind = kind;
    p->out = out;
    return (stmt_t)p;
}

void class_defs_print(list_t class_defs, int num_space) {
    space_print(num_space);

    fprintf(stdout, "class_defs->\n");

    list_t pf = class_defs;

    while (pf) {
        class_def_t node = (class_def_t)pf->data;

        if (node) {
            class_def_print(node, num_space + SPACE_STEP);
        }

        pf = pf->next;
    }

    fprintf(stdout, "\n");
}

void class_def_print(class_def_t node, int num_space) {
    space_print(num_space);

    fprintf(stdout, "class_def-><%s, %s>\n", node->id, node->super);
    fields_print(node->fields, num_space + SPACE_STEP);

    fprintf(stdout, "\n");
}

class_def_t class_def_new(string id, string super, list_t fields) {
    class_def_t p = (class_def_t)malloc(sizeof(*p));
    p->id = cpystr(id);
    p->super = cpystr(super);
    p->fields = fields;
    return p;
}

void prog_print(prog_t prog) {
    fprintf(stdout, "prog_tree->\n");

    class_defs_print(prog->class_defs, SPACE_STEP);

    fprintf(stdout, "\n");
}

prog_t prog_new(list_t class_defs) {
    prog_t p = (prog_t)malloc(sizeof(*p));
    p->class_defs = class_defs;
    return p;
}
