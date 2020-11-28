/******************************************************************************
 * Autor: Cristhian de la Rosa
 * ---------------------------
 * 
 * Nombre: ListaDoble.c
 * --------------------
 *
 * Objetivo:
 * ---------
 * Crear un conjunto de funcines que permiten operar sobre listas doblemente
 * emlazadas con punteros a caveza y cola.
 *
 * Descripcion:
 * ------------ 
 * Se proporcionan las estructuras de datos necesarias y las funciones para su
 * manipulacion.
 ******************************************************************************/

/*
+==============================================================================+
|                                  LIBRERIAS                                   |
+==============================================================================+*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*******************************************************************************
* DNodo
* ------ 
* Tipo de datos especial para la creacion de listas doblemente enlazadas,
* consta de tres campos:
*       struct DNodo *ant ==> puntero al elemento anteror de la lista.
*       info ==> guarda la informacion que queremos almacenar en la lista.
*       struct DNodo *sig ==> puntero al siguiente elemento de la lista.    
*
* El nuevo tipo creado, DLista_cc es un puntero a cabeza y cola de un DNodo.
* El tipo DNodo se renombra como nodo.
* El tipo DLista_cc se renombra como TipoLista;                       
********************************************************************************/
typedef struct DNodo {
    struct DNodo *ant;
    int info;
    struct DNodo *sig;
} Nodo;

typedef struct DLista_cc {
    struct DNodo *cabeza;
    struct DNodo *cola;
} TipoLista;


/*******************************************************************************
* Inicializacion y utilidades
* ---------------------------
* Conjunto de funciones a la creacion de listas doblemente enlazadas con
* doblemente enlazadas con punteros a cabeza y cola, asi como la comprobacion
* de su estado.                     
********************************************************************************/

/* Retorna una lista vacia con punteros apuntando a NULL en cabeza y cola */
TipoLista init(TipoLista lista)
{
   lista.cabeza = lista.cola =  NULL;
   return lista;
}

/* Retorna el numero de elementos de una lista doblemente enlazada */
int longitud(TipoLista lista)
{
    Nodo *aux;
    int longitud = 0;

    for (aux = lista.cabeza; aux != NULL; aux = aux->sig)
        longitud ++;

    return longitud;
}

/* Borra los nodos de una lista y libera su memoria */
void liberar(TipoLista *lista) 
{
    Nodo *aux;
    while (lista->cabeza != NULL) {
        aux = lista->cabeza;
        lista->cabeza = lista->cabeza->sig;
        free(aux);
    }
    lista->cola = NULL;
}

/* Retorna 1 si la lista esta vacia, retorna 0 si no esta vacia */
int estaVacia(TipoLista lista)
{
    return lista.cabeza == NULL;
}

/* Muestra el contenido de la lista al estilo python */
void mostrar(TipoLista lista)
{
    Nodo *aux;

    printf("[");
    for (aux = lista.cabeza; aux != NULL; aux = aux->sig) { 
        if (aux->sig != NULL)
        printf("%d, ", aux->info);
        else 
            printf("%d", aux->info);
    }
    printf("]\n");
}

/* Retorna una lista ordenada por el metodo buble sort */
TipoLista ordenar(TipoLista lista)
{   
    Nodo *aux;
    int i, j, lonLista, tmp;

    lonLista = longitud(lista) - 1;
    if (lonLista > 0) 
        for (i = 0; i < lonLista; i++)
            for (j = 0, aux = lista.cabeza; j < lonLista - i && aux != NULL; 
                 j++,aux = aux->sig) 
            {
                if (aux->info > aux->sig->info) {
                    tmp = aux->info;
                    aux->info = aux->sig->info;
                    aux->sig->info = tmp;
                }
            }
    return lista; 
}

/* Retorna 1 si la lista esta ordenada en orden ascendente y 0 si no lo esta */
int estaOrdenada(TipoLista lista)
{
    Nodo *aux;
    int estado = 1;

    if (longitud(lista) > 1)
        for (aux = lista.cabeza; aux->sig != NULL; aux = aux->sig)
            if (aux->info > aux->sig->info ) {
                estado = 0;
                break;
            }
    return estado;
}

/*******************************************************************************
* Insercion en orden
* ------------------
* Conjunto de funciones destinadas a la insercion de elementos en una lista con
* enlace doble y puntero a cabeza y cola asi como su ordenacion.
********************************************************************************/

/* Inserta un elemento en la cabeza de la lista */
TipoLista insertarCabeza(TipoLista lista, int valor)
{
    Nodo *nuevo = malloc(sizeof(Nodo));

    nuevo->ant = NULL;
    nuevo->info = valor;
    nuevo->sig = lista.cabeza;

    if (estaVacia(lista))
        lista.cola = nuevo;
    else  
        lista.cabeza->ant = nuevo;

    lista.cabeza = nuevo;
    return lista;
}

/* Inserta un elemento en la cola de la lista */
TipoLista insertarCola(TipoLista lista, int valor)
{
    Nodo *nuevo;

    nuevo = malloc(sizeof(Nodo));
    nuevo->info = valor;
    nuevo->sig = NULL;

    if(estaVacia(lista)) {
        nuevo->ant = NULL;
        lista.cabeza = nuevo;
    } else {
        nuevo->ant = lista.cola;
        lista.cola->sig = nuevo;
    }
    lista.cola = nuevo;
    return lista;
}

/* Inserta un elemento en la lista en la posicion indicada */
TipoLista insertarenPos(TipoLista lista, int pos, int valor)
{
    Nodo *aux, *nuevo;
    int i;

    if (pos >= longitud(lista))
        lista = insertarCola(lista, valor);

    else if( pos <= 0 || estaVacia(lista))
        lista = insertarCabeza(lista, valor);

    else {
        nuevo = malloc(sizeof(Nodo));
        nuevo->info = valor;
        for (i = 0, aux = lista.cabeza; i < pos && aux->sig != NULL; i++, aux = aux->sig);   
        nuevo->sig = aux;
        nuevo->ant = aux->ant;
        aux->ant->sig = nuevo;
        aux->ant = nuevo;
    }
    return lista;
}

/* Inserta un elemento manteniendo el orden en una lista ordenada */
TipoLista insertarenOrden(TipoLista lista, int valor)
{
    Nodo  *aux;
    int i, lon;

    lon = longitud(lista);
    
    for (i = 0, aux = lista.cabeza; i < lon; i++, aux = aux->sig)
        if (valor < aux->info) {
            lista = insertarenPos(lista, i, valor);
            return lista;
        }
    lista = insertarCola(lista, valor);
    return lista;
}


/*******************************************************************************
* Busqueda y Borrado
* ------------------
* Conjunto de funciones destinada a la busqueda selectiva de elementos de una
* lista doblemente enlazada con puntero a cabeza y cola.                  
********************************************************************************/

/* Borra el nodoque esta a la cabeza de la lista */
TipoLista borrarCabeza(TipoLista lista)
{
    Nodo *aux;

    if (estaVacia(lista))
        return lista;
    
    if (lista.cabeza == lista.cola) {
        free(lista.cabeza);
        lista.cabeza = lista.cola = NULL;
        return lista;
    } 

    aux = lista.cabeza->sig;
    free(lista.cabeza);
    aux->ant = NULL;
    lista.cabeza = aux;
    return lista;
}

/* Borra el nodo que esta a la cola de la lsita */
TipoLista borrarCola(TipoLista lista)
{
    Nodo *aux;

    if (estaVacia(lista))
        return lista;
    
    if (lista.cabeza == lista.cola) {
        free(lista.cabeza);
        lista.cabeza = lista.cola = NULL;
        return lista;
    } 

    aux = lista.cola->ant;
    free(lista.cola);
    aux->sig = NULL;
    lista.cola = aux;
    return lista;
}

/* Borra todas la primera  ocurrencias del valor suminsitrado */
TipoLista borrarOcurrenci(TipoLista lista, int valor)
{
    Nodo *aux;

    for (aux = lista.cabeza; aux != NULL; aux = aux->sig) {
        if (aux->info == valor)
            break;

        if (aux == NULL)
        return lista;
    }

    if (aux == lista.cabeza)
        lista = borrarCabeza(lista);

    else if (aux == lista.cola)
        lista = borrarCola(lista);
    
    else {
        aux->ant->sig = aux->sig;
        aux->sig->ant = aux->ant;
        free(aux);     
    } 
    return lista;
}

/* Borra todas las ocurrencias del valor suministrado */
TipoLista borrarValor(TipoLista lista, int valor)
{
    Nodo *aux;

    for (aux = lista.cabeza; aux != NULL; aux = aux->sig) {
        if (aux->info == valor) {
            if (aux == lista.cabeza)
                lista = borrarCabeza(lista);

            else if (aux == lista.cola)
                lista = borrarCola(lista);

            else {
                aux->ant->sig = aux->sig;
                aux->sig->ant = aux->ant;
                free(aux);
            }
        }
    }   
    return lista;
}    

/* Retorna una copia invertida una lista con enlace doble */
TipoLista reverse(TipoLista lista)
{
    Nodo *aux;
    TipoLista reversed;

    reversed = init(reversed);
    for(aux = lista.cabeza; aux != NULL; aux = aux->sig) 
        reversed = insertarCabeza(reversed, aux->info);
    return reversed;
}


/********************************* TEST ***************************************/
int main(void)
{
    TipoLista lista;
    int i, num;

    //system("cls");
    lista = init(lista);

    srand(time(0));
    for (i = 0; i < 10; i++) {
        num = rand()% (99-10+1) + 10;
        lista = insertarCola(lista, num);
    }

    //mostrar(lista);

    //lista = borrarCola(lista);
    //lista = borrarCabeza(lista);
    //lista = borrarValor(lista, 4);

    //lista = insertarenPos(lista, 9 , 800);

    lista = ordenar(lista);
    mostrar(lista);
    liberar(&lista);

    mostrar(lista);
    printf("Longitud: %d\n", longitud(lista));
    printf("Esta vacia: %d\n", estaVacia(lista));
    printf("Esta ordenad: %d", estaOrdenada(lista));

    return 0;
}
