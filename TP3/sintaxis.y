%{
    #include <stdlib.h>
    int yylex();
    int yyerror(char *s);
    void procesarSentenciaReservada(const char* palabraReservada);
%}
%token INICIO FIN ENTERO SIMBOLOS PUNTOCOMA ASIGNACION COMA RESERVADA NUMBERS TEXTO PARENTESISOPEN PARENTESISCLOSE

%type <cad> TEXTO
%type <number> ENTERO
%type <reservada> RESERVADA


%union{
    char cad[20];
    int number;
    char *reservada;
}

%%
prog: INICIO stmt FIN {printf("(SETEO DE PROGRAMA): \"%s\"\n",$1);}
    ;

stmt: RESERVADA PUNTOCOMA { procesarSentenciaReservada($1); }
    | RESERVADA PARENTESISOPEN lista_vars PARENTESISCLOSE PUNTOCOMA { procesarSentenciaReservada($1); }
    | TEXTO ASIGNACION expr PUNTOCOMA { /* Código semántico para la asignación */ }
    | RESERVADA PARENTESISOPEN lista_expr PARENTESISCLOSE PUNTOCOMA { procesarSentenciaReservada($1); }
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

int yyerror(char *s) {
    printf(stderr, "Error sintáctico: %s\n", s);
    return 0;
}

void procesarSentenciaReservada(const char* palabraReservada) {
    if (strcmp(palabraReservada, "leer") == 0) {
        /* Código semántico para la sentencia LEER */
        printf("Sentencia LEER\n");
    } else if (strcmp(palabraReservada, "escribir") == 0) {
        /* Código semántico para la sentencia ESCRIBIR */
        printf("Sentencia ESCRIBIR\n");
    } else {
        /* Código semántico para otros casos de RESERVADA */
        printf("Otra sentencia RESERVADA\n");
    }
}

int main (int argc, char **argv){
yyparse();
return 0;
}