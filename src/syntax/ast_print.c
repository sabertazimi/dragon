/*!
 * \file ast_print.cc
 * \brief
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#include "ast_print.h"

void type_print(type_t node, int num_space) {
    space_print(num_space);

    switch (node->kind) {
        case TYPE_INT:
            fprintf(stdout, "type_int\n");
            break;
        case TYPE_BOOL:
            fprintf(stdout, "type_bool\n");
            break;
        case TYPE_STRING:
            fprintf(stdout, "type_string\n");
            break;
        case TYPE_VOID:
            fprintf(stdout, "type_void\n");
            break;
        case TYPE_CLASS:
            {
                type_class_t p = (type_class_t)node;
                fprintf(stdout, "type_class->%s\n", p->class_id);
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
            fprintf(stdout, "unkown type\n");
            exit(1);
            break;
    }
}

void const_print(Const *node, int num_space) {
    space_print(num_space);

    switch (node->kind) {
        case CONST_INT:
            {
                // const_num_t p = (const_num_t)node;
                // cout << toString();
                break;
            }
        case CONST_BOOL:
            {
                // const_num_t p = (const_num_t)node;
                // cout << toString();
                break;
            }
        case CONST_STRING:
            {
                // const_string_t p = (const_string_t)node;
                // cout << toString();
                break;
            }
        case CONST_NIL:
            // cout << toString();
            break;
        default:
            fprintf(stdout, "unkown constant\n");
            exit(1);
            break;
    }
}

void var_def_print(var_def_t node, int num_space) {
    space_print(num_space);

    fprintf(stdout, "var_def->%s\n", node->id);

    type_print(node->type, num_space + SPACE_STEP);
    if (node->initializer) {
        expr_print((expr_t)node->initializer, num_space + SPACE_STEP);
    }
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
            fprintf(stdout, "unkown func_def\n");
            exit(1);
            break;
    }
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
                    case EXPR_LEFT_THIS:
                        fprintf(stdout, "expr_left_this\n");
                        break;
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
                            fprintf(stdout, "expr_left_func_call->%s\n", pp->id);
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
