/* Librerias incluidas en el programa */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* Declaracion de constantes */
#define MAX_LON 1000
#define ALPHABET 26

/* Programa principal */
int main(void)
{
    // Declaracion de variables
    char cadena[MAX_LON], cont[ALPHABET];
    int i, j, k, l, lonc;

    // Entrada y medicion de cadena de cadena;
    printf("Introduzca un texto: ");
    gets(cadena);
    lonc = strlen(cadena);

    // Medidor de ocurrencia de letras
    for(i = 0; i < ALPHABET; i++)
        cont[i] = 0;

    k = 65;
    l = 97;
    for (i = 0; i < ALPHABET; i++){
        for(j = 0; j < lonc; j++){
            if(isalpha(cadena[j]) && cadena[j] == k || cadena[j] == l)
                cont[i]++;
            else
                continue; 
        }       
        k++;
        l++;
    }

    // Muestra los resultados en pans
    j = 65;
    for(i = 0; i < ALPHABET; i++) {
        if (cont[i] !=0)
            printf("Letra %c: %d\n", j, cont[i]);
        j++;
    }

    return 0;
}