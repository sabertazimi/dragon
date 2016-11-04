/*
 * list.h
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef LIBS_LIST_H
#define LIBS_LIST_H

#include "libs_common.h"

typedef struct list_t {
    void *data;
    struct list_t *next;
} *list_t;

/*
 * @brief: insert a new node(data) into tail_list
 * @param: data new node to insert
 * @param: tail list
 * @return: list_t new list with new node inserted at head position
 */
list_t list_new(void *data, list_t tail);

/*
 * @brief: reverse a list
 * @param: l list to reverse
 * @return: list_t new list reversed from l
 */
list_t list_rev(list_t l);

#endif /* !LIBS_LIST_H */
