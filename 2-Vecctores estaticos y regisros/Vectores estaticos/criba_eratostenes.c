// LIBRERIAS
#include <stdio.h>
#include <math.h>

// CONSTANTES
#define N 100

// PROGRAMA PRIONCIPAL
int main(void)
{
    char criba[N];
    int i, j;

    // Inicializamos el vector criba
    criba[0] = 0;
    for (i = 1; i < N; i++)
        criba[i] = 1;

    // Criba de eratostenes optimizada
    for (i = 2; i < sqrt(N); i++)
        if (criba[i])
            for (j = 2; i*j < N; j++)
                criba[i*j] = 0;

    // Muestra los resultados
    for (i = 0; i < N; i++)
        if (criba[i])
            printf("%d\n", i);
    
    return 0;
}