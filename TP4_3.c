#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFSIZE 50

struct Tarea
{
    int TareaID;
    char *descripcion;
    int duracion;
} typedef Tarea;

struct Nodo{
    Tarea tarea;
    struct Nodo* sigNodo;
} typedef Nodo;

typedef Nodo* Lista;

void cargarTareas(Lista* listaTareas, short cantTareas);
Lista cargarTarea(Lista listaTareas, short ID);
void mostrarTareas(Lista listaTareas);
void mostrarTarea(Tarea tarea);
void consultarEstadoTareas(Lista* listaTareasPendientes, Lista* listaTareasRealizadas);
Nodo* buscarPorID(Lista listaTareas, int ID);
Nodo* buscarPorPalabra(Lista listaTareas, char* palabra);
Lista liberarMemoria(Lista tareas);

int main(){

    Lista tareasPendientes = NULL;
    Lista tareasRealizadas = NULL;
    // Inicializo las cabeceras de lista en NULL.

    short cantTareas;   

    printf("=======================================\n");

    do
    {
        printf("Indique la cantidad de tareas a cargar:");
        scanf("%hd", &cantTareas);
        fflush(stdin);
    } while (cantTareas <= 0);

    printf("=======================================\n");


    cargarTareas(&tareasPendientes,cantTareas);

    printf("A continuacion se presenta\ninformacion de las tareas cargadas:\n");
    mostrarTareas(tareasPendientes);

    printf("=======================================\n");

    printf("La tarea con el ID 2 es:\n");
    if(buscarPorID(tareasPendientes,2)){
        mostrarTarea(buscarPorID(tareasPendientes,2)->tarea);
    } else {
        printf("No se encontro la tarea\n");
    }

    printf("=======================================\n");

    printf("La tarea con la palabra 'comprar' es:\n");

    if(buscarPorPalabra(tareasPendientes,"comprar")){
        mostrarTarea(buscarPorPalabra(tareasPendientes,"comprar")->tarea);
    } else {
        printf("No se encontro la tarea\n");
    }

    printf("=======================================\n");


    consultarEstadoTareas(&tareasPendientes,&tareasRealizadas);

    printf("A continuacion se presenta\ninformacion de las tareas pendientes:\n");
    mostrarTareas(tareasPendientes);
    printf("A continuacion se presenta\ninformacion de las tareas realizadas:\n");
    mostrarTareas(tareasRealizadas);

    tareasRealizadas = liberarMemoria(tareasRealizadas);
    tareasPendientes = liberarMemoria(tareasPendientes);
    
    return 0;

}

Lista liberarMemoria(Lista tareas){
    Nodo* auxLiberarMemoria = NULL;
    while(tareas){
        free((tareas->tarea).descripcion);
        auxLiberarMemoria = tareas;
        tareas = tareas->sigNodo;
        free(auxLiberarMemoria);
    }
    return tareas;
}

void cargarTareas(Lista* listaTareas, short cantTareas){

    for (short i = 0; i < cantTareas; i++)
    {
        *listaTareas = cargarTarea(*listaTareas,i+1);
        printf("=======================================\n");

    }
    
} 

Lista cargarTarea(Lista listaTareas, short ID){

    short duracionTarea;
    char* buffer = (char*) malloc(BUFFSIZE);

    printf("Ingrese la descripcion de la tarea %d:\n",ID);
    gets(buffer);
    
    do
    {
        printf("Ingrese la duracion de la tarea, entre 10 y 100: \n");
        scanf("%hd", &duracionTarea);
        fflush(stdin);

    } while (duracionTarea < 10 || duracionTarea > 100);


    if(listaTareas != NULL){

        // Si la lista no esta vacia,
        Lista headAux = listaTareas;
        // uso un head auxiliar para llegar al último nodo de la lista y no mover el head de la lista

        while(headAux->sigNodo != NULL){
            headAux = headAux->sigNodo;
        }

        headAux->sigNodo = (Lista) malloc(sizeof(Nodo));
        // Reservo memoria para un nuevo nodo que se conectará al último de la lista

        headAux->sigNodo->tarea.duracion = duracionTarea;
        headAux->sigNodo->tarea.TareaID = ID;
        headAux->sigNodo->tarea.descripcion = (char*)malloc(strlen(buffer)+1);
        strcpy(headAux->sigNodo->tarea.descripcion,buffer);
        // Guardo datos

        headAux->sigNodo->sigNodo = NULL;
        // El nuevo nodo creado apuntará a NULL.

        return listaTareas;
        // Esto no es necesario, pero la función retorna Lista.
    

    } else {
        // Si la lista esta vacia, cargo el nuevo nodo directamente.

        listaTareas = (Lista) malloc(sizeof(Nodo));

        listaTareas->tarea.TareaID = ID;
        listaTareas->tarea.duracion = duracionTarea;
        listaTareas->tarea.descripcion = (char*)malloc(strlen(buffer)+1);
        strcpy(listaTareas->tarea.descripcion,buffer);
        // Se cargan los datos

        listaTareas->sigNodo = NULL;

        return listaTareas;

    }

    free(buffer);

}

void mostrarTareas(Lista listaTareas){

    while(listaTareas != NULL){

        mostrarTarea(listaTareas->tarea);
        listaTareas = listaTareas->sigNodo;

    }
}

void mostrarTarea(Tarea tarea){

    printf("=======================================\n");
    printf("Informacion de la tarea %d\n",tarea.TareaID);
    printf("-> Descripcion:");
    puts(tarea.descripcion);
    printf("-> Duracion: %d\n",tarea.duracion);

}

void consultarEstadoTareas(Lista* listaTareasPendientes, Lista* listaTareasRealizadas){

    short realizada;
    Lista listaTareasPendientesAux = NULL;
    Nodo* puntProxNodoAux = NULL;

    printf("- Ahora analicemos cada tarea:\n");

    while(*listaTareasPendientes != NULL){

        puntProxNodoAux = (*listaTareasPendientes)->sigNodo;

        mostrarTarea((*listaTareasPendientes)->tarea);

        do
        {
            printf("Fue realizada? 1: si, 0; no\n");
            scanf("%hd", &realizada);

        } while (realizada != 0 && realizada != 1);
    
        if(realizada == 1){
            (*listaTareasPendientes)->sigNodo = *listaTareasRealizadas;
            // El puntero del nodo a agregar a la lista de tareas realizadas apuntará al último nodo agregado a dicha lista.
            *listaTareasRealizadas = *listaTareasPendientes;
            // La cabecera de la lista de tareas realizadas apunta al nodo recién agregado a la lista.
        } else {
            (*listaTareasPendientes)->sigNodo = listaTareasPendientesAux;
            // El puntero del nodo a agregar a la lista de tareas pendientes (auxiliar) apuntará al último nodo agregado a dicha lista.
            listaTareasPendientesAux = *listaTareasPendientes;
            // El puntero del nodo a agregar a la lista de tareas pendientes (auxiliar) apuntará al último nodo agregado a dicha lista.
        }
        // Se usa una lista auxiliar para tareas pendientes a fin de evitar tener que revincular nodos de la lista de tareas pendientes y considerar distintos casos donde el nodo que puede ser pasado a la lista de tareas realizadas esté o al principio, o en el medio, o al final de la lista de tareas pendientes original.

        *listaTareasPendientes = puntProxNodoAux;

    }

    *listaTareasPendientes = listaTareasPendientesAux;

}


Nodo* buscarPorID(Lista listaTareas, int ID){

    while(listaTareas!=NULL){

        if((listaTareas->tarea).TareaID == ID){
            return listaTareas;
        }

        listaTareas = listaTareas->sigNodo;
    }


}

Nodo* buscarPorPalabra(Lista listaTareas, char* palabra){
    while(listaTareas!=NULL){

        if(strstr((listaTareas->tarea).descripcion,palabra)){
            return listaTareas;
        }
        listaTareas = listaTareas->sigNodo;
    }
}   