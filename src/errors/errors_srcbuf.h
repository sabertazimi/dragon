/*
 * errors_srcbuf.h
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef ERRORS_SRCBUF_H
#define ERRORS_SRCBUF_H

#include <string.h>
#include "errors_common.h"
#include "../scanner.h"

/*
 * @brief: set all memory of buffer to '\0'
 */
void srcbuf_init(void);

/*
 * @brief: send new rar source code to buffer
 */
void srcbuf_append(const char * src);

/*
 * @brief: get source code, with specific line number
 */
const char * srbuf_get(int num_line);



/*
 * @brief: get length of buffer
 */
int srcbuf_length(void);

/*
 * @brief: print source code in buffer, with specific line number
 */
void srcbuf_print(int num_line);

#endif /* !ERRORS_SRCBUF_H */
