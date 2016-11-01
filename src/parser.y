%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "errors.h"
    #include "ast.h"

    #undef YYDEBUG
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
    void *nil_val;
    char bool_val;
    int int_val;
    char str_val[80];
    type_t type_val;
    const_t const_val;
    expr_t expr_val;
    expr_bool_t expr_bool_val;
    list_t assigns_val;
    formal_t formal_val;
    list_t formals_val;
    actual_t actual_val;
    list_t actuals_val;
    var_def_t var_def_val;
    func_def_t func_def_val;
    field_t field_val;
    list_t fields_val;
    stmt_t stmt_val;
    list_t stmts_val;
    class_def_t class_def_val;
    list_t class_defs_val;
    prog_t prog_val;
}

%token OP_AND OP_OR OP_LE OP_GE OP_EQ OP_NE OP_ARROW
%token BOOL INT STRING FUNCTION VOID    ///< hidden type: function type
%token CLASS EXTENDS NEW THIS
%token IF ELSE FOR WHILE RETURN
%token PRINT READINTEGER READLINE

%token <nil_val> NIL
%token <bool_val> CONSTANT_BOOL
%token <int_val> CONSTANT_INT
%token <str_val> CONSTANT_STRING
%token <str_val> IDENTIFIER

%type <type_t> type
%type <const_t> constant
%type <expr_val> expr assign_expr or_expr and_expr eq_expr cmp_expr add_expr mul_expr unary_expr left_expr prim_expr
%type <expr_bool_val> bool_expr
%type <assigns_val> assign_list assign_list_body
%type <formal_val> formal
%type <formals_val> formals formals_body
%type <actual_val> actual
%type <actuals_val> actuals actuals_body
%type <var_def_val> var_def
%type <func_def_val> func_def func_normal_def func_anony_def
%type <field_val> field
%type <fields_val> fields
%type <stmt_val> stmt expr_stmt if_stmt while_stmt for_stmt return_stmt print_stmt
%type <stmts_val> stmts
%type <class_def_val> class_def
%type <class_defs_val> class_defs
%type <prog_val> program

/* to eliminate S/R conflict */
%nonassoc CLASS_FIELD
%left '(' ')'

/* to eliminate S/R conflict */
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
    /* error recovery */
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
    /* error recovery */
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
    | func_anony_def
    ;

func_normal_def
    : type IDENTIFIER '=' '(' formals ')' OP_ARROW '{' stmts '}' ';'
    /* error recovery */
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

func_anony_def
    : type '(' formals ')' OP_ARROW '{' stmts '}'
    /* error recovery */
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
    /* error recovery */
    | error {
        proposed_solution("expected keyword 'void' or at least 1 parameter");
    }
    ;

formals_body
    : formals_body ',' formal
    | formal
    | formals_body error formal
    {
        proposed_solution("expected ',' as separator");
    }
    | formals_body ',' error
    {
        proposed_solution("unexpected ','");
    }
    ;

formal
    : type IDENTIFIER
    /* error recovery */
    | type error
    {
        proposed_solution("expected identifier as parameter name");
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
    /* error recovery */
    | expr error
    {
        proposed_solution("expected ';'");
    }
    ;

if_stmt
    : IF '(' bool_expr ')' '{' stmts '}' %prec NOELSE
    | IF '(' bool_expr ')' '{' stmts '}' ELSE '{' stmts '}'
    /* error recovery */
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
    /* error recovery */
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
    /* error recovery */
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
    /* error recovery */
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
    /* error recovery */
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
    : actuals_body ',' actual
    | actual
    /* error recovery */
    | actuals_body error actual
    {
        proposed_solution("expected ',' as separator");
    }
    | actuals_body ',' error
    {
        proposed_solution("unexpected ','");
    }
    ;

actual
    : expr
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
    | VOID
    /* error recovery */
    | error {
        proposed_solution("expected keyword 'void' or at least 1 assign expression");
    }
    ;

assign_list_body
    : assign_list_body ',' assign_expr
    | assign_expr
    /* error recovery */
    | assign_list_body ',' error
    {
        proposed_solution("unexpected ','");
    }
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
	| left_expr '.' IDENTIFIER %prec CLASS_FIELD
    | left_expr '.' IDENTIFIER '(' actuals ')'
	| left_expr '(' actuals ')'
    | func_anony_def '(' actuals ')'
	;

prim_expr
	: IDENTIFIER
	| constant
	| '(' expr ')'
    | READINTEGER '(' ')'
    | READLINE '(' ')'
    | NEW IDENTIFIER '(' actuals ')'
    | NEW type '[' expr ']'
    /* error recovery */
	| '(' error ')'
    {
        proposed_solution("unexpected nested parenthesis");
    }
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
