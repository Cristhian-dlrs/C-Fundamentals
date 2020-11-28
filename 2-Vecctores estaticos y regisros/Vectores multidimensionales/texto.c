/* Librerias */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Declaracion de constantes */
#define MAX_LON 1000
#define MAX_PAL 100
#define MAXLONPAL 25

/* Programa principal */
int main(void)
{
    /* Declaracion de variables */
    char texto[MAX_LON], strVector[MAX_PAL][MAXLONPAL], dif_palabras[MAX_PAL][MAXLONPAL];
    int i, j, lontext, palabras, encontrada, dif;
    char aux[MAXLONPAL];

    /* Introduccion de texto */
    system("cls");
    printf("Introduzca un texto (< 1000 char): "); gets(texto);
    lontext = strlen(texto);

    /* Convertimos todas las letras en minusculas */
    for (i = 0; i < MAX_LON; i++) {
        if (texto[i] >= 65 && texto[i] <= 90)
            texto[i] += 32;
        else if (texto[i] == '\0')
            break;
    }

    /* Descomponemos en un vector de palabras */
    i = 0;
    while(i < lontext && !isalpha(texto[i])) i++; // Descarta las no palabras iniciales

    palabras = 0;
    while(i < lontext) {
        j = 0;

        // Escribe las palabras en el vector de palabras
        while( i < lontext && isalpha(texto[i])) strVector[palabras][j++] = texto[i++];
        strVector[palabras][j] = '\0'; // cerramos cadena
        palabras++;

        if(palabras == MAX_PAL)
            break;

        // Descartamos las no palabras intercaladas
        while(i < lontext && !isalpha(texto[i])) i++;
    }

    /* Colocamos las palabras diferentes en un vector */
    strcpy(dif_palabras[0], strVector[0]);
    dif = 0;
    encontrada = 0;
    for (i = 0; i < palabras; i++) {
         encontrada = 0;
        for (j = 0; j <= dif; j++ ) 
            if (strcmp(strVector[i], dif_palabras[j]) == 0) {
                encontrada = 1;
                break;
            }
        if (!encontrada) {
            strcpy(dif_palabras[dif+1], strVector[i]);
            dif++;
        }
    }
    
    /* Ordenamos el vector (bublesort) */
    for(i = 0; i < dif; i++)
        for (j = 0; j < dif-i; j++)
            if ((strcmp(dif_palabras[j], dif_palabras[j+1])) > 0) {
                strcpy(aux, dif_palabras[j]);
                strcpy(dif_palabras[j], dif_palabras[j+1]);
                strcpy(dif_palabras[j+1], aux);
            }
    
    /* Imprimimos el resultado en pans */
    printf("\n");
    for (i = 0; i < dif+1; i++)
        printf("%s, ", dif_palabras[i]);
    
    return 0;
}