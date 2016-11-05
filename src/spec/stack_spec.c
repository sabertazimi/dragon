/*
 * stack_spec.c
 * Copyright (C) 2016 sabertazimi <sabertazimi@avalon>
 *
 * Distributed under terms of the MIT license.
 */

#include "stack_spec.h"

void stack_spec(void) {
    stack_t s = stack_new();

    int *data = (int *)malloc(sizeof(int));
    *data = 233;

    assert(stack_empty(s) == 1);

    stack_push(s, data);

    assert(stack_empty(s) == 0);
    assert(s->list != NULL);
    assert(s->num_datas == 1);
}
