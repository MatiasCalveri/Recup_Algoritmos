#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cola.h"

int main()
{
    tCola cola;
    tCola cola2;
    ///archivo_leer(PATH_NUM);
    cola_crear(&cola);
    cola_crear(&cola2);
    cola_cargar_desde_archivo(&cola, PATH_NUM, sizeof(int));

    while(!cola_vacia(&cola))
    {
        int buffer;
        cola_ver_primero(&cola, &buffer);

        if((buffer%2 == 0))
        {
            cola_eliminar_elemento(&cola);
        }else
        {
            cola_poner_elemento(&cola2, &buffer, sizeof(buffer));
            cola_eliminar_elemento(&cola);
        }
    }

    printf("LA COLA 2 ME QUEDARIA TAL QUE: \n");
    cola_mostrar(&cola2);
    return 0;
}
