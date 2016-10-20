%{

    #include <stdio.h>
    #include "decaf.tab.h"

    // #undef YYDEBUG

    int column = 1;

    int yywrap(void);
    void count(void);
%}

%%

"+"     {
    count();
#ifdef YYDEBUG
    fprintf(yyout, " ADD ");
#endif
    return ADD;
}
"-"     {
    count();
#ifdef YYDEBUG
    fprintf(yyout, " SUB ");
#endif
    return SUB;
}
"*"     {
    count();
#ifdef YYDEBUG
    fprintf(yyout, " MUL ");
#endif
    return MUL;
}
"/"     {
    count();
#ifdef YYDEBUG
    fprintf(yyout, " DIV ");
#endif
    return DIV;
}
"("     {
    count();
#ifdef YYDEBUG
    fprintf(yyout, " LP ");
#endif
    return LP;
}
")"     {
    count();
#ifdef YYDEBUG
    fprintf(yyout, " RP ");
#endif
    return RP;
}
"\n"    {
    count();
    return CR;
}
([1-9][0-9]*)|0|([0-9]+\.[0-9]+) {
    count();
    double temp;
    sscanf(yytext, "%lf", &temp);
    yylval.double_value = temp;

#ifdef YYDEBUG
    fprintf(yyout, " DOUBLE_LITERAL ");
#endif

    return DOUBLE_LITERAL;
}
[ \t] {
    count();
}
. {
    fprintf(stderr, "Lexical error near %s.\n", yytext);
    exit(1);
}

%%

int yywrap(void) {
    return 1;
}

void count(void) {
    for (int i = 0; yytext[i] != '\0'; i++) {
        if (yytext[i] == '\n') {
            column = 0;

        } else if (yytext[i] == '\t') {
            column += (8 - (column % 8));
        } else {
            column++;
        }
    }

#ifdef YYDEBUG
    for (int i = 0; yytext[i] != '\0'; i++) {
        if (yytext[i] == '\n') {
            fprintf(yyout, "\n");
        } else if (yytext[i] == '\t') {
            fprintf(yyout, "\t");
        } else if (yytext[i] == ' '){
            fprintf(yyout, " ");
        }
    }
#endif

/* #ifdef YYDEBUG */
/*     ECHO; */
/* #endif */
}
