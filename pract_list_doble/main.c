#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"


int main()
{
    tListaDoble listaDoble;
    lista_doble_crear(&listaDoble);

    lista_cargar_desde_archivo(&listaDoble, PATH_NUM, sizeof(int));
    lista_ordenar_lista_doble(&listaDoble, cmp_ints);
    int num = 5;
    poner_ord_lista(&listaDoble, &num, sizeof(int), cmp_ints);
    lista_mostrar_contenido(&listaDoble);

    return 0;
}
