/*
 * errors.h
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef ERRORS_H
#define ERRORS_H

#define LEX_DEBUG
// #undef LEX_DEBUG

#include "ast.h"
#include "../parser.h"
#include "errors_srcbuf.h"
#include "errors_debug.h"

extern FILE* yyout;

#endif /* !ERRORS_H */
