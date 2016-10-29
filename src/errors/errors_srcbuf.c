/*
 * errors_srcbuf.c
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <string.h>
#include "errors_srcbuf.h"

#define SRCBUF_MAXLEN 100

typedef struct srcbuf {
    char buf[SRCBUF_MAXLEN];    ///< buffer cache memory for source code
    char cnt;                   ///< number of characters still in buffer
} srcbuf_t;

static srcbuf_t srcbuf;

void srcbuf_init(void) {
    srcbuf.cnt = 0;

    for (int i = 0; i < SRCBUF_MAXLEN; i++) {
        srcbuf.buf[i] = '\0';
    }
}

void srcbuf_append(const char *src) {
    srcbuf.cnt += strlen(src);
    strcat(srcbuf.buf, src);
}
