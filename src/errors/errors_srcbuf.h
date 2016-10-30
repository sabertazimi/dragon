/*
 * errors_srcbuf.h
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef ERRORS_SRCBUF_H
#define ERRORS_SRCBUF_H

/*
 * @brief: set all memory of buffer to '\0'
 */
void srcbuf_init(void);

/*
 * @brief: send new rar source code to buffer
 */
void srcbuf_append(const char *src);

/*
 * @brief: get pointer to source code buffer
 */
char *srcbuf_get(void);

/*
 * @brief: get length of buffer
 */
int srcbuf_length(void);

/*
 * @brief: print source code in buffer
 */
void srcbuf_print(void);

#endif /* !ERRORS_SRCBUF_H */
