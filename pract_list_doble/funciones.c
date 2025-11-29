#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"


void lista_doble_crear(tListaDoble* pLis)
{
    *pLis = NULL;
}


int lista_doble_insertar_elemento_principio(tListaDoble* pLis, void* pd, size_t tam)
{
    tNodo* nue = (tNodo*)malloc(sizeof(tNodo)+tam);
    if(!nue)
    {
        printf("ERROR AL INTENTAR GUARDAR UN DATO");
        return ERROR;
    }

    nue->tamInfo = tam;
    nue->nAnt = NULL;
    nue->info = nue + 1;
    memcpy(nue->info, pd, tam);


    nue->nSig = *pLis;
    nue->nAnt = NULL;

   if (*pLis) ///SI ESTÁ VACIO SE SALTEA EL IF
   {
        (*pLis)->nAnt = nue;
   }
    *pLis = nue;

    return TODO_OK;
}


int lista_cargar_desde_archivo(tListaDoble* pLis, const char* pathArchivo, size_t tamElem)
{
    FILE* fp;
    fp = fopen(pathArchivo, "rb");
    if(!fp)
    {
        printf("ERROR AL PROCESAR ARCHIVO BINARIO");
        return ERROR;
    }

    void* buffer = malloc(tamElem);
    while(fread(buffer, tamElem, 1, fp))
    {
        lista_doble_insertar_elemento_principio(pLis, buffer, tamElem);
    }



    fclose(fp);
    return TODO_OK;

}


void lista_mostrar_contenido(const tListaDoble* pLis)
{
    if(!*pLis)
    {
        printf("LISTA VACIA");
        return;
    }
    tNodo* aux = *pLis;

    while(aux)
    {
        printf("%d\t", *(int*)(aux->info));
        aux = aux->nSig;
    }

}



void lista_ordenar_lista_doble(tListaDoble* pLis, int(*cmp)(const void*,const void*))
{
    if(!*pLis || !((*pLis)->nSig))
    {
        printf("LA LISTA ESTA VACIA O TIENE UN SOLO ELEMENTO");
        return;
    }

    tNodo* inicio = *pLis;
    while(inicio != NULL)
    {
        tNodo* minNodo = inicio;
        tNodo* actual = inicio->nSig;

        while(actual != NULL)
        {
            if (cmp(actual->info, minNodo->info) < 0) {
                minNodo = actual;
            }
            actual = actual->nSig;
        }

        // Si el nodo mínimo no es el nodo de 'inicio', intercambiamos
        if (minNodo != inicio) {
            void* temp = inicio->info;
            size_t tempTam = inicio->tamInfo;

            inicio->info = minNodo->info;
            inicio->tamInfo = minNodo->tamInfo;

            minNodo->info = temp;
            minNodo->tamInfo = tempTam;
        }

        inicio = inicio->nSig;
    }

}

int cmp_ints(const void* a, const void* b)
{
    int ia = *(const int*)a;
    int ib = *(const int*)b;

    if (ia < ib)
        return -1;
    if (ia > ib)
        return 1;
    return 0;
}


int poner_ord_lista(tListaDoble* pl, const void* pd, size_t tam, int (*cmp)(const void*, const void*))
{
    tNodo* act = *pl;
    tNodo* ant = NULL;

    // Buscar posición de inserción
    while(act && cmp(pd, act->info) > 0)
    {
        ant = act;
        act = act->nSig;
    }

    // Verificar duplicado
    if(act && cmp(pd, act->info) == 0)
        return -1;

    // Crear nodo
    tNodo* nue = (tNodo*)malloc(sizeof(tNodo) + tam);
    if(!nue)
        return -2;

    nue->info = nue + 1;
    memcpy(nue->info, pd, tam);
    nue->tamInfo = tam;

    // Insertar enlaces
    nue->nAnt = ant;
    nue->nSig = act;

    if(ant)
        ant->nSig = nue;
    else
        *pl = nue;      // Inserta al inicio

    if(act)
        act->nAnt = nue;

    return 1;
}














