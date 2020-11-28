#include <stdio.h>
#include <string.h>

/* Constantes */
#define MAX_LON 100


/* Programa principal */
int main(void)
{
    // Defincion de variables 
    char cadena[MAX_LON+1], sub_cadena[MAX_LON+1];
    int i, j, indice, lonc, lonsc, cont;

    // Introduccion y medicion de cadenas
    printf("Introduzca una cadena: "); gets(cadena);
    printf("Introduzca la cadena a buscar: "); gets(sub_cadena);
    lonc = strlen(cadena);
    lonsc = strlen(sub_cadena);

    // Transforma las cadenas en minusculas
    i = 0;
    j = 0;
    for (i = 0; i <= MAX_LON; i++) {
        if (cadena[i] >= 65 && cadena[i] <= 90)
            cadena[i] += 32;
        else if (cadena[i] == '\0')
            break;
    }

    for (j = 0; j <= MAX_LON; j++) {
        if (sub_cadena[j] >= 65 && sub_cadena[j] <= 90)
            sub_cadena[j] += 32;
        else if (sub_cadena[j] == '\0')
            break;
    }
   
    // Buscamos la subcadena dentro de la cadena principal
    cont = 0;
    indice = -1; // devuelce -1 si no se encuentra la subcadena buscada
    for (i = 0; i <= lonc - lonsc; i++){
        for (j = 0; j < lonsc; j++){
            if(cadena[i+j] == sub_cadena[j])
                cont++;
            else {
                cont = 0;
                break;
            }
        }
        
        if (cont == lonsc){
            indice = i;
            break;
        }
    }

    // Muestra el resultado en pantalla
    if (indice != -1){
        printf("La subcadena introducida empieza en el indice %d:\n", indice);
        printf("%s\n", cadena);
        for (i = 0; i < indice; i++)
            printf(" ");
        printf("^\n");
    }
    else
        printf("La subcadena introducida no aparece en la cadena principal.");
    
    return 0;
}

