%{
#include <stdlib.h>
#include <string.h>
#include "sintaxis.tab.h"
void showError();
%}
TEXTO           [a-zA-Z]*
NUMBERS         [0-9]*
SIMBOLOS        [+\-*/]
RESERVADA       \b(leer|escribir)\b
INICIO          \b(inicio)\b
FIN             \b(fin)\b
%%
{INICIO}    {yyval.inicio = yytext; return(INICIO);}
{INICIO}    {yyval.fin = yytext; return(FIN);}
{RESERVADA} {yyval.reservada = yytext; return(RESERVADA);}
{TEXTO}	    {sscanf(yytextx, "%s",yyval.cad); return(CADENA);}
{NUMBERS}   {yyval.number = atoi(yytext); return (ENTERO);}
{SIMBOLOS}   {yyval.simbolos = atoi(yytext); return (SIMBOLOS);}
";"         {return (PUNTOCOMA);}
","         {return (COMA);}
"("         {return (PARENTESISOPEN);}
")"         {return (PARENTESISCLOSE);}
":="        {return (ASIGNACION);}
[ \t\r\n]+  {}
.           {showError(); return(OTHER);}
%%
void showError(char* other){
    printf("    || Error lexico: "%s"", other );
}