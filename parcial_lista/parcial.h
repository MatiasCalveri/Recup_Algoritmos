#ifndef PARCIAL_H_INCLUDED
#define PARCIAL_H_INCLUDED



#define TODO_OK 1
#define ERROR 0
#define PATH_ALUS  "ArchivoAlumons.dat"

///DEFINICION DE LA PARTE DE ALUMNOS

/*
Y la siguiente estructura de t_materia:
• cod_materia: entero sin signo de 4 digitos
• cod_cursada: cadena de 6 caracteres (ej*/

typedef struct
{
    unsigned cod_materia;
    char cod_cursada[7];
    unsigned nota_final;
}t_materia;

/*
Y la siguiente estructura de t_materias:
• materias: Array de 50 t_materias
• cant_materias: entero sin signo
*/

typedef struct
{
    t_materia materia[50];
    unsigned cant_materias;
}t_materias;


/*Ejercicio 1:
Dada la siguiente estructura t_alumno:
• dni: Entero sin signo
• apellido: cadena de 20 caracteres
• nombres: cadena de 20 caracteres
• cod_carrera: cadena 3 caracteres (INF, ELE, IND, MED, ABO)
• materias: t_materias*/

typedef struct
{
    unsigned dni;
    char apellido[21];
    char nombres[21];
    char cod_carrera[4];
    t_materias materias;
}t_alumno;


///DEFINICION DE LA LISTA

typedef struct sNodo
{
    void* info;
    struct sNodo* nSig;
    size_t tamInfo;
}tNodo;

typedef tNodo* tLista;


///FUNCIONES TDA_LISTA
void lista_crear(tLista* pLis);
int lista_llenar_elementos(tLista* pLis, const char* pathArch, size_t tamElem);
int lista_insertar_elemento(tLista* pLis, FILE* fp, size_t tamElem, int(*leer)(void**,void*, size_t));
void lista_mostrar(const tLista* pLis, void (*mostrarElem)(const void*));
void lista_ordenar(tLista* pLis, int(*cmp)(const void*, const void *));

///FUNCIONES PARA CREAR LOTE DE PRUEBA;

void archivo_crear_alumnos(const char* pathAlum);
void archivo_mostrar_alumnos(const char* pathAlum);
void mostrar_alumno(const void* elem);
int leer_desde_archivo(void** dst ,void* fp, size_t tam);
int comparar_alumnos(const void* a, const void* b);
#endif // PARCIAL_H_INCLUDED
