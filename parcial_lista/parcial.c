#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parcial.h"


///FUNCIONES TDA_LISTA
void lista_crear(tLista* pLis)
{
    *pLis=NULL;
}

int lista_llenar_elementos(tLista* pLis, const char* pathArch, size_t tamElem)
{
    FILE* fp;
    fp = fopen(pathArch, "rb");
    if(!fp)
    {
        printf("ERROR AL ABRIR ARCHIVO");
        return ERROR;
    }

    ///poner
    lista_insertar_elemento(pLis, fp, tamElem, leer_desde_archivo);

    fclose(fp);
    return TODO_OK;
}


int lista_insertar_elemento(tLista* pLis, FILE* fp, size_t tamElem,
                            int(*leer)(void**, void*, size_t))
{
    int leidos = 1;

    while(leidos)
    {
        tNodo* nue = (tNodo*)malloc(sizeof(tNodo) + tamElem);
        if(!nue)
        {
            printf("ERROR AL INSERTAR ELEMENTO\n");
            return ERROR;
        }

        nue->info = nue + 1;

        leidos = leer(&(nue->info), fp, tamElem);

        if(leidos != 1)
        {
            free(nue);
            continue;   // SIN break — respetando tu consigna
        }

        nue->tamInfo = tamElem;
        nue->nSig = *pLis;
        *pLis = nue;
    }

    return TODO_OK;
}

int leer_desde_archivo(void** dst ,void* fp, size_t tam)
{
    return fread(*dst, tam, 1, (FILE*)fp);
}

void lista_mostrar(const tLista* pLis, void (*mostrarElem)(const void*))
{
    if(!*pLis)
    {
        printf("LA LISTA ESTÁ VACÍA :c\n");
        return;
    }

    while(*pLis)
    {
        mostrarElem((*pLis)->info);
        pLis = &(*pLis)->nSig;
    }
}


void lista_ordenar(tLista* pLis, int(*cmp)(const void*, const void *))
{

    if(!*pLis || !(*pLis)->nSig)
    {
        return;
    }
    ///SU FUNCION ES MANTENER SIEMPRE EL PRI DE LA LISTA, ASI EMPIEZA EL 2do WHILE  con "q"
    tLista* pri = pLis;
    while((*pLis)->nSig)
    {
        if(cmp((*pLis)->info, (*pLis)->nSig->info)<0)
        {
            tLista *q = pri;
            tNodo *aux = (*pLis)->nSig;

            (*pLis)->nSig = aux->nSig; ///Este es el desplazamiento para la primera condicion del while, muevo
                                       ///el tercer nodo, porque los dos anteriores ya los roté

            while(cmp((*q)->info, aux->info)>=0) ///compara para buscar donde hacer la insersion
                q = &(*q)->nSig;
            aux->nSig = *q;
            *q = aux;
        }else{
            pLis = &(*pLis)->nSig;
        }
    }
}

int comparar_alumnos(const void* a, const void* b)
{
    t_alumno* al1 = (t_alumno*)a;
    t_alumno* al2 = (t_alumno*)b;

    return al1->dni - al2->dni;
}







///FUNCIONES CREACION LOTE DE PRUEBA

void archivo_crear_alumnos(const char* pathAlum)
{
    FILE* fp;

    fp = fopen(pathAlum, "wb");
    if(!fp)
    {
        printf("ERROR AL CREAR ARCHIVO ALUMNO");
        return;
    }

    t_alumno vAlumno[] ={
        {   41673159, "Calveri", "Matias", "ING", {  {  {1234, "20242C",10}, {1235, "20242C",12}  },2  }   },
        {   85367823, "Perez", "Yopa", "FDS", {  {  {5475, "20242C",5}, {1235, "20242C",8}  },2  }   },
        {   91686152, "Gonzales", "Kanguro", "ASD", {  {  {5424, "20242C",4}, {1235, "20242C",7}  },2  }   },
        {   56784345, "Bokita", "Juniors", "WES", {  {  {1756, "20242C",7}, {1235, "20242C",4}, {1233, "20242C",20}   },3  }   }
        };

    fwrite(vAlumno, sizeof(vAlumno), 1, fp);

    fclose(fp);
}

void archivo_mostrar_alumnos(const char* pathAlum)
{
    FILE* fp = fopen(pathAlum, "rb");
    if(!fp)
    {
        printf("ERROR AL ABRIR EL ARCHIVO\n");
        return;
    }

    t_alumno alum;

    printf("=== LISTADO DE ALUMNOS ===\n");
    while(fread(&alum, sizeof(t_alumno), 1, fp) == 1)
    {
        printf("DNI: %u\n", alum.dni);
        printf("Apellido: %s\n", alum.apellido);
        printf("Nombres: %s\n", alum.nombres);
        printf("Carrera: %s\n", alum.cod_carrera);
        printf("Materias (%u):\n", alum.materias.cant_materias);

        for(unsigned i = 0; i < alum.materias.cant_materias; i++)
        {
            printf("  Cod Materia: %u\n", alum.materias.materia[i].cod_materia);
            printf("  Cod Cursada: %s\n", alum.materias.materia[i].cod_cursada);
            printf("  Nota Final: %u\n", alum.materias.materia[i].nota_final);
        }
        printf("\n");
    }

    fclose(fp);
}

void mostrar_alumno(const void* elem)
{
    const t_alumno* alum = (const t_alumno*)elem;

    printf("DNI: %u\n", alum->dni);
    printf("Apellido: %s\n", alum->apellido);
    printf("Nombres: %s\n", alum->nombres);
    printf("Carrera: %s\n", alum->cod_carrera);

    printf("Materias (%u):\n", alum->materias.cant_materias);

    for(unsigned i = 0; i < alum->materias.cant_materias; i++)
    {
        printf("  Cod Materia: %u\n", alum->materias.materia[i].cod_materia);
        printf("  Cursada: %s\n", alum->materias.materia[i].cod_cursada);
        printf("  Nota Final: %u\n",
               alum->materias.materia[i].nota_final);
    }

    printf("---------------------------\n");
}

void lista_invertir(tLista *p)
{
    tNodo *ant = NULL;
    tNodo *act = *p;
    tNodo *sig;

    while (act)
    {
        sig = act->nSig;   // guardo el siguiente
        act->nSig = ant;   // invierto el enlace
        ant = act;        // avanzo ant
        act = sig;        // avanzo act
    }

    *p = ant;  // actualizar el puntero al inicio
}
