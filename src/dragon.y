%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #define YYDEBUG 1
    #define STRING_MAXLEN 80

    extern char *yytext;
    extern FILE *yyin;
    extern int yycolumn;

    extern int yylex(void);
    extern int yyparse(void);

    int yyerror(char const *str);
%}

%locations

%union {
    char type_bool;
    int type_int;
    char type_string[80];
    char plain_text[80];
}

%token IDENTIFIER
%token <type_bool> CONSTANT_BOOL
%token <type_int> CONSTANT_INT
%token <type_string> CONSTANT_STRING
%token OP_AND OP_OR OP_LE OP_GE OP_EQ OP_NE OP_ARROW
%token BOOL INT STRING NIL
%token STATIC VOID
%token CLASS EXTENDS NEW THIS
%token IF ELSE FOR WHILE BREAK RETURN
%token PRINT READINTEGER READLINE

%right '='
%left '+' '-'
%left '*' '/'

%%

lines: line
     | line lines
     ;

line: error '\n' {
        yyclearin;
        yyerrok;
    }
    | '\n'
    ;

%%

int yyerror(char const *str) {
    // fprintf(stderr, "parser error near %s\n", yytext);
    // memset(yytext, '\0', strlen(yytext));
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
