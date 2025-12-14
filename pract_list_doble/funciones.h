#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#define TODO_OK 1
#define ERROR 0

#define PATH_NUM "vNumeros.dat"

typedef struct sNodo
{
    void* info;
    struct sNodo* nSig;
    struct sNodo* nAnt;
    size_t tamInfo;
}tNodo;

typedef tNodo* tListaDoble;


void lista_doble_crear(tListaDoble* pLis);
int lista_doble_insertar_elemento_principio(tListaDoble* pLis, void* pd, size_t tam);
int lista_cargar_desde_archivo(tListaDoble* pLis, const char* pathArchivo, size_t tamElem);
void lista_mostrar_contenido(const tListaDoble* pLis);
void lista_ordenar_lista_doble(tListaDoble* pLis, int(*cmp)(const void*,const void*));
int cmp_ints(const void* a, const void* b);
int poner_ord_lista(tListaDoble* pl, const void* pd, size_t tam, int (*cmp)(const void*, const void*));


void ordenarD(tListaDoble* pLis, int (*comparar)(const void *, const void *));

#endif // FUNCIONES_H_INCLUDED
