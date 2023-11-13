#include<stdio.h>
#include<string.h>
#include<stdbool.h>

bool esCaracterNumerico(char caracter);

void tomaCaracter (int contador); 


int main(int argc, char const *argv[])
{
   
    tomaCaracter(0);
    return 0;
}


void tomaCaracter (int contador){

char caracter;
    bool continuar;

    printf("         | Ingrese un caracter numerico: ");
    scanf(" %c", &caracter);

    if (esCaracterNumerico(caracter))
    {
        printf("-------  |\n");
        printf("| q%d+ |  | El caracter %c es numerico y su valor entero es %d\n", contador, caracter, caracter - '0');
        printf("-------  |\n");
        printf("   |     |\n");
        printf("   V     |\n");
        tomaCaracter(contador + 1);
    }
    else
    {
        continuar = false;
        printf("-------  |\n");
        printf("|  q%d-|  | El caracter %c no es numerico\n", contador, caracter);
        printf("-------  |\n");
    }
    
    if (continuar)
    {
        tomaCaracter(contador);
    }

}



bool esCaracterNumerico(char caracter)
{
    // Comprobamos si el caracter es digito numerico ('0' a '9')
    return (caracter >= '0' && caracter <= '9');
}
