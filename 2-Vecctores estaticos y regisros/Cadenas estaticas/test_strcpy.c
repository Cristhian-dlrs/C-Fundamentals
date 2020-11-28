/* Librerias */
#include <stdio.h>
#include <string.h>

/* Constantes */
#define MAX_LON 50

/* Programa principal */
int main(void)
{
    // Declaracion de variables
    char cadena[MAX_LON+1], copia[MAX_LON+1];
    int i;

    // Entrada de datos
    printf("Introduce una cadena: "); gets(cadena);

    // Copiamos la cadena 
    strncpy(copia, cadena, MAX_LON+1);
    copia[MAX_LON] = '\0';

    // Convertimos todas las letras en minusculas
    for (i = 0; i <= MAX_LON; i++) {
        if (cadena[i] >= 65 && cadena[i] <= 90)
            cadena[i] += 32;
        else if (cadena[i] == '\0')
            break;
    }

    // Muestra por pans
    printf("%s", copia);

    return 0;
}