/* Librerias */
#include <stdio.h>

/* Constantes */
#define MAX_LON 50

/* Programa principal */
int main(void)
{
    /* Defincion de variables */
    char cadena[MAX_LON+1];
    char copia[MAX_LON +1];
    int i;

    /* Entrada de datos */
    printf("Escriba una cadena: "); gets(cadena);

    /* Encriptamos los datos y comvertimos en minusculas */
    i = 0;
    while (cadena[i] != '\0'){
        if (cadena[i] == 90 || cadena[i] == 122)
            cadena[i] -= 25;
        else
            cadena[i] += 1;
        i++;
    }

    /* Copiamos los datos a la nueva cadena */

    for (i = 0; i <= MAX_LON; i++){
        cadena[i] = cadena[i];
        if (cadena[i] == '\0')
            break;
    }

    /* Escribe resultados */
    printf("%s", copia);

    return 0;
}