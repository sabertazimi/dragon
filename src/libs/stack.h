/*
 * stack.h
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef STACK_H
#define STACK_H

#include <libs_common.h>
#include "list.h"

/*
 * @brief: use list_t to implement stack_t
 */
typedef struct _stack_ *stack_t;

struct _stack_ {
    list_t list;
    int num_datas;
};

/*
 * @brief: basic operations on stack_t
 */

/*
 * top ---> bottom
 * 0 -> 1-> ... -> s->num_datas - 1
 */

/*
 * @brief: create a empty stack
 */
stack_t stack_new(void);

/*
 * @brief: test whether stack is empty
 */
int stack_empty(stack_t s);

/*
 * @brief: get specfic index node of stack
 */
void *stack_get(stack_t s, int index);

/*
 * @brief: push a new data node into stack
 */
stack_t stack_push(stack_t s, void *data);

/*
 * @brief: remove specific data node from stack
 */
void *stack_remove(stack_t s, int index);

/*
 * @brief: pop top data node from stack
 * @return: top data node
 */
void *stack_pop(stack_t s);

#endif /* !STACK_H */
