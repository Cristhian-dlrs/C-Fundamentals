/*
 * AUTOR: Christian de la Rosa
 * 
 * PROPOSITO: Simula una agenda con opciones de edicion
 * 
 * DESCRIPTCION: La aplicacion ha sido programada sin funciones 
 * a la espera de la futura implementacion de las mismas.
 * 
 * /

/********************************************************************************************************************************
* Librerias
*********************************************************************************************************************************/

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>


/********************************************************************************************************************************
* Definicion de Constantes
*********************************************************************************************************************************/

#define MAXPER 100
#define MAXNUM 20
#define NAMES 50


/********************************************************************************************************************************
* Definicion de estructuras y tipos
**********************************************************************************************************************************/

enum {AgregarContacto = 1, ListarContactos, BuscarContactos,
      EditarContacto, EliminarContacto, Salir};

typedef struct {
    // Guarda nombre y telefonos de un contacto
    char nombre[NAMES+1];
    int telefono[MAXNUM+1];
    int cells;
} TipoPersona;

typedef struct {
    // Guarda hasta 100 contactos
    TipoPersona persona[MAXPER+1];
    int cantidad;
} TipoAgenda;


/********************************************************************************************************************************
* Programa principal
*********************************************************************************************************************************/

int main(void) 
{
    /* Declaracion de variables */
    TipoAgenda agenda;
    int exist, opcion, smenu, index, numeros, lonl;
    int contador, i, j, k, aux;
    char linea[NAMES+1], num[MAXNUM+1], ch; // Para evitar los problemas de scanf

    /* Inicializamos contadores */
    agenda.cantidad = 0;
    for (i = 0; i < MAXPER+1; i++)
        agenda.persona[i].cells = 0;

    /* Main loop */
    do {
        opcion = 0;

        /* Menu principal */
        do { 
            system("cls");
            printf("+-----------------------+\n");
            printf("|  AGENDA DE CONTACTOS  |\n");
            printf("+-----------------------+\n");
            printf("\n");
            printf("1) Agregar Contacto\n");
            printf("2) Listar Contactos\n");
            printf("3) Buscar Contactos\n");
            printf("4) Editar Contacto\n");
            printf("5) Eliminar Contacto\n");
            printf("6) Salir\n");
            printf("\nElija una opcion: ");
            gets(linea); sscanf(linea, "%d", &opcion);
        } while (opcion < 1 || opcion > 6);

        /* Bloque de opciones */
        switch (opcion) {

            case AgregarContacto: 
                system("cls");
                printf("+------------------------+\n");
                printf("|    AGREGAR CONTACTO    |\n");
                printf("+------------------------+\n");
                printf("\n");
                if (agenda.cantidad == MAXPER)
                    printf("La agenda esta llena, debe borrar un contacto para seguir añadiendo\n");
                else {
                    printf("Nombre: "); gets(agenda.persona[agenda.cantidad].nombre);
                    printf("Telefono: ");gets(linea);
                    sscanf(linea, "%d", &agenda.persona[agenda.cantidad].telefono[0]);
                    agenda.persona[agenda.cantidad].cells ++;
                }

                // Retorno
                agenda.cantidad++;
                printf("Contacto agregado con exito!\n");
                printf("Presione culaquier tecal para continuar: "); scanf("%f", ch);
                break;
        
            case ListarContactos:
                system("cls");
                printf("+------------------------+\n");
                printf("|   LISTA DE CONTACTOS   |\n");
                printf("+------------------------+\n");
                printf("\n");
                for (i = 0; i < agenda.cantidad; i++){
                    printf("Nombre: %s\n", agenda.persona[i].nombre);
                    for (j = 0; j < agenda.persona[i].cells; j++)
                        printf("Telefono %d: %d\n", (j+1), agenda.persona[i].telefono[j]);
                    printf("\n");
                }

                // Retorno
                printf("Presione culaquier tecla para volver al menu anterior: "); scanf("%f", ch);
                break;

            case BuscarContactos: 
                system("cls");
                printf("+-----------------------+\n");
                printf("|    BUSCAR CONTACTO    |\n");
                printf("+-----------------------+\n");
                printf("\n");
                printf("Buscar: "); gets(linea);
                printf("Contactos encontrados:\n");
                printf("\n");

                lonl = strlen(linea);
                              
                // Buscamos la cadena dentro de los nombres de contactos
                contador = 0;
                for (i = 0; i < agenda.cantidad; i++){
                    aux = 0;
                    for (j = 0; j < lonl; j++){
                        if(linea [j] == agenda.persona[i].nombre[j])
                           aux++;
                        else  
                            break;
                    }

                    if (aux == lonl){
                        contador++;
                        printf("Nombre: %s\n", agenda.persona[i].nombre);
                        for (k = 0; k < agenda.persona[i].cells; k++)
                            printf("Telefono %d: %d\n", (k+1), agenda.persona[i].telefono[k]);
                        printf("\n");
                    }
                } 
                if (contador == 0)
                    printf("No se han encontrado coincidencias");

                // Retorno
                printf("Presione culaquier tecla para volver al menu anterior: "); scanf("%f", ch);
                break;
                    
            case EditarContacto: 
                do{
                    smenu = 0;

                    // Submenu de edicion
                    do {
                        system("cls");
                        printf("+----------------------------+\n");
                        printf("| MNU DE EDICION DE CONTACTO |\n");
                        printf("+----------------------------+\n");
                        printf("\n");
                        printf("1) Cambiar nombre\n");
                        printf("2) Eliminar telefono\n");
                        printf("3) Agregar telefono\n");
                        printf("4) Regresar a menu anterior\n");
                        gets(linea); sscanf(linea, "%d", &smenu);
                    } while (smenu < 1 || smenu > 4);

                // Switch de submenu de edicuion
                    switch (smenu) {
                        case 1: // Cambiar nombre 

                            system("cls");
                            printf("+-----------------------+\n");
                            printf("|     EDITAR NOMBRE     |\n");
                            printf("+-----------------------+\n");
                            printf("\n");               
                            printf("Ingrese el nombre del contacto que desea editar: "); gets(linea);

                            // Comprobamos si el cliente existe
                            exist = 0;
                            for (i = 0; i < agenda.cantidad; i++)
                                if (strcmp(linea, agenda.persona[i].nombre) == 0){
                                    exist = 1;
                                    index = i;
                                    break;
                                }

                            // No hay contacto 
                            if (exist != 1) 
                            printf("No hay contactos con ese nombre\n");

                            // Editamos el nombre si existe el contacto
                            else if (exist == 1){
                                printf("Ingrese el nuevo nombre: "); gets(linea);
                                strcpy(agenda.persona[index].nombre, linea);
                            }

                            // Retorno
                            printf("Nombre cambiado con exito!\n");
                            printf("Presione culaquier tecal para continuar: "); scanf("%f", ch);
                            break;

                        case 2: // Eliminar telefono

                            system("cls");
                            printf("+-----------------------+\n");
                            printf("|   ELIMINAR TELEFONO   |\n");
                            printf("+-----------------------+\n");
                            printf("\n");
                            printf("Ingrese el nombre del contacto que desea editar: "); gets(linea);

                            // Comprobamos si el cliente existe
                            exist = 0;
                            for (i = 0; i < agenda.cantidad; i++)
                                if (strcmp(linea, agenda.persona[i].nombre) == 0){
                                    exist = 1;
                                    index = i;
                                    break;
                                }

                            // No hay contacto 
                            if (exist != 1) 
                                printf("No hay contactos con ese nombre\n");

                            // Eliminamos el telefono
                            if (exist == 1){
                                printf("\n");
                                printf("%s\n", agenda.persona[index].nombre);
                                for (k = 0; k < agenda.persona[index].cells; k++)
                                    printf("Telefono %d: %d\n", (k+1), agenda.persona[index].telefono[k]);                               
                                printf("\n");
                                printf("Ingrese el telefono que desea eliminar: "); gets(num);
                                sscanf(num, "%d", numeros);
                                for(i = 0; i < agenda.persona[index].cells; i++){
                                    if (numeros == agenda.persona[index].telefono[i]) {
                                        contador ++;  
                                        for( j = i; j < MAXNUM; j++)
                                            agenda.persona[index].telefono[j] = agenda.persona[index].telefono[j+1];
                                        printf("Numero eliminado con exito!\n");                                         
                                    }
                                    break;
                                }
                            }
                            if (contador == 0)
                                printf("El numero '%d' no pertenece al contanco '%f'\n", numeros, linea);
                            else 
                                agenda.persona[index].cells--;

                            // Retorno
                            printf("Presione culaquier tecal para continuar: "); scanf("%f", ch);
                            break; 

                        case 3: // Agregar telefono

                            system("cls");
                            printf("+----------------------+\n");
                            printf("|   AGREGAR TELEFONO   |\n");
                            printf("+----------------------+\n");
                            printf("\n");
                            printf("Ingrese el nombre del contacto que desea editar: "); gets(linea);

                            // Comprobamos si el cliente existe
                            exist = 0;
                            for (i = 0; i < agenda.cantidad; i++)
                                if (strcmp(linea, agenda.persona[i].nombre) == 0){
                                    exist = 1;
                                    index = i;
                                    break;
                                }

                            // No hay contacto 
                            if (exist != 1) 
                                printf("No hay contactos con ese nombre\n");

                            // Eliminamos el telefono
                            if (exist == 1){
                                printf("\n");
                                printf("%s\n", agenda.persona[index].nombre);
                                for (k = 0; k < agenda.persona[index].cells; k++)
                                    printf("Telefono %d: %d\n", (k+1), agenda.persona[index].telefono[k]);                               
                                printf("\n");
                                printf("Ingrese el telefono que desea agregar: "); 
                                gets(num); sscanf(num, "%d", &agenda.persona[index].telefono[agenda.persona[index].cells]);
                                agenda.persona[index].cells++;
                                printf("Numero agregado con exito!\n");
                            }
                            else if (contador == 0)
                                printf("El numero '%d' no pertenece al contanco '%f'\n", numeros, linea);

                            // Retorno
                            printf("Presione culaquier tecal para continuar: "); scanf("%f", ch);
                            break; 

                        case 4:
                            break;
                    } // end switch smenu

                } while( smenu != 4); // end do wile editar

                break;

            case EliminarContacto:
                system("cls");
                printf("+-----------------------+\n");
                printf("|   ELIMINAR CONTACTO   |\n");
                printf("+-----------------------+\n");
                printf("\n");
                printf("Ingrese el nombre del contacto que desea eliminar: "); gets(linea);

                // Comprobamos si el cliente existe
                exist = 0;
                for (i = 0; i < agenda.cantidad; i++)
                    if (strcmp(linea, agenda.persona[i].nombre) == 0){
                        exist = 1;
                        index = i;
                        break;
                    }

                // No hay contacto 
                if (exist != 1) 
                        printf("No hay contactos con ese nombre\n");

                // Eliminamos el contacto y telefonos
                else if (exist == 1 && agenda.cantidad != 1) {
                    for (i = index; i < agenda.cantidad-1; i ++){
                        strcpy(agenda.persona[i].nombre, agenda.persona[i+1].nombre);
                        for (j = 0; j < MAXNUM+1; j++)
                            agenda.persona[i].telefono[j] = agenda.persona[i+1].telefono[j]; 
                    }
                    agenda.cantidad--;         
                    printf("Contacto '%s' eliminado con exito\n", linea);  
                }
                else if ( exist == 1 && agenda.cantidad == 1) {
                    agenda.persona[0].nombre[0] = '\0';
                    for (i = 0; i < MAXNUM+1; i++)
                         agenda.persona[0].telefono[i] = 0;
                    printf("Contacto '%s' eliminado con exito\n", linea);
                    agenda.cantidad--;
                }

                // Retorno
                printf("Presione culaquier tecal para continuar: "); scanf("%f", ch);
                break;
        } //end switch main menu

    } while (opcion != 6); // end do while principal

    return 0;
}
