// AUTOR: CRITSHIAN DE LA ROSA

/*
 * Este programa define un tipo de registro y una serie de funciones para
 * representar y manipular fechas.
 */

/*
+==============================================================================+
|                                  LIBRERIAS                                   |
+==============================================================================+*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
+==============================================================================+
|                            ESTRUCTURA DE DATOS                               |
+==============================================================================+*/
struct Fecha {
    int day;
    int month;
    int year;
};

void lee_fecha(struct Fecha *fecha)
{   
    printf("Day: "); scanf("%d" , &fecha->day);
    printf("month: "); scanf("%d" , &fecha->month);
    printf("Year: "); scanf("%d" , &fecha->year);
}

void muestra_fecha(struct Fecha fecha) 
{
    if (fecha.day < 10 && fecha.month <10) {
        printf("0%d/0%d/%d\n", fecha.day, fecha.month, fecha.year);
    }

    else if (fecha.day < 10 && fecha.month > 10) {
        printf("0%d/%d/%d\n", fecha.day, fecha.month, fecha.year);
    }

    else if (fecha.day > 10 && fecha.month < 10) {
        printf("%d/0%d/%d\n", fecha.day, fecha.month, fecha.year);
    }

    else {
        printf("%d/%d/%d\n", fecha.day, fecha.month, fecha.year);
    }
}

void str_fecha(struct Fecha fecha)
{
    int i;
    char mes[12];
    char meses[12][12] = {"enero", "febrero", "marzo", "abril", "mayo",
                          "junio", "julio", "agosto", "septiembre", "octubre",
                          "noviembre", "diciembre"};
    
    for (i = 0; i < 12; i++) 
        if (i == fecha.month) 
            strcpy(mes, meses[i-1]);
    
    printf("%d de %s de %d\n", fecha.day, mes, fecha.year);
}

int es_bisiesto(struct Fecha fecha)
{
    if (fecha.year % 4 == 0 && fecha.year % 100 != 0)
        return 1;

    else if (fecha.year % 400 == 0 && fecha.year % 100 == 0 && fecha.year % 4 == 0)
        return 1;

    else  
        return 0;
}

int intbis(int year)
{
    if (year % 4 == 0 && year % 100 != 0)
        return 1;

    else if (year % 400 == 0 && year % 100 == 0 && year % 4 == 0)
        return 1;

    else  
        return 0;
}

int fecha_comp(struct Fecha fecha1, struct Fecha fecha2)
{
    /* 
     * Compara una fecha A con una fecha B
     * Devuelve 1 si A es mayor que B
     * Devuelve -1 si A es menor que B
     * Devuelve 0 si A == B
     */
     
    if (fecha1.year > fecha2.year)
        return 1;

    else if (fecha1.year < fecha2.year)
        return -1;

    else {
        if (fecha1.month > fecha2.month)
            return 1;

        else if (fecha1.month < fecha2.month)
            return -1;

        else {
            if (fecha1.day > fecha2.day)
                return 1;

            else if (fecha1.day < fecha2.day)
                return -1;

            else
                return 0;
        }
    }          
}

int valida_fecha(struct Fecha fecha)
{   
    if (fecha.month > 0 && fecha.month <= 12 && fecha.day > 0)
        
        switch (fecha.month) {
            
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                if (fecha.day <= 31)
                    return 1;
                else 
                    return 0;
                break;

            case 4:
            case 6:
            case 9:
            case 11:
                if (fecha.day <= 30)
                    return 1;
                else    
                    return 0;
                break;

            case 2:
                if(es_bisiesto(fecha) && fecha.day <= 29)
                    return 1;
                else if (!es_bisiesto(fecha) && fecha.day <= 28)
                    return 1;
                else 
                    return 0;  
                break;
            }
    else 
        return 0;
}

/* ------------------------- Diferencia entre dos fechas -------------------- */

/**
 * Contiene una serie de funciones orientadas a calcular la diferencia entre dos 
 * fechas dadas.
 * 
 ==============================================================================+
 * complet_YearI: Determina el numero de dias hasta finalizar un año.          |
 *                                                                             |
 * comlet_yearF: Determnina el numero de dias desde el inicio de año.          |
 *                                                                             |
 * dif_sameYr: Determina la dierencia en dias etre fechas del mismo año.       |
 *                                                                             |
 * fecha_dif: Engloba las funciones anteriores para determinar la diferencia   |
 * en dias entre dos fechas dadas.                                             |
 ==============================================================================+
 */

int complet_yearI(struct Fecha fecha)
{
    int i, mes, dias, aux;

    dias = 0;   
    aux = fecha.year;
    mes = fecha.month;
    for (i = mes; i <= 12; i++)
        switch (i) {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                dias += 31;
                break;

            case 4:
            case 6:
            case 9:
            case 11:
                if (i == mes)
                    dias += 30 - fecha.day;
                else 
                    dias += 30;
                break;

            case 2:
                if(intbis(aux) && i == mes)
                    dias += 29 - fecha.day;
                else if (!intbis(aux) && i == mes)
                    dias += 28 - fecha.day; 
                else 
                    dias += 28;
                break;
        }
    
    return dias;
}

int complet_yearF(struct Fecha fecha)
{
    int i, mes, dias, aux;

    dias = 0;   
    aux = fecha.year;
    mes = fecha.month;
    for (i = 1; i < mes; i++)
        switch (i) {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                dias += 31;
                break;

            case 4:
            case 6:
            case 9:
            case 11:
                    dias += 30;
                break;

            case 2:
                if(intbis(aux))
                    dias += 29 ;
                else 
                    dias += 28;
                break;
        }
    
    dias += fecha.day;
    return dias;
}

int dif_sameYr(struct Fecha fecha1, struct Fecha fecha2)
{
    int i, max, min, dias, aux, comp, dmin, dmax;

    dias = 0;
    comp = fecha_comp(fecha1, fecha2);
    switch (comp) {
        case -1:
            max = fecha2.month;
            min = fecha1.month;
            aux = fecha1.year;
            dmin = fecha1.day;
            dmax = fecha2.day;
            break;
    
        case 0:
            return dias;
            break;

        case 1:
            max = fecha1.month;
            min = fecha2.month;
            aux = fecha1.year;
            dmin = fecha2.day;
            dmax = fecha1.day;
    }   

    if (min != max) {
        for (i = min; i <= max; i++)
            switch (i) {
                case 1:
                case 3:
                case 5:
                case 7:
                case 8:
                case 10:
                case 12:
                    if (i == min)
                        dias += 31 - dmin;
                    else if (i == max)
                        dias += dmax;
                    else 
                        dias += 31;
                    break;

                case 4:
                case 6:
                case 9:
                case 11:
                    if (i == min)
                        dias += 30 - dmin;
                    else if (i == max)
                        dias += dmax;
                    else 
                        dias += 30;
                    break;

                case 2:
                    if(intbis(aux) && i == min)
                        dias += 29 - dmin ;
                    else if (intbis(aux) && i == max)
                        dias += dmax;
                    else if(!intbis(aux) && i == min)
                        dias += 28 - dmin ;
                    else if (!intbis(aux) && i == max)
                        dias += dmax;
                    else 
                        dias += 28;
                    break;
            }
        return dias;
    }

    else
        return abs(fecha1.day - fecha2.day);

    return dias-1;
}

int fecha_dif(struct Fecha fecha1, struct Fecha fecha2)
{
    int i, min, max, dias, aux;

    aux = fecha_comp(fecha1, fecha2);
    dias = 0;
    switch (aux) { 
    
        case -1:
            if (fecha1.year != fecha2.year){
                min = fecha1.year;
                max = fecha2.year;
                for (i = (min+1); i < max; i++) {
                    if (intbis(i))
                        dias += 366;
                    else 
                        dias += 365;
                }

                dias += complet_yearI(fecha1);
                dias += complet_yearF(fecha2);
                return dias;
            }

            else 
                return dif_sameYr(fecha1, fecha2);
            break;

        case 0:
            return dias;
            break;

        case 1:
            if (fecha1.year != fecha2.year) {
                min = fecha2.year;
                max = fecha1.year;
                for (i = (min+1); i < max; i++) {
                    if (intbis(i))
                        dias += 366;
                    else 
                        dias += 365;
                }

                dias += complet_yearI(fecha2);
                dias += complet_yearF(fecha1);
                return dias;
            }

            else 
                return dif_sameYr(fecha1, fecha2);
            break;
    }
}

/*
+==============================================================================+
|                               PROGRAMA PRINCIPAL                             |
+==============================================================================+*/

int main (void)
{
    /*  --------------------  Declaracion de vartiables  -------------------  */
    struct Fecha fecha1, fecha2;
    int a;
    /*
    system("cls");
    lee_fecha(&fecha1);
    if (!valida_fecha(fecha1))
        printf("Fecha no valida\n");

    lee_fecha(&fecha2);
    if (!valida_fecha(fecha2))
        printf("Fecha no valida\n");
    //muestra_fecha(fecha1);
    //str_fecha(fecha1);
    //printf("%d", fecha_cmop(fecha1, fecha2));
    //printf("%d", fecha_dif(fecha1, fecha2));
    printf("%d", fecha_dif(fecha1, fecha2));
    */
    //scanf("%d", &a); printf("%d" , intbis(a));
    return 0;
}

