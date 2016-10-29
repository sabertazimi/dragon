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

#endif /* !ERRORS_SRCBUF_H */
