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

%error-verbose
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

// hidden type: function type
%token BOOL INT STRING FUNCTION NIL

%token VOID
%token CLASS EXTENDS NEW THIS
%token IF ELSE FOR WHILE RETURN
%token PRINT READINTEGER READLINE

%nonassoc CLASS_MEMBER
%left '(' ')'

%nonassoc NOELSE
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

fields: fields_body
      |
      ;

fields_body
    : fields_body field
    | field
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

func_normal_def: type IDENTIFIER '=' '(' formals ')' OP_ARROW '{' stmts '}' ';'
               ;

func_anonymous_def: '(' formals ')' OP_ARROW '{' stmts '}'
                  ;

formals: formals_body
       | VOID
       |
       ;

formals_body: formals_body ',' var
            | var
            ;

stmts
    : stmts stmt
    |
    ;

stmt
    : var_def
    | expr_stmt
    | if_stmt
    | while_stmt
    | for_stmt
    | return_stmt
    | print_stmt
    ;

expr_stmt: expr ';'
         | ';'
         ;

if_stmt
    : IF '(' bool_expr ')' '{' stmts '}' %prec NOELSE
    | IF '(' bool_expr ')' '{' stmts '}' ELSE '{' stmts '}'
    ;

while_stmt: WHILE '(' bool_expr ')' '{' stmts '}'
          ;

for_stmt: FOR '(' assign_list ';' bool_expr ';' assign_list ')' '{' stmts '}'
        ;

return_stmt: RETURN ';'
           | RETURN VOID ';'
           | RETURN expr ';'
           ;

print_stmt: PRINT '(' expr ')' ';'
          ;

actuals: actuals_body
       |
       ;

actuals_body: actuals_body ',' expr
            | expr
            ;

bool_expr
    : expr
    ;

expr
    : assign_expr
    ;

assign_expr
	: or_expr
	| left_expr '=' assign_expr
	;

assign_list
    : assign_list_body
    |
    ;

assign_list_body
    : assign_list_body ',' assign_expr
    | assign_expr
    ;

or_expr
	: and_expr
	| or_expr OP_OR and_expr
	;

and_expr
	: eq_expr
	| and_expr OP_AND eq_expr
	;

eq_expr
	: cmp_expr
	| eq_expr OP_EQ cmp_expr
	| eq_expr OP_NE cmp_expr
	;

cmp_expr
	: add_expr
	| cmp_expr '<' add_expr
	| cmp_expr '>' add_expr
	| cmp_expr OP_LE add_expr
	| cmp_expr OP_GE add_expr
	;

add_expr
	: mul_expr
	| add_expr '+' mul_expr
	| add_expr '-' mul_expr
	;

mul_expr
	: unary_expr
	| mul_expr '*' unary_expr
	| mul_expr '/' unary_expr
	| mul_expr '%' unary_expr
	;

unary_expr
    : left_expr
    | THIS
    | '+' unary_expr
    | '-' unary_expr
    | '!' unary_expr
    ;

left_expr
	: prim_expr
	| left_expr '[' expr ']'
	| left_expr '.' IDENTIFIER %prec CLASS_MEMBER
    | left_expr '.' IDENTIFIER '(' actuals ')'
	| left_expr '(' actuals ')'
    | func_anonymous_def '(' actuals ')'
	;

prim_expr
	: IDENTIFIER
	| constant
	| '(' expr ')'
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

