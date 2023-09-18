/*
 ============================================================================
 Name        : SSL.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int Verifica (char *s) {
 unsigned i;
 for (i=0; s[i]; i++)
 if (! (isdigit(s[i]) || s[i] == '+' || s[i] == '-')) return 0;
 return 1;
} /* fin Verifica */

int Columna (int c) {
 switch (c) {
 case '+': return 1;
 case '-': return 2;
 default /* es digito */: return 0;
 }
} /* fin Columna */



int EsPalabra (const char *cadena) { /* Automata 1 */
 static int tt [4][3] = {{2,1,1}, /* Tabla de Transiciones */
 {2,3,3},
{2,3,3},
{3,3,3}};
 int e = 0; /* estado inicial */
 unsigned int i = 0; /* recorre la cadena */
 int c = cadena[0]; /* primer caracter */

 while (c != '\0') {
 e = tt[e][Columna(c)]; /* nuevo estado */
 c = cadena[++i]; /* proximo caracter */
 }
 if (e == 2) /* estado final */ return 1;
 return 0;
} /* fin EsPalabra */


int main () {
 char s1[] = "12a45";
 if (! Verifica(s1)) printf("Caracteres invalidos\n");
 if (EsPalabra(s1))printf("Pertenece al lenguaje\n");
 printf("no pertenece al lenguaje\n"); return 0;
}


