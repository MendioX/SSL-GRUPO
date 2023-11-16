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

%token INICIO FIN RESERVADA IDENTIFICADOR ENTERO SIMBOLOS PUNTOCOMA COMA PARENTESISOPEN PARENTESISCLOSE ASIGNACION OTHER

%type <cad> IDENTIFICADOR
%type <number> ENTERO
%type <reservada> RESERVADA
%type <inicio> INICIO
%type <fin> FIN
%type <simbolos> SIMBOLOS

%%
prog: INICIO codigo FIN 
    ;

codigo: /* empty */
    | codigo stmt 
    ;

stmt: RESERVADA PARENTESISOPEN lista_vars PARENTESISCLOSE PUNTOCOMA 
    | IDENTIFICADOR ASIGNACION expr PUNTOCOMA
    ;

lista_vars: IDENTIFICADOR 
    | lista_vars COMA IDENTIFICADOR 
    ;

expr: ENTERO 
    | IDENTIFICADOR 
    | expr SIMBOLOS expr
    ;

%%



int main(int argc, char **argv){
    printf("      Comienzo de analis... \n");
    printf("--------------------------------------\n");

    yyparse();
    
    getchar();
    printf("--------------------------------------\n");
    
     printf("       Fin analisis... \n");
    return 0;
}

void yyerror(char *s) {
   
    printf("Error sintactico");
}

int yywrap(){
    return 1;
}