/*
 * errors_srcbuf.c
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include <string.h>
#include "errors.h"

#define SRCBUF_MAXLEN 100

typedef struct srcbuf {
    char buf[SRCBUF_MAXLEN];    ///< buffer cache memory for source code
    int  cnt;                   ///< number of characters still in buffer
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

    if (strcmp(src, "\n")) {
        strcat(srcbuf.buf, src);
    }
}

char *srcbuf_get(void) {
    return srcbuf.buf;
}

int srcbuf_length(void) {
    return srcbuf.cnt;
}

static int srcbuf_printable(void) {
    int length = srcbuf_length();

    for (int i = 0; i < length; i++) {
        if (srcbuf.buf[i] != ' ' && srcbuf.buf[i] != '\t' && srcbuf.buf[i] != '\n') {
            return 1;
        }
    }

    // characters in buffer are all whitespece
    return 0;
}

void srcbuf_print(void) {
    if (srcbuf_printable()) {
        fprintf(yyout, "%s\n", srcbuf.buf);
    }

    for (int i = 1; i < yylloc.first_column; i++) {
        fprintf(stderr, " ");
    }

    for (int i = yylloc.first_column - 1; i < yylloc.last_column; i++) {
        fprintf(stderr, "^");
    }
    fprintf(stderr, "\n");


}
