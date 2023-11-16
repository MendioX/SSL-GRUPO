%{
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "y.tab.h"

%}

%option noyywrap
identificador           [a-zA-Z]*
numbers         [0-9]*
simbolos        [+\-*/]
reservada       leer|escribir
inicio          inicio
fin             fin

%%
{inicio}    {yylval.inicio = yytext; return(INICIO);}
{fin}       {yylval.fin = yytext; return(FIN);}
{reservada} {yylval.reservada = yytext; return(RESERVADA);}
{identificador}	    {sscanf(yytext, "%s",yylval.cad); return(IDENTIFICADOR);}
{numbers}   {yylval.number = atoi(yytext); return (ENTERO);}
{simbolos}  {yylval.simbolos = atoi(yytext); return (SIMBOLOS);}
";"         {return (PUNTOCOMA);}
","         {return (COMA);}
"("         {return (PARENTESISOPEN);}
")"         {return (PARENTESISCLOSE);}
":="        {return (ASIGNACION);}
[ \t\r\n]+  {}
.           {printf("Error lexico");   return(OTHER);}




