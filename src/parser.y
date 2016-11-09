%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "errors.h"
    #include "ast.h"

    #undef YYDEBUG
    #define YYDEBUG 1
    #define YYERROR_VERBOSE 1

    extern char *yytext;
    int yylex(void);
    int yyerror(const char *msg);

    // enable/disable state machine working result output
    // yydebug = 1;

    int parse_failed;
    int proposed_solution(const char *sol);

    prog_t prog_tree;
%}

%defines
%error-verbose
%locations

%union {
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

%token END
%token NIL
%token BOOL INT STRING FUNCTION VOID    ///< hidden type: function type
%token OP_AND OP_OR OP_LE OP_GE OP_EQ OP_NE OP_ARROW
%token CLASS EXTENDS NEW THIS
%token IF ELSE FOR WHILE RETURN
%token PRINT READINTEGER READLINE

%token <bool_val> CONSTANT_BOOL
%token <int_val> CONSTANT_INT
%token <str_val> CONSTANT_STRING
%token <str_val> IDENTIFIER

%type <type_val> type
%type <const_val> constant
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
    : class_defs END
    {
        @$ = @1;
        $1 = list_rev($1);
        prog_tree = prog_new(@1, $1);
    }
    ;

class_defs
    : class_defs class_def
    {
        @$ = @2;
        $$ = list_new($2, $1);
    }
    | class_def
    {
        @$ = @1;
        $$ = list_new($1, NULL);
    }
    ;

class_def
    : CLASS IDENTIFIER '{' fields '}'
    {
        @$ = @2;
        $4 = list_rev($4);
        $$ = class_def_new(@2, $2, "\0", $4);
    }
    | CLASS IDENTIFIER EXTENDS IDENTIFIER '{' fields '}'
    {
        @$ = @2;
        $6 = list_rev($6);
        $$ = class_def_new(@2, $2, $4, $6);
    }
    /* error recovery */
    | error IDENTIFIER '{' fields '}'
    {
        @$ = @2;
        $$ = NULL;
        proposed_solution("expected keyword \"class\"");
    }
    | CLASS error '{' fields '}'
    {
        @$ = @2;
        $$ = NULL;
        proposed_solution("expected identifier as class name");
    }
    | CLASS IDENTIFIER error fields '}'
    {
        @$ = @2;
        $$ = NULL;
        proposed_solution("unmatched '{' or '}'");
    }
    | CLASS IDENTIFIER '{' fields error
    {
        @$ = @2;
        $$ = NULL;
        proposed_solution("unmatched '{' or '}'");
    }
    | error IDENTIFIER EXTENDS IDENTIFIER '{' fields '}'
    {
        @$ = @2;
        $$ = NULL;
        proposed_solution("expected keyword \"class\"");
    }
    | CLASS error EXTENDS IDENTIFIER '{' fields '}'
    {
        @$ = @2;
        $$ = NULL;
        proposed_solution("expected identifier as class name");
    }
    | CLASS IDENTIFIER error IDENTIFIER '{' fields '}'
    {
        @$ = @2;
        $$ = NULL;
        proposed_solution("expected keyword \"extends\"");
    }
    | CLASS IDENTIFIER EXTENDS error '{' fields '}'
    {
        @$ = @2;
        $$ = NULL;
        proposed_solution("expected identifier as class name");
    }
    | CLASS IDENTIFIER EXTENDS IDENTIFIER error fields '}'
    {
        @$ = @2;
        $$ = NULL;
        proposed_solution("unmatched '{' or '}'");
    }
    | CLASS IDENTIFIER EXTENDS IDENTIFIER '{' fields error
    {
        @$ = @2;
        $$ = NULL;
        proposed_solution("unmatched '{' or '}'");
    }
    ;

fields
    : fields field
    {
        @$ = @2;
        $$ = list_new($2, $1);
    }
    | field
    {
        @$ = @1;
        $$ = list_new($1, NULL);
    }
    ;

field
    : var_def
    {
        @$ = @1;
        $$ = field_var_new(FIELD_VAR, @1, $1);
    }
    | func_def
    {
        @$ = @1;
        $$ = field_func_new(FIELD_FUNC, @1, $1);
    }
    ;

var_def
    : type IDENTIFIER ';'
    {
        @$ = @2;
        $$ = var_def_new(@2, $1, $2, NULL);
    }
    | type IDENTIFIER '=' assign_expr ';'
    {
        @$ = @2;
        $$ = var_def_new(@2, $1, $2, (expr_assign_t)$4);
    }
    /* error recovery */
    | type error ';'
    {
        @$ = @2;
        $$ = NULL;
        proposed_solution("expected identifier as variable name");
    }
    | type IDENTIFIER error
    {
        @$ = @2;
        $$ = NULL;
        proposed_solution("expected ';' or expected '=' as assign operator");
    }
    | type error '=' assign_expr ';'
    {
        @$ = @2;
        $$ = NULL;
        proposed_solution("expected identifier as variable name");
    }
    | type IDENTIFIER '=' assign_expr error
    {
        @$ = @2;
        $$ = NULL;
        proposed_solution("expected ';'");
    }
    ;

type
    : INT
    {
        @$ = @1;
        $$ = type_basic_new(TYPE_INT, @1);
    }
    | BOOL
    {
        @$ = @1;
        $$ = type_basic_new(TYPE_BOOL, @1);
    }
    | STRING
    {
        @$ = @1;
        $$ = type_basic_new(TYPE_STRING, @1);
    }
    | VOID
    {
        @$ = @1;
        $$ = type_basic_new(TYPE_VOID, @1);
    }
    | CLASS IDENTIFIER
    {
        @$ = @2;
        $$ = type_class_new(TYPE_CLASS, @2, $2);
    }
    | type '[' ']'
    {
        @$ = @1;
        $$ = type_array_new(TYPE_ARRAY, @1, $1);
    }
    /* error recovery */
    | error IDENTIFIER
    {
        @$ = @2;
        $$ = NULL;
        proposed_solution("unkown type");
    }
    | CLASS error
    {
        @$ = @2;
        $$ = NULL;
        proposed_solution("expected identifier as class name");
    }
    ;

func_def
    : func_normal_def
    {
        @$ = @1;
        $$ = $1;
    }
    | func_anony_def
    {
        @$ = @1;
        $$ = $1;
    }
    ;

func_normal_def
    : type IDENTIFIER '=' '(' formals ')' OP_ARROW '{' stmts '}' ';'
    {
        @$ = @2;
        $5 = list_rev($5);
        $9 = list_rev($9);
        $$ = func_normal_def_new(FUNC_NORMAL_DEF, @2, $1, $5, $9, $2);
    }
    /* error recovery */
    | type error '=' '(' formals ')' OP_ARROW '{' stmts '}' ';'
    {
        @$ = @2;
        $$ = NULL;
        proposed_solution("expected identifier as variable name");
    }
    | type IDENTIFIER error '(' formals ')' OP_ARROW '{' stmts '}' ';'
    {
        @$ = @2;
        $$ = NULL;
        proposed_solution("expected '=' as function defination");
    }
    | type IDENTIFIER '=' '(' formals ')' error '{' stmts '}' ';'
    {
        @$ = @2;
        $$ = NULL;
        proposed_solution("expected '=>' as function defination");
    }
    | type IDENTIFIER '=' '(' formals ')' OP_ARROW error stmts '}' ';'
    {
        @$ = @2;
        $$ = NULL;
        proposed_solution("unmatched '{' or '}'");
    }
    | type IDENTIFIER '=' '(' formals ')' OP_ARROW '{' stmts error ';'
    {
        @$ = @2;
        $$ = NULL;
        proposed_solution("unmatched '{' or '}'");
    }
    | type IDENTIFIER '=' '(' formals ')' OP_ARROW '{' stmts '}' error
    {
        @$ = @2;
        $$ = NULL;
        proposed_solution("expected ';'");
    }
    ;

func_anony_def
    : type '(' formals ')' OP_ARROW '{' stmts '}'
    {
        @$ = @1;
        $3 = list_rev($3);
        $7 = list_rev($7);
        $$ = func_anony_def_new(FUNC_ANONY_DEF, @1, $1, $3, $7);
    }
    /* error recovery */
    | type '(' formals ')' error '{' stmts '}'
    {
        @$ = @1;
        $$ = NULL;
        proposed_solution("expected '=>' as function defination");
    }
    | type '(' formals ')' OP_ARROW error stmts '}'
    {
        @$ = @1;
        $$ = NULL;
        proposed_solution("unmatched '{' or '}'");
    }
    | type '(' formals ')' OP_ARROW '{' stmts error
    {
        @$ = @1;
        $$ = NULL;
        proposed_solution("unmatched '{' or '}'");
    }
    ;

formals
    : formals_body
    {
        @$ = @1;
        $$ = $1;
    }
    | VOID
    {
        @$ = @1;
        $$ = NULL;
    }
    /* error recovery */
    | error {
        @$ = @1;
        $$ = NULL;
        proposed_solution("expected keyword 'void' or at least 1 parameter");
    }
    ;

formals_body
    : formals_body ',' formal
    {
        @$ = @3;
        $$ = list_new($3, $1);
    }
    | formal
    {
        @$ = @1;
        $$ = list_new($1, NULL);
    }
    /* error recovery */
    | formals_body error formal
    {
        @$ = @3;
        $$ = NULL;
        proposed_solution("expected ',' as separator");
    }
    | formals_body ',' error
    {
        @$ = @3;
        $$ = NULL;
        proposed_solution("unexpected ','");
    }
    ;

formal
    : type IDENTIFIER
    {
        @$ = @2;
        $$ = formal_new(@2, $1, $2);
    }
    /* error recovery */
    | type error
    {
        @$ = @2;
        $$ = NULL;
        proposed_solution("expected identifier as parameter name");
    }
    ;

stmts
    : stmts stmt
    {
        @$ = @2;
        $$ = list_new($2, $1);
    }
    | /* empty */
    {
        $$ = NULL;
    }
    ;

stmt
    : var_def
    {
        @$ = @1;
        $$ = stmt_var_def_new(STMT_VAR_DEF, @1, $1);
    }
    | expr_stmt
    {
        @$ = @1;
        $$ = $1;
    }
    | if_stmt
    {
        @$ = @1;
        $$ = $1;
    }
    | while_stmt
    {
        @$ = @1;
        $$ = $1;
    }
    | for_stmt
    {
        @$ = @1;
        $$ = $1;
    }
    | return_stmt
    {
        @$ = @1;
        $$ = $1;
    }
    | print_stmt
    {
        @$ = @1;
        $$ = $1;
    }
    ;

expr_stmt
    : expr ';'
    {
        @$ = @1;
        $$ = stmt_expr_new(STMT_EXPR, @1, $1);
    }
    | ';'
    {
        @$ = @1;
        $$ = stmt_expr_new(STMT_EXPR, @1, NULL);
    }
    /* error recovery */
    | expr error
    {
        @$ = @1;
        $$ = NULL;
        proposed_solution("expected ';'");
    }
    ;

if_stmt
    : IF '(' bool_expr ')' '{' stmts '}' %prec NOELSE
    {
        @$ = @1;
        $6 = list_rev($6);
        $$ = stmt_if_new(STMT_IF, @1, $3, $6, NULL);
    }
    | IF '(' bool_expr ')' '{' stmts '}' ELSE '{' stmts '}'
    {
        @$ = @1;
        $6  = list_rev($6);
        $10 = list_rev($10);
        $$  = stmt_if_new(STMT_IF, @1, $3, $6, $10);
    }
    /* error recovery */
    | IF error bool_expr ')' '{' stmts '}' %prec NOELSE
    {
        @$ = @1;
        $$ = NULL;
        proposed_solution("unmatched '(' or ')'");
    }
    | IF '(' bool_expr error '{' stmts '}' %prec NOELSE
    {
        @$ = @1;
        $$ = NULL;
        proposed_solution("unmatched '(' or ')'");
    }
    | IF '(' bool_expr ')' error stmts '}' %prec NOELSE
    {
        @$ = @1;
        $$ = NULL;
        proposed_solution("unmatched '{' or '}'");
    }
    ;

while_stmt
    : WHILE '(' bool_expr ')' '{' stmts '}'
    {
        @$ = @1;
        $6 = list_rev($6);
        $$ = stmt_while_new(STMT_WHILE, @1, $3, $6);
    }
    /* error recovery */
    | WHILE error bool_expr ')' '{' stmts '}'
    {
        @$ = @1;
        $$ = NULL;
        proposed_solution("unmatched '(' or ')'");
    }
    | WHILE '(' bool_expr error '{' stmts '}'
    {
        @$ = @1;
        $$ = NULL;
        proposed_solution("unmatched '(' or ')'");
    }
    | WHILE '(' bool_expr ')' error stmts '}'
    {
        @$ = @1;
        $$ = NULL;
        proposed_solution("unmatched '{' or '}'");
    }
    ;

for_stmt
    : FOR '(' assign_list ';' bool_expr ';' assign_list ')' '{' stmts '}'
    {
        @$  = @1;
        $3  = list_rev($3);
        $7  = list_rev($7);
        $10 = list_rev($10);
        $$  = stmt_for_new(STMT_FOR, @1, $3, $5, $7, $10);
    }
    /* error recovery */
    | FOR error assign_list ';' bool_expr ';' assign_list ')' '{' stmts '}'
    {
        @$ = @1;
        $$ = NULL;
        proposed_solution("unmatched '(' or ')'");
    }
    | FOR '(' assign_list error bool_expr ';' assign_list ')' '{' stmts '}'
    {
        @$ = @1;
        $$ = NULL;
        proposed_solution("expected ';' as separator between initializer and boolean expression");
    }
    | FOR '(' assign_list ';' bool_expr error assign_list ')' '{' stmts '}'
    {
        @$ = @1;
        $$ = NULL;
        proposed_solution("expected ';' as separator between boolean expression and assignment");
    }
    | FOR '(' assign_list ';' bool_expr ';' assign_list error '{' stmts '}'
    {
        @$ = @1;
        $$ = NULL;
        proposed_solution("unmatched '(' or ')'");
    }
    | FOR '(' assign_list ';' bool_expr ';' assign_list ')' error stmts '}'
    {
        @$ = @1;
        $$ = NULL;
        proposed_solution("unmatched '{' or '}'");
    }
    ;

return_stmt
    : RETURN ';'
    {
        @$ = @1;
        $$ = stmt_return_new(STMT_RETURN, @1, NULL);
    }
    | RETURN VOID ';'
    {
        @$ = @1;
        $$ = stmt_return_new(STMT_RETURN, @1, NULL);
    }
    | RETURN expr ';'
    {
        @$ = @1;
        $$ = stmt_return_new(STMT_RETURN, @1, $2);
    }
    /* error recovery */
    | RETURN error ';'
    {
        @$ = @1;
        $$ = NULL;
        proposed_solution("unkown return value");
    }
    | RETURN VOID error
    {
        @$ = @2;
        $$ = NULL;
        proposed_solution("expected ';'");
    }
    | RETURN expr error
    {
        @$ = @2;
        $$ = NULL;
        proposed_solution("expected ';'");
    }
    ;

print_stmt
    : PRINT '(' expr ')' ';'
    {
        @$ = @1;
        $$ = stmt_print_new(STMT_PRINT, @1, $3);
    }
    /* error recovery */
    | PRINT error expr ')' ';'
    {
        @$ = @3;
        $$ = NULL;
        proposed_solution("unmatched '(' or ')'");
    }
    | PRINT '(' expr error ';'
    {
        @$ = @3;
        $$ = NULL;
        proposed_solution("unmatched '(' or ')'");
    }
    | PRINT '(' expr ')' error
    {
        @$ = @3;
        $$ = NULL;
        proposed_solution("expected ';'");
    }
    ;

actuals
    : actuals_body
    {
        @$ = @1;
        $$ = $1;
    }
    | /* empty */
    {
        $$ = NULL;
    }
    ;

actuals_body
    : actuals_body ',' actual
    {
        @$ = @3;
        $$ = list_new($3, $1);
    }
    | actual
    {
        @$ = @1;
        $$ = list_new($1, NULL);
    }
    /* error recovery */
    | actuals_body error actual
    {
        @$ = @3;
        $$ = NULL;
        proposed_solution("expected ',' as separator");
    }
    | actuals_body ',' error
    {
        @$ = @3;
        $$ = NULL;
        proposed_solution("unexpected ','");
    }
    ;

actual
    : expr
    {
        @$ = @1;
        $$ = actual_new(@1, $1);
    }
    ;

bool_expr
    : expr
    {
        @$ = @1;
        $$ = expr_bool_new(EXPR_BOOL, @1, $1);
    }
    ;

expr
    : assign_expr
    {
        @$ = @1;
        $$ = $1;
    }
    ;

assign_expr
	: or_expr
    {
        @$ = @1;
        $$ = $1;
    }
	| left_expr '=' assign_expr
    {
        @$ = @2;
        $$ = expr_assign_new(EXPR_ASSIGN, @2, (expr_left_t)$1, (expr_assign_t)$3);
    }
	;

assign_list
    : assign_list_body
    {
        @$ = @1;
        $$ = $1;
    }
    | VOID
    {
        @$ = @1;
        $$ = NULL;
    }
    /* error recovery */
    | error {
        @$ = @1;
        $$ = NULL;
        proposed_solution("expected keyword 'void' or at least 1 assign expression");
    }
    ;

assign_list_body
    : assign_list_body ',' assign_expr
    {
        @$ = @3;
        $$ = list_new($3, $1);
    }
    | assign_expr
    {
        @$ = @1;
        $$ = list_new($1, NULL);
    }
    /* error recovery */
    | assign_list_body ',' error
    {
        @$ = @3;
        $$ = NULL;
        proposed_solution("unexpected ','");
    }
    ;

or_expr
	: and_expr
    {
        @$ = @1;
        $$ = $1;
    }
	| or_expr OP_OR and_expr
    {
        @$ = @2;
        $$ = expr_or_new(EXPR_OR, @2, (expr_or_t)$1, (expr_and_t)$3);
    }
	;

and_expr
	: eq_expr
    {
        @$ = @1;
        $$ = $1;
    }
	| and_expr OP_AND eq_expr
    {
        @$ = @2;
        $$ = expr_and_new(EXPR_AND, @2, (expr_and_t)$1, (expr_eq_t)$3);
    }
	;

eq_expr
	: cmp_expr
    {
        @$ = @1;
        $$ = $1;
    }
	| eq_expr OP_EQ cmp_expr
    {
        @$ = @2;
        $$ = expr_eq_new(EXPR_EQ, EXPR_EQ_EQ, @2, (expr_eq_t)$1, (expr_cmp_t)$3);
    }
	| eq_expr OP_NE cmp_expr
    {
        @$ = @2;
        $$ = expr_eq_new(EXPR_EQ, EXPR_EQ_NE, @2, (expr_eq_t)$1, (expr_cmp_t)$3);
    }
	;

cmp_expr
	: add_expr
    {
        @$ = @1;
        $$ = $1;
    }
	| cmp_expr '<' add_expr
    {
        @$ = @2;
        $$ = expr_cmp_new(EXPR_CMP, EXPR_CMP_LT, @2, (expr_cmp_t)$1, (expr_add_t)$3);
    }
	| cmp_expr '>' add_expr
    {
        @$ = @2;
        $$ = expr_cmp_new(EXPR_CMP, EXPR_CMP_GT, @2, (expr_cmp_t)$1, (expr_add_t)$3);
    }
	| cmp_expr OP_LE add_expr
    {
        @$ = @2;
        $$ = expr_cmp_new(EXPR_CMP, EXPR_CMP_LE, @2, (expr_cmp_t)$1, (expr_add_t)$3);
    }
	| cmp_expr OP_GE add_expr
    {
        @$ = @2;
        $$ = expr_cmp_new(EXPR_CMP, EXPR_CMP_GE, @2, (expr_cmp_t)$1, (expr_add_t)$3);
    }
	;

add_expr
	: mul_expr
    {
        @$ = @1;
        $$ = $1;
    }
	| add_expr '+' mul_expr
    {
        @$ = @2;
        $$ = expr_add_new(EXPR_ADD, EXPR_ADD_ADD, @2, (expr_add_t)$1, (expr_mul_t)$3);
    }
	| add_expr '-' mul_expr
    {
        @$ = @2;
        $$ = expr_add_new(EXPR_ADD, EXPR_ADD_SUB, @2, (expr_add_t)$1, (expr_mul_t)$3);
    }
	;

mul_expr
	: unary_expr
    {
        @$ = @1;
        $$ = $1;
    }
	| mul_expr '*' unary_expr
    {
        @$ = @2;
        $$ = expr_mul_new(EXPR_MUL, EXPR_MUL_MUL, @2, (expr_mul_t)$1, (expr_unary_t)$3);
    }
	| mul_expr '/' unary_expr
    {
        @$ = @2;
        $$ = expr_mul_new(EXPR_MUL, EXPR_MUL_DIV, @2, (expr_mul_t)$1, (expr_unary_t)$3);
    }
	| mul_expr '%' unary_expr
    {
        @$ = @2;
        $$ = expr_mul_new(EXPR_MUL, EXPR_MUL_MOD, @2, (expr_mul_t)$1, (expr_unary_t)$3);
    }
	;

unary_expr
    : left_expr
    {
        @$ = @1;
        $$ = $1;
    }
    | '+' unary_expr
    {
        @$ = @1;
        $$ = expr_unary_new(EXPR_UNARY, EXPR_UNARY_PLUS, @1, (expr_unary_t)$2);
    }
    | '-' unary_expr
    {
        @$ = @1;
        $$ = expr_unary_new(EXPR_UNARY, EXPR_UNARY_MINUS, @1, (expr_unary_t)$2);
    }
    | '!' unary_expr
    {
        @$ = @1;
        $$ = expr_unary_new(EXPR_UNARY, EXPR_UNARY_NOT, @1, (expr_unary_t)$2);
    }
    ;

left_expr
	: prim_expr
    {
        @$ = @1;
        $$ = $1;
    }
    | THIS
    {
        @$ = @1;
        $$ = expr_left_this_new(EXPR_LEFT, EXPR_LEFT_THIS, @1);
    }
	| left_expr '[' expr ']'
    {
        @$ = @1;
        $$ = expr_left_index_new(EXPR_LEFT, EXPR_LEFT_INDEX, @1, (expr_left_t)$1, $3);
    }
	| left_expr '.' IDENTIFIER %prec CLASS_FIELD
    {
        @$ = @3;
        $$ = expr_left_class_field_new(EXPR_LEFT, EXPR_LEFT_CLASS_FIELD, @3, (expr_left_t)$1, $3);
    }
    | left_expr '.' IDENTIFIER '(' actuals ')'
    {
        @$ = @3;
        $5 = list_rev($5);
        $$ = expr_left_class_call_new(EXPR_LEFT, EXPR_LEFT_CLASS_CALL, @3, (expr_left_t)$1, $3, $5);
    }
	| IDENTIFIER '(' actuals ')'
    {
        @$ = @1;
        $3 = list_rev($3);
        $$ = expr_left_func_call_new(EXPR_LEFT, EXPR_LEFT_FUNC_CALL, @1, $1, $3);
    }
    | func_anony_def '(' actuals ')'
    {
        @$ = @1;
        $3 = list_rev($3);
        $$ = expr_left_anony_call_new(EXPR_LEFT, EXPR_LEFT_ANONY_CALL, @1, (func_anony_def_t)$1, $3);
    }
	;

prim_expr
	: IDENTIFIER
    {
        @$ = @1;
        $$ = expr_prim_ident_new(EXPR_PRIM, EXPR_PRIM_IDENT, @1, $1);
    }
	| constant
    {
        @$ = @1;
        $$ = expr_prim_const_new(EXPR_PRIM, EXPR_PRIM_CONST, @1, $1);
    }
	| '(' expr ')'
    {
        @$ = @2;
        $$ = $2;
    }
    | READINTEGER '(' ')'
    {
        @$ = @1;
        $$ = expr_prim_read_new(EXPR_PRIM, EXPR_PRIM_READINT, @1);
    }
    | READLINE '(' ')'
    {
        @$ = @1;
        $$ = expr_prim_read_new(EXPR_PRIM, EXPR_PRIM_READLINE, @1);
    }
    | NEW IDENTIFIER '(' actuals ')'
    {
        @$ = @2;
        $4 = list_rev($4);
        $$ = expr_prim_newclass_new(EXPR_PRIM, EXPR_PRIM_NEWCLASS, @2, $2, $4);
    }
    | NEW type '[' expr ']'
    {
        @$ = @2;
        $$ = expr_prim_newarray_new(EXPR_PRIM, EXPR_PRIM_NEWARRAY, @2, $2, $4);
    }
    /* error recovery */
	| '(' error ')'
    {
        @$ = @2;
        $$ = NULL;
        proposed_solution("unexpected nested parenthesis");
    }
	;

constant
    : CONSTANT_INT
    {
        @$ = @1;
        $$ = const_num_new(CONST_INT, @1, $1);
    }
    | CONSTANT_BOOL
    {
        @$ = @1;
        $$ = const_num_new(CONST_BOOL, @1, $1);
    }
    | CONSTANT_STRING
    {
        @$ = @1;
        $$ = const_string_new(CONST_STRING, @1, $1);
    }
    | NIL
    {
        @$ = @1;
        $$ = const_nil_new(CONST_NIL, @1);
    }
    ;

%%

// return value will be ignored
int yyerror(const char *msg) {
    dragon_report(yylloc, "%s", msg);
    memset(yytext, '\0', strlen(yytext));
    parse_failed = 1;
    return 0;
}

int proposed_solution(const char *sol) {
    fprintf(stderr, "    proposed solution: %s\n", sol);
    return 0;
}
