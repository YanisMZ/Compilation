%{
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "le_parser.h"  // Inclut les définitions des tokens générées par Bison
int yycolumn = 0;
%}

%x COM1 COM2
%option noinput
%option nounput
%option yylineno 

%%

\/\/                    { BEGIN COM1; yycolumn += yyleng; }
<COM1>.*\n               { yycolumn = 0; BEGIN INITIAL; }
\/\*                    { BEGIN COM2; yycolumn += yyleng; }
<COM2>\n                 { yycolumn = 0; }
<COM2>\*\/               { yycolumn += yyleng; BEGIN INITIAL; }


"struct"      { yycolumn += yyleng; strcpy(yylval.id, yytext); return STRUCT; }
"int"         { yycolumn += yyleng;  strcpy(yylval.id, yytext); return TYPE; }
"char"        { yycolumn += yyleng;  strcpy(yylval.id, yytext); return TYPE; }
"if"          { yycolumn += yyleng; return IF; }
"else"        { yycolumn += yyleng; return ELSE; }
"return"      { yycolumn += yyleng; return RETURN; }
"void"        { yycolumn += yyleng;  strcpy(yylval.id, yytext); return VOID; }
"while"        { yycolumn += yyleng;  strcpy(yylval.id, yytext); return WHILE; }
[a-zA-Z_][a-zA-Z0-9_]*  { 
    yycolumn += yyleng; 
    strcpy(yylval.id,yytext); 
    return IDENT; 
}
[0-9]+  { 
    yycolumn += yyleng; 
    yylval.num = atoi(yytext); 
    return NUM; 
}

\'([^\\']|\\[ntr'])\'  { 
    yycolumn += yyleng; 
    yylval.character = yytext[1]; 
    return CHARACTER; 
}


"==" { yycolumn += yyleng; strcpy(yylval.id, yytext); return EQ; }
"!=" { yycolumn += yyleng; strcpy(yylval.id, yytext); return EQ; }
"<=" { yycolumn += yyleng; strcpy(yylval.id, yytext); return ORDER; }
">=" { yycolumn += yyleng; strcpy(yylval.id, yytext); return ORDER; }
"<"  { yycolumn += yyleng; strcpy(yylval.id, yytext); return ORDER; }
">"  { yycolumn += yyleng; strcpy(yylval.id, yytext); return ORDER; }
"||" { yycolumn += yyleng; strcpy(yylval.id, yytext); return OR; }
"&&" { yycolumn += yyleng; strcpy(yylval.id, yytext); return AND; }
"+"  { yycolumn += yyleng; strcpy(yylval.id, yytext); return ADDSUB; }
"-"  { yycolumn += yyleng; strcpy(yylval.id, yytext); return ADDSUB; }
"*"  { yycolumn += yyleng; strcpy(yylval.id, yytext);return DIVSTAR; }
"/"  { yycolumn += yyleng; strcpy(yylval.id, yytext);return DIVSTAR; }
"%"  { yycolumn += yyleng; strcpy(yylval.id, yytext);return DIVSTAR; }



[;,(){}=!]  { yycolumn += yyleng; return yytext[0]; }

[ \t\r] { yycolumn += yyleng; }

\n          { yycolumn = 0; }

. { 
    /* fprintf(stderr, "Erreur lexicale à la ligne %d, colonne %d : mot inattendu '%s'\n", 
            yylineno, yycolumn, yytext); */
    yycolumn += yyleng; 
    return yytext[0]; // Forcer une erreur lexicale
}

%%

int yywrap(){
    return 1;
}
