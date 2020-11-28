/******************************************************************************
 * Autor: Cristhian de la Rosa
 * ---------------------------
 * 
 * Nombre: mayoresd.c
 * -------------------
 *
 * Objetivo:
 * ---------
 * Escribe un programa que lea por teclado un vector de int cuyo tamaño se
 * solicitará previamente al usuario. Una vez leídos los componentes del vector, 
 * se ordenará con el método de la burbuja. Recuerda liberar toda memoria dinámica 
 * solicitada antes de finalizar el programa.
 *
 * Descripcion:
 * ------------ 
 * ...
 ******************************************************************************/

/*
+==============================================================================+
|                                  LIBRERIAS                                   |
+==============================================================================+*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*******************************************************************************
* Vector Dinamico de Enteros 
* --------------------------
* Esta estructura de datos que almacena vectores dinamicos y su tamaño, para
* designarla usaremos las siglas VDE.        
********************************************************************************/
struct VDE {
    int* elementos;
    int talla;
};

void buble_sort(struct VDE *entrada)
{
    int i, j, aux;

    for (i = 0; i < (entrada->talla - 1); i++)
        for (j = 0; j < ((entrada->talla -1)- i); j++) 
            if (entrada->elementos[j] > entrada->elementos[j+1]) {
                aux = entrada->elementos[j];
                entrada->elementos[j] = entrada->elementos[j+1];
                entrada->elementos[j+1] = aux;
            }
}

/*******************************************************************************
* Test
* ----     
* Comprobacion del correcto funcinamiento de la funcion.
********************************************************************************/
int main(void)
{
    int i;
    struct VDE vector;

    // Soliictamos el tamaño del vector
    system("cls");
    printf("Digite la talla del vector: ");
    scanf("%d", &vector.talla);
    
    // Solicitamos memoria para alojar el vector
    vector.elementos = malloc(vector.talla * sizeof(int));

    // Cargamos el vector con valores aleatorios
    srand(time(0));
    for (i = 0; i < vector.talla; i++)
        vector.elementos[i] = rand() % (1000-0+1) + 0; // (ls - li+1) + li

    // Ordenamos e imprimimos por pantalla
    printf("\nEntrada: \n");
    printf("[");
    for (i = 0; i < vector.talla; i ++)
        printf("%d ,", vector.elementos[i]);
    printf("]\n");

    buble_sort(&vector);
    printf("\nSalida: \n");
    printf("[");
    for (i = 0; i < vector.talla; i ++)
        printf("%d ,", vector.elementos[i]);
    printf("]\n");
    
    // Liberamos la memoria solicitada
    free(vector.elementos);
    vector.elementos = NULL;
    vector.talla = 0;

    return 0;
}