#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFSIZE 50

// Tipificación

struct Tarea
{
    short TareaID;
    char *descripcion;
    int duracion;
} typedef Tarea;

struct Nodo{
    Tarea tarea;
    struct Nodo* sigNodo;
} typedef Nodo;

typedef Nodo* Lista;

// -------------


// Funciones

void cargarTareas(Lista* listaTareas, short cantTareas);
void cargarTareaAlFinal(Lista *listaTareas, short ID);

Nodo* crearNodo(short ID);

void enlazarNodoAlFinal(Lista* listaTareas, Nodo* nuevoNodo);

void mostrarTareas(Lista listaTareas);
void mostrarTarea(Tarea tarea);

void consultarEstadoTareas(Lista* listaTareasPendientes, Lista* listaTareasRealizadas);
void consultarEstadoTareas2(Lista* listaTareasPendientes, Lista* listaTareasRealizadas);
// La nueva función consultarEstadoTareas2 está mejor modularizada y carga las tareas a cada lista en orden respectivo (no invertido).

Nodo* buscarPorID(Lista listaTareas, int ID);
Nodo* buscarPorPalabra(Lista listaTareas, char* palabra);

Lista liberarMemoria(Lista tareas);

// ------------
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
    // Tras cargar las tareas, se las muestra


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
    // Prueba de las funciones de búsqueda.

    consultarEstadoTareas2(&tareasPendientes,&tareasRealizadas);
    // Consultamos al usuario si cada tarea fue realizada o no.

    printf("A continuacion se presenta\ninformacion de las tareas pendientes:\n");
    mostrarTareas(tareasPendientes);
    printf("A continuacion se presenta\ninformacion de las tareas realizadas:\n");
    mostrarTareas(tareasRealizadas);


    tareasRealizadas = liberarMemoria(tareasRealizadas);
    tareasPendientes = liberarMemoria(tareasPendientes);
    // Liberación de memoria

    mostrarTareas(tareasRealizadas);
    mostrarTareas(tareasPendientes);
    // Control para verificar que las listas quedaron vacías.

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
        cargarTareaAlFinal(listaTareas,i+1);
        printf("=======================================\n");

    }
    
} 

Nodo* crearNodo(short ID){

    int duracionTarea;

    Nodo* nuevoNodo = (Nodo*) malloc(sizeof(Nodo));

    printf("Ingrese la descripcion de la tarea %d: \n",ID);

    char* buffer = (char*) malloc(BUFFSIZE);
    // Buffer para pedir la descripción de la tarea
    gets(buffer);

    do
    {
        printf("Ingrese la duracion de la tarea, entre 10 y 100: \n");
        scanf("%hd", &duracionTarea);
        fflush(stdin);

    } while (duracionTarea < 10 || duracionTarea > 100);

    nuevoNodo->sigNodo = NULL;
    // Inicializo por defecto el puntero del nuevo nodo en NULL

    (nuevoNodo->tarea).descripcion = (char*) malloc(strlen(buffer)+1);
    strcpy((nuevoNodo->tarea).descripcion,buffer);

    (nuevoNodo->tarea).duracion = duracionTarea;
    (nuevoNodo->tarea).TareaID = ID;

    free(buffer);

    return nuevoNodo;

}

void enlazarNodoAlFinal(Lista* listaTareas, Nodo* nuevoNodo){
    if(*listaTareas != NULL){

        // Si la lista no esta vacia,
        Lista headAux = *listaTareas;
        // uso un head auxiliar para llegar al último nodo de la lista y no mover el head de la lista

        while(headAux->sigNodo != NULL){
            headAux = headAux->sigNodo;
        }

        headAux->sigNodo = nuevoNodo;
        // Ahora el último nodo apunta a el nuevo nodo creado, que ya está inicializado con su puntero en NULL.

    } else {
        // Si la lista esta vacia, cargo el nuevo nodo directamente.

        *listaTareas = nuevoNodo;
        // Notar que el nuevo nodo ya viene inicializado con su puntero en NULL, por lo que no hago la asignación
        // nuevoNodo = *listaTareas

        // Además, en este caso la lista está vacía, no hace falta tener en cuenta el enlazamiento de otros nodos.
    }
}

void cargarTareaAlFinal(Lista* listaTareas, short ID){

    Nodo* nuevoNodo = crearNodo(ID);

    enlazarNodoAlFinal(listaTareas,nuevoNodo);

}

void mostrarTareas(Lista listaTareas){

    if (listaTareas == NULL){
        printf("La lista no tiene tareas cargadas! \n");
    } else {

        while(listaTareas != NULL){
            mostrarTarea(listaTareas->tarea);
            listaTareas = listaTareas->sigNodo;
        }
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

Nodo* quitarNodo(Lista* listaTareas){

    Nodo* aux = NULL;

    if(*listaTareas != NULL){
        aux = *listaTareas;
        *listaTareas = (*listaTareas)->sigNodo;
        aux->sigNodo = NULL;
        // Para poder agregar el nodo a otra lista de ser necesario, modifico su puntero a NULL
    }

    return aux;
}

void consultarEstadoTareas2(Lista* listaTareasPendientes, Lista* listaTareasRealizadas){

    Lista listaTareasPendientesAux = NULL;
    short realizada;

    printf("Ahora analicemos cada tarea: \n");

    while(*listaTareasPendientes != NULL){

        mostrarTarea((*listaTareasPendientes)->tarea);

        do
        {
            printf("Fue realizada? 1: si, 0; no\n");
            scanf("%hd", &realizada);

        } while (realizada != 0 && realizada != 1);

        if(realizada == 1){
            enlazarNodoAlFinal(listaTareasRealizadas,quitarNodo(listaTareasPendientes));
        } else {
            enlazarNodoAlFinal(&listaTareasPendientesAux,quitarNodo(listaTareasPendientes));
        }
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