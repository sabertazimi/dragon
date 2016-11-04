/*
 * errors_debug.c
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "errors_debug.h"

void dragon_debug(const char *type, const char *value) {
    fprintf(yyout, "line %4d, column %-4d-%4d: ", yylloc.first_line, yylloc.first_column, yylloc.last_column);
    fprintf(yyout, "(%s, %s)\n", type, value);
}
