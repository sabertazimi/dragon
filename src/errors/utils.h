/*!
 * \file utils.h
 * \brief
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#ifndef ERRORS_UTILS_H
#define ERRORS_UTILS_H

#include <stdarg.h>
#include "location.h"
#include "errors/common.h"
#include "errors/srcbuf.h"

/*
 * @macro: DRAGON_DEBUG
 * @brief: print debug info for lexical analysis
 */
#ifdef LEX_DEBUG
    #undef DRAGON_DEBUG
    #define DRAGON_DEBUG(type, value) do { dragon_debug(type, value); } while (0)
#else
    #undef DRAGON_DEBUG
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
