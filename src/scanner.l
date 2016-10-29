%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "dragon.tab.h"
    #include "errors.h"

    // #undef YYDEBUG

    /*
     * @macro: DRAGON_DEBUG
     * @brief: print debug info for lexical analysis
     */
    #ifdef YYDEBUG
        #define DRAGON_DEBUG(type, value) do { dragon_debug(type, value); } while (0)
    #else
        #define DRAGON_DEBUG(type, value) do { } while (0)
    #endif

    /*
     * @brief: informations of locations
     */
    int yycolumn = 1;
    #define YY_USER_INIT                                    \
        yylloc.first_line = yylloc.first_column = 1;        \
        srcbuf_init();
    #define YY_USER_ACTION                                  \
        yylloc.first_line = yylloc.last_line = yylineno;    \
        yylloc.first_column = yycolumn;                     \
        yylloc.last_column = yycolumn + yyleng - 1;         \
        yycolumn += yyleng;                                 \
        srcbuf_append(yytext);

    /*
     * @brief: debug output function
     */
    void dragon_debug(const char *type, const char *value);

    /*
     * @brief: return 1 making parse only get done 1 time
     */
    int yywrap(void);

    /*
     * @brief: skip block comment
     */
    void dragon_comment(void);
%}

digit   [0-9]
letter  [a-zA-Z]
hexical [a-fA-F0-9]

%option yylineno
%option nounput

%%

"/*"   {
    dragon_comment();
}
"//"[^\n]* {
    /* Skip comment line */
}
"bool" {
    DRAGON_DEBUG("keyword", "BOOL");
    return BOOL;
}
"class" {
    DRAGON_DEBUG("keyword", "CLASS");
    return CLASS;
}
"else" {
    DRAGON_DEBUG("keyword", "ELSE");
    return ELSE;
}
"extends" {
    DRAGON_DEBUG("keyword", "EXTENDS");
    return EXTENDS;
}
"for" {
    DRAGON_DEBUG("keyword", "FOR");
    return FOR;
}
"if" {
    DRAGON_DEBUG("keyword", "IF");
    return IF;
}
"int" {
    DRAGON_DEBUG("keyword", "INT");
    return INT;
}
"new" {
    DRAGON_DEBUG("keyword", "NEW");
    return NEW;
}
"null" {
    DRAGON_DEBUG("keyword", "NULL");
    return NIL;
}
"return" {
    DRAGON_DEBUG("keyword", "RETURN");
    return RETURN;
}
"string" {
    DRAGON_DEBUG("keyword", "STRING");
    return STRING;
}
"this" {
    DRAGON_DEBUG("keyword", "THIS");
    return THIS;
}
"void" {
    DRAGON_DEBUG("keyword", "VOID");
    return VOID;
}
"while" {
    DRAGON_DEBUG("keyword", "WHILE");
    return WHILE;
}
"true"  {
    DRAGON_DEBUG("keyword", "CONSTANT_BOOL");
    yylval.bool_val = 1;
    return CONSTANT_BOOL;
}
"false" {
    DRAGON_DEBUG("keyword", "CONSTANT_BOOL");
    yylval.bool_val = 0;
    return CONSTANT_BOOL;
}
"Print" {
    DRAGON_DEBUG("keyword", "PRINT");
    return PRINT;
}
"ReadInteger" {
    DRAGON_DEBUG("keyword", "READINTEGER");
    return READINTEGER;
}
"ReadLine" {
    DRAGON_DEBUG("keyword", "READLINE");
    return READLINE;
}
({letter}|_)({letter}|{digit}|_)* {
    DRAGON_DEBUG("identifier", "IDENTIFIER");
    return IDENTIFIER;
}
(0|[1-9]{digit}*) {
    DRAGON_DEBUG("constant", "CONSTANT_DEC");
    yylval.int_val = atoi(yytext);
    return CONSTANT_INT;
}
0[xX]{hexical}+ {
    DRAGON_DEBUG("constant", "CONSTANT_HEX");
    yylval.int_val = strtol(yytext, NULL, 16);
    return CONSTANT_INT;
}
\"(\\.|[^\\"\n])*\"	{
    DRAGON_DEBUG("constant", "CONSTANT_STRING");
    strcpy(yylval.str_val, yytext + 1);
    memset(yylval.str_val + strlen(yytext) - 2, '\0', 1);
    DRAGON_DEBUG("string", yylval.str_val);
    return CONSTANT_STRING;
}
"&&"	{
    DRAGON_DEBUG("operator", yytext);
    return(OP_AND);
}
"||"	{
    DRAGON_DEBUG("operator", yytext);
    return(OP_OR);
}
"<="	{
    DRAGON_DEBUG("operator", yytext);
    return(OP_LE);
}
">="	{
    DRAGON_DEBUG("operator", yytext);
    return(OP_GE);
}
"=>"    {
    DRAGON_DEBUG("operator", yytext);
    return(OP_ARROW);
}
"=="	{
    DRAGON_DEBUG("operator", yytext);
    return(OP_EQ);
}
"!="	{
    DRAGON_DEBUG("operator", yytext);
    return(OP_NE);
}
";"		{
    DRAGON_DEBUG("separator", yytext);
    return(';');
}
"{"		{
    DRAGON_DEBUG("separator", yytext);
    return('{');
}
"}"		{
    DRAGON_DEBUG("separator", yytext);
    return('}');
}
"["		{
    DRAGON_DEBUG("separator", yytext);
    return('[');
}
"]"		{
    DRAGON_DEBUG("separator", yytext);
    return(']');
}
"("		{
    DRAGON_DEBUG("separator", yytext);
    return('(');
}
")"		{
    DRAGON_DEBUG("separator", yytext);
    return(')');
}
"="		{
    DRAGON_DEBUG("operator", yytext);
    return('=');
}
","		{
    DRAGON_DEBUG("separator", yytext);
    return(',');
}
"."		{
    DRAGON_DEBUG("operator", yytext);
    return('.');
}
"!"		{
    DRAGON_DEBUG("operator", yytext);
    return('!');
}
"+"		{
    DRAGON_DEBUG("operator", yytext);
    return('+');
}
"-"		{
    DRAGON_DEBUG("operator", yytext);
    return('-');
}
"*"		{
    DRAGON_DEBUG("operator", yytext);
    return('*');
}
"/"		{
    DRAGON_DEBUG("operator", yytext);
    return('/');
}
"%"		{
    DRAGON_DEBUG("operator", yytext);
    return('%');
}
"<"		{
    DRAGON_DEBUG("operator", yytext);
    return('<');
}
">"		{
    DRAGON_DEBUG("operator", yytext);
    return('>');
}
" "  {
#ifdef YYDEBUG
    // fprintf(yyout, " ");
#endif
}
\t {
#ifdef YYDEBUG
    // fprintf(yyout, "\t");
#endif
}
\n  {
#ifdef YYDEBUG
    // fprintf(yyout, "\n");
#endif
    // reset column counter
    yycolumn = 1;
    // re-init source buffer
    srcbuf_init();
}

. {
    fprintf(stderr, "Lexical error near %s, line %4d, column %4d\n", yytext, yylloc.first_line, yylloc.first_column);
}

%%

int yywrap(void) {
    return 1;
}

void dragon_debug(const char *type, const char *value) {
    fprintf(yyout, "line %4d, column %-4d-%4d: ", yylloc.first_line, yylloc.first_column, yylloc.last_column);
    fprintf(yyout, "(%s, %s)\n", type, value);
}

void dragon_comment(void) {
    char ch = '\0',
         prev = '\0';

    while ((ch = input()) != '\0') {
        if (prev == '*' && ch == '/') {
            return;
        } else {
            prev = ch;
        }
    }

    fprintf(stderr, "Unterminated block comment!");
}
