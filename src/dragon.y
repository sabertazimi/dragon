%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #define YYDEBUG 1
    #define STRING_MAXLEN 80

    extern int yycolumn;
    extern char *yytext;
    int yylex(void);
    int yyerror(const char *msg);
%}

%locations

%union {
    char bool_val;
    int int_val;
    char str_val[80];
    char plain_text[80];
}

%token IDENTIFIER
%token <bool_val> CONSTANT_BOOL
%token <int_val> CONSTANT_INT
%token <str_val> CONSTANT_STRING
%token OP_AND OP_OR OP_LE OP_GE OP_EQ OP_NE OP_ARROW
%token BOOL INT STRING NIL
%token VOID
%token CLASS EXTENDS NEW THIS
%token IF ELSE FOR WHILE RETURN
%token PRINT READINTEGER READLINE

%left BOOL INT STRING VOID

%nonassoc '='

%left OP_OR
%left OP_AND
%left OP_EQ OP_NE
%left OP_GE OP_LE '<' '>'
%left '+' '-' 
%left '*' '/' '%'
%left NEG

%nonassoc '!'
%nonassoc NoELSE
%nonassoc ELSE

%%

program: class_defs
       ;

class_defs: class_defs class_def
          | class_def
          ;

/* lines: line */
/*      | line lines */
/*      ; */

/* line: error '\n' { */
/*         yyclearin; */
/*         yyerrok; */
/*     } */
/*     | '\n' */
/*     ; */

class_def: CLASS IDENTIFIER '{' fields '}'
         | CLASS IDENTIFIER EXTENDS IDENTIFIER '{' fields '}'
         ;

fields: field fields
      |
      ;

field: var_def
     | func_def
     ;

var_def: var ';'
       ;

var: type IDENTIFIER
   ;

type: INT
    | BOOL
    | STRING
    | VOID
    | CLASS IDENTIFIER
    | type '[' ']'
    ;

func_def: func_normal_def
        | func_anonymous_def
        ;

func_normal_def: type IDENTIFIER '=' '(' formals ')' OP_ARROW '{' stmt '}'
               ;

func_anonymous_def: '(' formals ')' OP_ARROW '{' stmt '}'
                  ;

formals: var ',' formals
       | var
       |
       ;

stmt: var_def
    | simple_stmt ';'
    | if_stmt
    | while_stmt
    | for_stmt
    | return_stmt ';'
    | print_stmt ';'
    ;

simple_stmt: left_val '=' right_val
           ;

left_val: expr '.' IDENTIFIER
        | IDENTIFIER
        | expr '[' expr ']'
        ;

right_val: expr
         | call
         |
         ;

if_stmt: IF '(' bool_expr ')' '{' stmt '}' %prec NoELSE
       | IF '(' bool_expr ')' '{' stmt '}' ELSE '{' stmt '}'
       ;

while_stmt: WHILE '(' bool_expr ')' '{' stmt '}'
          ;

for_stmt: FOR '(' simple_stmt ';' bool_expr ';' simple_stmt ')' '{' stmt '}'
        ;

return_stmt: RETURN
           | RETURN expr
           ;

print_stmt: PRINT '(' expr ')'
          ;

call: expr '.' IDENTIFIER '(' actuals ')'
    | IDENTIFIER '(' actuals ')'
    | func_anonymous_def '(' actuals ')'
    ;

actuals: expr ',' actuals
       | expr
       |
       ;

bool_expr: expr
         ;

expr: constant
    | left_val
    | THIS
    | call
    | '(' expr ')'
    | expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | expr '%' expr
    | '-' expr %prec NEG
    | expr '<' expr
    | expr OP_LE expr
    | expr '>' expr
    | expr OP_GE expr
    | expr OP_EQ expr
    | expr OP_NE expr
    | expr OP_AND expr
    | expr OP_OR expr
    | '!' expr
    | READINTEGER '(' ')'
    | READLINE '(' ')'
    | NEW IDENTIFIER '(' actuals ')'
    | NEW type '[' expr ']'
    ;

constant: CONSTANT_INT
        | CONSTANT_BOOL
        | CONSTANT_STRING
        | NIL
        ;

%%

// return value will be ignored
int yyerror(const char *msg) {
    fprintf(stderr, "Sytax error near %s, line %d, column %d\n", yytext, yylloc.first_line, yylloc.first_column);
    memset(yytext, '\0', strlen(yytext));
    return 0;
}

