%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "location.h"
    #include "errors/errors.h"
    #include "libs/List.h"
    #include "ast/ast.h"
    #include "ast/Tree.h"

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
    Const *const_val;
    expr_t expr_val;
    expr_bool_t expr_bool_val;
    List<var_def_t> formals_val;
    List<expr_t> actuals_val;
    var_def_t var_def_val;
    func_def_t func_def_val;
    field_t field_val;
    List<field_t> fields_val;
    stmt_t stmt_val;
    List<stmt_t> stmts_val;
    class_def_t class_def_val;
    List<class_def_t> class_defs_val;
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
%type <formals_val> formals vars
%type <actuals_val> actuals exprs
%type <var_def_val> var_def var
%type <func_def_val> func_def
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
        prog_tree = prog_new(locdup(&@1), $1);
    }
    ;

class_defs
    : class_defs class_def
    {
        @$ = @2;
        ($$ = $1)->append($2);
    }
    | class_def
    {
        @$ = @1;
        ($$ = new List<class_def_t>())->append($1);
    }
    ;

class_def
    : CLASS IDENTIFIER '{' fields '}'
    {
        @$ = @2;
        $$ = class_def_new(@2, $2, strdup("\0"), $4);
    }
    | CLASS IDENTIFIER EXTENDS IDENTIFIER '{' fields '}'
    {
        @$ = @2;
        $$ = class_def_new(@2, $2, $4, $6);
    }
    /* error recovery */
    | error IDENTIFIER '{' fields '}'
    {
        @$ = @2;
        $$ = 0;
        proposed_solution("expected keyword \"class\"");
    }
    | CLASS error '{' fields '}'
    {
        @$ = @2;
        $$ = 0;
        proposed_solution("expected identifier as class name");
    }
    | CLASS IDENTIFIER error fields '}'
    {
        @$ = @2;
        $$ = 0;
        proposed_solution("unmatched '{' or '}'");
    }
    | CLASS IDENTIFIER '{' fields error
    {
        @$ = @2;
        $$ = 0;
        proposed_solution("unmatched '{' or '}'");
    }
    | error IDENTIFIER EXTENDS IDENTIFIER '{' fields '}'
    {
        @$ = @2;
        $$ = 0;
        proposed_solution("expected keyword \"class\"");
    }
    | CLASS error EXTENDS IDENTIFIER '{' fields '}'
    {
        @$ = @2;
        $$ = 0;
        proposed_solution("expected identifier as class name");
    }
    | CLASS IDENTIFIER error IDENTIFIER '{' fields '}'
    {
        @$ = @2;
        $$ = 0;
        proposed_solution("expected keyword \"extends\"");
    }
    | CLASS IDENTIFIER EXTENDS error '{' fields '}'
    {
        @$ = @2;
        $$ = 0;
        proposed_solution("expected identifier as class name");
    }
    | CLASS IDENTIFIER EXTENDS IDENTIFIER error fields '}'
    {
        @$ = @2;
        $$ = 0;
        proposed_solution("unmatched '{' or '}'");
    }
    | CLASS IDENTIFIER EXTENDS IDENTIFIER '{' fields error
    {
        @$ = @2;
        $$ = 0;
        proposed_solution("unmatched '{' or '}'");
    }
    ;

fields
    : fields field
    {
        @$ = @2;
        ($$ = $1)->append($2);
    }
    | field
    {
        @$ = @1;
        ($$ = new List<class_def_t>())->append($1);
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
    : var ';'
    {
        @$ = @1;
        $$ = $1;
    }
    | var error
    {
        @$ = @1;
        $$ = 0;
        proposed_solution("expected ';' or expected '=' as assign operator");
    }
    ;


var
    : type IDENTIFIER
    {
        @$ = @2;
        $$ = var_def_new(@2, $1, $2, 0);
    }
    /* error recovery */
    | type error
    {
        @$ = @2;
        $$ = 0;
        proposed_solution("expected identifier as variable name");
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
        $$ = 0;
        proposed_solution("unkown type");
    }
    | CLASS error
    {
        @$ = @2;
        $$ = 0;
        proposed_solution("expected identifier as class name");
    }
    ;

func_def
    : type IDENTIFIER '=' '(' formals ')' OP_ARROW stmt_block ';'
    {
        @$ = @2;
        $$ = func_normal_def_new(FUNC_NORMAL_DEF, @2, $1, $5, $9, $2);
    }
    /* error recovery */
    | type error '=' '(' formals ')' OP_ARROW stmt_block ';'
    {
        @$ = @2;
        $$ = 0;
        proposed_solution("expected identifier as variable name");
    }
    | type IDENTIFIER error '(' formals ')' OP_ARROW stmt_block ';'
    {
        @$ = @2;
        $$ = 0;
        proposed_solution("expected '=' as function defination");
    }
    | type IDENTIFIER '=' '(' formals ')' error stmt_block  ';'
    {
        @$ = @2;
        $$ = 0;
        proposed_solution("expected '=>' as function defination");
    }
    | type IDENTIFIER '=' '(' formals ')' OP_ARROW stmt_block error
    {
        @$ = @2;
        $$ = 0;
        proposed_solution("expected ';'");
    }
    ;

formals
    : vars
    {
        @$ = @1;
        $$ = $1;
    }
    | /* empty */
    {
        $$ = new List<var_def_t>();
    }
    ;

vars
    : vars ',' var
    {
        @$ = @3
        ($$ = $1)->append($3);
    }
    | var
    {
        @$ = @1
        ($$ = new List<class_def_t>())->append($1);
    }
    /* error recovery */
    | vars error var
    {
        @$ = @3;
        $$ = 0;
        proposed_solution("expected ',' as separator");
    }
    | vars ',' error
    {
        @$ = @2;
        $$ = 0;
        proposed_solution("unexpected ','");
    }
    ;

actuals
    : exprs
    {
        @$ = @1;
        $$ = $1;
    }
    | /* empty */
    {
        $$ = new List<expr_t>();
    }
    ;

exprs
    : exprs ',' expr
    {
        @$ = @3;
        ($$ = $1)->append($3);
    }
    | expr
    {
        @$ = @1;
        ($$ = new List<class_def_t>())->append($1);
    }
    /* error recovery */
    | exprs error expr
    {
        @$ = @3;
        $$ = 0;
        proposed_solution("expected ',' as separator");
    }
    | exprs ',' error
    {
        @$ = @3;
        $$ = 0;
        proposed_solution("unexpected ','");
    }
    ;

stmt_block
    : '{' stmts '}'
    {
        @$ = @1;
        $$ = new Block($2, locdup(&@1));
    }
    | error stmts '}'
    {
        @$ = @2;
        $$ = 0;
        proposed_solution("unmatched '{' or '}'");
    }
    | '{' stmts error
    {
        @$ = @1;
        $$ = 0;
        proposed_solution("unmatched '{' or '}'");
    }
    ;

stmts
    : stmts stmt
    {
        @$ = @2;
        ($$ = $1)->append($2);
    }
    | /* empty */
    {
        $$ = new List<stmt_t>();
    }
    ;

stmt
    : var_def
    {
        @$ = @1;
        $$ = $1;
    }
    | simple_stmt ';'
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
    | return_stmt ';'
    {
        @$ = @1;
        $$ = $1;
    }
    | print_stmt ';'
    {
        @$ = @1;
        $$ = $1;
    }
    | stmt_block
    {
        @$ = @1;
        $$ = $1;
    }
    /* error recovery */
    | simple_stmt error
    {
        @$ = @1;
        $$ = 0;
        proposed_solution("expected ';'");
    }
    | return_stmt error
    {
        @$ = @1;
        $$ = 0;
        proposed_solution("expected ';'");
    }
    | print_stmt error
    {
        @$ = @1;
        $$ = 0;
        proposed_solution("expected ';'");
    }
    ;

simple_stmt
    : Lvalue '=' expr
    {
        @$ = @2;
        $$ = expr_assign_new(EXPR_ASSIGN, locdup(&@2), (expr_left_t)$1, (expr_assign_t)$3);
    }
    | call
    {
        @$ = @1;
        $$ = new Exec($1, locdup(&@1));
    }
    ;

if_stmt
    : IF '(' expr ')' stmt %prec NOELSE
    {
        @$ = @1;
        $$ = stmt_if_new(STMT_IF, @1, $3, $6, 0);
    }
    | IF '(' expr ')' stmt ELSE stmt
    {
        @$ = @1;
        $$  = stmt_if_new(STMT_IF, @1, $3, $6, $10);
    }
    /* error recovery */
    | IF error expr ')' stmt %prec NOELSE
    {
        @$ = @1;
        $$ = 0;
        proposed_solution("unmatched '(' or ')'");
    }
    | IF '(' expr error stmt %prec NOELSE
    {
        @$ = @1;
        $$ = 0;
        proposed_solution("unmatched '(' or ')'");
    }
    ;

while_stmt
    : WHILE '(' expr ')' stmt
    {
        @$ = @1;
        $$ = stmt_while_new(STMT_WHILE, @1, $3, $6);
    }
    /* error recovery */
    | WHILE error expr ')' stmt
    {
        @$ = @1;
        $$ = 0;
        proposed_solution("unmatched '(' or ')'");
    }
    | WHILE '(' expr error stmt
    {
        @$ = @1;
        $$ = 0;
        proposed_solution("unmatched '(' or ')'");
    }
    ;

for_stmt
    : FOR '(' simple_stmt ';' expr ';' simple_stmt ')' stmt
    {
        @$  = @1;
        $$  = stmt_for_new(STMT_FOR, @1, $3, $5, $7, $10);
    }
    /* error recovery */
    | FOR error simple_stmt ';' expr ';' simple_stmt ')' stmt
    {
        @$ = @1;
        $$ = 0;
        proposed_solution("unmatched '(' or ')'");
    }
    | FOR '(' simple_stmt error expr ';' simple_stmt ')' stmt
    {
        @$ = @1;
        $$ = 0;
        proposed_solution("expected ';' as separator between initializer and boolean expression");
    }
    | FOR '(' simple_stmt ';' expr error simple_stmt ')' stmt
    {
        @$ = @1;
        $$ = 0;
        proposed_solution("expected ';' as separator between boolean expression and assignment");
    }
    | FOR '(' simple_stmt ';' expr ';' simple_stmt error stmt
    {
        @$ = @1;
        $$ = 0;
        proposed_solution("unmatched '(' or ')'");
    }
    ;

return_stmt
    : RETURN
    {
        @$ = @1;
        $$ = stmt_return_new(STMT_RETURN, @1, 0);
    }
    | RETURN expr
    {
        @$ = @1;
        $$ = stmt_return_new(STMT_RETURN, @1, $2);
    }
    /* error recovery */
    | RETURN error
    {
        @$ = @1;
        $$ = 0;
        proposed_solution("unkown return value");
    }
    ;

print_stmt
    : PRINT '(' exprs ')'
    {
        @$ = @1;
        $$ = stmt_print_new(STMT_PRINT, @1, $3);
    }
    /* error recovery */
    | PRINT error exprs ')' ';'
    {
        @$ = @3;
        $$ = 0;
        proposed_solution("unmatched '(' or ')'");
    }
    | PRINT '(' exprs error ';'
    {
        @$ = @3;
        $$ = 0;
        proposed_solution("unmatched '(' or ')'");
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
        $$ = expr_left_class_call_new(EXPR_LEFT, EXPR_LEFT_CLASS_CALL, @3, (expr_left_t)$1, $3, $5);
    }
	| IDENTIFIER '(' actuals ')'
    {
        @$ = @1;
        $$ = expr_left_func_call_new(EXPR_LEFT, EXPR_LEFT_FUNC_CALL, @1, $1, $3);
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
        $$ = 0;
        proposed_solution("unexpected nested parenthesis");
    }
	;

constant
    : CONSTANT_INT
    {
        @$ = @1;
        $$ = new ConstInt(@1, $1);
    }
    | CONSTANT_BOOL
    {
        @$ = @1;
        $$ = new ConstBool(@1, $1);
    }
    | CONSTANT_STRING
    {
        @$ = @1;
        $$ = new ConstString(@1, $1);
    }
    | NIL
    {
        @$ = @1;
        $$ = new ConstNil(@1);
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
