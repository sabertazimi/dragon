%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "errors.h"

    #define YYDEBUG 1
    #define YYERROR_VERBOSE 1

    extern int yycolumn;
    extern char *yytext;
    int yylex(void);
    int yyerror(const char *msg);

    int parse_failed;
    int proposed_solution(const char *sol);
%}

%defines
%error-verbose
%locations

%union {
    char bool_val;
    int int_val;
    char str_val[80];
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

%left error

%start program

%%

program
    : class_defs
    ;

class_defs
    : class_defs class_def
    | class_def
    ;

class_def
    : CLASS IDENTIFIER '{' fields '}'
    | CLASS IDENTIFIER EXTENDS IDENTIFIER '{' fields '}'
    /* error recovery */
    | error IDENTIFIER '{' fields '}'
    {
        proposed_solution("expected keyword \"class\"");
    }
    | CLASS error '{' fields '}'
    {
        proposed_solution("expected identifier as class name");
    }
    | CLASS IDENTIFIER error fields '}'
    {
        proposed_solution("unmatched '{' or '}'");
    }
    | CLASS IDENTIFIER '{' fields error
    {
        proposed_solution("unmatched '{' or '}'");
    }
    | error IDENTIFIER EXTENDS IDENTIFIER '{' fields '}'
    {
        proposed_solution("expected keyword \"class\"");
    }
    | CLASS error EXTENDS IDENTIFIER '{' fields '}'
    {
        proposed_solution("expected identifier as class name");
    }
    | CLASS IDENTIFIER error IDENTIFIER '{' fields '}'
    {
        proposed_solution("expected keyword \"extends\"");
    }
    | CLASS IDENTIFIER EXTENDS error '{' fields '}'
    {
        proposed_solution("expected identifier as class name");
    }
    | CLASS IDENTIFIER EXTENDS IDENTIFIER error fields '}'
    {
        proposed_solution("unmatched '{' or '}'");
    }
    | CLASS IDENTIFIER EXTENDS IDENTIFIER '{' fields error
    {
        proposed_solution("unmatched '{' or '}'");
    }
    ;

fields
    : fields field
    | field
    ;

field
    : var_def
    | func_def
    ;

var_def
    : type IDENTIFIER ';'
    | type IDENTIFIER '=' assign_expr ';'
    | type error ';'
    {
        proposed_solution("expected identifier as variable name");
    }
    | type IDENTIFIER error
    {
        proposed_solution("expected ';' or expected '=' as assign operator");
    }
    | type error '=' assign_expr ';'
    {
        proposed_solution("expected identifier as variable name");
    }
    | type IDENTIFIER '=' assign_expr error
    {
        proposed_solution("expected ';'");
    }
    ;

type
    : INT
    | BOOL
    | STRING
    | VOID
    | CLASS IDENTIFIER
    | type '[' ']'
    | error IDENTIFIER
    {
        proposed_solution("unkown type");
    }
    | CLASS error
    {
        proposed_solution("expected identifier as class name");
    }
    ;

func_def
    : func_normal_def
    | func_anonymous_def
    ;

func_normal_def
    : type IDENTIFIER '=' '(' formals ')' OP_ARROW '{' stmts '}' ';'
    | type error '=' '(' formals ')' OP_ARROW '{' stmts '}' ';'
    {
        proposed_solution("expected identifier as variable name");
    }
    | type IDENTIFIER error '(' formals ')' OP_ARROW '{' stmts '}' ';'
    {
        proposed_solution("expected '=' as function defination");
    }
    | type IDENTIFIER '=' '(' formals ')' error '{' stmts '}' ';'
    {
        proposed_solution("expected '=>' as function defination");
    }
    | type IDENTIFIER '=' '(' formals ')' OP_ARROW error stmts '}' ';'
    {
        proposed_solution("unmatched '{' or '}'");
    }
    | type IDENTIFIER '=' '(' formals ')' OP_ARROW '{' stmts error ';'
    {
        proposed_solution("unmatched '{' or '}'");
    }
    | type IDENTIFIER '=' '(' formals ')' OP_ARROW '{' stmts '}' error
    {
        proposed_solution("expected ';'");
    }
    ;

func_anonymous_def
    : type '(' formals ')' OP_ARROW '{' stmts '}'
    | type '(' formals ')' error '{' stmts '}'
    {
        proposed_solution("expected '=>' as function defination");
    }
    | type '(' formals ')' OP_ARROW error stmts '}'
    {
        proposed_solution("unmatched '{' or '}'");
    }
    | type '(' formals ')' OP_ARROW '{' stmts error
    {
        proposed_solution("unmatched '{' or '}'");
    }
    ;

formals
    : formals_body
    | VOID
    ;

formals_body
    : formals_body ',' type IDENTIFIER
    | type IDENTIFIER
    | formals_body error type IDENTIFIER
    {
        proposed_solution("expected ',' as separator");
    }
    | formals_body ',' type error
    {
        proposed_solution("expected identifier as variable name");
    }
    | type error
    {
        proposed_solution("expected identifier as variable name");
    }
    ;

stmts
    : stmts stmt
    | /* empty */
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

expr_stmt
    : expr ';'
    | ';'
    | expr error
    {
        proposed_solution("expected ';'");
    }
    ;

if_stmt
    : IF '(' bool_expr ')' '{' stmts '}' %prec NOELSE
    | IF '(' bool_expr ')' '{' stmts '}' ELSE '{' stmts '}'
    | IF error bool_expr ')' '{' stmts '}' %prec NOELSE
    {
        proposed_solution("unmatched '(' or ')'");
    }
    | IF '(' bool_expr error '{' stmts '}' %prec NOELSE
    {
        proposed_solution("unmatched '(' or ')'");
    }
    | IF '(' bool_expr ')' error stmts '}' %prec NOELSE
    {
        proposed_solution("unmatched '{' or '}'");
    }
    ;

while_stmt
    : WHILE '(' bool_expr ')' '{' stmts '}'
    | WHILE error bool_expr ')' '{' stmts '}'
    {
        proposed_solution("unmatched '(' or ')'");
    }
    | WHILE '(' bool_expr error '{' stmts '}'
    {
        proposed_solution("unmatched '(' or ')'");
    }
    | WHILE '(' bool_expr ')' error stmts '}'
    {
        proposed_solution("unmatched '{' or '}'");
    }
    ;

for_stmt
    : FOR '(' assign_list ';' bool_expr ';' assign_list ')' '{' stmts '}'
    | FOR error assign_list ';' bool_expr ';' assign_list ')' '{' stmts '}'
    {
        proposed_solution("unmatched '(' or ')'");
    }
    | FOR '(' assign_list error bool_expr ';' assign_list ')' '{' stmts '}'
    {
        proposed_solution("expected ';' as separator between initializer and boolean expression");
    }
    | FOR '(' assign_list ';' bool_expr error assign_list ')' '{' stmts '}'
    {
        proposed_solution("expected ';' as separator between boolean expression and assignment");
    }
    | FOR '(' assign_list ';' bool_expr ';' assign_list error '{' stmts '}'
    {
        proposed_solution("unmatched '(' or ')'");
    }
    | FOR '(' assign_list ';' bool_expr ';' assign_list ')' error stmts '}'
    {
        proposed_solution("unmatched '{' or '}'");
    }
    ;

return_stmt
    : RETURN ';'
    | RETURN VOID ';'
    | RETURN expr ';'
    | RETURN error ';'
    {
        proposed_solution("unkown return value");
    }
    | RETURN VOID error
    {
        proposed_solution("expected ';'");
    }
    | RETURN expr error
    {
        proposed_solution("expected ';'");
    }
    ;

print_stmt
    : PRINT '(' expr ')' ';'
    | PRINT error expr ')' ';'
    {
        proposed_solution("unmatched '(' or ')'");
    }
    | PRINT '(' expr error ';'
    {
        proposed_solution("unmatched '(' or ')'");
    }
    | PRINT '(' expr ')' error
    {
        proposed_solution("expected ';'");
    }
    ;

actuals
    : actuals_body
    | /* empty */
    ;

actuals_body
    : actuals_body ',' expr
    | expr
    | actuals_body error expr
    {
        proposed_solution("expected ',' as separator");
    }
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
	/* | left_expr error assign_expr */
    /* { */
        /* proposed_solution("expected '=' as assign operator"); */
    /* } */
	;

assign_list
    : assign_list_body
    | VOID
    | error {
        proposed_solution("expected keyword 'void' or assign expression");
    }
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

constant
    : CONSTANT_INT
    | CONSTANT_BOOL
    | CONSTANT_STRING
    | NIL
    ;

%%

// return value will be ignored
int yyerror(const char *msg) {
    fprintf(stderr, "<<<=================\n");
    fprintf(stderr, "<%d:%d><Error>: %s\n", yylloc.first_line, yylloc.first_column, msg);
    srcbuf_print();
    memset(yytext, '\0', strlen(yytext));
    parse_failed = 1;
    return 0;
}


int proposed_solution(const char *sol) {
    fprintf(stderr, "<Proposed Solution>: %s\n", sol);
    fprintf(stderr, "=================>>>\n\n");
    return 0;
}
