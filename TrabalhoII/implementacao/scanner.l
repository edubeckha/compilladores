%{
#include <string>
#include "ast.h"
#include "parser.h"
extern int yylineno;
void yyerror(const char* s, ...);
%}

%option noyywrap nodefault yylineno

digs [0-9]+
nome [a-z]+
strg \"([^\"\\\\]|\\\\.)*\" 
%% http://wordaligned.org/articles/string-literals-and-regular-expressions

[ \t]               ; //ignores spaces

"int"				{return T_DINT;}
"real"				{return T_DREAL;}
"bool"				{return T_DBOOL;}
"string"			{return T_DSTRING;}

{digs}              {yylval.integer = std::atoi(yytext); return T_INT;}

{digs}\.{digs}		{yylval.doubler = std::atof(yytext); return T_DOUBLE;}
\.{digs} 			{yylval.doubler = std::atof(yytext); return T_DOUBLE;}
{digs}\.		 	{yylval.doubler = std::atof(yytext); return T_DOUBLE;}

"true"				{return T_BOOLTRUE;}
"false"				{return T_BOOLFALSE;}

"+"                 {return T_PLUS;}
"-"                 {return T_SUB;}
"*"                 {return T_TIMES;}
"/"                 {return T_DIV;}

","                 {return T_COMMA;}
"="                 {return T_ASSIGN;}
"!="				{return T_DIFERENTE;}
">"					{return T_MAIOR;}
"<"					{return T_MENOR;}
"=="				{return T_IGUAL;}
">="				{return T_MAIORIGUAL;}
"<="				{return T_MENORIGUAL;}

"&&"				{return T_AND;}
"||"				{return T_OR;}
"~"					{return T_UNIBOOL;}

"("					{return T_PARA;}
")"					{return T_PARAF;}
"["					{return T_ARRA;}
"]"					{return T_ARRAF;}

"while"				{return T_WHILE;}
"if"				{return T_IF;}
"then"				{return T_THEN;}
"else"				{return T_ELSE;}

"return" 			{return T_RETO;}

"{"					{return T_CHAVE;}
"}"					{return T_CHAVEF;}

"class"				{return T_CLASSE;}
"."					{return T_DOT;}
"new"				{return T_NEW;}
".substring"		{return T_SUBSTRG;}
".tamanho" 			{return T_TAMANHO;}


";"					{return T_FINALEXP;}
"\n"                {return T_NL;}
{nome}              {yylval.name = strdup(yytext); return T_ID;}
{strg}     			{yylval.String = strdup(yytext); return T_STRING;}
.                   {yyerror("Erro lexico: simbolo desconhecido %c\n", *yytext);} 

%%1

void yyerror(const char *s, ...){
    va_list ap;
    va_start(ap, s);
    std::fprintf(stderr, "Line %d: error: ", yylineno);
    std::vfprintf(stderr, s, ap);
}