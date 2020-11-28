/******************************************************************************
 * Autor: Cristhian de la Rosa
 * ---------------------------
 * 
 * 
 * Objetivo:
 * ------------
 * Este programa implementa una version en C del juego  Tres en Raya.
 * 
 * 
 * Descripcion:
 * ------------ 
 * El tablero se representara con una matriz de 3x3. Las casillas en blanco se
 * represntaran con espacios vacios, el caracter "O" represenara una casilla
 * ocupada con un circulo y el caracter "X" representara una casilla marcada 
 * con una cruz.
 * 
 ** El jugador sera CRUZ y la computadora CIRCULO.
 *
 ** La IA tomara el primer turno.
 * 
 ******************************************************************************/

/*
+==============================================================================+
|                                  LIBRERIAS                                   |
+==============================================================================+*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

/*
+==============================================================================+
|                                   CONSTANTES                                 |
+==============================================================================+*/
#define TALLA 3
#define CRUZ 'X'
#define CIRCULO 'O'
#define ESP 32

/*******************************************************************************
* TABLERO 
* -------       
* Conjunto que definen y muestran el tablero.                          
********************************************************************************/
void init_tablero(char m[TALLA][TALLA])
{
    int i, j;

    for (i = 0; i < TALLA; i++)
        for (j = 0; j < TALLA; j++) 
            m[i][j] = ESP;
}

void muestra_tablero(char m[TALLA][TALLA])
{
    int i, j;

    system("cls");
    printf("+==================================+\n");
    printf("|           TRES EN RAYA           |\n");
    printf("+==================================+\n");
    printf("\n            0    1    2\n");
    printf("         +----+----+----+\n");
    for (i = 0; i < TALLA; i++){
        printf("       %d ", i);
        for (j = 0; j < TALLA; j++) {
            printf("| ");
            printf(" %c ", m[i][j]);
        }
        printf("|");
        printf("\n");
        printf("         +----+----+----+\n");
    }
}

/*******************************************************************************
* ESTADO DEL TABLERO
* ------------------    
* Conjunto de funciones qu comprueban el estado del tablero.
* Las funciones con prefijo "est" buscan el patron ganador de tres en raya.                        
********************************************************************************/

int esta_lleno(char m[TALLA][TALLA])
{
    /* 
     * Retorna 1 si esta lleno.
     * Retorna 0 si esta vacío.
     */

    int i, j;

    for (i = 0; i < TALLA; i++)
        for (j = 0; j < TALLA; j++) 
            if (m[i][j] == ESP)
                return 0;
    return 1;
}

int est_F(char player, char m[TALLA][TALLA])
{
    /* Comprueba Filas */
    int i, j, comp, cont;

    comp = 0;
    for (i = 0; i < TALLA; i++) {
        cont = 0;
        for (j = 1; j < TALLA; j++) 
            if (m[i][0] == m[i][j] && m[i][0] != ESP)
                cont++;
        if (cont == 2) {
            comp = 1;
            break;
        }   
    }
    return comp;
}

int est_C(char player, char m[TALLA][TALLA])
{
    /* Comprueba Columnas */
    int i, j, comp, cont;

    comp = 0;
    for (j = 0; j < TALLA; j++) {
        cont = 0;
        for (i = 1; i < TALLA; i++) 
            if (m[0][j] == m[i][j] && m[0][j] != ESP)
                cont++;
        if (cont == 2) {
            comp = 1;
            break;  
        } 
    }
    return comp;
}

int est_DP(char player, char m[TALLA][TALLA])
{
    /* Comprueba Diagonal principal */
    int i, comp, cont;

    comp = 0;
    cont = 0;
    if(m[0][0] == player) {
        for (i = 1; i < TALLA; i++) 
            if (m[0][0] == m[i][i])
                cont++;
        if (cont == 2) 
            comp = 1; 
    }
    return comp;
}

int est_DS(char player, char m[TALLA][TALLA])
{
    /* Comprueba Diagonal secundaria */
    int i, j, comp, cont;

    comp = 0;
    cont = 0;
    j = 1;
    if(m[0][2] == player) {
        for (i = 1; i  < TALLA; i++) {
            if (m[0][2] == m[i][j])
                cont ++;
            j--;
        }
        if (cont == 2) 
            comp = 1; 
    }
    return comp;
}

int est_ganado(char player, char m[TALLA][TALLA])
{
    /* 
     * Recibe como parametro la letra del jugador y el tablero.
     * Retorna 1 si algun jugador completo 3 en raya.
     * Retorna 0 si ningun jugador completo 3 en eraya.
     */
    int i, comp;

    comp = 0;
    for (i = 0; i < 1; i++) {
        if (est_F(player, m)) {
            comp = 1;
            break;
        }
        if (est_C(player, m)) {
            comp = 1;
            break;
        }
        if (est_DP(player, m)) {
            comp = 1;
            break;
        }
        if (est_DS(player, m)) {
            comp = 1;
            break;
        }
    } 
    return comp;
}

/*******************************************************************************
* JUGADOR
* -------       
* Conjunto de funcines que gestionan las jugadas realizadas por los diferentes
* jugadores asi como la entrada de datos por teclado.                          
********************************************************************************/
int validar_jugada(int fila, int columna, char tablero[][TALLA])
{   
    /*
     * Retorna 1 si la casilla esta Vacia.
     * Retorna 0 si la casilla esta llena.
     */

    int estado = 0;

    if (tablero[fila][columna] == ESP)
        estado = 1;
    return estado;
}

int jugada(int fila, int columna, char tablero[][TALLA])
{
    int jugada;

    if (validar_jugada(fila, columna, tablero)) {
        tablero[fila][columna] = CRUZ;
        jugada = 1;
    }
    else {
        printf("La casilla seleccionada ya esta ocupada!");
        jugada = 0;
    }
    return jugada;
}

int input_jugada(int pos)
{   
    int valido = 1;

    if (pos > 2 || pos < 0) {
        valido = 0;
        return valido;
    }
    return valido;
}

/*******************************************************************************
* IA
* --      
* Conjunto de funcines que gestionan las jugadas realizadas por el computador.                     
********************************************************************************/
void jugadaIA(char tablero[][TALLA])
{
    /* Realiza la primera jugada de la IA */

    int fila, columna;

    // Si fila completa cambiar intervalo
    // Si columna comleta cambiar intervalo
    do {
        srand (time(NULL));
        fila = rand() % (2-0+1) + 0;
        columna = rand() % (2-0+1) + 0;  
    } while (!validar_jugada(fila, columna, tablero));
    tablero[fila][columna] = CIRCULO;
}

// Si fila completa ===================================| Falta por
// Si columna comleta                                  | Implementar 

/*
+==============================================================================+
|                               PROGRAMA PRINCIPAL                             |
+==============================================================================+*/

int main(void)
{

    /*  --------------------  Declaracion de vartiables  -------------------  */

    char tablero[TALLA][TALLA];
    int fila, columna, valido;
    char continuar;

    /* Inicializamos */
    init_tablero(tablero);
    muestra_tablero(tablero);
    printf("\n Presione cualquier techla para empezar: "); 
    scanf("%c", &continuar);


    /* Main loop */
    do {

        muestra_tablero(tablero);
        printf("\n         Turno de la IA...\n");
        /* Turno de la IA */
        if (!est_ganado(CRUZ, tablero)) {
            Sleep(1000);
            jugadaIA(tablero);
            muestra_tablero(tablero);
            if(esta_lleno(tablero)) {
                printf("\n         Hubo un empate!");
                break;
            }
        }
        else {
            muestra_tablero(tablero);
            printf("\n          Has ganado!");
            break;
        }
        
        /* Turno del jugador */
        if (!est_ganado(CIRCULO, tablero)){
            muestra_tablero(tablero);
            printf("\n            Tu turno!\n");

            do {
                do {

                    printf("Fila: "); scanf("%d", &fila);
                    valido = input_jugada(fila);
                } while (!valido);

                do {

                    printf("Columna: "); scanf("%d", &columna);
                    valido = input_jugada(fila);
                } while (!valido);
            } while (!validar_jugada(fila, columna, tablero));

            jugada(fila, columna, tablero);
            muestra_tablero(tablero);
        }   
        else {
            muestra_tablero(tablero);
            printf("\n          Gana la IA");
            break;
        }
       
    } while (!esta_lleno(tablero));

    return 0;
}