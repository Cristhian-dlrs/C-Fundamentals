// AUTOR: CRITSHIAN DE LA ROSA

/*
 * Este programa tiene por objetivo construir una serie de funciones
 * que permitan efectuar transformaciones afines sobre puntos en el 
 * plano.
 */

/*
+==================================================================+
|                           LIBRERIAS                              |
+==================================================================+*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*
+==================================================================+
|                       ESTRUCTURA DE DATOS                        |
+==================================================================+*/

struct Punto {
    float x, y;
};

/*
+==================================================================+
|                          PROCEDIMIENTOS                          |
+==================================================================+*/

void lee_punto(struct Punto *p)
{
    printf("Ingrese las coordenadas\n");
    printf("x: "); scanf("%f", &p->x);
    printf("y: "); scanf("%f", &p->y);
}

void muestra_punto(struct Punto p)
{
    printf("(%f, %f)\n", p.x, p.y);
}

void translada_punto(struct Punto *p, struct Punto trans)
{
    p->x += trans.x;
    p->y += trans.y;
}

void rotacion(struct Punto *p, float rads)
{
    p->x = (p->x * cos(rads) - p->y * sin(rads));
    p->y = (p->x * sin(rads) + p->y * cos(rads));
}

/*
+==================================================================+
|                          PROGRAMA PRINCIPAL                      |
+==================================================================+*/

int main(void)
{
    /*
     * Declaracon de variables
     */

    struct Punto punto, traslacion;
    float rads;


    /*
     * Translacion y rotacion de un punto
     */

    system("cls");
    printf("Punto: ");
    lee_punto(&punto);
    printf("Vector de translacion: ");
    lee_punto(&traslacion);
    translada_punto(&punto, traslacion);
    printf("Ingrese el angulo de rotacion: "); scanf("%f", &rads);
    rotacion(&punto, rads);
    printf("Puntotransladado y rotado %0.1f radianes ==> ", rads);
    muestra_punto(punto);

    return 0;
}