/*
 * semantic_typechk.c
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed underf terms of the MIT license.
 */

#include <stdlib.h>
#include "semantic.h"

// type_kind_t(enum) start from 21
#define TYPE_NAME(node) (type_name[((node)->kind)-21])

static type_name[6][] = {
    "int",
    "bool",
    "string",
    "void",
    "class",
    "array",
};

extern int typechk_failed;

type_t type_basic_new(type_kind_t kind);
type_t type_class_new(type_kind_t kind, string class_id);
type_t type_array_new(type_kind_t kind, type_t type);



type_t type_typechk(type_t node) {
    return node;
}

type_t const_typechk(const_t node) {
    type_t p;   ///< store result of type check

    switch (node->kind) {
        case CONST_INT:
            p = (type_t)type_basic_new(TYPE_INT);
            break;
        case CONST_BOOL:
            p = (type_t)type_basic_new(TYPE_BOOL);
            break;
        case CONST_STRING:
            p = (type_t)type_basic_new(TYPE_STRING);
            break;
        case CONST_NIL:
            p = (type_t)type_basic_new(TYPE_VOID);
            break;
        default:
            p = NULL;
            break;
    }

    return p;
}

/*
 * @brief: kind of symbol
 */
typedef enum sym_kind {
    SYM_VARDEF,
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
    type_t type;
    string id;
    sym_classdef_t classdef;
};

struct sym_funcdef {
    sym_kind_t kind;
    type_t type;
    list_t formals;
    list_t stmts;
    sym_classdef_t classdef;
}

// @TODO: symbol table generation
// 第一次遍历语法树: 查询 var_def_t/func_def_t/class_def_t, 构造符号表
// 先 sym_classdef_new(), 对于所有 sym_vardef_new/sym_funcdef_new, 将生成的结点插入 classdef->sym_vardef_t/sym_funcdef_t 链表
// 遍历完一个 classdef 中所有的 var_def_t/func_def_t 后, 再遍历 sym_vardef_t/sym_funcdef_t 链表, 将所有 sym_vardef/sym_funcdef 结点的 symclassdef 指针指向 classdef 结点

struct sym_classdef {
    sym_kind_t kind;
    string id;
    list_t vardefs;     ///< list_t <sym_vardef_t>
    list_t funcdefs;    ///< list_t <sym_funcdef_t>
    // @TODO: scope_t class_scope;
}

// scope_t
// sym_classdef -> ... -> ... -> sym_classdef_main

sym_t sym_vardef_new(sym_kind_t kind, var_def_t var_def) {
    sym_vardef_t p = (sym_vardef_t)malloc(sizeof(*p));
    p->kind = kind;
    p->type = var_def->type;
    p->id = id;
    return (sym_t)p;
}

/*
 * @mock: temporary for testing
 * @TODO: implements truly symtab_lookup function
 */
sym_t symtab_lookup(sym_kind_t kind, string id) {
    switch (kind) {
        case SYM_VARDEF:
        {
            // sym_vardef_t p = sym_vardef_new(SYM_VARDEF, （type_t)type_basic_new(TYPE_INT));
            break;
        }
        case SYM_FUNCDEF:
        {

            break;
        }
        case SYM_CLASSDEF:
        {

            break;
        }
    }

    sym_vardef_t p = sym_vardef_new(SYM_VARDEF, （type_t)type_basic_new(TYPE_INT));
    return (sym_t)p;
}

type_t var_def_typechk(var_def_t node) {
    sym_vardef_t p = (sym_vardef_t *)symtab_lookup(SYM_VARDEF, node->id);
    type_t left = (type_t)p->type;

    if (node->initializer) {
        type_t right = expr_typechk((expr_t)node->initializer);

        // @TODO: add advanced branch reporting
        if (left->kind != right->kind) {
            fprintf("Type dismatch in var_def<%s, %s>\n", TYPE_NAME(left), TYPE_NAME(right));
            typechk_failed = 1;
        }
    }
}

type_t func_def_typechk(func_def_t node) {
    sym_funcdef_t p = (sym_funcdef_t *)symtab_lookup(SYM_FUNCDEF, node->id);

    type_t ret_def = (type_t)p->type;
    type_t ret_stmt;

    list_t stmts = p->stmts;

    while (stmts) {
        stmt_t stmt = stmts->data;

        if (stmt->kind == STMT_RETURN) {
            ret_stmt = stmt_typechk(stmt);
            break;
        }
    }

    if (ret_def->kind != ret_stmt->kind) {
        fprintf("Type dismatch in func_def: conflict return type <%s, %s>\n", TYPE_NAME(ret_def), TYPE_NAME(ret_stmt));
    }

    if (node->initializer) {
        type_t right = expr_typechk((expr_t)node->initializer);

        // @TODO: add advanced branch reporting
        if (TYPE_NAME(left) != TYPE_NAME(right)) {
            fprintf("Type dismatch in var_def<%s, %s>\n", TYPE_NAME(left), TYPE_NAME(right));
            typechk_failed = 1;
        }
    }

        case FUNC_NORMAL_DEF:
            type_print(p->type, num_space + SPACE_STEP);
            formals_print(p->formals, num_space + SPACE_STEP);
            stmts_print(p->stmts, num_space + SPACE_STEP);
            break;
        case FUNC_ANONY_DEF:
}

type_t class_def_typechk(class_def_t node) {

}

type_t class_defs_typechk(list_t class_defs) {

}

type_t expr_typechk(expr_t node) {

}

type_t assigns_typechk(list_t assigns) {

}

type_t stmt_typechk(stmt_t node) {

}

type_t stmts_typechk(list_t stmts) {

}

type_t formal_typechk(formal_t node) {

}

type_t formals_typechk(list_t formals) {

}

type_t actual_typechk(actual_t node) {

}

type_t actuals_typechk(list_t actuals) {

}

type_t field_typechk(field_t node) {

}

type_t fields_typechk(list_t fields) {

}

type_t prog_typechk(prog_t prog) {

}



void func_def_print(func_def_t node, int num_space) {

}

void class_def_print(class_def_t node, int num_space) {
    space_print(num_space);

    fprintf(stdout, "class_def-><%s, %s>\n", node->id, node->super);
    fields_print(node->fields, num_space + SPACE_STEP);
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
                    fprintf(stdout, "unkown expr\n");
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
                    fprintf(stdout, "unkown expr\n");
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
                    fprintf(stdout, "unkown expr\n");
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
                    fprintf(stdout, "unkown expr\n");
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
                    fprintf(stdout, "this\n");
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
                    fprintf(stdout, "unkown expr\n");
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
                    fprintf(stdout, "unkown expr\n");
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
                    fprintf(stdout, "expr_prim_ident->%s\n", pp->id);
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
                    fprintf(stdout, "expr_prim_readint\n");
                    break;
                }
                case EXPR_PRIM_READLINE:
                {
                    fprintf(stdout, "expr_prim_readline\n");
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
                    fprintf(stdout, "unkown expr\n");
                    exit(1);
                    break;
            }

            break;
        }
        default:
            fprintf(stdout, "unkown expr\n");
            exit(1);
            break;
    }
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
            fprintf(stdout, "unkown stmt\n");
            exit(1);
            break;
    }
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
}

void formal_print(formal_t node, int num_space) {
    space_print(num_space);

    fprintf(stdout, "formal->%s\n", node->id);
    type_print(node->type, num_space + SPACE_STEP);
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
}

void actual_print(actual_t node, int num_space) {
    space_print(num_space);

    fprintf(stdout, "actual->\n");
    expr_print(node->expr, num_space + SPACE_STEP);
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
            fprintf(stdout, "unkown field\n");
            exit(1);
            break;
    }
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
}

void prog_print(prog_t prog) {
    fprintf(stdout, "prog_tree->\n");

    class_defs_print(prog->class_defs, SPACE_STEP);
}
