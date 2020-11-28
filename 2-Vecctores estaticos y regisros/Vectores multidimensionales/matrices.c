/* Librerias */
#include <stdio.h>
#include <stdlib.h>

/* Constantes */
#define MAX_DIM 10

/* Programa principal */
int main(void)
{ 
    // Declaracion de variables
    float a[MAX_DIM][MAX_DIM], b[MAX_DIM][MAX_DIM], p[MAX_DIM][MAX_DIM], s[MAX_DIM][MAX_DIM];
    int filas_a, columnas_a, filas_b, columnas_b, filas_p, columnas_p;
    int i, j, k, filas_s, columnas_s, opcion, retorno;

    // Main loop
    opcion = 0;
    do {
        // Menu principal
        do {
            system ("cls");
            printf("+-------------------------+\n");
            printf("| CALCULADORA DE MATRICES |\n");
            printf("+-------------------------+\n");
            printf("\n");
            printf("1-Definir matriz A\n");
            printf("2-Definir matriz B\n");
            printf("3-Suma de matrices A+B\n");
            printf("4-Producto de matrices AxB\n");
            printf("5-Salir\n");
            printf("\n");
            printf("Elija una opcion valida: "); scanf("%d", &opcion);
            system ("cls");
        } while (opcion < 1 || opcion > 5);

        // Cuerpo del programa
        switch (opcion) {
            
            /* Definir A */
            case 1:
                do {
                    system ("cls");
                    printf("Rango maximo 10x10\n");
                    printf("Ingrese el numero de filas de la matriz A: "); scanf("%d", &filas_a);
                    printf("Ingrese el numero de columnas de la matriz A: "); scanf("%d", &columnas_a);
                } while (filas_a > 10 || filas_a < 1 || columnas_a > 10 || filas_a < 1);

                // Cargamos matriz A             
                for (i = 0; i < filas_a; i++) 
                    for (j = 0; j < columnas_a; j++){
                        printf("A(%d%d): ", (i+1), (j+1)); scanf("%8.2f", &a[i][j]);
                    }

                // Retorno
                printf("\n");
                printf("Presione 1 para volver al menu anterior: ");scanf("%d", retorno);
                system ("cls");
                break;

            /* Definir B */
            case 2:
                do {
                    system ("cls");
                    printf("Rango maximo 10x10\n");
                    printf("Ingrese el numero de filas de la matriz B: "); scanf("%d", &filas_b);
                    printf("Ingrese el numero de columnas de la matriz B: "); scanf("%d", &columnas_b);
                } while (filas_b > 10 || filas_b < 1 || columnas_b > 10 || filas_b < 1);

                // Cargamos matriz B             
                for (i = 0; i < filas_b; i++) 
                    for (j = 0; j < columnas_b; j++){
                        printf("B(%d%d): ", (i+1), (j+1)); scanf("%8.2f", &b[i][j]);
                    }

                // Retorno
                printf("\n");
                printf("Presione 1 para volver al menu anterior: ");scanf("%d", retorno);
                system ("cls");
                break;

            /* A+B */
            case 3:
                // Guardamos la suma de A+B en S
                system ("cls");
                filas_s = filas_a;
                columnas_s = columnas_a;
                if (filas_a == filas_b && columnas_a == columnas_b && filas_a != 0){
                    for (i = 0; i < filas_a; i++)
                        for (j = 0; j < columnas_b; j++) 
                            s[i][j] = a[i][j] + b[i][j];

                    // Mostramos el resultado en pans
                    printf("El resultado de sumar las matrices A y B es la matriz S:\n");
                    printf("\n");
                    for (i = 0; i < filas_s; i++) {
                        printf("|");
                        for (j = 0; j < columnas_s; j++)
                            printf("%8.1f", s[i][j]);
                        printf("    |");
                        printf("\n");
                    }
                }
                else 
                    printf("Las matrices no son conformables\n");

                // Retorno
                printf("\n");
                printf("Presione 1 para volver al menu anterior: ");scanf("%d", retorno);
                system ("cls");
                break;
            
            /* AxB */
            case 4:
                // Guardamos el producto de AxB en P
                system ("cls");
                filas_p = filas_a;
                columnas_p = columnas_b;
                if (filas_a == columnas_b && filas_a != 0){
                    for (i = 0; i < filas_p; i++)
                        for (j = 0; j < columnas_p; j++) {
                            p[i][j] = 0;
                            for (k = 0; k < columnas_a; k++)
                                p[i][j] += a[i][k]*b[k][j];
                        }
                
                    // Mostramos el resultado por pans
                    printf("El resultado de multiplicar las matrices A y B es la matriz P:\n");
                    printf("\n");
                    for (i = 0; i < filas_p; i++) {
                        printf("|");
                        for (j = 0; j < columnas_p; j++)
                            printf("%8.1f", p[i][j]);
                        printf("    |");
                        printf("\n");
                    }


                }
                else 
                    printf("Las matrices no son conformables");

                // Retorno
                printf("\n");
                printf("Presione 1 para volver al menu anterior: ");scanf("%d", retorno);
                system ("cls");
                break;
        }

    } while (opcion != 5);

    return 0;
}