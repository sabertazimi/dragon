/*
 * stack_spec.c
 * Copyright (C) 2016 sabertazimi <sabertazimi@avalon>
 *
 * Distributed under terms of the MIT license.
 */

#include "stack_spec.h"

void stack_spec(void) {
    stack_t s = stack_new();
    int data[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    assert(stack_empty(s) == 1);

    stack_push(s, data);
    assert(stack_empty(s) == 0);
    assert(s->list != NULL);
    assert(s->num_datas == 1);
    assert(*((int *)s->list->data) == 0);

    stack_push(s, data + 1);
    assert(stack_empty(s) == 0);
    assert(s->list != NULL);
    assert(s->num_datas == 2);
    assert(*((int *)s->list->data) == 1);
    assert(*((int *)s->list->next->data) == 0);
}
