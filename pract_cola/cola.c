#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cola.h"



///FUNCIONES DEL TDA

void cola_crear(tCola* pCol)
{
    pCol->pri = NULL;
    pCol->ult = NULL;
}


int cola_poner_elemento(tCola* pCol, void* pd, size_t tamElem)
{
    tNodo* nue = (tNodo*)malloc(sizeof(tNodo)+tamElem);
    if(!nue)
    {
        printf("ERROR AL RESERVAR MEMORIA");
        return ERROR;
    }

    nue->info = nue + 1;
    memcpy(nue->info, pd, tamElem);
    nue->tamInfo = tamElem;
    nue->nSig = NULL;


    if(pCol->ult)
    {
         pCol->ult->nSig = nue;
    }else
    {
        pCol->pri = nue;
    }

    pCol->ult = nue;

    return TODO_OK;
}

int cola_cargar_desde_archivo(tCola* pCol, const char* pathArch, size_t tam)
{
    FILE* fp = fopen(pathArch, "rb");
    if(!fp)
    {
        printf("ERROR AL LEER ARCHIVO BINARIO");
        return ERROR;
    }

    void* buffer = malloc(tam);
    if(!buffer)
        return ERROR;

    while(fread(buffer, tam, 1, fp) == 1)
    {
        cola_poner_elemento(pCol, buffer, tam);
    }

    free(buffer);
    fclose(fp);

    return TODO_OK;
}

int cola_ver_primero(tCola* pCol, void* pd)
{
    if(!pCol->pri)
    {
        return ERROR;
    }

    memcpy(pd, pCol->pri->info, pCol->pri->tamInfo);

    return TODO_OK;
}

int cola_eliminar_elemento(tCola* pCol)
{
    if(!pCol->pri)
    {
        printf("LA COLA ESTÁ VACIA");
        return ERROR;
    }

    tNodo* elim = pCol->pri;
    pCol->pri = elim->nSig;

    free(elim);

    if(pCol->pri == NULL)
        pCol->ult = NULL;

    return TODO_OK;
}

int cola_vacia(const tCola* pCol)
{
    return pCol->pri == NULL;
}

void cola_mostrar(const tCola* pCol)
{
    tNodo* act = pCol->pri;   // puntero para recorrer

    while(act)
    {
        printf("%d\t", *(int*)act->info);
        act = act->nSig;
    }
}

///FUNCIONES QUE NO SON DEL TDA


int archivo_leer(void* pathArchivo)
{
    FILE* fp = fopen(pathArchivo, "rb");
    if(!fp)
    {
        printf("ERROR AL LEER ARCHIVO BINARIO");
        return ERROR;
    }
    int buffer;
    while(fread(&buffer, sizeof(buffer), 1, fp))
    {
        printf("%d\t", buffer);
    }


    fclose(fp);
    return TODO_OK;
}
