%{
    #include <stdlib.h>
    #include <stdio.h>
    void yyerror(char *s);
    int yylex();
    #include <unistd.h>
%}


%union{
    char cad[20];
    int number;
    char *reservada;
    char *inicio;
    char *fin;
    int simbolos;
}

%token INICIO FIN ENTERO SIMBOLOS PUNTOCOMA ASIGNACION COMA RESERVADA NUMBERS TEXTO PARENTESISOPEN PARENTESISCLOSE OTHER

%type <cad> TEXTO
%type <number> ENTERO
%type <reservada> RESERVADA
%type <inicio> INICIO
%type <fin> FIN
%type <simbolos> SIMBOLOS

%%
prog: INICIO stmt FIN 
    ;

stmt: RESERVADA PUNTOCOMA
    | RESERVADA PARENTESISOPEN lista_vars PARENTESISCLOSE PUNTOCOMA 
    | TEXTO ASIGNACION expr PUNTOCOMA 
    | RESERVADA PARENTESISOPEN lista_expr PARENTESISCLOSE PUNTOCOMA 
    ;
lista_vars: TEXTO 
    | lista_vars COMA TEXTO 
    ;

expr: NUMBERS 
    | TEXTO 
    | expr SIMBOLOS expr
    ;

lista_expr: expr 
    | lista_expr COMA expr 
    ;
%%



int main(int argc, char **argv){
    yyparse();
    getchar();
    return 0;
}

void yyerror(char *s) {
   
    printf("Error sintactico");
}

int yywrap(){
    return 1;
}