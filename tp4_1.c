#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



struct Tarea{
        int TareaID;//Numérico autoincremental comenzando en 1000
        char *Descripcion; //
        int Duracion; // entre 10 – 100
}typedef Tarea;

struct Nodo{
    Tarea T;
    struct Nodo *Siguiente;
}typedef Nodo;

Nodo *crearListaVacia();
Nodo *crearNodo(int Duracion, char *Descripcion, int *TareaID);
void insertarNodo(Nodo **tareasPendientes, Nodo *nNodo);
Nodo *buscarT(Nodo *TareasPendientes, int tareaBuscar);
void SacarTPendiente(Nodo **TareasPendientes, int TareadID);
void listarTareasP(Nodo *TareasPendientes);
void listarTareasR(Nodo *TareasRealizadas);
void consultarTarea(Nodo *TareaP, Nodo *TareaR, int id, char * palabra);


int main()
{
    srand(time(NULL));
    char *Descripcion, * palabraClave = NULL;
    int duracion, tareaID = 1000;
    int opcion, tareaBuscar, id = NULL;
    Nodo * TareasPendientes = crearListaVacia();
    Nodo * TareasRealizadas = crearListaVacia();

    do
    {
        printf("---1 Para cargar tareas pendientes---\n");
        printf("---2 Para para pasar de tarea pendiente a realizada---\n");
        printf("---3 Listar tareas pendientes y realizadas---\n");
        printf("---4 Consultar Tarea---\n");
        printf("---5 SALIR---\n");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            duracion = rand() % 100 + 10;
            printf("Ingrese la Descripcion de la Tarea\n");
            Descripcion = (char*) malloc(sizeof(char)* 50);
            fflush(stdin);
            scanf("%s", Descripcion);
            insertarNodo(&TareasPendientes, crearNodo(duracion, Descripcion, &tareaID));
            printf("TAREA AGREGADA\n");
            break;
        
        case 2:
            printf("Ingrese el ID de la tarea a buscar\n");
            scanf("%d", &tareaBuscar);
            Nodo * tareaCambiar = buscarT(TareasPendientes,tareaBuscar);
            if (tareaCambiar != NULL)
            {
                insertarNodo(&TareasRealizadas, tareaCambiar);
                SacarTPendiente(&TareasPendientes, tareaCambiar->T.TareaID);
                printf("TAREA MARCADA COMO REALIZADA\n");
            }else{
                printf("TAREA NO ENCONTRADA");
            }
            break;

        case 3:
            listarTareasP(TareasPendientes);
            listarTareasR(TareasRealizadas);
            break;
        case 4:
            printf("Ingrese el ID de la tarea:");
            scanf("%d", &id);
            printf("Ingrese palabra Clave:");
            palabraClave = (char*)malloc(sizeof(char) * 50);
            fflush(stdin);
            scanf("%s", palabraClave);
            consultarTarea(TareasPendientes,TareasRealizadas, id, palabraClave);
            
        default:
            break;
        }
    } while (opcion != 5);
    
        
    
    
    return 0; 
}

Nodo *crearListaVacia()
{
    return NULL;
}

Nodo *crearNodo(int Duracion, char *Descripcion, int * TareaID)
{
    Nodo *nNodo = (Nodo*) malloc(sizeof(Nodo));
    nNodo->T.TareaID = *TareaID;
    (*TareaID)++;
    nNodo->T.Duracion = Duracion;
    nNodo->T.Descripcion = (char*) malloc(sizeof(char) * strlen(Descripcion) + 1);
    strcpy(nNodo->T.Descripcion, Descripcion);
    nNodo->Siguiente = NULL;
    return nNodo;
}

void insertarNodo(Nodo **tareasPendientes, Nodo *nNodo){
    nNodo->Siguiente = *tareasPendientes;
    *tareasPendientes = nNodo;
}

Nodo *buscarT(Nodo *TareasPendientes, int tareaBuscar)
{
    Nodo *Aux = TareasPendientes;
    while (Aux&&Aux->T.TareaID != tareaBuscar)
    {
        Aux = Aux->Siguiente;
    }
    return Aux;
}

void SacarTPendiente(Nodo **TareasPendientes, int TareadID)
{
    Nodo ** aux = TareasPendientes;

    while (*aux != NULL && (*aux)->T.TareaID != TareadID)
    {
        aux = &(*aux)->Siguiente;
    }
    
    if (*aux)
    {
        Nodo * temporal = *aux;
        *aux = (*aux)->Siguiente;
        free(temporal);
    }
    
}

void listarTareasP(Nodo *TareasPendientes)
{
    Nodo *Aux = TareasPendientes;

    while (Aux)
    {
        printf("---TAREAS PENDIENTES---");
        printf("\n---TAREA NUMERO %d---", Aux->T.TareaID);
        printf("\n---DESCRIPCION: %s---", Aux->T.Descripcion);
        printf("\n---DURACION: %d---", Aux->T.Duracion);
        Aux = Aux->Siguiente;
    }
}

void listarTareasR(Nodo *TareasRealizadas)
{
    Nodo *Aux = TareasRealizadas;
   
    while (Aux)
    {
        printf("---TAREAS REALIZADAS---");
        printf("\n---TAREA NUMERO %d---", Aux->T.TareaID);
        printf("\n---DESCRIPCION: %s---", Aux->T.Descripcion);
        printf("\n---DURACION: %d---", Aux->T.Duracion);
        Aux = Aux->Siguiente;
    }
}

void consultarTarea(Nodo *TareaP, Nodo *TareaR, int id, char * palabra)
{
    Nodo * AuxP = TareaP;
    Nodo * AuxR = TareaR;

    while (AuxP != NULL && AuxP->T.TareaID != id || AuxP->T.Descripcion != palabra)
    {
        AuxP = AuxP->Siguiente;
    }
    if (AuxP)
    {
        printf("---LA TAREA PERTENECE A LA LISTA DE PENDIENTES---");
        printf("\n---TAREA NUMERO %d---", AuxP->T.TareaID);
        printf("\n---DESCRIPCION: %s---", AuxP->T.Descripcion);
        printf("\n---DURACION: %d---", AuxP->T.Duracion);
    }
    
    while (AuxR && AuxR->T.TareaID != id || AuxR->T.Descripcion != palabra)
    {
        AuxR = AuxP->Siguiente;
    }
    if (AuxR)
    {
        printf("---LA TAREA PERTENECE A LA LISTA DE PENDIENTES---");
        printf("\n---TAREA NUMERO %d---", AuxR->T.TareaID);
        printf("\n---DESCRIPCION: %s---", AuxR->T.Descripcion);
        printf("\n---DURACION: %d---", AuxR->T.Duracion);
    }
}
