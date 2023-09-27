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
#include <string.h>


int VerificaDecimal (char *s) {
 unsigned i;
 for (i=0; s[i]; i++)
 if (! (isdigit(s[i]) || s[i] == '+' || s[i] == '-')) return 0;
 return 1;
} /* fin Verifica */

int VerificaOctal (char *s) {
 unsigned i;
 for (i=0; s[i]; i++)
 if (! (isdigit(s[i]) && (s[i] != '8') && (s[i] != '9') )) return 0;
 return 1;
} /* fin Verifica */

int VerificaHexadecimal (char *s) {
 unsigned i;
 for (i=0; s[i]; i++)
 if (! (isxdigit(s[i]) || (s[i] == 'x'))) return 0;
 return 1;
} /* fin Verifica */




int ColumnaDecimal (int c) {
 switch (c) {
 case '+': return 1;
 case '-': return 2;
 default /* es digito */: return 0;
 }
} /* fin Columna */

int ColumnaOctal (int c) {
 switch (c) {
 case '0': return 0;
 default /* es digito */: return 1;
 }
} /* fin Columna */

int ColumnaHexadecimal (int c) {
 switch (c) {
 case 'x': return 1;
 case '0': return 0;
 default /* es digito */: return 2;
 }
} /* fin Columna */


int EsDecimal (const char *cadena) { /* Automata 1 */
 static int tt [4][3] = {{2,1,1}, /* Tabla de Transiciones */
 {2,3,3},
{2,3,3},
{3,3,3}};
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

int EsOctal (const char *cadena) { /* Automata 1 */
 static int tt [4][2] = {{1,3}, /* Tabla de Transiciones */
 {2,2},
{2,2},
{3,3}};
 int e = 0; /* estado inicial */
 unsigned int i = 0; /* recorre la cadena */
 int c = cadena[0]; /* primer caracter */

 while (c != '\0') {
 e = tt[e][ColumnaOctal(c)]; /* nuevo estado */
 c = cadena[++i]; /* proximo caracter */
 }
 if (e == 2) /* estado final */ return 1;
 return 0;
} /* fin EsPalabra */


int EsHexadecimal (const char *cadena) { /* Automata 1 */
 static int tt [5][3] = {{1,4,4}, /* Tabla de Transiciones */
 {4,2,4},
{3,4,3},
{3,4,3},
 {4,4,4}};
 int e = 0; /* estado inicial */
 unsigned int i = 0; /* recorre la cadena */
 int c = cadena[0]; /* primer caracter */

 while (c != '\0') {
 e = tt[e][ColumnaHexadecimal(c)]; /* nuevo estado */
 c = cadena[++i]; /* proximo caracter */
 }
 if (e == 3) /* estado final */ return 1;
 return 0;
} /* fin EsPalabra */


int main () {
 char s1[] = "0xFA2$12345$0123$0123987";
 //if (! VerificaOctal(s1)) printf("Caracteres invalidos\n");
 //if (EsOctal(s1))printf("Pertenece al lenguaje\n");
 //printf("no pertenece al lenguaje\n"); return 0;
 const char s[2] = "$";
 char *token;

 unsigned int w = 0; //cantidad errores lexicos
 unsigned int x = 0; //cantidad numeros decimales
 unsigned int y = 0; //cantidad numeros octales
 unsigned int z = 0; //cantidad numeros hexadecimales

   /* get the first token */
   token = strtok(s1, s);

   /* walk through other tokens */
   while( token != NULL ) {
      if( VerificaDecimal(token) && EsDecimal(token)){
    	  x++;
    	  printf( "El numero %s es decimal \n", token);
      }
      if( VerificaOctal(token) && EsOctal(token)){
          	  y++;
          	  printf( "El numero %s es octal \n", token);
      }
      if( VerificaHexadecimal(token) && EsHexadecimal(token)){
          	  z++;
          	  printf( "El numero %s es hexadecimal \n", token);
      }



      token = strtok(NULL, s);
   }
   printf("Son %d decimales \n", x);
   printf("Son %d octales \n", y);
   printf("Son %d hexadecimales \n", z);
   return(0);
}



