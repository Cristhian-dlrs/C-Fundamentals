// MODULOS
#include <stdio.h>

// CONSTANTES
#define SIZE 40

int main(void)
{
    // Variables
    int i, f[SIZE], num;
    char num_in;

    // Carga el vector con numeros de fibonacci
    f[0] = 0;
    f[1] = 1;
    for (i = 2; i < SIZE; i++){
        f[i] = f[i-1] + f[i-2];
    }

    // Verifica si el numero esta en la sucesion generada
    printf("Type a number: "); scanf("%d", &num);
    
    num_in = 0;
    for (i = 0; i < SIZE; i++){
        if (num == f[i]){
            printf("El numero indicado esta en la sucesion de fibonacci \n");
            num_in = 1;
            break;
        }
    }

    if (num_in == 0)
        printf("El numero indicado NO esta en la sucesion de fibonacci \n");

    return 0;
}