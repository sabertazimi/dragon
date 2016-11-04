/*
 * errors_debug.h
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef ERRORS_DEBUG_H
#define ERRORS_DEBUG_H

#include "errors_common.h"

#define LEX_DEBUG
#undef LEX_DEBUG

/*
 * @macro: DRAGON_DEBUG
 * @brief: print debug info for lexical analysis
 */
#ifdef LEX_DEBUG
    #define DRAGON_DEBUG(type, value) do { dragon_debug(type, value); } while (0)
#else
    #define DRAGON_DEBUG(type, value) do { } while (0)
#endif

/*
 * @brief: debug output function
 */
void dragon_debug(const char *type, const char *value);

/*
 * @brief: print error information
 */
void dragon_debug(const char *type, const char *value);

#endif /* !ERRORS_DEBUG_H */
