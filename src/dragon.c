/*
 * dragon.c
 * Copyright (C) 2016 sabertazimi <sabertazimi@avalon>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

#define AST_DEBUG
// #undef AST_DEBUG

extern FILE *yyin;
extern int yyparse(void);
extern prog_t prog_tree;

extern int lex_failed;
extern int parse_failed;

int main(int argc, char **argv) {
    FILE *fp = NULL;

    if (argc > 1 && (fp = fopen(argv[1], "r")) != NULL) {
        yyin = fp;
    }

    // yyparse return value: 1 represent error occurs
    while (yyparse()) {
        fprintf(stderr, "*** bison panic.\n");
        exit(1);
    }

    if (parse_failed == 1) {
        fprintf(stderr, "*** please fix syntax error first!\n");
        exit(0);
    }

#ifdef AST_DEBUG
    prog_print(prog_tree);
#endif


    fclose(fp);
    return 0;
}
