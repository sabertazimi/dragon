/*
 * errors_utils.h
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef ERRORS_UTILS_H
#define ERRORS_UTILS_H

#include <stdarg.h>
#include "errors_common.h"
#include "errors_srcbuf.h"
#include "../scanner.h"

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
void dragon_report(yyltype loc, const char *fmt, ...);

/*
 * @brief: simple logger function
 */
void dragon_log(const char *fmt, ...);

#endif /* !ERRORS_UTILS_H */
