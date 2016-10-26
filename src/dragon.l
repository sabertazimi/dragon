%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "dragon.tab.h"

    // #undef YYDEBUG

    /*
     * @macro: DRAGON_DEBUG
     * @brief: print debug info for lexical analysis
     */
    #define DRAGON_DEBUG(outmode, outstr)       \
        do {                                    \
            if (outmode == 0) {                 \
                fprintf(yyout, outstr);         \
            } else {                            \
                fprintf(yyout, "%s", outstr);   \
            }                                   \
        } while (0)

    // disable DRAGON_DEBUG macro when YYDEBUG undefined
    #ifndef YYDEBUG
    #undef DRAGON_DEBUG
    #endif

    /*
     * @brief: informations of locations
     */
    int yycolumn = 1;
    #define YY_USER_INIT yylloc.first_line = yylloc.first_column = 1;
    #define YY_USER_ACTION                                  \
        yylloc.first_line = yylloc.last_line = yylineno;    \
        yylloc.first_column = yycolumn;                     \
        yylloc.last_column = yycolumn + yyleng - 1;         \
        yycolumn += yyleng;                                 \
        strcpy(yylval.plain_text, yytext);

    /*
     * @brief: return 1 making parse only get done 1 time
     */
    int yywrap(void);

    /*
     * @brief: skip block comment
     */
    void comment(void);
%}

digit   [0-9]
letter  [a-zA-Z]
hexical [a-fA-F0-9]

%option yylineno
%option nounput

%%

"/*"   {
    comment();
}
"//"[^\n]* {
    /* Skip comment line */
}
"bool" {
    DRAGON_DEBUG(0, "BOOL");
    return BOOL;
}
"break" {
    DRAGON_DEBUG(0, "BREAK");
    return BREAK;
}
"class" {
    DRAGON_DEBUG(0, "CLASS");
    return CLASS;
}
"else" {
    DRAGON_DEBUG(0, "ELSE");
    return ELSE;
}
"extends" {
    DRAGON_DEBUG(0, "EXTENDS");
    return EXTENDS;
}
"for" {
    DRAGON_DEBUG(0, "FOR");
    return FOR;
}
"if" {
    DRAGON_DEBUG(0, "IF");
    return IF;
}
"int" {
    DRAGON_DEBUG(0, "INT");
    return INT;
}
"new" {
    DRAGON_DEBUG(0, "NEW");
    return NEW;
}
"null" {
    DRAGON_DEBUG(0, "NULL");
    return NIL;
}
"return" {
    DRAGON_DEBUG(0, "RETURN");
    return RETURN;
}
"string" {
    DRAGON_DEBUG(0, "STRING");
    return STRING;
}
"this" {
    DRAGON_DEBUG(0, "THIS");
    return THIS;
}
"void" {
    DRAGON_DEBUG(0, "VOID");
    return VOID;
}
"while" {
    DRAGON_DEBUG(0, "WHILE");
    return WHILE;
}
"static" {
    DRAGON_DEBUG(0, "STATIC");
    return STATIC;
}
"true"  {
    DRAGON_DEBUG(0, "CONSTANT_BOOL");
    yylval.bool_val = 1;
    return CONSTANT_BOOL;
}
"false" {
    DRAGON_DEBUG(0, "CONSTANT_BOOL");
    yylval.bool_val = 0;
    return CONSTANT_BOOL;
}
"Print" {
    DRAGON_DEBUG(0, "PRINT");
    return PRINT;
}
"ReadInteger" {
    DRAGON_DEBUG(0, "READINTEGER");
    return READINTEGER;
}
"ReadLine" {
    DRAGON_DEBUG(0, "READLINE");
    return READLINE;
}
{letter}({letter}|{digit})* {
    DRAGON_DEBUG(0, "IDENTIFIER");
    return IDENTIFIER;
}
(0|[1-9]{digit}*) {
    DRAGON_DEBUG(0, "CONSTANT_DEC");
    yylval.int_val = atoi(yytext);
    return CONSTANT_INT;
}
0[xX]{hexical}+ {
    DRAGON_DEBUG(0, "CONSTANT_HEX");
    yylval.int_val = strtol(yytext, NULL, 16);
    return CONSTANT_INT;
}
\"(\\.|[^\\"\n])*\"	{
    DRAGON_DEBUG(0, "CONSTANT_STRING");
    strcpy(yylval.str_val, yytext + 1);
    return CONSTANT_STRING;
}
"&&"	{
    DRAGON_DEBUG(1, yytext);
    return(OP_AND);
}
"||"	{
    DRAGON_DEBUG(1, yytext);
    return(OP_OR);
}
"<="	{
    DRAGON_DEBUG(1, yytext);
    return(OP_LE);
}
">="	{
    DRAGON_DEBUG(1, yytext);
    return(OP_GE);
}
"=>"    {
    DRAGON_DEBUG(1, yytext);
    return(OP_ARROW);
}
"=="	{
    DRAGON_DEBUG(1, yytext);
    return(OP_EQ);
}
"!="	{
    DRAGON_DEBUG(1, yytext);
    return(OP_NE);
}
";"		{
    DRAGON_DEBUG(1, yytext);
    return(';');
}
"{"		{
    DRAGON_DEBUG(1, yytext);
    return('{');
}
"}"		{
    DRAGON_DEBUG(1, yytext);
    return('}');
}
"["		{
    DRAGON_DEBUG(1, yytext);
    return('[');
}
"]"		{
    DRAGON_DEBUG(1, yytext);
    return(']');
}
"("		{
    DRAGON_DEBUG(1, yytext);
    return('(');
}
")"		{
    DRAGON_DEBUG(1, yytext);
    return(')');
}
"="		{
    DRAGON_DEBUG(1, yytext);
    return('=');
}
","		{
    DRAGON_DEBUG(1, yytext);
    return(',');
}
"."		{
    DRAGON_DEBUG(1, yytext);
    return('.');
}
"!"		{
    DRAGON_DEBUG(1, yytext);
    return('!');
}
"+"		{
    DRAGON_DEBUG(1, yytext);
    return('+');
}
"-"		{
    DRAGON_DEBUG(1, yytext);
    return('-');
}
"*"		{
    DRAGON_DEBUG(1, yytext);
    return('*');
}
"/"		{
    DRAGON_DEBUG(1, yytext);
    return('/');
}
"%"		{
    DRAGON_DEBUG(1, yytext);
    return('%');
}
"<"		{
    DRAGON_DEBUG(1, yytext);
    return('<');
}
">"		{
    DRAGON_DEBUG(1, yytext);
    return('>');
}
" "  {
    DRAGON_DEBUG(0, " ");
}
\t {
    DRAGON_DEBUG(0, "\t");
}
\n  {
    yycolumn = 1;
    DRAGON_DEBUG(0, "\n");
    return '\n';
}

. {
    fprintf(stderr, "Lexical error near %s.\n", yytext);
    exit(1);
}

%%

int yywrap(void) {
    return 1;
}

void comment(void) {
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
    exit(1);
}
