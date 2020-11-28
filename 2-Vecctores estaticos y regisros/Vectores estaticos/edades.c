// Librerias
#include <stdio.h>
#include <math.h>

// Constantes
#define MAX_PERSONAS 100
#define HIST 15

// Prorama principal
int main (void)
{
    // Declaracion de variables
    int edad[MAX_PERSONAS], personas, i, j, k, w, aux;
    float media, suma_edades, suma_desviacion, desviacion;
    int moda, frecuencia, frecuencia_moda, mediana;
    int frecuencia_clase[HIST], rango_inf, rango_sup, maximo;

    // Lectura de edades (termina con un valor negatio)
    personas = 0;
    for (i = 0; i < MAX_PERSONAS; i++){
        printf("Porfavor introduce la edad %d (si es negativa, acabar): ", i+1);
        scanf("%d", &edad[i]);
        if (edad[i] < 0)
            break;
        personas ++;
    }

    if (personas > 0){

         // Calcula la media de edadaes
        suma_edades = 0;
        for (i = 0; i < personas; i++)
            suma_edades += edad[i];
        media = suma_edades/personas;

        // Calculo de la desviación tipica
        suma_desviacion = 0;
        for (i = 0; i < personas; i++)
            suma_desviacion = (edad[i] - media) * (edad[i] - media);
        desviacion = sqrt(suma_desviacion/personas);
        
        //Ordenamos el vector
        for (i = 0; i < personas-1; i++)
            for (j = 0; j < (personas- 1) -i; j++)
                if (edad[j] > edad[j+1]){
                    aux = edad[j];
                    edad[j] = edad [j+1];
                    edad[j+1] = aux;
                }

        // Calculamos la moda
        frecuencia = 0;
        frecuencia_moda = 0;
        moda = -1;
        for (i = 0; i < personas; i++){
            if (edad[i] == edad[i+1]){
                frecuencia ++;
                if (frecuencia > frecuencia_moda){
                    frecuencia_moda = frecuencia;
                    moda = edad[i];
                }
            }
            else
                frecuencia = 0;
        }
                
        // Calculo de la mediana
        mediana = edad[personas/2];

        // Calculamos las frecuencias por intervalos de edad
        for (i = 0; i < HIST; i++)
            frecuencia_clase[i] = 0;

        j = 0;
        k = j+10;
        for (i =0; i < HIST; i++){
            for (w = 0; w < personas; w++)
                if (edad[w] >= j && edad[w] < k) 
                    frecuencia_clase[i]++;
            j += 10;
         k += 10;
        }

        // Determinamos la frecuencia maxima por intervalos
        maximo = 0;
        for (i = 0; i < HIST; i++)
            if (frecuencia_clase[i] > maximo)
                maximo = frecuencia_clase[i];

        // Determinamos el rango util de edades
        for (i = 0; i < HIST; i++) 
            if (frecuencia_clase[i] != 0){
                rango_inf = i;
                break;
            }

        for (i = HIST-1; i > 0; i--) 
            if (frecuencia_clase[i] != 0){
                rango_sup = i+1;
                break;
            }

        // Muestra el vector con las edades ordenado
        printf("\n");
        printf("|");
        for (i = 0; i < personas; i++)
            printf(" %d | ", edad[i]);
        printf("\n");
 
        // Muestra los calculos estadisticos
        printf("\n");
        printf("La media de edad es: %8.2f\n", media);
        printf("La desviacion tipica es: %8.2f\n", desviacion);
        printf("La moda es: %d\n", moda);
        printf("La mediana es: %d\n", mediana);
        printf("\n");
        printf("Histograma: \n");
        printf("\n");

        // Baras del histograma
        j = maximo;
        while(j > 0){
            for (i = rango_inf; i < rango_sup; i++)
                if(frecuencia_clase[i] >= j)
                    printf("|#########");
                else
                    printf("|         ");
            j--;
            printf("|\n");
        }      

        // Separador
        for (i = rango_inf; i < rango_sup; i++)
            printf("+---------");
        printf("+\n");

        // Rangos
        j = rango_inf*10;
        k = j+9;
        for (i = rango_inf; i < rango_sup; i++){        
            printf("|  %d-%d  ", j, k);
            j += 10;
            k += 10;
        }
        printf("|\n");
        printf("\n");
    }
    else
        printf("No se han introducido datos \n");
    
    return 0;
}
