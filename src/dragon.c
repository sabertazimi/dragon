/*
 * dragon.c
 * Copyright (C) 2016 sabertazimi <sabertazimi@avalon>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

extern FILE *yyin;
extern int yyparse(void);
extern int parse_failed;

int main(int argc, char **argv) {
    FILE *fp = NULL;

    if (argc > 1 && (fp = fopen(argv[1], "r")) != NULL) {
        yyin = fp;
    }

    // yyparse return value: 1 represent error occurs
    while (yyparse()) {
        fprintf(stderr, "Bison panic.\n");
        exit(1);
    }

    if (parse_failed == 1) {
        fprintf(stderr, "Please fix syntax error first!\n");
        exit(0);
    }

    fclose(fp);
    return 0;
}
