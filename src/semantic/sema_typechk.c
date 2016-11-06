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
    char *typestr = strdup("\0");

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

// mock location information
static yyltype mock_loc = { 233, 233, 233, 234 };

int typechk(type_t left, type_t right) {
    int equality;

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


type_t const_typechk(const_t node) {
    type_t ret;   ///< store result of type check

    switch (node->kind) {
        case CONST_INT:
            ret = (type_t)type_basic_new(TYPE_INT, node->loc);
            break;
        case CONST_BOOL:
            ret = (type_t)type_basic_new(TYPE_BOOL, node->loc);
            break;
        case CONST_STRING:
            ret = (type_t)type_basic_new(TYPE_STRING, node->loc);
            break;
        case CONST_NIL:
            ret = (type_t)type_basic_new(TYPE_VOID, node->loc);
            break;
        default:
            ret = NULL;
            typechk_failed = 1;
            dragon_report(node->loc, "unkown const");
            break;
    }

    return ret;
}

type_t var_def_typechk(var_def_t node) {
    type_t left = (type_t)node->type;

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
    type_t ret_def = (type_t)node->type;
    type_t ret_stmt = NULL;

    list_t stmts = node->stmts;

    // search return statement node
    while (stmts) {
        stmt_t stmt = stmts->data;

        if (stmt->kind == STMT_RETURN) {
            ret_stmt = stmt_typechk(stmt);
            break;
        }
    }

    if (ret_stmt = NULL) {
        ret_stmt = (type_t)type_basic_new(TYPE_VOID, node->loc);
    }

    if (!typechk(ret_def, ret_stmt)) {
        typechk_failed = 1;
        dragon_report(ret_stmt->loc, "incompatible types when returning type '%s' but '%s' was expected",
                type_name(ret_stmt), type_name(ret_def));
    }

    stmts_typechk(node->stmts);
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

    switch (node->kind) {
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
            ret = array;

            if (array->kind != TYPE_ARRAY) {
                typechk_failed = 1;
                dragon_report(p->array->loc, "subscripted value is neither array nor vector");
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
                ret = NULL;
                typechk_failed = 1;
                dragon_report(p->left->loc, "invalid access to private class field");
            } else {
                symbol_t symbol = scope_lookup(p->env->parent, p->field_id);

                if (symbol == NULL) {
                    ret = NULL;
                    typechk_failed = 1;
                    dragon_report(p->left->loc, "invalid access to non-exist class field");
                } else {
                    // @FIXME: maybe bugs(segment fault)
                    if (symbol->kind == SYMBOL_CLASS_DEF) {
                        ret = NULL;
                        typechk_failed = 1;
                        dragon_report(p->left->loc, "invalid access to non-exist class field");
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
            type_t left = expr_typchk((expr_t)p->left);

            if (left->kind == TYPE_CLASS) {
                symbol_t class_def = scope_lookup(glb_scopem, left->class_id);
                symbol_t symbol = scope_lookup(class_def->scope, p->field_id);

                if (symbol == NULL) {
                    ret = NULL;
                    typechk_failed = 1;
                    dragon_report(p->loc, "invalid access to non-exist class field");
                } else {
                    func_normal_def_t func = (func_normal_def_t)symbol->def;

                    if (symbol->kind == SYMBOL_CLASS_DEF) {
                        ret = NULL;
                        typechk_failed = 1;
                        dragon_report(p->left->loc, "invalid access to non-exist class field");
                    } else if (!arguments_typchk(func->formals, p->actuals)) {
                        ret = NULL;
                        typechk_failed = 1;
                        dragon_report(p->loc, "incompatible arguments when call %s", func->id);
                    } else {
                        ret = func->type;
                    }
                }
            } else {
                ret = NULL;
                typechk_failed = 1;
                dragon_report(p->left->loc, "invalid access to field of a non-class variable");
            }

            break;
        }
        case EXPR_LEFT_FUNC_CALL:
        {
            expr_left_func_call_t p = (expr_left_func_call_t)node;
            symbol_t symbol = scope_lookup(p->env->parent, p->id);

            if (symbol == NULL) {
                ret = NULL;
                typechk_failed = 1;
                dragon_report(p->loc, "invalid access to non-exist class field");
            } else {
                ret = symbol->type;
                func_normal_def_t func = (func_normal_def_t)

                if (symbol->kind == SYMBOL_CLASS_DEF) {
                    ret = NULL;
                    typechk_failed = 1;
                    dragon_report(p->left->loc, "invalid access to non-exist class field");
                } else if (!arguments_typchk(func->formals, p->actuals)) {
                    ret = NULL;
                    typechk_failed = 1;
                    dragon_report(p->loc, "incompatible arguments when call %s", func->id);
                } else {
                    ret = func->type;
                }
            }

            break;
        }
        case EXPR_LEFT_ANONY_CALL:
        {
            // @TODO: implement type check for anonymous function call
            break;
        }
        default:
            ret = NULL;
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
                ret = NULL;
                typechk_failed = 1;
                dragon_report(pp->loc, "undefined %s", pp->id);
            } else {
                ret = symbol->type;
            }
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
            ret = NULL;
            typechk_failed = 1;
            dragon_report(node->loc, "unkown unary expression");
        default:
            fprintf(stdout, "unkown expr\n");
            exit(1);
            break;
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
            ret = NULL;
            typechk_failed = 1;
            dragon_report(node->loc, "unkown expression");
            break;
    }
}

type_t assigns_typechk(list_t assigns) {
    return NULL;
}

type_t stmt_typechk(stmt_t node) {
    return NULL;
}

type_t stmts_typechk(list_t stmts) {
    return NULL;
}

type_t formal_typechk(formal_t node) {
    return NULL;
}

type_t formals_typechk(list_t formals) {
    return NULL;
}

type_t actual_typechk(actual_t node) {
    return NULL;
}

type_t actuals_typechk(list_t actuals) {
    return NULL;
}

type_t field_typechk(field_t node) {
    return NULL;
}

type_t fields_typechk(list_t fields) {
    return NULL;
}

int prog_typechk(prog_t prog) {
    return 0;
}




/* void class_def_print(class_def_t node, int num_space) { */
/*     space_print(num_space); */

/*     fprintf(stdout, "class_def-><%s, %s>\n", node->id, node->super); */
/*     fields_print(node->fields, num_space + SPACE_STEP); */
/* } */

/* void class_defs_print(list_t class_defs, int num_space) { */
/*     space_print(num_space); */

/*     fprintf(stdout, "class_defs->\n"); */

/*     list_t pf = class_defs; */

/*     while (pf) { */
/*         class_def_t node = (class_def_t)pf->data; */

/*         if (node) { */
/*             class_def_print(node, num_space + SPACE_STEP); */
/*         } */

/*         pf = pf->next; */
/*     } */
/* } */

/* void expr_print(expr_t node, int num_space) { */
/* } */

/* void assigns_print(list_t assigns, int num_space) { */
/*     space_print(num_space); */

/*     fprintf(stdout, "assigns->\n"); */

/*     list_t pf = assigns; */

/*     while (pf) { */
/*         expr_assign_t node = (expr_assign_t)pf->data; */

/*         if (node) { */
/*             expr_print((expr_t)node, num_space + SPACE_STEP); */
/*         } */

/*         pf = pf->next; */
/*     } */
/* } */

/* void stmt_print(stmt_t node, int num_space) { */
/*     space_print(num_space); */

/*     switch (node->kind) { */
/*         case STMT_VAR_DEF: */
/*         { */
/*             stmt_var_def_t p = (stmt_var_def_t)node; */
/*             fprintf(stdout, "stmt_var_def->\n"); */
/*             var_def_print(p->var_def, num_space + SPACE_STEP); */
/*             break; */
/*         } */
/*         case STMT_EXPR: */
/*         { */
/*             stmt_expr_t p = (stmt_expr_t)node; */
/*             fprintf(stdout, "stmt_expr->\n"); */
/*             if (p->expr) { */
/*                 expr_print(p->expr, num_space + SPACE_STEP); */
/*             } */
/*             break; */
/*         } */
/*         case STMT_IF: */
/*         { */
/*             stmt_if_t p = (stmt_if_t)node; */
/*             fprintf(stdout, "stmt_if->\n"); */
/*             expr_print((expr_t)p->cond, num_space + SPACE_STEP); */
/*             stmts_print(p->body_then, num_space + SPACE_STEP); */
/*             stmts_print(p->body_else, num_space + SPACE_STEP); */
/*             break; */
/*         } */
/*         case STMT_WHILE: */
/*         { */
/*             stmt_while_t p = (stmt_while_t)node; */
/*             fprintf(stdout, "stmt_while->\n"); */
/*             expr_print((expr_t)p->cond, num_space + SPACE_STEP); */
/*             stmts_print(p->body, num_space + SPACE_STEP); */
/*             break; */
/*         } */
/*         case STMT_FOR: */
/*         { */
/*             stmt_for_t p = (stmt_for_t)node; */
/*             fprintf(stdout, "stmt_for->\n"); */
/*             assigns_print(p->initializer, num_space + SPACE_STEP); */
/*             expr_print((expr_t)p->cond, num_space + SPACE_STEP); */
/*             assigns_print(p->assigner, num_space + SPACE_STEP); */
/*             stmts_print(p->body, num_space + SPACE_STEP); */
/*             break; */
/*         } */
/*         case STMT_RETURN: */
/*         { */
/*             stmt_return_t p = (stmt_return_t)node; */
/*             fprintf(stdout, "stmt_return->\n"); */
/*             if (p->ret_val) { */
/*                 expr_print(p->ret_val, num_space + SPACE_STEP); */
/*             } */
/*             break; */
/*         } */
/*         case STMT_PRINT: */
/*         { */
/*             stmt_print_t p = (stmt_print_t)node; */
/*             fprintf(stdout, "stmt_print->\n"); */
/*             expr_print(p->out, num_space + SPACE_STEP); */
/*             break; */
/*         } */
/*         default: */
/*             fprintf(stdout, "unkown stmt\n"); */
/*             exit(1); */
/*             break; */
/*     } */
/* } */

/* void stmts_print(list_t stmts, int num_space) { */
/*     space_print(num_space); */

/*     fprintf(stdout, "stmts->\n"); */

/*     list_t pf = stmts; */

/*     while (pf) { */
/*         stmt_t node = (stmt_t)pf->data; */

/*         if (node) { */
/*             stmt_print(node, num_space + SPACE_STEP); */
/*         } */

/*         pf = pf->next; */
/*     } */
/* } */

/* void formal_print(formal_t node, int num_space) { */
/*     space_print(num_space); */

/*     fprintf(stdout, "formal->%s\n", node->id); */
/*     type_print(node->type, num_space + SPACE_STEP); */
/* } */

/* void formals_print(list_t formals, int num_space) { */
/*     space_print(num_space); */

/*     fprintf(stdout, "formals->\n"); */

/*     list_t pf = formals; */

/*     while (pf) { */
/*         formal_t node = (formal_t)pf->data; */

/*         if (node) { */
/*             formal_print(node, num_space + SPACE_STEP); */
/*         } */

/*         pf = pf->next; */
/*     } */
/* } */

/* void actual_print(actual_t node, int num_space) { */
/*     space_print(num_space); */

/*     fprintf(stdout, "actual->\n"); */
/*     expr_print(node->expr, num_space + SPACE_STEP); */
/* } */

/* void actuals_print(list_t actuals, int num_space) { */
/*     space_print(num_space); */

/*     fprintf(stdout, "actuals->\n"); */

/*     list_t pf = actuals; */

/*     while (pf) { */
/*         actual_t node = (actual_t)pf->data; */

/*         if (node) { */
/*             actual_print(node, num_space + SPACE_STEP); */
/*         } */

/*         pf = pf->next; */
/*     } */
/* } */

/* void field_print(field_t node, int num_space) { */
/*     space_print(num_space); */

/*     switch (node->kind) { */
/*         case FIELD_VAR: */
/*         { */
/*             field_var_t p = (field_var_t)node; */
/*             fprintf(stdout, "field_var->\n"); */
/*             var_def_print(p->var_def, num_space + SPACE_STEP); */
/*             break; */
/*         } */
/*         case FIELD_FUNC: */
/*         { */
/*             field_func_t p = (field_func_t)node; */
/*             fprintf(stdout, "field_func->\n"); */
/*             func_def_print(p->func_def, num_space + SPACE_STEP); */
/*             break; */
/*         } */
/*         default: */
/*             fprintf(stdout, "unkown field\n"); */
/*             exit(1); */
/*             break; */
/*     } */
/* } */

/* void fields_print(list_t fields, int num_space) { */
/*     space_print(num_space); */

/*     fprintf(stdout, "fields->\n"); */

/*     list_t pf = fields; */

/*     while (pf) { */
/*         field_t node = (field_t)pf->data; */

/*         if (node) { */
/*             field_print(node, num_space + SPACE_STEP); */
/*         } */

/*         pf = pf->next; */
/*     } */
/* } */

/* void prog_print(prog_t prog) { */
/*     fprintf(stdout, "prog_tree->\n"); */

/*     class_defs_print(prog->class_defs, SPACE_STEP); */
/* } */
