#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED

#define TODO_OK 1
#define ERROR 0

#define PATH_NUM "vNumeros.dat"


typedef struct sNodo
{
    void* info;
    struct sNodo* nSig;
    size_t tamInfo;
}tNodo;

typedef struct
{
    tNodo* pri;
    tNodo* ult;
}tCola;


///FUNCIONES DEL TDA_COLA
void cola_crear(tCola* pCol);
int cola_poner_elemento(tCola* pCol, void* pd, size_t tamElem);
int cola_cargar_desde_archivo(tCola* pCol, const char* pathArch, size_t tam);
int cola_ver_primero(tCola* pCol, void* pd);
int cola_eliminar_elemento(tCola* pCol);
int cola_vacia(const tCola* pCol);
void cola_mostrar(const tCola* pCol);

///FUNCIONES QUE NO SON TDA
int archivo_leer(void* pathArchivo);


#endif // COLA_H_INCLUDED
