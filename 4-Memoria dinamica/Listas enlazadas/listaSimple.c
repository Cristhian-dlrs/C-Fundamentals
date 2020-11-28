/******************************************************************************
 * Autor: Cristhian de la Rosa
 * ---------------------------
 * 
 * Nombre: ListaSimple.c
 * ---------------------
 *
 * Objetivo:
 * ---------
 * Crear un conjunto de funcines que permiten operar sobre estructuras de datos
 * dinamicas, como listas enlazadas.
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
* Nodo
* -----   
* Tipo de datos especial para la creacion de listas enlazadas, consta de dos
* campos:
*       # info ==> guarda la informacion que queremos almacenar en la lista.
*       # struct Nodo *sig ==> puntero al siguiente elemento de la lista.  
*
* El nuevo tipo creado, TipoLista es un puntero a un nodo.                       
********************************************************************************/
struct Nodo {
    int info;
    struct Nodo *sig;
};

typedef struct Nodo *TipoLista;

/* Crea una lista vacia */
TipoLista lista_vacia(void)
{
    return NULL;
}

/* Comprueba si la lista esta vacia */
int es_lista_vacia(TipoLista lista)
{
    return lista == NULL;
}

/* Devuelve la longitud de la lista */
int longitud_lista(TipoLista lista)
{
    struct Nodo *aux;
    int contador = 0;

    for (aux = lista; aux != NULL; aux = aux->sig)
        contador ++;
    return contador;
}

/* Devuelve el maximo valor de una lista de enteros */
int max_lista(TipoLista lista)
{
    struct Nodo *aux;
    int maximo;
    
    if (lista != NULL) { 
        maximo = lista->info;
        for (aux = lista; aux != NULL; aux = aux->sig)
            if (aux->info > maximo)
                maximo = aux->info;
    }
    else 
        maximo = 0;
    return maximo;
}

/* Devuelve el menor elemento de una lista de enetros */
int min_lista(TipoLista lista)
{
    struct Nodo *aux;
    int minimo;
    
    if (lista != NULL) { 
        minimo = lista->info;
        for (aux = lista; aux != NULL; aux = aux->sig)
            if (aux->info < minimo)
                minimo = aux->info;
    }
    else 
        minimo = 0;
    return minimo;
}

/* Devuelve la media de los elementos de la lista */
float media_lista(TipoLista lista)
{
    struct Nodo *aux;
    int sumatoria = 0;
    float media;
    
    if (lista != NULL) 
        for (aux = lista; aux != NULL; aux = aux->sig)
            sumatoria += aux->info;
    else 
        sumatoria = 0;
    
    if (sumatoria!= 0)
        media = sumatoria / longitud_lista(lista);
    else 
        media = 0;

    return media;
}

/* Muestra la lista en consola al estilo python */
void mostrar_lista(TipoLista lista)
{
    struct Nodo *aux;

    printf("[");
    for (aux = lista; aux != NULL; aux = aux->sig)
        if (aux->sig != NULL)
            printf("%d, ", aux->info);
        else 
            printf("%d", aux->info);
    printf("]\n");
}

/* Muestra la lista en consola al estilo linked list */
void mostrar_lista_link(TipoLista lista)
{
    struct Nodo *aux;

    printf("-->");
    for (aux = lista; aux != NULL; aux = aux->sig)
        printf("[%d]-->", aux->info);
    printf("|\n");
}

/* Retorna la union de la copia de dos listas */
TipoLista concatenar_listas(TipoLista a, TipoLista b)
{   
    TipoLista c = NULL;
    struct Nodo *aux, *nuevo, *anterior = NULL;

    for (aux = a; aux != NULL; aux = aux->sig) { 
        nuevo = malloc(sizeof(struct Nodo));
        nuevo->info = aux->info;
        if (anterior != NULL)
            anterior->sig = nuevo;
        else 
            c = nuevo;
        anterior = nuevo;
    } 

    for (aux = b; aux != NULL; aux = aux->sig) { 
        nuevo = malloc(sizeof(struct Nodo));
        nuevo->info = aux->info;
        if (anterior != NULL)
            anterior->sig = nuevo;
        else 
            c = nuevo;
        anterior = nuevo;
    } 

    if (anterior != NULL)
        anterior->sig = NULL;
    return c;
}

/*******************************************************************************
* Busqueda y Borrado
* ------------------
* Conjunto de funciones destinada a la busqueda selectiva de elementos de una
* lista simplemente enlazada.                     
********************************************************************************/

/* 
 * Borra un elemento al final de la lista. Presenta dos casos especiales.
 * Si la lista esta vacia, retorna la misma lista.
 * Si la lista tiene un solo elemento, lo borra y hace a la lista valer null.
 */
TipoLista borrar_cola(TipoLista lista)
{
    struct Nodo *aux, *atras;

    if (lista != NULL) {
        for (atras = NULL, aux = lista; aux->sig != NULL; atras = aux, aux = aux->sig);
        free(aux);
        if (atras == NULL)
            lista = NULL;
        else 
            atras->sig = NULL;
    }
    return lista;
}

/* Elimina un elemento al inicio de la lista */
TipoLista borrar_cabeza(TipoLista lista)
{
    struct Nodo *aux;

    if (lista != NULL) { 
        aux = lista->sig;
        free(lista);
        lista = aux;
    }
    return lista;
}

/* Determina si un elemento pertenece o no a la lista */
int pertenece(TipoLista lista, int valor)
{
    struct Nodo *aux;

    for (aux = lista; aux != NULL; aux = aux->sig)
        if (aux->info == valor)
            return 1;
    return 0;
}

/* Elimina la primera ocurrencia de un valor en la lista */
TipoLista borrar_primera_ocurrencia(TipoLista lista, int valor)
{
    struct Nodo *aux, *atras;

    for (atras = NULL, aux = lista; aux != NULL; atras = aux, aux = aux->sig)
        if (aux->info == valor) {
            if (atras = NULL)
                lista = aux->sig;
            else 
                atras->sig = aux->sig;
            free(aux);
            return lista;
        }
    return lista;
}

/* Borra todas las ocurrencias de un valor determinado */
TipoLista borrar_valor(TipoLista lista, int valor)
{
    struct Nodo *aux, *atras;

    atras = NULL;
    aux = lista;
    while (aux != NULL) {
        if (aux->info == valor) {
            if (atras == NULL)
                lista = aux->sig;
            else 
                atras->sig = aux->sig;
            free(aux);
            if (atras == NULL)
                aux = lista;
            else
                aux = atras->sig;
        }
        else {
            atras = aux;
            aux = atras->sig;
        }

    }
    return lista;
}

/* Borrado completo de la lista */
TipoLista libera_lista(TipoLista lista)
{
    struct Nodo *aux, *otroaux;

    aux = lista;
    while(aux != NULL) {
        otroaux = aux->sig;
        free(aux);
        aux = otroaux;
    }
    return NULL;
}

/*******************************************************************************
* Insercion y Ordenacion
* ----------------------
* Conjunto de funciones destinada a la insercion de elementos en una lista con
* enlace simple asi como su ordenacion.
********************************************************************************/

/* Inserta un nuevo elemento al inicio de la lista */
TipoLista insertar_por_cabeza(TipoLista lista, int valor)
{
    struct Nodo *nuevo = malloc(sizeof(struct Nodo));

    nuevo->info = valor;
    nuevo->sig = lista;
    lista = nuevo;
    return lista;
}

/* Inserta un nuevo elemento al final de la lista */
TipoLista insertar_por_cola(TipoLista lista, int valor)
{
    struct Nodo *aux, *nuevo;

    nuevo = malloc(sizeof(struct Nodo));
    nuevo->info = valor;
    nuevo->sig = NULL;

    if (lista == NULL) 
        lista = nuevo;
    else {
        for (aux = lista; aux->sig != NULL; aux = aux->sig);
        aux->sig = nuevo;
    }
    return lista;
}

/* Inserta un elemento en una posicion dada */
TipoLista inserta_en_posicion(TipoLista lista, int pos, int valor)
{
    struct Nodo *aux, *atras, *nuevo;
    int i, lon;

    lon = longitud_lista(lista);
    nuevo = malloc(sizeof(struct Nodo));
    nuevo->info = valor;

    if (pos < lon) {
        for (i = 0, atras = NULL, aux = lista; i < pos && aux != NULL; i++, 
                                              atras = aux, aux = aux->sig);
        nuevo->sig = aux;
        if (atras == NULL)
            lista = nuevo;
        else 
            atras->sig = nuevo;
    }
    return lista;
}

/* Inserta valores en una lista en orden ascendente */
TipoLista insercion_asc(TipoLista lista, int valor)
{
    struct Nodo *aux, *atras, *nuevo;

    nuevo = malloc(sizeof(struct Nodo));
    nuevo->info = valor;

    for (atras = NULL, aux = lista; aux != NULL; atras = aux, aux = aux->sig)
        if (valor < aux->info) {
            /* Insertar nodo entre atras y aux */
            nuevo->sig = aux;
            if (atras == NULL)
                lista = nuevo;
            else 
                atras->sig = nuevo;
            return lista;
        }
    /* Si va al final de la lista */
    nuevo->sig = NULL;
    if(atras == NULL)
        lista = nuevo;
    else 
        atras->sig = nuevo;
    return lista;
}

/* Inserta valores en una lista en orden descendente */
TipoLista insercion_desc(TipoLista lista, int valor)
{
    struct Nodo *aux, *atras, *nuevo;

    nuevo = malloc(sizeof(struct Nodo));
    nuevo->info = valor;

    for (atras = NULL, aux = lista; aux != NULL; atras = aux, aux = aux->sig)
        if (valor > aux->info) {
            /* Insertar nodo entre atras y aux */
            nuevo->sig = aux;
            if (atras == NULL)
                lista = nuevo;
            else 
                atras->sig = nuevo;
            return lista;
        }
    /* Si va al final de la lista */
    nuevo->sig = NULL;
    if(atras == NULL)
        lista = nuevo;
    else 
        atras->sig = nuevo;
    return lista;
}

/* Devuelve la copia invertida de una lista */
TipoLista invertir_lsita(TipoLista lista)
{   
    TipoLista reverse = NULL;
    struct Nodo *aux;
    
    for (aux = lista; aux != NULL; aux = aux->sig)
        reverse = insertar_por_cabeza(reverse, aux->info);
    return reverse;
}

/* 
 * Inserta un nuevo valor si y solo si el valor no esta en la lista.
 * La variable orden indica la forma de insercion.
 * Orden == 1 ==> insercion ascendente.
 * Orden == 0 ==> insercion por cola.
 * Orden == -1 ==> insercion descendente.
 */
TipoLista insertar_dif(TipoLista lista, int valor, char orden)
{
    if (!pertenece(lista, valor)) {
        if (orden == 1)
            lista = insercion_asc(lista, valor);
        else if (orden == 0)
            lista = insertar_por_cola(lista, valor);
        else if (orden == -1)
            lista = insercion_desc(lista, valor);
    }
    return lista;
}

/* Ordena una lista mediante el metodo de la burbuja */
TipoLista sort_lista(TipoLista lista)
{
    struct Nodo *aux, *atras;
    int i, j, lon, tmp;

    lon = longitud_lista(lista) - 1;
    if (lon > 0) 
        for (i = 0; i < lon; i++)
            for (j = 0, atras = lista, aux = lista->sig; j < lon - i && aux 
                != NULL; j++, atras = aux, aux = aux->sig) {
                if (atras->info > aux->info) {   
                    tmp = atras->info;
                    atras->info = aux->info;
                    aux->info = tmp;
                }
            }
    return lista;
}

/* Determina si una lista esta ordenada en orden ascendente */
int esta_ordenada(TipoLista lista)
{   
    struct Nodo *aux, *atras;
    int lon, ordenada = 1;

    lon = longitud_lista(lista);
    if (lon > 1)
        for (atras = lista, aux = lista->sig; aux != NULL; atras = aux, aux = aux->sig)
            if (atras->info > aux->info) {
                ordenada = 0;
                break;
            }
    return ordenada;
}

/*
+==============================================================================+
|                               PROGRAMA PRINCIPAL                             |
+==============================================================================+*/

int main(void)
{
    /*  --------------------  Declaracion de vartiables  -------------------  */
    TipoLista lista, invertida;
    int i, num;

    /* Test */
    system("cls");
    lista = lista_vacia();

   srand(time(0));
    for (i = 0; i < 40; i++) {
        num = rand()% (99-10+1) + 10;
        lista = insertar_por_cola(lista, num);
    }

    lista =  sort_lista(lista);
    invertida = invertir_lsita(lista);

    mostrar_lista(lista);
    mostrar_lista(invertida);
    lista = libera_lista(lista);
    mostrar_lista(lista);

    printf("La longitud de la lista es: %d\n", longitud_lista(lista));
    printf("El maximo elemento de la lista es: %d\n", max_lista(lista));
    printf("El minimo elemento de la lista es: %d\n", min_lista(lista));
    printf("La media de la lista es: %1.2f\n", media_lista(lista));
    if (esta_ordenada(lista))
        printf("Esta ordenada");
    else 
        printf("No esta ordenada");

    return 0;
}
