#include<stdio.h>
#include<string.h>
#include<stdbool.h>

bool esCaracterNumerico(char caracter);


int main(int argc, char const *argv[])
{
    char caracter;
    bool continuar;
    int contador = 0 ;
    
    do
    {
            printf("         | Ingrese un caracter numerico: ");
        scanf(" %c", &caracter);

        if (esCaracterNumerico(caracter))
        {
            // printf("El caracter %c es numerico y su valor entero es %d\n", caracter, caracter - '0');
            printf("-------  |\n");
            printf("| q%d+ |  | El caracter %c es numerico y su valor entero es %d \n",contador,caracter, caracter - '0');
            printf("-------  |\n");
            printf("   |     |\n");
            printf("   V     |\n");
            continuar = true;
            contador++;
        }
        else
        {
            //printf("El caracter %c no es numerico\n", caracter);
            continuar = false;
            printf("-------  |\n");
            printf("|  q%d-|  | El caracter %c no es numerico\n",contador,caracter);
            printf("-------  |\n");
            }

        
    } while (continuar);

    return 0;
}


bool esCaracterNumerico(char caracter)
{
    // Comprobamos si el caracter es digito numerico ('0' a '9')
    return (caracter >= '0' && caracter <= '9');
}
