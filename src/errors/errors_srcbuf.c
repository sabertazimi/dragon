/*
 * errors_srcbuf.c
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include <string.h>
#include "../scanner.h"
#include "errors.h"

typedef struct srcbuf {
    list_t buf;     ///< list_t <string>: store source code
    int  cnt_line;  ///< number of line in buffer
    int  cnt_chars; ///< number of characters in buffer
} srcbuf_t;

static srcbuf_t srcbuf;

void srcbuf_init(void) {
    srcbuf.cnt_line = 1;
    srcbuf.cnt_chars = 0;

    // set line 0 to empty line
    // true source start from line 1
    srcbuf.buf = list_new(strdup("\0"), NULL);
}

void srcbuf_append(const char *src) {
    srcbuf.cnt_line += 1;
    srcbuf.cnt_chars += strlen(src);
    srcbuf.buf = list_new(strdup(src), srcbuf.buf);
}

const char * srcbuf_get(int num_line) {
    int i;
    list_t srcs;
    char * src;

    // argument check
    if (num_line <= 0 || num_line > srcbuf_length()) num_line = 1;

    for (i = srcbuf_length(), srcs = srcbuf.buf; i > num_line && srcs != NULL; i++, srcs = srcs->next) {
        ;
    }

    src = (char *)srcs->data;
    return src;
}

int srcbuf_length(void) {
    return srcbuf.cnt_line - 1;
}

static int srcbuf_printable(int num_line) {
    const char * src = srcbuf_get(num_line);

    for (unsigned i = 0; i < strlen(src); i++) {
        if (src[i] != ' ' && src[i] != '\t' && src[i] != '\n') {
            return 1;
        }
    }

    // characters in buffer are all whitespece
    return 0;
}

void srcbuf_print(int num_line) {
    if (srcbuf_printable(num_line)) {
        fprintf(stderr , "%s\n", srcbuf_get(num_line));
    }
}
