%{

    #include <stdio.h>
    #include "decaf.tab.h"

    // #undef YYDEBUG

    int column = 1;

    int yywrap(void);
    void count(void);
%}

%%

"/*"   {
    comment();
}
"//"[^\n]* { /* Skip comment line */ }

"bool" {
    count();
#ifdef YYDEBUG
    fprintf(yyout, "BOOL ");
#endif
    return BOOL;
}
"break" {
    count();
#ifdef YYDEBUG
    fprintf(yyout, "BREAK ");
#endif
    return BREAK;
}
"class" {
    count();
#ifdef YYDEBUG
    fprintf(yyout, "CLASS ");
#endif
    return CLASS;
}
"else" {
    count();
#ifdef YYDEBUG
    fprintf(yyout, "ELSE ");
#endif
    return ELSE;
}
"extends" {
    count();
#ifdef YYDEBUG
    fprintf(yyout, "EXTENDS ");
#endif
    return EXTENDS;
}
"for" {
    count();
#ifdef YYDEBUG
    fprintf(yyout, "FOR ");
#endif
    return FOR;
}
"if" {
    count();
#ifdef YYDEBUG
    fprintf(yyout, "IF ");
#endif
    return IF;
}
"int" {
    count();
#ifdef YYDEBUG
    fprintf(yyout, "INT ");
#endif
    return INT;
}
"new" {
    count();
#ifdef YYDEBUG
    fprintf(yyout, "NEW ");
#endif
    return NEW;
}
"null" {
    count();
#ifdef YYDEBUG
    fprintf(yyout, "NULL ");
#endif
    return NULL;
}
"return" {
    count();
#ifdef YYDEBUG
    fprintf(yyout, "RETURN ");
#endif
    return RETURN;
}
"string" {
    count();
#ifdef YYDEBUG
    fprintf(yyout, "STRING ");
#endif
    return STRING;
}
"this" {
    count();
#ifdef YYDEBUG
    fprintf(yyout, "THIS ");
#endif
    return THIS;
}
"void" {
    count();
#ifdef YYDEBUG
    fprintf(yyout, "VOID ");
#endif
    return VOID;
}
"while" {
    count();
#ifdef YYDEBUG
    fprintf(yyout, "WHILE ");
#endif
    return WHILE;
}
"static" {
    count();
#ifdef YYDEBUG
    fprintf(yyout, "STATIC ");
#endif
    return STATIC;
}
"Print" {
    count();
#ifdef YYDEBUG
    fprintf(yyout, "PRINT ");
#endif
    return PRINT;
}
"ReadInteger" {
    count();
#ifdef YYDEBUG
    fprintf(yyout, "READINTEGER ");
#endif
    return READINTEGER;
}
"ReadLine" {
    count();
#ifdef YYDEBUG
    fprintf(yyout, "READLINE ");
#endif
    return READLINE;
}
"instanceof" {
    count();
#ifdef YYDEBUG
    fprintf(yyout, "INSTANCEOF");
#endif
    return INSTANCEOF;
}
"+"     {
    count();
#ifdef YYDEBUG
    fprintf(yyout, "ADD ");
#endif
    return '+';
}
"-"     {
    count();
#ifdef YYDEBUG
    fprintf(yyout, "SUB ");
#endif
    return '-';
}
"*"     {
    count();
#ifdef YYDEBUG
    fprintf(yyout, "MUL ");
#endif
    return '*';
}
"/"     {
    count();
#ifdef YYDEBUG
    fprintf(yyout, "DIV ");
#endif
    return '/';
}
"("     {
    count();
#ifdef YYDEBUG
    fprintf(yyout, "LP ");
#endif
    return '(';
}
")"     {
    count();
#ifdef YYDEBUG
    fprintf(yyout, "RP ");
#endif
    return ')';
}
"\n"    {
    count();
    return '\n';
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

/*
 * @brief: function for recording column number
 */
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
