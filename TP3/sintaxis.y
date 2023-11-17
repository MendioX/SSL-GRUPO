%{
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <unistd.h>
    void yyerror(char *s);
    int yylex();

   /*Estructura para un nodo en la tabla de símbolos*/ 

typedef struct SymbolTableNode {
    char id[20];
    struct SymbolTableNode* next;
} SymbolTableNode;


/*Tabla de símbolos*/ 
SymbolTableNode* symbolTable = NULL;



/*Función para insertar un ID en la tabla de símbolos*/ 
void insertId(char* id) {
    SymbolTableNode* newNode = (SymbolTableNode*)malloc(sizeof(SymbolTableNode));
    if (newNode == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria para el nodo de la tabla de símbolos.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(newNode->id, id);
    newNode->next = symbolTable;
    symbolTable = newNode;
}




/*Función para liberar la memoria de la tabla de símbolos*/ 
void freeSymbolTable() {
    SymbolTableNode* current = symbolTable;
    while (current != NULL) {
        SymbolTableNode* next = current->next;
        free(current);
        current = next;
    }
}

/*Función para imprimir la tabla de símbolos (solo para propósitos de depuración)*/ 
void printSymbolTable() {
    SymbolTableNode* current = symbolTable;
    printf("Tabla de simbolos:\n");
    while (current != NULL) {
        printf("%s\n", current->id);
        current = current->next;
    }
}

/* Declaraciones adelantadas de funciones*/
void stackId(char* id);
void processReservada(char* reservada, char* listaVars);
void lista_vars_stack(char* lista);
void lista_vars_check(char* lista);
int isIdDeclared(char* id);

%}


%union{
    char cad[40];
    int number;
    char reservada[10];
    char *inicio;
    char *fin;
    char *coma;
    int simbolos;
}

%token INICIO FIN RESERVADA IDENTIFICADOR ENTERO SIMBOLOS PUNTOCOMA COMA PARENTESISOPEN PARENTESISCLOSE ASIGNACION OTHER

%type <cad> IDENTIFICADOR lista_vars 
%type <number> ENTERO
%type <reservada> RESERVADA
%type <inicio> INICIO
%type <fin> FIN
%type <simbolos> SIMBOLOS
%type <coma> COMA
%%
prog: INICIO codigo FIN 
    ;

codigo: /* empty */
    | codigo stmt 
    ;

stmt: RESERVADA PARENTESISOPEN lista_vars PARENTESISCLOSE PUNTOCOMA 
    {
        processReservada($1, $3);
    }
    | IDENTIFICADOR ASIGNACION expr PUNTOCOMA
    {
        stackId($1);
    }
    ;

lista_vars: lista_vars COMA IDENTIFICADOR 
    |  IDENTIFICADOR 
    ;


expr: ENTERO 
    | IDENTIFICADOR 
    | expr SIMBOLOS expr
    ;

%%





void lista_vars_stack(char* lista) {
    /* Aquí puedes procesar la lista de variables y agregarlas a la tabla de símbolos*/

    // Hacer una copia de la cadena original
    char* lista_copy = strdup(lista);
    if (lista_copy == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria para la copia de la lista de variables.\n");
        exit(EXIT_FAILURE);
    }

    // Tokenizar la copia de la cadena
    char* token = strtok(lista_copy, ",");
    while (token != NULL) {
        stackId(token);
        token = strtok(NULL, ",");
    }

    // Liberar la memoria de la copia
    free(lista_copy);
}

void lista_vars_check (char* lista) {
    

    char* token = strtok(lista, ",");
    while (token != NULL) {

         if (!isIdDeclared(token)) {
        printf("\n-------------------------------------------------\n");
        fprintf(stderr, "   Error semántico: Identificador utilizado sin declarar '%s'\n", token);
        printf("-------------------------------------------------\n");
        exit(EXIT_FAILURE);
         }
        token = strtok(NULL, ",");
    }
}

void stackId(char* id) {
    if (!isIdDeclared(id)) {
        insertId(id);
    } else {
        printf("\n-------------------------------------------------\n");
        fprintf(stderr, "   Error semántico: Identificador duplicado '%s'\n", id);
        printf("-------------------------------------------------\n");
        exit(EXIT_FAILURE);
    }
}


void processReservada(char* reservada, char* listaVars) {
    printf("Procesando palabra reservada: %s\n", reservada);
    printf("Procesando palabra lista: %s\n", listaVars);
    if (strcmp(reservada, "leer") == 0) {
        printf("\nInstruccion LEER\n\n");
        lista_vars_stack(listaVars);
    } else if (strcmp(reservada, "escribir") == 0) {
        printf("\nInstruccion ESCRIBIR\n");
         lista_vars_check(listaVars);
        
    }
}

/*Función para verificar si un ID ya está en la tabla de símbolos*/ 
int isIdDeclared(char* id) {
    SymbolTableNode* current = symbolTable;
    while (current != NULL) {
        if (strcmp(current->id, id) == 0) {
            return 1; // El ID ya está en la tabla de símbolos
        }
        current = current->next;
    }
    return 0; // El ID no está en la tabla de símbolos
}








void yyerror(char *s) {
   
    printf("Error sintactico");
}

int yywrap(){
    return 1;
}


int main(int argc, char **argv){
    printf("      Comienzo de analis... \n");
    printf("--------------------------------------\n");

    yyparse();
    
    getchar();
    printf("--------------------------------------\n");
    
     printf("       Fin analisis... \n");
     printf("       ID encontrados \n");
     printSymbolTable();
    return 0;
}