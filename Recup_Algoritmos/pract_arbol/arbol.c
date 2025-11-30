#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbol.h"


void arbol_inicializar(tArbol* pAr)
{
    *pAr = NULL;
}


int arbol_cargar_desde_archivo(tArbol* pAr, const char* pathArchivo, size_t tamElem, int(*leer)(void** ,void* , unsigned, size_t))
{
    FILE* fpArchivo;
    fpArchivo = fopen(pathArchivo, "rb");
    if(!fpArchivo)
    {
        printf("ERROR AL ABRIR EL ARCHIVO BINARIO");
        return ERROR;
    }

    ///AVERIGUO EL TAMAÑO DEL ARCHIVO
    fseek(fpArchivo, 0, SEEK_END);
    int tamArchivo = ftell(fpArchivo) / tamElem;
    rewind(fpArchivo);

    ///PASO TODO A UNA FUNCION DE PONER ELEMENTOS
    arbol_insertar_en_arbol(pAr, fpArchivo, 0, tamArchivo-1, tamElem, leer);

    fclose(fpArchivo);
    return TODO_OK;
}

int arbol_insertar_en_arbol(tArbol* pAr, FILE* fpArchivo, int li, int ls, size_t tamElem, int(*leer)(void** ,void* , unsigned, size_t))
{
    int mitad = (li+ls)/2;
    int r;

    if(li>ls)
    {
        return TODO_OK;
    }

    ///PREPARO INICIALIZACION
    *pAr = (tNodo*)malloc(sizeof(tNodo)+tamElem);
    if(!*pAr)
    {
        printf("FALTA DE MEMORIA");
        return ERROR;
    }

    (*pAr)->info = *pAr + 1;

    ///VOY A BUSCAR EL REGISTRO
    if(!((*pAr)->tamInfo =  leer(&(*pAr)->info, fpArchivo, mitad, tamElem)))
    {
        printf("NO SE PUDO INSERTAR EN ARBOL");
        free(*pAr);
        return ERROR;
    }

    (*pAr)->der = (*pAr)->izq = NULL;

    if((r = arbol_insertar_en_arbol(&(*pAr)->izq, fpArchivo, li, mitad-1, tamElem, leer)) != TODO_OK)
        return r;

    arbol_insertar_en_arbol(&(*pAr)->der, fpArchivo, mitad+1, ls, tamElem, leer);

    return TODO_OK;
}

int archivo_leer_desde_binario(void** dato, void* fp, unsigned pos, size_t tamElem)
{
    *dato = malloc(tamElem);
    if(!*dato)
    {
        return ERROR;
    }

    fseek((FILE*)fp, tamElem * pos, SEEK_SET);

    return fread(*dato, tamElem, 1, (FILE*)fp);

}



void arbol_mostrar(const tArbol* pAr, int nivel, void(*mostrar)(void*))
{
    if(!*pAr)
        return;

    arbol_mostrar(&(*pAr)->der, nivel+1, mostrar);

    for(int i = 0; i<nivel; i++)
    {
        printf("    ");
    }
    mostrar((*pAr)->info);

    arbol_mostrar(&(*pAr)->izq, nivel+1, mostrar);

}


int arbol_borrar_elemento(tArbol* pAr, void* pd, size_t tamElem, int(*cmp)(void* , void* ))
{
    if(!(pAr = arbol_buscar_nodo(pAr, pd, cmp)))
    {
        printf("NODO NO ENCONTRADO");
        return ERROR;
    }

    arbol_eliminar_nodo(pAr);

    return TODO_OK;
}


int arbol_eliminar_nodo(tArbol* pAr)
{
    tNodo *elim, **remp;

    if(!(*pAr)->izq && !(*pAr)->der)
    {
        free(*pAr);
        *pAr = NULL;
        return TODO_OK;
    }


    remp = (arbol_altura(&(*pAr)->izq) > arbol_altura(&(*pAr)->der)) ?
    BuscarNodoMax(&(*pAr)->izq):
    BuscarNodoMin(&(*pAr)->der);


    elim = *pAr;
    *pAr = *remp;

    *remp = (*remp)->izq ? (*remp)->izq  : (*remp)->der;

    (*pAr)->izq = (elim)->izq;
    (*pAr)->der   = (elim)->der;

    free(elim);

    return TODO_OK;
}



tNodo** arbol_buscar_nodo(const tArbol* pAr, void* pd, int(*cmp)(void* , void* ))
{
    if(!*pAr)
    {
        printf("EL ARBOL ESTA VACIO");
        return ERROR;
    }

    int comparacion;

    while(*pAr && (comparacion = cmp((*pAr)->info, pd)))
    {
        if(comparacion>0)
            pAr = &(*pAr)->izq;
        else
            pAr = &(*pAr)->der;
    }

    if(!*pAr)
            printf("NO SE ENCUENTRA EL ELEMENTO");

    return (tNodo**)pAr;
}


int arbol_altura(const tArbol* pAr)
{
    if(!*pAr)
    {
        return ERROR;
    }

    int hi = arbol_altura(&(*pAr)->izq);
    int hd = arbol_altura(&(*pAr)->der);

    return (hi > hd ? hi : hd) +1;
}


tNodo** BuscarNodoMin( tArbol* pAr)
{
    while((*pAr)->izq)
        pAr = &(*pAr)->izq;
    return pAr;
}

tNodo** BuscarNodoMax( tArbol* pAr)
{
    while((*pAr)->der)
        pAr = &(*pAr)->der;
    return pAr;
}


int comparacion_verduras(void* a, void* b)
{
    t_verduleria* v1 = (t_verduleria*)a;
    t_verduleria* v2 = (t_verduleria*)b;

    return (v1->id - v2->id);

}


void mostrar_verdura(void* pd)
{
    t_verduleria* verdu = (t_verduleria*)pd;

    printf("%d\n", verdu->id);
}


void archivo_mostrar(const char* pathBin)
{
    FILE* fpBin;

    fpBin = fopen(pathBin, "rb");
    if(!fpBin)
    {
        printf("ERROR AL CARGAR ARCHIVO");
        return;
    }

    t_verduleria verdura;
    fseek(fpBin, 0L, SEEK_END);
    int cantRegistros = ftell(fpBin) / sizeof(t_verduleria);

    rewind(fpBin);
    for(int i = 0; i<cantRegistros; i++)
    {
        fread(&verdura, sizeof(t_verduleria), 1, fpBin);
        printf("%d\t%-15s\t\t%4.2f\n", verdura.id, verdura.verdura, verdura.precio);
    }

    fclose(fpBin);
}
