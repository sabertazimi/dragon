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


%nonassoc NoELSE
%nonassoc ELSE

/* %nonassoc '=' */
/* %left OP_OR */
/* %left OP_AND */
/* %left OP_EQ OP_NE */
/* %left OP_GE OP_LE '<' '>' */
/* %left '+' '-' */ 
/* %left '*' '/' '%' */
/* %left NEG */
/* %nonassoc '!' */
/* %left CALL_EXPR PAREN_EXPR */
/* %left BOOL INT STRING VOID */

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

fields: fields field
      | field
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

func_normal_def: type IDENTIFIER '=' '(' formals ')' OP_ARROW '{' stmts '}'
               ;

func_anonymous_def: '(' formals ')' OP_ARROW '{' stmts '}'
                  ;

formals: formals_body
       |
       ;

formals_body: formals_body ',' var
            | var
            ;

stmts: stmts stmt
     |
     ;

stmt: var_def
    | expr_stmt ';'
    | if_stmt
    | while_stmt
    | for_stmt
    | return_stmt ';'
    | print_stmt ';'
    ;

expr_stmt: expr ';'
         | ';'
         ;

if_stmt: IF '(' bool_expr ')' '{' stmts '}' %prec NoELSE
       | IF '(' bool_expr ')' '{' stmts '}' ELSE '{' stmts '}'
       ;

while_stmt: WHILE '(' bool_expr ')' '{' stmts '}'
          ;

for_stmt: FOR '(' simple_stmt ';' bool_expr ';' simple_stmt ')' '{' stmts '}'
        ;

return_stmt: RETURN
           | RETURN expr
           ;

print_stmt: PRINT '(' expr ')'
          ;

actuals: actuals_body
       |
       ;

actuals_body: actuals_body ',' expr
            | expr
            ;

bool_expr: expr
         ;

prim_expr
	: IDENTIFIER
	| CONSTANT
	| '(' expr ')'
	;

left_expr
	: prim_expr
	| left_expr '[' expression ']'
	| left_expr '.' IDENTIFIER
    | left_expr '.' IDENTIFIER '(' actuals ')'
	| left_expr '(' actuals ')'
    | func_anonymous_def '(' actuals ')'
	;

mul_expr
	: left_expr
	| mul_expr '*' left_expr
	| mul_expr '/' left_expr
	| mul_expr '%' left_expr
	;

add_expr
	: mul_expr
	| add_expr '+' mul_expr
	| add_expr '-' mul_expr
	;

cmp_expr
	: add_expr
	| cmp_expr '<' additive_expression
	| cmp_expr '>' additive_expression
	| cmp_expr LE_OP additive_expression
	| cmp_expr GE_OP additive_expression
	;

equality_expression
	: relational_expression
	| equality_expression EQ_OP relational_expression
	| equality_expression NE_OP relational_expression
	;

logical_and_expression
	: equality_expression
	| logical_and_expression AND_OP equality_expression
	;

logical_or_expression
	: logical_and_expression
	| logical_or_expression OR_OP logical_and_expression
	;

assignment_expression
	: logical_or_expression
	| postfix_expression assignment_operator assignment_expression
	;

assignment_operator
	: '='
	| MUL_ASSIGN
	| DIV_ASSIGN
	| MOD_ASSIGN
	| ADD_ASSIGN
	| SUB_ASSIGN
	| LEFT_ASSIGN
	| RIGHT_ASSIGN
	| AND_ASSIGN
	| XOR_ASSIGN
	| OR_ASSIGN
	;

expression
	: assignment_expression
	| expression ',' assignment_expression
	;

constant_expression
	: logical_or_expression
	;


cmp_expr

expr: constant
    | left_val
    | THIS
    | call %prec CALL_EXPR
    | '(' expr ')' %prec PAREN_EXPR
    | expr OP_AND expr
    | expr OP_OR expr
    | expr '<' expr
    | expr OP_LE expr
    | expr '>' expr
    | expr OP_GE expr
    | expr OP_EQ expr
    | expr OP_NE expr
    | expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | expr '%' expr
    | '-' expr %prec NEG
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

