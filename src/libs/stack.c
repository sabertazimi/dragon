/*
 * stack.c
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "stack.h"

stack_t stack_new(void) {
    stack_t s = (stack_t)malloc(sizeof(*s));
    s->list = NULL;
    s->num_datas = 0;
    return s;
}

int stack_empty(stack_t s) {
    if (s->list == NULL && s->num_datas == 0) {
        return 1;
    } else {
        return 0;
    }
}

void *stack_get(stack_t s, int index) {
    void *data;

    int i;
    list_t cur;

    if (stack_empty(s) || index > s->num_datas - 1) {
        data = NULL;
    } else {
        for (i = 0, cur = s->list; i < index && cur != NULL; i++, cur = cur->next) {
            ;   // search target node
        }

        data = cur->data;
    }

    return data;
}

stack_t stack_push(stack_t s, void *data) {
    s->list = list_new(data, s->list);
    s->num_datas += 1;
    return s;
}

void *stack_remove(stack_t s, int index) {
    void *data;

    int i;
    list_t prev, cur;

    if (stack_empty(s) || index > s->num_datas - 1) {
        data = NULL;
    } else {
        for (i = 0, prev = s->list, cur = s->list;
                i < index && cur != NULL;
                i++, prev = cur, cur = cur->next) {
            ;   // search target node
        }

        if (prev == cur) {
            data = s->list->data;
            s->list = s->list->next;
        } else {
            data = cur->data;
            prev->next = cur->next;
        }
    }

    return data;
}

void *stack_pop(stack_t s) {
    void *data = stack_remove(s, 0);
    return data;
}

