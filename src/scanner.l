%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "parser.h"
    #include "errors.h"

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
        yycolumn += yyleng;
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
    srcbuf_append(yytext);
    return BOOL;
}
"class" {
    DRAGON_DEBUG("keyword", "CLASS");
    srcbuf_append(yytext);
    return CLASS;
}
"else" {
    DRAGON_DEBUG("keyword", "ELSE");
    srcbuf_append(yytext);
    return ELSE;
}
"extends" {
    DRAGON_DEBUG("keyword", "EXTENDS");
    srcbuf_append(yytext);
    return EXTENDS;
}
"for" {
    DRAGON_DEBUG("keyword", "FOR");
    srcbuf_append(yytext);
    return FOR;
}
"if" {
    DRAGON_DEBUG("keyword", "IF");
    srcbuf_append(yytext);
    return IF;
}
"int" {
    DRAGON_DEBUG("keyword", "INT");
    srcbuf_append(yytext);
    return INT;
}
"new" {
    DRAGON_DEBUG("keyword", "NEW");
    srcbuf_append(yytext);
    return NEW;
}
"null" {
    DRAGON_DEBUG("keyword", "NULL");
    srcbuf_append(yytext);
    return NIL;
}
"return" {
    DRAGON_DEBUG("keyword", "RETURN");
    srcbuf_append(yytext);
    return RETURN;
}
"string" {
    DRAGON_DEBUG("keyword", "STRING");
    srcbuf_append(yytext);
    return STRING;
}
"this" {
    DRAGON_DEBUG("keyword", "THIS");
    srcbuf_append(yytext);
    return THIS;
}
"void" {
    DRAGON_DEBUG("keyword", "VOID");
    srcbuf_append(yytext);
    return VOID;
}
"while" {
    DRAGON_DEBUG("keyword", "WHILE");
    srcbuf_append(yytext);
    return WHILE;
}
"true"  {
    DRAGON_DEBUG("keyword", "CONSTANT_BOOL");
    yylval.bool_val = 1;
    srcbuf_append(yytext);
    return CONSTANT_BOOL;
}
"false" {
    DRAGON_DEBUG("keyword", "CONSTANT_BOOL");
    yylval.bool_val = 0;
    srcbuf_append(yytext);
    return CONSTANT_BOOL;
}
"Print" {
    DRAGON_DEBUG("keyword", "PRINT");
    srcbuf_append(yytext);
    return PRINT;
}
"ReadInteger" {
    DRAGON_DEBUG("keyword", "READINTEGER");
    srcbuf_append(yytext);
    return READINTEGER;
}
"ReadLine" {
    DRAGON_DEBUG("keyword", "READLINE");
    srcbuf_append(yytext);
    return READLINE;
}
({letter}|_)({letter}|{digit}|_)* {
    DRAGON_DEBUG("identifier", "IDENTIFIER");
    srcbuf_append(yytext);
    return IDENTIFIER;
}
(0|[1-9]{digit}*) {
    DRAGON_DEBUG("constant", "CONSTANT_DEC");
    yylval.int_val = atoi(yytext);
    srcbuf_append(yytext);
    return CONSTANT_INT;
}
0[xX]{hexical}+ {
    DRAGON_DEBUG("constant", "CONSTANT_HEX");
    yylval.int_val = strtol(yytext, NULL, 16);
    srcbuf_append(yytext);
    return CONSTANT_INT;
}
\"(\\.|[^\\"\n])*\"	{
    DRAGON_DEBUG("constant", "CONSTANT_STRING");
    strcpy(yylval.str_val, yytext + 1);
    memset(yylval.str_val + strlen(yytext) - 2, '\0', 1);
    DRAGON_DEBUG("string", yylval.str_val);
    srcbuf_append(yytext);
    return CONSTANT_STRING;
}
"&&"	{
    DRAGON_DEBUG("operator", yytext);
    srcbuf_append(yytext);
    return(OP_AND);
}
"||"	{
    DRAGON_DEBUG("operator", yytext);
    srcbuf_append(yytext);
    return(OP_OR);
}
"<="	{
    DRAGON_DEBUG("operator", yytext);
    srcbuf_append(yytext);
    return(OP_LE);
}
">="	{
    DRAGON_DEBUG("operator", yytext);
    srcbuf_append(yytext);
    return(OP_GE);
}
"=>"    {
    DRAGON_DEBUG("operator", yytext);
    srcbuf_append(yytext);
    return(OP_ARROW);
}
"=="	{
    DRAGON_DEBUG("operator", yytext);
    srcbuf_append(yytext);
    return(OP_EQ);
}
"!="	{
    DRAGON_DEBUG("operator", yytext);
    srcbuf_append(yytext);
    return(OP_NE);
}
";"		{
    DRAGON_DEBUG("separator", yytext);
    srcbuf_append(yytext);
    return(';');
}
"{"		{
    DRAGON_DEBUG("separator", yytext);
    srcbuf_append(yytext);
    return('{');
}
"}"		{
    DRAGON_DEBUG("separator", yytext);
    srcbuf_append(yytext);
    return('}');
}
"["		{
    DRAGON_DEBUG("separator", yytext);
    srcbuf_append(yytext);
    return('[');
}
"]"		{
    DRAGON_DEBUG("separator", yytext);
    srcbuf_append(yytext);
    return(']');
}
"("		{
    DRAGON_DEBUG("separator", yytext);
    srcbuf_append(yytext);
    return('(');
}
")"		{
    DRAGON_DEBUG("separator", yytext);
    srcbuf_append(yytext);
    return(')');
}
"="		{
    DRAGON_DEBUG("operator", yytext);
    srcbuf_append(yytext);
    return('=');
}
","		{
    DRAGON_DEBUG("separator", yytext);
    srcbuf_append(yytext);
    return(',');
}
"."		{
    DRAGON_DEBUG("operator", yytext);
    srcbuf_append(yytext);
    return('.');
}
"!"		{
    DRAGON_DEBUG("operator", yytext);
    srcbuf_append(yytext);
    return('!');
}
"+"		{
    DRAGON_DEBUG("operator", yytext);
    srcbuf_append(yytext);
    return('+');
}
"-"		{
    DRAGON_DEBUG("operator", yytext);
    srcbuf_append(yytext);
    return('-');
}
"*"		{
    DRAGON_DEBUG("operator", yytext);
    srcbuf_append(yytext);
    return('*');
}
"/"		{
    DRAGON_DEBUG("operator", yytext);
    srcbuf_append(yytext);
    return('/');
}
"%"		{
    DRAGON_DEBUG("operator", yytext);
    srcbuf_append(yytext);
    return('%');
}
"<"		{
    DRAGON_DEBUG("operator", yytext);
    srcbuf_append(yytext);
    return('<');
}
">"		{
    DRAGON_DEBUG("operator", yytext);
    srcbuf_append(yytext);
    return('>');
}
" "  {
    srcbuf_append(yytext);
}
\t {
    srcbuf_append(yytext);
}
\n  {
    // reset column counter
    yycolumn = 1;
    // re-init source buffer
    srcbuf_init();
}

. {
    fprintf(stderr, "<%4d:%4d><Error>: lexical error near %s\n", yylloc.first_line, yylloc.first_column, yytext);
}

%%

int yywrap(void) {
    return 1;
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
