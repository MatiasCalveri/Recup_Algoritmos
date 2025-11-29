#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#define TODO_OK 1
#define ERROR 0

#define PATH_BIN "verduleria.dat"

typedef struct
{
    int id;
    char verdura[50];
    float precio;
}t_verduleria;

typedef struct sNodo
{
    void* info;
    struct sNodo* der;
    struct sNodo* izq;
    size_t tamInfo;
}tNodo;

typedef tNodo* tArbol;

void arbol_inicializar(tArbol* pAr);
int arbol_cargar_desde_archivo(tArbol* pAr, const char* pathArchivo, size_t tamElem, int(*leer)(void** ,void* , unsigned, size_t));
int arbol_insertar_en_arbol(tArbol* pAr, FILE* fpArchivo, int li, int ls, size_t tamElem, int(*leer)(void** ,void* , unsigned, size_t));
int archivo_leer_desde_binario(void** dato, void* fp, unsigned pos, size_t tamElem);
void arbol_mostrar(const tArbol* pAr, int nivel, void(*mostrar)(void*));


int arbol_borrar_elemento(tArbol* pAr, void* pd, size_t tamElem, int(*cmp)(void* , void* ));
tNodo** arbol_buscar_nodo(const tArbol* pAr, void* pd, int(*cmp)(void* , void* ));

int arbol_altura(const tArbol* pAr);

tNodo** BuscarNodoMin( tArbol* pAr);
tNodo** BuscarNodoMax( tArbol* pAr);
int arbol_eliminar_nodo(tArbol* pAr);

void archivo_mostrar(const char* pathBin);
void mostrar_verdura(void* pd);
int comparacion_verduras(void* a, void* b);
#endif // ARBOL_H_INCLUDED
