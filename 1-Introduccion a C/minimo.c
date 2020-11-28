/**********************************************************************************
 * Un programa de ejemplo
 *-----------------------------------------
 *Propósito: afianzar los fundamentos de C
 **********************************************************************************/

// MODULOS
# include <stdio.h>

/*------------------------------------------
 * Programa principal
 *------------------------------------------*/
int main(void)
{
    // Declaracion de variables
    int a, b, c, minimo;

    // Lectura de datos
    printf("introduce el valor de a: "); scanf("%d", &a);
    printf("introduce el valor de b: "); scanf("%d", &b);
    printf("introduce el valor de c: "); scanf("%d", &c);
    
    // Determina el menor de los numeros
    if (a < b) {
        if (a < c) minimo = a;
        else minimo = c;
    }
    else {
        if (b < c) minimo = b;
        else minimo = c;
    }

    // Imprime el resultado en pans
    printf("El minimo es %d\n", minimo);

    return 0;
}