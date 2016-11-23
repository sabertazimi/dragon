/*
 * utils.c
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "utils.h"

void space_print(int num_space) {
    fprintf(stdout, "%4d:", num_space / SPACE_STEP);
    for (int i = 0;i < num_space - 4; i++) {
        fprintf(stdout, " ");
    }
}
