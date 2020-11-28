/******************************************************************************
 * Autor: Cristhian de la Rosa
 * ---------------------------
 * 
 * Nombre: DBCancionesV2.c
 * ---------------------
 *
 * Objetivo:
 * ---------
 * Crea una aplicacion que gestiona una base de datos de discos compactos con 
 * persistencia de datos.
 *
 * Descripcion:
 * ------------ 
 * Cada disco compacto contendrá un título, un intérprete, un año de edición y 
 * una lista de canciones. De cada canción nos interesará únicamente el título.
 * 
 * El menu tendra las siguientes opciones:
 *      1. Añadir un disco.
 *      2. Buscar discos por título.
 *      3. Buscar discos por intérprete.
 *      4. Buscar discos por título de canción.
 *      5. Mostrar el contenido completo de la colección.
 *      6. Eliminar un disco de la base de datos dados su título y 
 *         el nombre del intérprete.
 *      7. Finalizar   
 ******************************************************************************/

/*
+==============================================================================+
|                                  LIBRERIAS                                   |
+==============================================================================+*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/*******************************************************************************
* CONSTANTES Y TIPOS ENUMERADOS
* -----------------------------
* MAXCAD ==> Longitud de la cadena auxiliar para el titulo del disco, nombre, 
             interprete, etc...   
* ENUM ==> Enumera las opciones del menu;                     
********************************************************************************/
#define MAXCAD 100

enum { Agregar = 1, BuscarPorTituloDisco, BuscarPorInterprete, 
      BuscarPorTituloCancion, Mostrar, EliminarDisco, EliminarTodo, Salir };


/*
+==============================================================================+
|                               DATA STRUCTURES                                |
+==============================================================================+*/

/*******************************************************************************
* Struct Cancion 
* ==============     
* Implementa una lista simplemente enlazada con punteros a cabeza y cola para 
* almacenar canciones, asi como una serie de funciones para su gestion.   
* 
* Struct TipoListaC 
* =================
* Representa un puntero a cabeza y cola de una lista de nodos tipo Cancion.
*
* Funciones
* ---------
* + newSongList() ==> Crea una lista de canciones vacia.
* + addSong() ==> Inserta una cancion en la lista (por cola).
* + printSongList() ==> Mostrar la lista de canciones por pantalla.
* + existSong() ==> Retorna 1 o 0 dependiendo de si la cancion esta en la lista.
* + delSongList() ==> Elimina todas las canciones de la lista.               
********************************************************************************/
typedef struct Nodo {
    char *titulo;
    struct Nodo *sig;
} Cancion;

typedef struct ListaCC {
    struct Nodo *cabeza;
    struct Nodo *cola;
} TipoListaC;

//---------------------------------FUNCIONES-----------------------------------//

TipoListaC newSongList(void)
{
    TipoListaC newList;

    newList.cabeza = newList.cola = NULL;
    return newList;
}

TipoListaC addSong(TipoListaC lista, char titulo[])
{
    Cancion *nuevo = malloc(sizeof(Cancion));

    nuevo->titulo = malloc((strlen(titulo)+1) * sizeof(char));
    strcpy(nuevo->titulo, titulo);
    nuevo->sig = NULL;

    if (lista.cola != NULL) { 
        lista.cola->sig = nuevo;
    } else {
        lista.cabeza = nuevo;
    }
    lista.cola = nuevo;
    return lista;
}

void printSongList(TipoListaC lista)
{
    Cancion *aux;

    for (aux = lista.cabeza; aux != NULL; aux = aux->sig)
        printf("    %s\n", aux->titulo);
}

int existSong(TipoListaC lista, char titulo[])
{
    Cancion *aux;

    for (aux = lista.cabeza; aux != NULL; aux = aux->sig)
        if (strcmp(aux->titulo, titulo) == 0)
            return 1;
    return 0;
}

TipoListaC delSongList(TipoListaC lista)
{
    Cancion *aux, *siguiente;

    aux = lista.cabeza;
    while (aux != NULL) {
        siguiente = aux->sig;
        free(aux->titulo);
        free(aux);
        aux = siguiente;
    }
    lista.cabeza = NULL;
    lista.cabeza = NULL;
    return lista;
}


/*******************************************************************************
* Struct Disco 
* ============   
* Implementa una lista simplemente enlazada para almacenar discos, asi como una 
* serie de funciones para su gestion.   
* 
* Struct TipoListaD 
* =================
* Representa un puntero lista de nodos tipo Disco.
*
* Funciones
* ---------
* + newDsicList() ==> Crea una lista de discos vacia.
* + addDisc() ==> Inserta un disco en la lista (por cabeza).
* + delDiscList() ==> Elimina todos los discos de la lista.
* + printDic() ==> Muestra el contenido de un disco.
* + printDsicgList() ==> Mostrar la lista de discos por pantalla.
* + getDiscByTitle () ==> Busca el disco por titulo y lo imprme.
* + getDiscByInterp() ==> Busca el disco por interprete y lo imprime. 
* + getDiscBySong() ==> Busca un disco por cancion.
* + delDiscByTitleAndInterp() ==> Borra el disco dados titulo e interprete.              
********************************************************************************/
typedef struct Disco {
    char *titulo;
    char *interpete;
    int year;
    TipoListaC canciones;
    struct Disco *sig;
} Disco;

typedef struct Disco *TipoListaD;

TipoListaD newDiscList(void)
{
    return NULL;
}

TipoListaD addDisc(TipoListaD lista, char titulo[], char interprete [], int year,
                    TipoListaC canciones)
{
    Disco *disco = malloc(sizeof(Disco));

    disco->titulo = malloc((strlen(titulo)+1)* sizeof(char));
    strcpy(disco->titulo, titulo);

    disco->interpete = malloc((strlen(interprete)+1) * sizeof(char));
    strcpy(disco->interpete, interprete);

    disco->year = year;
    disco->canciones = canciones;
    disco->sig = lista;
    lista =  disco;
    return lista;
} 

TipoListaD delDiscList(TipoListaD lista)
{
    Disco *aux, *siguiente;

    aux = lista;
    while (aux != NULL) { 
        siguiente = aux->sig;
        free(aux->titulo);
        free(aux->interpete);
        aux->canciones = delSongList(aux->canciones);
        free(aux);
        aux = siguiente;
    }
    return NULL;
}

void printDisc(Disco eldisco)
{
    printf("Titulo: %s\n", eldisco.titulo);
    printf("Interprete: %s\n", eldisco.interpete);
    printf("Fecha de lanzamiento: %d\n", eldisco.year);
    printf("Canciones:\n");
    printSongList(eldisco.canciones);
}

void printDiscList(TipoListaD lista)
{
    Disco *aux;

    for (aux = lista; aux != NULL; aux = aux->sig) { 
        printDisc(*aux);
        printf("========================================\n");
    }
}

Disco* getDiscByTitle(TipoListaD lista, char titulo[])
{
    Disco *aux;

    for (aux = lista; aux != NULL; aux = aux->sig)
        if (strcmp(aux->titulo, titulo) == 0)
            return aux;
    return NULL;
}

Disco* getDiscByInterp(TipoListaD lista, char interprete[])
{
    Disco *aux;

    for (aux = lista; aux != NULL; aux = aux->sig)
        if (strcmp(aux->interpete, interprete) == 0)
            return aux;
    return NULL;
}

Disco* getDiscBySong(TipoListaD lista, char cancion[])
{
    Disco *aux;

    for (aux = lista; aux != NULL; aux = aux->sig)
        if (existSong(aux->canciones, cancion))
            return aux;
    return NULL;
}

TipoListaD delDiscByTitleAndInterp(TipoListaD lista, char titulo[],
                                   char interprete[])
{
    Disco *aux, *atras;

    for(atras = NULL, aux = lista; aux != NULL; atras = aux, aux = aux->sig)
        if(strcmp(aux->titulo, titulo) == 0 && strcmp(aux->interpete, interprete) == 0) 
        {
            if (atras == NULL)
                lista = aux->sig;
            else 
                atras->sig = aux->sig;
            free(aux->titulo);
            free(aux->interpete);
            aux->canciones = delSongList(aux->canciones);
            free(aux);
            printf("\nDisco borrado con exito!\n");
            return lista;
        }
    printf("\nNo existen discos de con titulo %s e interprete %s!\n", titulo, interprete);
    return lista;
}


/*******************************************************************************
* Persitencia de datos 
* ====================
* Conjunto de funciones que gestionan la peristencia de datos.
*
* Funciones
* ---------
* + removeEndLine () ==> Quita el salto de linea del final de linea.
* + loadData() ==> Carga los datos en memoria.
* + saveData() ==> Guarda los datos en la rom en un archivo de texto.
********************************************************************************/
void removeEndLine(char linea[])
{
    int i;

    for (i = 0; linea[i] != '\0'; i++)
        if (linea[i] == '\n') { 
            linea[i] = '\0';
            break;
        }
}

TipoListaD loadData(char fileName[])
{   
    FILE *f;
    int opcion, year, songNumber, i;
    TipoListaD coleccion;
    char tituloDisco[MAXCAD+1], tituloCancion[MAXCAD+1], interprete[MAXCAD+1];
    char linea[MAXCAD+1];
    TipoListaC listaCanciones;

    coleccion = newDiscList();
    f = fopen(fileName, "r");
    while (1) { 
        fgets(tituloDisco, MAXCAD, f);
        if (feof(f))
            break;

        removeEndLine(tituloDisco);
        fgets(interprete, MAXCAD, f);
        removeEndLine(interprete);
        fgets(linea, MAXCAD, f); sscanf(linea, "%d", &year);
        fgets(linea, MAXCAD, f); sscanf(linea, "%d", &songNumber);

        listaCanciones = newSongList();
        for (i = 0; i < songNumber; i++) { 
            fgets(tituloCancion, MAXCAD, f);
            removeEndLine(tituloCancion);
            listaCanciones = addSong(listaCanciones, tituloCancion);
        }
        coleccion = addDisc(coleccion, tituloDisco, interprete, year, listaCanciones);
    }
    fclose(f);
    return coleccion;
}

void saveData(TipoListaD coleccion, char fileName[])
{
    Disco *disco;
    TipoListaC cancion;
    Cancion *aux;
    int songNumber;
    FILE *f;

    f = fopen(fileName, "w");
    for (disco = coleccion; disco != NULL; disco = disco->sig) { 
        fprintf(f, "%s\n", disco->titulo);
        fprintf(f, "%s\n", disco->interpete);
        fprintf(f, "%d\n", disco->year);

        songNumber = 0;
        for (cancion = disco->canciones, aux = cancion.cabeza; aux != NULL; 
             aux = aux->sig)
            songNumber ++;
        fprintf(f, "%d\n", songNumber);

        for (cancion = disco->canciones, aux = cancion.cabeza; aux != NULL; 
             aux = aux->sig)
            fprintf(f, "%s\n", aux->titulo);
    }
    fclose(f);
}


/*
+==============================================================================+
|                               PROGRAMA PRINCIPAL                             |
+==============================================================================+*/

int main(void)
{
    /*  --------------------  Declaracion de vartiables  -------------------  */
    int opcion, year;
    TipoListaD coleccion;
    char tituloDisco[MAXCAD+1], tituloCancion[MAXCAD+1], interprete[MAXCAD+1];
    char linea[MAXCAD+1];
    Disco *undisco;
    TipoListaC listaCanciones;
    FILE *f;

    /*  -------------------- Inicializacion de variables -------------------  */
    coleccion = loadData("data.txt");

    do {

        /*  -------------------------  Main menu  -------------------------  */
        system("cls");
        printf("==================== MENU =====================\n");
        printf("\n[1]- Agregar disco\n");
        printf("[2]- Buscar por titulo del disco\n");
        printf("[3]- Buscar por interprete\n");
        printf("[4]- Buscar por titulo de cancion\n");
        printf("[5]- Mostrar todo\n");
        printf("[6]- Eliminar un disco por titulo e interprete\n");
        printf("[7]- Eliminar todo\n");
        printf("[8]- Salir\n");
        printf("\nOpcion: "); gets(linea); sscanf(linea, "%d", &opcion);

        switch (opcion) {
        
            case Agregar:
                system("cls");
                printf("=========== AGREGAR DISCO ===========\n");
                printf("\nTitulo: "); gets(tituloDisco);
                printf("Interprete: "); gets(interprete);
                printf("Fecha de Lanzamiento: "); 
                gets(linea); sscanf(linea, "%d", &year);

                listaCanciones = newSongList();
                printf("\n============= CANCIONES =============\n");
                printf("Pulse INTRO para acabar \n");
                do {
                    printf("Titulo de cancion: ");
                    gets(tituloCancion);
                    if (strlen(tituloCancion) > 0)
                        listaCanciones = addSong(listaCanciones, tituloCancion);
                } while (strlen(tituloCancion) > 0);
                coleccion = addDisc(coleccion, tituloDisco, interprete, 
                                     year, listaCanciones);
                printf("\nPresione enter para continuar: ");
                gets(linea);
                if (strlen(linea) == 0)
                    break;
            
            case BuscarPorTituloDisco:
                system("cls");
                printf("========= BUSCAR DISCO POR TITULO =======\n");
                printf("\nTitulo de disco: "); gets(tituloDisco);
                undisco = getDiscByTitle(coleccion, tituloDisco);
                printf("\n============== RESULTADOS ==============\n");

                if(undisco != NULL)
                    printDisc(*undisco);
                else 
                    printf("No hay discos con ese titulo");

                printf("\nPresione enter para continuar: ");
                gets(linea);
                if (strlen(linea) == 0)
                    break;

            case BuscarPorInterprete:
                system("cls");
                printf("======= BUSCAR DISCO POR INTERPRETE =====\n");
                printf("\nInterprete: "); gets(interprete);
                undisco = getDiscByInterp(coleccion, interprete);
                printf("\n============== RESULTADOS ==============\n");

                if(undisco != NULL)
                    printDisc(*undisco);
                else 
                    printf("No hay discos con de ese interprete");

                printf("\nPresione enter para continuar: ");
                gets(linea);
                if (strlen(linea) == 0)
                    break;

            case BuscarPorTituloCancion:
                system("cls");
                printf("======== BUSCAR DISCO POR CANCION ======\n");
                printf("\nNombre de la cancion: "); gets(tituloCancion);
                undisco = getDiscBySong(coleccion, tituloCancion);
                printf("\n============== RESULTADOS ==============\n");

                if(undisco != NULL)
                    printDisc(*undisco);
                else 
                    printf("La cancion no pertenece a ningun disco");

                printf("\nPresione enter para continuar: ");
                gets(linea);
                if (strlen(linea) == 0)
                    break;

            case Mostrar:
                system("cls");
                printf("========== COLECCION DE DISCOS =========\n");
                printDiscList(coleccion);

                printf("\nPresione enter para continuar: ");
                gets(linea);
                if (strlen(linea) == 0)
                    break;

            case EliminarDisco:
                system("cls");
                printf("============ ELIMINAR DISCO ============\n");
                printf("\nTitulo de disco: "); gets(tituloDisco);
                printf("Interprete: "); gets(interprete);
                coleccion = delDiscByTitleAndInterp(coleccion, tituloDisco, interprete);

                printf("\nPresione enter para continuar: ");
                gets(linea);
                if (strlen(linea) == 0)
                    break;
            case EliminarTodo:
                system("cls");
                printf("============= BORRAR TODO ==============\n");
                f = fopen("data.txt", "r");
                fclose(f);
                coleccion = delDiscList(coleccion);

                printf("\nSe han eliminado todos los datos...");
                printf("\nPresione enter para continuar: ");
                gets(linea);
                gets(linea);
                if (strlen(linea) == 0)
                    break;

            case Salir:
                break;
        }
    } while (opcion != Salir);

    saveData(coleccion, "data.txt");
    coleccion = delDiscList(coleccion);
    system("cls");
    printf("Ha salido de la aplicacion...\n");

    return 0;
}