#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbol.h"

int main()
{
    tArbol arbol;
    arbol_inicializar(&arbol);
    printf("EL ARCHIVO ORIGINALMENTE CONTIENE: \n");
    archivo_mostrar(PATH_BIN);
    arbol_cargar_desde_archivo(&arbol, PATH_BIN, sizeof(t_verduleria), archivo_leer_desde_binario);

    t_verduleria verdu;

    verdu.id = 9;

    arbol_borrar_elemento(&arbol, &verdu, sizeof(t_verduleria), comparacion_verduras);

    printf("EL ARBOL QUEDO TAL QUE: \n");
    arbol_mostrar(&arbol, 0, mostrar_verdura);
    return 0;
}
