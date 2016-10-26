%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "dragon.tab.h"

    // #undef YYDEBUG

    int yycolumn = 1;

    #define YY_USER_INIT yylloc.first_line = yylloc.first_column = 1;

    #define YY_USER_ACTION                                  \
        yylloc.first_line = yylloc.last_line = yylineno;    \
        yylloc.first_column = yycolumn;                     \
        yylloc.last_column = yycolumn + yyleng - 1;         \
        yycolumn += yyleng;                                 \
        strcpy(yylval.plain_text, yytext);

    int yywrap(void);
    void comment(void);
%}

digit   [0-9]
letter  [a-zA-Z]
hexical [a-fA-F0-9]

%option yylineno

%%

"/*"   {
    comment();
}
"//"[^\n]* {
    /* Skip comment line */
}
"bool" {
#ifdef YYDEBUG
    fprintf(yyout, "BOOL");
#endif
    return BOOL;
}
"break" {
#ifdef YYDEBUG
    fprintf(yyout, "BREAK");
#endif
    return BREAK;
}
"class" {
#ifdef YYDEBUG
    fprintf(yyout, "CLASS");
#endif
    return CLASS;
}
"else" {
#ifdef YYDEBUG
    fprintf(yyout, "ELSE");
#endif
    return ELSE;
}
"extends" {
#ifdef YYDEBUG
    fprintf(yyout, "EXTENDS");
#endif
    return EXTENDS;
}
"for" {
#ifdef YYDEBUG
    fprintf(yyout, "FOR");
#endif
    return FOR;
}
"if" {
#ifdef YYDEBUG
    fprintf(yyout, "IF");
#endif
    return IF;
}
"int" {
#ifdef YYDEBUG
    fprintf(yyout, "INT");
#endif
    return INT;
}
"new" {
#ifdef YYDEBUG
    fprintf(yyout, "NEW");
#endif
    return NEW;
}
"null" {
#ifdef YYDEBUG
    fprintf(yyout, "NULL");
#endif
    return NIL;
}
"return" {
#ifdef YYDEBUG
    fprintf(yyout, "RETURN");
#endif
    return RETURN;
}
"string" {
#ifdef YYDEBUG
    fprintf(yyout, "STRING");
#endif
    return STRING;
}
"this" {
#ifdef YYDEBUG
    fprintf(yyout, "THIS");
#endif
    return THIS;
}
"void" {
#ifdef YYDEBUG
    fprintf(yyout, "VOID");
#endif
    return VOID;
}
"while" {
#ifdef YYDEBUG
    fprintf(yyout, "WHILE");
#endif
    return WHILE;
}
"static" {
#ifdef YYDEBUG
    fprintf(yyout, "STATIC");
#endif
    return STATIC;
}
"true"  {
#ifdef YYDEBUG
    fprintf(yyout, "CONSTANT_BOOL");
#endif
    yylval.type_bool = 1;
    return CONSTANT_BOOL;
}
"false" {
#ifdef YYDEBUG
    fprintf(yyout, "CONSTANT_BOOL");
#endif
    yylval.type_bool = 0;
    return CONSTANT_BOOL;
}
"Print" {
#ifdef YYDEBUG
    fprintf(yyout, "PRINT");
#endif
    return PRINT;
}
"ReadInteger" {
#ifdef YYDEBUG
    fprintf(yyout, "READINTEGER");
#endif
    return READINTEGER;
}
"ReadLine" {
#ifdef YYDEBUG
    fprintf(yyout, "READLINE");
#endif
    return READLINE;
}
{letter}({letter}|{digit})* {
#ifdef YYDEBUG
    fprintf(yyout, "IDENTIFIER");
#endif
    return IDENTIFIER;
}
(0|[1-9]{digit}*) {
#ifdef YYDEBUG
    fprintf(yyout, "CONSTANT_DEC");
#endif
    yylval.type_int = atoi(yytext);
    return CONSTANT_INT;
}
0[xX]{hexical}+ {
#ifdef YYDEBUG
    fprintf(yyout, "CONSTANT_HEX");
#endif
    yylval.type_int = strtol(yytext, NULL, 16);
    return CONSTANT_INT;
}
\"(\\.|[^\\"\n])*\"	{
#ifdef YYDEBUG
    fprintf(yyout, "CONSTANT_STRING");
#endif
    strcpy(yylval.type_string, yytext + 1);
    return CONSTANT_STRING;
}
"&&"	{
#ifdef YYDEBUG
    fprintf(yyout, "%s", yytext);
#endif
    return(OP_AND);
}
"||"	{
#ifdef YYDEBUG
    fprintf(yyout, "%s", yytext);
#endif
    return(OP_OR);
}
"<="	{
#ifdef YYDEBUG
    fprintf(yyout, "%s", yytext);
#endif
    return(OP_LE);
}
">="	{
#ifdef YYDEBUG
    fprintf(yyout, "%s", yytext);
#endif
    return(OP_GE);
}
"=="	{
#ifdef YYDEBUG
    fprintf(yyout, "%s", yytext);
#endif
    return(OP_EQ);
}
"!="	{
#ifdef YYDEBUG
    fprintf(yyout, "%s", yytext);
#endif
    return(OP_NE);
}
";"		{
#ifdef YYDEBUG
    fprintf(yyout, "%s", yytext);
#endif
    return(';');
}
"{"		{
#ifdef YYDEBUG
    fprintf(yyout, "%s", yytext);
#endif
    return('{');
}
"}"		{
#ifdef YYDEBUG
    fprintf(yyout, "%s", yytext);
#endif
    return('}');
}
"["		{
#ifdef YYDEBUG
    fprintf(yyout, "%s", yytext);
#endif
    return('[');
}
"]"		{
#ifdef YYDEBUG
    fprintf(yyout, "%s", yytext);
#endif
    return(']');
}
"("		{
#ifdef YYDEBUG
    fprintf(yyout, "%s", yytext);
#endif
    return('(');
}
")"		{
#ifdef YYDEBUG
    fprintf(yyout, "%s", yytext);
#endif
    return(')');
}
"="		{
#ifdef YYDEBUG
    fprintf(yyout, "%s", yytext);
#endif
    return('=');
}
","		{
#ifdef YYDEBUG
    fprintf(yyout, "%s", yytext);
#endif
    return(',');
}
"."		{
#ifdef YYDEBUG
    fprintf(yyout, "%s", yytext);
#endif
    return('.');
}
"!"		{
#ifdef YYDEBUG
    fprintf(yyout, "%s", yytext);
#endif
    return('!');
}
"+"		{
#ifdef YYDEBUG
    fprintf(yyout, "%s", yytext);
#endif
    return('+');
}
"-"		{
#ifdef YYDEBUG
    fprintf(yyout, "%s", yytext);
#endif
    return('-');
}
"*"		{
#ifdef YYDEBUG
    fprintf(yyout, "%s", yytext);
#endif
    return('*');
}
"/"		{
#ifdef YYDEBUG
    fprintf(yyout, "%s", yytext);
#endif
    return('/');
}
"%"		{
#ifdef YYDEBUG
    fprintf(yyout, "%s", yytext);
#endif
    return('%');
}
"<"		{
#ifdef YYDEBUG
    fprintf(yyout, "%s", yytext);
#endif
    return('<');
}
">"		{
#ifdef YYDEBUG
    fprintf(yyout, "%s", yytext);
#endif
    return('>');
}
" "  {
#ifdef YYDEBUG
    fprintf(yyout, " ");
#endif
}
\t {
#ifdef YYDEBUG
    fprintf(yyout, "\t");
#endif
}
\n  {
    yycolumn = 1;
#ifdef YYDEBUG
    fprintf(yyout, "\n");
#endif
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

/*
 * @brief: skip block comment
 */
void comment(void) {
    char ch, prev;

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
