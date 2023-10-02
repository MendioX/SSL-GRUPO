#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
//Codigo para generar la cadena postfija (notacion polaca inversa)

// creamos la pila para los operadores
typedef struct opNodo
{
   char info;
   struct opNodo* sig;
}nodoOp;

typedef nodoOp* ptrNodoOp;

void pushOp(ptrNodoOp* pila, char info)
{
   ptrNodoOp nuevo=(ptrNodoOp)malloc(sizeof(nodoOp));
   nuevo->info=info;
   nuevo->sig=*pila;
   *pila=nuevo;
}

char popOp(ptrNodoOp* pila)
{
      char ret=(*pila)->info;
      ptrNodoOp aux=(*pila);
      *pila=aux->sig;
       free(aux);

      return ret;

}

int estaVacia(ptrNodoOp pila){
	if(pila == NULL){
		return 1;
	}else{
	return 0;
	}
}

//devuelve un int que ese el nivel de precedencia del operador
int nivelPrecedencia(char operador){
	int nivel =0;
	switch(operador){
			case '+': nivel =1;
			          break;
			case '-': nivel =1;
			          break;
			case '*': nivel =2;
			          break;
			case '/': nivel =2;
			          break;
		}
		return nivel;
}

int tieneMayorOIgualPrioridad(char operador1, char operador2){
	int precedenciaPrimerOperador=nivelPrecedencia(operador1);
	int precedenciaSegundoOperador=nivelPrecedencia(operador2);
	if(precedenciaPrimerOperador>=precedenciaSegundoOperador){
		return 1;
	}else{
		return 0;
	}
}


int esOperador(char elemento){
	if(elemento == '+' ||
	   elemento == '-' ||
	   elemento == '*' ||
	   elemento == '/'
	   ){
		return 1;
	}else{
		return 0;
	}
}

//verifica que los caracters operando son decimales
int esOperando(char elemento){
	if(elemento >='0' && elemento <='9'){
		return 1;
	}else{
		return 0;
	}
}


//transforma la cadena de la expresion aritmetica que se ingresa en notacion infija, a la notacion postfija (polaca inversa)
char* infijaToPostfija(char * infija){
	char elemento,operador;
	char  *postfija;
	postfija=malloc(sizeof(char)*100);
	int j=0;
	int i=0;
	ptrNodoOp pilaOp = NULL;

	//creamos el ciclo para procesar la cadena infija
	int longitud= strlen(infija);

	while (i<longitud){
		elemento= infija[i];
		i++;
	//procesar todos los caracteres numericos de izquierda a derecha hasta encontrar un operador
			while(esOperando(elemento)){
				postfija[j]=elemento;
				j++;

				elemento= infija[i];
				i++;
			}
			postfija[j]= '$'; //delimitador
			j++;

		if (esOperador(elemento)){	//generamos pila de operadores
			if(!estaVacia(pilaOp)){	//check pila diferente de vacio
				int seDebeContinuar;
				do{
					operador=popOp(&pilaOp);
				    if(tieneMayorOIgualPrioridad(operador, elemento)){
						postfija[j]=operador;
						j++;
						postfija[j] = '$';
						j++;

						seDebeContinuar=1;
					}else{
						seDebeContinuar=0;
						pushOp(&pilaOp,operador);

					}
				}while(!estaVacia(pilaOp) && seDebeContinuar);
			}
			pushOp(&pilaOp,elemento);

		}
	}
	while(!estaVacia(pilaOp)) {
		operador=popOp(&pilaOp);
		postfija[j]=operador;
		j++;
		postfija[j] = '$';
		j++;
	}
	postfija[j]='\0';
    return postfija;
}
//Codigo para hacer el calculo

int VerificaDecimal (char *s) {
 unsigned i;
 for (i=0; s[i]; i++)
 if (! (isdigit(s[i]) || s[i] == '+' || s[i] == '-')) return 0;
 return 1;
} /* fin Verifica */

int ColumnaDecimal (int c) {
 switch (c) {
 case '0': return 0;
 case '+': return 1;
 case '-': return 2;

 default /* es digito 1-9 */: return 3;
 }
} /* fin Columna */

int EsDecimal (const char *cadena) { /* Automata 1 */
 static int tt [4][4] = {{3,1,1,2}, /* Tabla de Transiciones */
 {3,3,3,2},
{2,3,3,2},
{3,3,3,3}};
 int e = 0; /* estado inicial */
 unsigned int i = 0; /* recorre la cadena */
 int c = cadena[0]; /* primer caracter */

 while (c != '\0') {
 e = tt[e][ColumnaDecimal(c)]; /* nuevo estado */
 c = cadena[++i]; /* proximo caracter */
 }
 if (e == 2) /* estado final */ return 1;
 return 0;
} /* fin EsPalabra */


//pila de la calculadora
typedef struct tnodo
{
   int info;
   struct tnodo* sig;
}nodo;

typedef nodo* ptrNodo;

void push(ptrNodo* pila, int info)
{
   ptrNodo nuevo=(ptrNodo)malloc(sizeof(nodo));
   nuevo->info=info;
   nuevo->sig=*pila;
   *pila=nuevo;
}

int pop(ptrNodo* pila)
{
      int ret=(*pila)->info;
      ptrNodo aux=(*pila);
      *pila=aux->sig;
       free(aux);

      return ret;

}



void tomarCalculo(char cadena[]){

printf("Ingrese el calculo a realizar: ");

scanf("%s", cadena);

}


void nuevaOperacion(bool *seguir){
char next;

printf ("\n--------------------------------\n");
printf ("Desea operar nuevamente? Y/N  -> ");

scanf(" %c", &next);

if (next == 'y' || next == 'Y')
{
	*seguir = true;
	system("cls");
}else{
	*seguir= false;
}
}


int main(){
	bool seguir = true;

	do{

	char cadena [100];
	// char cadena[]="12*12-1000";

	tomarCalculo(cadena);
	char *postfija;
	postfija=infijaToPostfija(cadena);
	printf("Cadena postfija %s \n",postfija);

	ptrNodo pila = NULL;
	int op2;


	char delimitador[2] = "$";
	char *token;


	token = strtok(postfija, delimitador);

		   /* para recorrer la cadena con el $ como delimitador */
		   //mientras token diferente de vacio
		   while( token != NULL ) {
		     if(VerificaDecimal(token) && EsDecimal(token)){

		    	push(&pila, atoi(token)); //transformamos caracter a numero
		    	//printf("%s \n", token);
		      }else{

		   switch(token[0]){
		   	   case '+':
		   		   push(&pila, pop(&pila) + pop(&pila));
		   		   break;
		   	   case '-':
		   		   op2 = pop(&pila);
		   		   push(&pila, pop(&pila) - op2);
		   		   break;
		   	   case '/':
		   		   op2 = pop(&pila);
		   		   if(op2 != 0){
		   			   push(&pila, pop(&pila) / op2);

		   		   }else{
		   			   printf("error division por cero \n");
		   		   }
		   		   break;
		   	   case '*':
		   		   push(&pila, pop(&pila) * pop(&pila));
		   		   break;
		   	   default:
		   		   printf("Error desconocido");
		   		   break;

		   	   }
		      }
		      token = strtok(NULL, delimitador);

		   }
<<<<<<< HEAD
		   
		   printf("Valor de la pila %d \n", pop(&pila));
=======
		   printf("El resultado es %d", pop(&pila));
>>>>>>> bb3cad4a2cf796daadcadb1a98564862832d657a

		   nuevaOperacion(&seguir);
	}while (seguir);

	printf("\n-------------Fin Programa---------------");
	return 0;
}
