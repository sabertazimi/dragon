/*
 * list.c
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "list.h"

list_t list_new(void *data, list_t tail) {
    list_t p = (list_t)malloc(sizeof(*p));
    p->data = data;
    p->next = tail;
    return p;
}

list_t list_rev(list_t l) {
    list_t p = NULL;

    while (l) {
        p = list_new(l->data, p);
        l = l->next;
    }

    return p;
}
