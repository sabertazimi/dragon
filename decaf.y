%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #define YYDEBUG 1

    extern char *yytext;
    extern FILE *yyin;
    extern int column;

    extern int yylex(void);
    extern int yyparse(void);

    int yyerror(char const *str);
%}

%union {
    int int_value;
    double double_value;
}

%token <double_value> DOUBLE_LITERAL;

%type <double_value> exp

%left '+' '-'
%left '*' '/'

%%

lines: line
     | line lines
     ;

line: exp '\n' {
        printf(">> value=%.10g\n",$1);
    }
    | error '\n' {
        yyclearin;
        yyerrok;
    }
    | '\n'
    ;


exp: DOUBLE_LITERAL { $$ = $1; }
   | exp '+' exp    { $$ = $1 + $3;}
   | exp '-' exp    { $$ = $1 - $3;}
   | exp '/' exp    { $$ = $1 / $3;}
   | exp '*' exp    { $$ = $1 * $3;}
   | '(' exp ')'     { $$ = $2;}
   ;

%%

int yyerror(char const *str) {
    fprintf(stderr, "parser error near %s\n", yytext);
    memset(yytext, '\0', strlen(yytext));
    return 0;
}

int main(int argc, char **argv) {
    FILE *fp;

    if (argc > 1 && (fp = fopen(argv[1], "r")) != NULL) {
        yyin = fp;
    }

    if (yyparse()) {
        fprintf(stderr, "Bison panic.\n");
        exit(1);
    }

    fclose(fp);
    return 0;
}
