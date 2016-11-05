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

    for (int i = 0; i < 10; i++) {
        stack_push(s, data + i);
        assert(stack_empty(s) == 0);
        assert(s->list != NULL);
        assert(s->num_datas == i + 1);

        for (int j = 0; j < i + 1; j++) {
            assert(*((int*)stack_get(s, j)) == (i - j));
        }

    }
}
