/* Modulos importados */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* Definimos  constantes */
#define MAXTALL 1000

/* Definicion de structs */
struct Punto {
    float x,y;
};

struct ListaPuntos {
    struct Punto punto[MAXTALL];
    int s;
};
 
/* Programa principal */
int main(void)
{
    /* Definicion de variables */
    struct ListaPuntos representantes;
    struct ListaPuntos vecino;
    float distancias[MAXTALL], minDist, dx, dy, distancia;
    int i, indexMin;
    char ch; // valor de pausa/retorno

    /* Main loop */
    representantes.s = 0;
    do {

        /* Introduccion de puntos */
        system("cls");
        printf("Coordenadads en x del putno %d: ", (representantes.s+1));
        scanf("%f", &representantes.punto[representantes.s].x);
        printf("Coordenadads en y del putno %d: ", (representantes.s+1)); 
        scanf("%f", &representantes.punto[representantes.s].y);
        
        if (representantes.punto[representantes.s].x == 0 && representantes.punto[representantes.s].y == 0){
            printf("\n");
            printf("Ha salido del programa");
            break; //==> end
        }
        /* Calculamos la distancia a cada punto introducido */
        if (representantes.s > 0){
            for (i = 0; i < representantes.s; i++) {
                dx =  (representantes.punto[representantes.s].x -  representantes.punto[i].x);
                dy = (representantes.punto[representantes.s].y - representantes.punto[i].y);
                distancia = sqrt(dx*dx + dy*dy);
                distancias[i] = distancia;
            }
        }
        else{
            printf("==> Solo ha introducido un punto\n");
            printf("Presione una tecla para continuar: "); scanf("%s", &ch);
    
        }

        /* Calculamos la menor distancia */
        minDist = distancias[0];
        indexMin = 0;
        for (i = 0; i < representantes.s; i ++){
            if (distancias[i] < minDist){
                minDist = distancias[i];
                indexMin = i; 
            }
        }

        /* Imprimimios por pancantidad el vector mas cercano al introducido */
        if(representantes.s > 0){
            printf("Puntos:[");
            for (i = 0; i <= representantes.s; i ++){
                printf("(%8.2f,%8.2f ),", representantes.punto[i].x, representantes.punto[i].y);
            }
            printf("]\n");
            printf("\n");
            printf("El punto mas cercano a (%8.2f,%8.2f ) ",representantes.punto[representantes.s].x, representantes.punto[representantes.s].y);
            printf(" es  el punto ==> (%8.2f, %8.2f)\n", representantes.punto[indexMin].x, representantes.punto[indexMin].y);
            printf("Presione una tecla para continuar: "); scanf("%s", &ch);
        }

        /* Incrementar numero de vectores */
        representantes.s ++;
    } while (representantes.s < MAXTALL);

    return 0;   
}