#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parcial.h"

int main()
{
    tLista lista;
    archivo_crear_alumnos(PATH_ALUS);

    lista_crear(&lista);
    lista_llenar_elementos(&lista, PATH_ALUS, sizeof(t_alumno));
    lista_ordenar(&lista, comparar_alumnos);
    lista_mostrar(&lista, mostrar_alumno);

    /*printf("Pos de memoria que contiene la lista es: %p\n", (void*)lista); ///DIRECCION DEL PRIMER NODO
    printf("Pos de memoria real de donde esta la lista es: %p\n", (void*)&lista);

    printf("Pos de memoria real de donde esta la &lista->info: %p\n", (void*)&lista->info);
    printf("Pos de memoria real de donde esta la &lista->nSig: %p\n", (void*)&lista->nSig);
    printf("Pos de memoria real de donde esta la &lista->tamInfo: %p\n", (void*)&lista->tamInfo);

    printf("\n\n\n\n");
    printf("Pos de memoria que contiene la lista->info: %p\n", (void*)lista->info);
    printf("Pos de memoria que contiene  la lista->nSig: %p\n", (void*)lista->nSig);
    printf("Pos de memoria que contiene la lista->tamInfo: %p\n", (void*)lista->tamInfo);
    printf("\n\n\n\n");

    printf("Pos de memoria que contiene la &(*lista)->info: %p\n",  (void*)&lista->info);

    mostrar_alumno((*lista).info);
    */

    ///archivo_mostrar_alumnos(PATH_ALUS);


    return 0;
}

/*
int main()
{

    tLista lista;
    lista_crear(&lista);
    printf("Pos de memoria de lista es: %p", (void*)lista);


    return 0;
}

*/

