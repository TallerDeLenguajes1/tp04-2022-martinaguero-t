#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFSIZE 100

struct Tarea
{
    int TareaID;
    char *descripcion;
    int duracion;
} typedef Tarea;

void cargarTareas(Tarea **listaTareas, short cantTareas);
void mostrarTarea(Tarea tarea);
void consultarTareasRealizadas(Tarea **listaTareas, Tarea **listaTareasRealizadas, short cantTareas);
void mostrarEstadoTareas(Tarea **tareasPendientes, Tarea **tareasRealizadas, short cantTareas);
Tarea* buscarTareaPorPalabra(Tarea **tareas, short cantTareas, char *palabraBuscada);
Tarea* buscarTareaPorID(Tarea **tareas, short cantTareas, int IDbuscado);
void LiberarMemoria(Tarea** listadoTareas, short cantTareas);

int main()
{

    short cantTareas;
    Tarea **listaTareas;

    printf("=======================================\n");
    do
    {
        printf("Indique la cantidad de tareas a cargar:");
        scanf("%hd", &cantTareas);
        fflush(stdin);
    } while (cantTareas <= 0);
    printf("=======================================\n");

    listaTareas = (Tarea **)malloc(sizeof(Tarea *) * cantTareas);
    // Generacion del arreglo con un puntero doble de manera dinámica

    cargarTareas(listaTareas, cantTareas);

    printf("=======================================\n");

    printf("Busco la tarea que contenga la palabra \'Java\' en su descripcion:\n");

    if(buscarTareaPorPalabra(listaTareas,cantTareas,"Java")!= NULL){

        printf("Se encontro la tarea, es\n");
        mostrarTarea(*buscarTareaPorPalabra(listaTareas,cantTareas,"Java"));

    } else {

        printf("No se encontro la tarea.\n");

    }

    printf("=======================================\n");

    printf("Se busca la tarea con ID 5:\n");
    
    if(buscarTareaPorID(listaTareas,cantTareas,5)!=NULL){

        mostrarTarea(*buscarTareaPorID(listaTareas,cantTareas,5));

    } else {

        printf("No se encontro la tarea.\n");

    }

    printf("=======================================\n");

    Tarea **listaTareasRealizadas;
    listaTareasRealizadas = (Tarea **)malloc(sizeof(Tarea *) * cantTareas);
    // Se genera el arreglo de punteros donde se guardarán las tareas realizadas.

    for (short i = 0; i < cantTareas; i++)
    {
        listaTareasRealizadas[i] = NULL;
    }
    // Precargo en NULL el arreglo de punteros para guardar las tareas realizadas

    consultarTareasRealizadas(listaTareas, listaTareasRealizadas, cantTareas);

    mostrarEstadoTareas(listaTareas, listaTareasRealizadas, cantTareas);

    LiberarMemoria(listaTareas,cantTareas);
    LiberarMemoria(listaTareasRealizadas,cantTareas);

    return 0;
}

void cargarTareas(Tarea **listaTareas, short cantTareas)
{

    char *Buffer = (char *)malloc(BUFFSIZE * sizeof(char));

    for (short i = 0; i < cantTareas; i++)
    {

        printf("------------------------------------>");
        listaTareas[i] = (Tarea *)malloc(sizeof(Tarea) * 1);
        // Para cada puntero del arreglo reservo dinámicamente memoria para una tarea.

        listaTareas[i]->TareaID = i + 1;

        printf("\nIngrese la descripcion de la tarea %d:\n", i + 1);
        gets(Buffer);
        fflush(stdin);

        listaTareas[i]->descripcion = (char *)malloc(strlen(Buffer) + 1);

        strcpy(listaTareas[i]->descripcion, Buffer);

        do
        {

            printf("Ingrese la duracion de la tarea, entre 10 y 100: \n");
            scanf("%d", &(listaTareas[i]->duracion));
            fflush(stdin);

        } while (listaTareas[i]->duracion < 10 || listaTareas[i]->duracion > 100);
    }

    free(Buffer);
}

void mostrarTarea(Tarea tarea)
{

    printf("==> Informacion de la tarea %d\n", tarea.TareaID);
    printf("- ID: %d\n", tarea.TareaID);
    printf("- Descripcion:");
    puts(tarea.descripcion);
    printf("- Duracion: %d\n", tarea.duracion);
}

void consultarTareasRealizadas(Tarea **listaTareas, Tarea **listaTareasRealizadas, short cantTareas)
{

    printf("- Ahora analicemos cada tarea:\n");
    short realizada;
    short indiceTRealizadas = 0;

    for (int i = 0; i < cantTareas; i++)
    {
        mostrarTarea(*listaTareas[i]);

        do
        {
            printf("Fue realizada? 1: si, 0; no\n");
            scanf("%hd", &realizada);

        } while (realizada != 0 && realizada != 1);

        if (realizada == 1)
        {

            listaTareasRealizadas[indiceTRealizadas] = listaTareas[i];
            listaTareas[i] = NULL;
            indiceTRealizadas++;

            // Solo si se encontró una tarea realizada se carga el arreglo de tareas realizadas y se mueve el indice.

        }
    }
}

void mostrarEstadoTareas(Tarea **tareasPendientes, Tarea **tareasRealizadas, short cantTareas)
{

    printf("Se muestran las tareas sin realizar:\n");
    for (int i = 0; i < cantTareas; i++)
    {
        if (tareasPendientes[i] != NULL)
        {
            mostrarTarea(*tareasPendientes[i]);
        }
    }

    printf("Se muestran las tareas realizadas:\n");
    int j = 0;

    while (j < cantTareas && tareasRealizadas[j] != NULL)
    {
        mostrarTarea(*tareasRealizadas[j]);
        j++;
    }
}

Tarea* buscarTareaPorPalabra(Tarea **tareas, short cantTareas, char *palabraBuscada)
{
    for (int i = 0; i < cantTareas; i++)
    {
        if (strstr(tareas[i]->descripcion,palabraBuscada) != NULL)
        {
            return tareas[i];
        }

    }

    return NULL;

}

Tarea* buscarTareaPorID(Tarea **tareas, short cantTareas, int IDbuscado)
{
    for (int i = 0; i < cantTareas; i++)
    {
        if (tareas[i]->TareaID == IDbuscado)
        {
            return tareas[i];
        }

    }
    
    return NULL;
    
}

void LiberarMemoria(Tarea** listadoTareas, short cantTareas){

    for (short i = 0; i < cantTareas; i++)
    {
        if(listadoTareas[i] != NULL){ 
            
            free(listadoTareas[i]->descripcion);
            free(listadoTareas[i]);
        }
        // Se libera la memoria usada para guardar la descripcion de la tarea

        // Se libera la memoria reservada para cada struct Tarea

    }

    free(listadoTareas);
    // Se libera la memoria para el puntero doble.
    
}

