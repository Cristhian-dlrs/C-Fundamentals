/******************************************************************************
 * Autor: Cristhian de la Rosa
 * ---------------------------
 * 
 * Nombre: Programa.c
 * ------------------
 *
 * Objetivo:
 * ------------
 *
 * Descripcion: No depurado!!
 * ------------ 
 *
 ******************************************************************************/

/*
+==============================================================================+
|                                  LIBRERIAS                                   |
+==============================================================================+*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*******************************************************************************
* CONSTANTES
* ----------      
* TALLA : Maxima longitud de palabra de entrada                          
********************************************************************************/
#define TALLA 30

/*******************************************************************************
* Diccionario
* -----------
* Gestiona un diccionario de palabras de longitud variable.         
********************************************************************************/
struct Dict {
    char **palabra;
    int palabras;
};

struct Dict crea_dict(void)
{
    struct Dict d;

    d.palabra = NULL;
    d.palabras = 0;
    return d;
}

/*
 * Comprueba si una palabra existe en el diccionario
 * Retorna 1 si existe.
 * Retorna 0 si no existe.
 */
int esta_en_dict(struct Dict *d, char pal[])
{   
    int i, esta = 0;

    for (i = 0; i < d->palabras; i ++)
        if (strcmp(d->palabra[i], pal) == 0) {
            esta = 1;
            break;
        }
    return esta;
}

/* 
 * Inserta una palabra en el diccionario si la misma no se encuentra ya en el.
 * La asignacion de memoria para la palabra se realiza de forma dinamica.
 * Se realloca la memoria reservada a las palabras del diccionario.
 */
void insertar_palabra(struct Dict *d, char pal[])
{   
    if (esta_en_dict(d, pal))
         return;
    else {
        d->palabra = realloc(d->palabra, (d->palabras+1) * sizeof(char*));
        d->palabra[d->palabras] = malloc((strlen(pal)+1) * sizeof(char));
        strcpy(d->palabra[d->palabras], pal);
        d->palabras ++;
    }
}

/* Libera la memoria ocupada por el diccionario cuando no la necesite mas */
void libera_dict(struct Dict *d)
{
    int i;
    
    if(d->palabra != NULL){
        for (i = 0; i < d->palabras; i++)
            free(d->palabra[i]);
        free(d->palabra);
        d->palabra = NULL;
        d->palabras = 0;
    }
}

/* Elimina una palabra de un diccionario */
void borrar_palabra(struct Dict *d, char pal[])
{
    int i, j;

    for (i = 0; i < d->palabras; i++)
        if (strcmp(d->palabra[i], pal) == 0) {
            d->palabra = realloc(d->palabra, (d->palabras) * sizeof(char*));
            for (j = i; j < (d->palabras - 1); j++)
                d->palabra[j] = d->palabra[j+1]; 
            d->palabras --;
            break;
        }
}
 
/* 
 * Muestra por pantalla todas las palabras del diccionario que empiecen por
 * un prefijo indicado
 */
void buscar_pref(struct Dict *d, char pref[])
{
    int i, j, lon;
    int igual = 1;

    lon = strlen(pref);
    for (i = 0; i < d->palabras; i++)
        for (j = 0; j < lon; j++)
            if (d->palabra[i][j] == pref[j])
                igual = 1;
            else {
                igual = 0;
                break;
            }
        
        if (igual == 1)
            printf("%s", d->palabra[i]);
}

/* Listar diccionario */
void listar(struct Dict *d)
{
    int i;

    for (i = 0; i < d->palabras; i++)
        printf("%s\n", d->palabra[i]);
}

/*
 * Muestra por pantalla las palabras del diccionario que terminen por
 * un sufijo indicado
 */

void buscar_suf(struct Dict *d, char suf[])
{
    int i, j, lons, lonp;
    int igual = 1;

    lons = strlen(suf);
    for (i = 0; i < d->palabras; i++) { 
        lonp = strlen(d->palabra[i]);
        for (j = lonp - lons; j < lonp; j++)
            if (d->palabra[i][j] == suf[j])
                igual = 1;
            else {
                igual = 0;
                break;
            }
        if (igual == 1)
            printf("%s", d->palabra[i]);
    }
}

/* Desppliega el menu principal */
int main_menu()
{
    int opcion;
    char linea[1];

    do { 
                system("cls");
                printf("+-----------------------+\n");
                printf("|      DICCIONARIO      |\n");
                printf("+-----------------------+\n");
                printf("\n");
                printf("[1] Agregar palabra\n");
                printf("[2] Eliminar palabra\n");
                printf("[3] Buscar por prefijo\n");
                printf("[4] Buscar por sufijio\n");
                printf("[5] Listar diccionario\n");
                printf("[6] Eliminar diccionario\n");
                printf("[7] Salir\n");
                printf("\nElija una opcion: ");
                gets(linea); sscanf(linea, "%d", &opcion);
            } while (opcion < 1 || opcion > 7);

    return opcion;
}

/*
+==============================================================================+
|                               PROGRAMA PRINCIPAL                             |
+==============================================================================+*/

int main(void)
{
    /*  --------------------  Declaracion de vartiables  -------------------  */

    struct Dict diccionario;
    int opcion;
    char palabra[TALLA], ch;
    
    /* Inicializamos */
    diccionario = crea_dict();

    /* Main loop */
    do {
        opcion = main_menu();
        switch (opcion) { 
        
            case 1:
                system("cls");
                printf("Introduzca una palabra: ");
                gets(palabra);
                insertar_palabra(&diccionario, palabra);
                printf("Palabra agregado con exito!\n");
                printf("\nPresione culaquier tecal para continuar: ");
                scanf("%f", ch);
                break;

            case 2:
                system("cls");
                printf("Introduzca una palabra: ");
                gets(palabra);
                borrar_palabra(&diccionario, palabra);
                printf("Palabra borrada con exito!\n");
                printf("\nPresione culaquier tecal para continuar: ");
                scanf("%f", ch);
                break;

            case 3:
                system("cls");
                printf("Introduzca el prefijo: ");
                gets(palabra);
                buscar_pref(&diccionario, palabra);
                printf("\nPresione culaquier tecal para continuar: ");
                scanf("%f", ch);
                break;

            case 4: 
                system("cls");
                printf("Introduzca el sufijo: ");
                gets(palabra);
                buscar_suf(&diccionario, palabra);
                printf("\nPresione culaquier tecal para continuar: ");
                scanf("%f", ch);
                break;

            case 5:
                system("cls");
                listar(&diccionario);
                printf("\nPresione culaquier tecal para continuar: ");
                scanf("%f", ch);

            case 6:
                system("cls");
                printf("Diccionario borrado");
                libera_dict(&diccionario);
                printf("Diccionario borrado!\n");
                printf("\nPresione culaquier tecal para continuar: ");
                scanf("%f", ch);
                break;
        }

    } while (opcion != 7);

    return 0;
}
