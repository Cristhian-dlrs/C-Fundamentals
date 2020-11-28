/******************************************************************************
 * Autor: Cristhian de la Rosa
 * ---------------------------
 * 
 * Nombre: mayoresd.c
 * -------------------
 *
 * Objetivo:
 * ---------
 * Desarrollar una función que seleccione todos los números de un vector de 
 * float mayores que un valor dado. Diseña un programa que llame correctamente 
 * a la función y muestre por pantalla el resultado.
 *
 * Descripcion:
 * ------------ 
 *
 ******************************************************************************/

/*
+==============================================================================+
|                                  LIBRERIAS                                   |
+==============================================================================+*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*******************************************************************************
* CONSTANTES
* ----------      
* Documentacion                          
********************************************************************************/
#define TALLA 10

/*******************************************************************************
* Funcioon 
* ---------
*                 
********************************************************************************/
int * select_mayorde(int n, int v[], int talla, int * validados)
{
    int i, j;
    int *mayoresde;

    // Determinamos la cantidad de valores del vctor que  cumplen con la condicion
    *validados = 0;
    for (i =0; i < talla; i++) 
        if (v[i] > n)
            (*validados) ++;

    // Reservamos memoria para los elementos del nuevo vector
    mayoresde = malloc(*validados * sizeof(int));

    // Cargamos el ector con los elementos mayores que n
    j = 0;
    for (i =0; i < talla; i++) 
        if (v[i] > n)
            mayoresde[j++] = v[i];

    return mayoresde;
}


/*******************************************************************************
* Test
* ----     
* Comprobacion del correcto funcinamiento de la funcion.
********************************************************************************/
int main(void)
{
    int v[TALLA], i, j, n;
    int *seleccion, validados;

    // Cargamos el vector con valores aleatorios
    srand(time(0));
    for (i = 0; i < TALLA; i++)
        v[i] = rand()/1000;

    // Solicitamos el valor de condicion
    printf("Seleccionar mayores de N = ");
    scanf("%d", &n);

    // Se efectua la seleccion
    seleccion = select_mayorde(n, v, TALLA, &validados);

    // Mostramos los resultados por pantalla
    printf("Vector original: \n");
    printf("[");
    for (i = 0; i < TALLA; i ++)
        printf("%d, ", v[i]);
    printf("]\n");

    printf("\nSeleccionados: \n");
    printf("[");
    for (i = 0; i < validados; i ++)
        printf("%d ,", seleccion[i]);
    printf("]\n");

    // Liberamos la memoria reservada
    free(seleccion);
    seleccion = NULL;

    return 0;
}
