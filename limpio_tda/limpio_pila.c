///PILA ESTÁTICA
///PILA ESTÁTICA

typedef struct
{
    char pila[TAM_PILA]; ///CANTIDAD DE BYTES RESERVADOS(?
    unsigned tope; ///PRRIMER LUGAR DONDE SE PUEDE INGRESAR EL PRIMER ELEMENTO
}PilaEstatica;

void pilaCrearEstatica(PilaEstatica* pp){

    pp->tope = TAM_PILA;

}

int pilaLlenaEstatica(PilaEstatica* pp, unsigned cantBytes)
{
    return pp->tope < cantBytes + sizeof(unsigned);
    /// cantBytes es el tamaño de struct y el sizeof(unsigned) es el tamaño del dato
    ///que se guarda
}


int pilaPonerElementoEstatica(PilaEstatica* pp, const void* pd, unsigned cantBytes)
{
    if(pp->tope < cantBytes + sizeof(unsigned))
    {
        return 0;
    }

    pp->tope -= cantBytes;
    memcpy(pp->pila + pp->tope, pd, cantBytes);
    pp->tope -= sizeof(unsigned);
    memcpy(pp->pila + pp->tope, &cantBytes, sizeof(unsigned));
                            /// &cantBytes sería cuanto cuesta guardar el tamaño de datos supongo
    return 1;
}


int pilaSacarElementoEstatica(PilaEstatica* pp, void* pd, unsigned cantBytes)
{
    unsigned tamInfo;

    if(pp->tope >= TAM_PILA)
    {
        return 0; ///PILA VACIA
    }


    memcpy(&cantBytes, pp->pila + pp->tope, sizeof(unsigned));
    pp->tope += sizeof(unsigned);
    memcpy(pd, pp->pila + pp->tope, MINIMO(tamInfo, cantBytes));
    pp->tope += cantBytes;

    return 1;

}


int pilaVerTopeEstatica(PilaEstatica* pp, void* pd, unsigned cantBytes)
{
    unsigned tamInfo;

    if(pp->tope == TAM_PILA)
        return 0;

    memcpy(&cantBytes, pp->pila+pp->tope, sizeof(unsigned));
    memcpy(pd, pp->pila + pp->tope + sizeof(unsigned), MINIMO(cantBytes, tamInfo));


    return 1;
}


int pilaVaciarEstatica(PilaEstatica* pp)
{
    return pp->tope >= TAM_PILA;
}



///PILA DINÁMICA


void pilaCrearDinamica(PilaDinamica* pp)
{
    *pp = NULL;
}

///TO DO lo estoy haciendo
int pilaVaciarDinamica(PilaDinamica* pp)
{
    tNodo* aux = (tNodo*)malloc(sizeof(tNodo));
    if(!aux)
    {
        printf("ERROR AL RESERVAR MEMORIA.");
        return 0;
    }

    while(*pp != NULL)
    {

    }

    return  1;
}


int pilaPonerElementoDinamica(PilaDinamica* pp, const void* pd, unsigned cantBytes){

    tNodo* nuevoNodo;

    if((nuevoNodo = (tNodo*)malloc(sizeof(tNodo)))== NULL || (nuevoNodo->dato = (void*)malloc(cantBytes))==NULL)
    {
        free(nuevoNodo);
        return 0;
    }

    memcpy(nuevoNodo->dato, pd, cantBytes);
    nuevoNodo->tamElem = cantBytes;
    nuevoNodo->sig = *pp;
    *pp=nuevoNodo;
    return 1;
}

int pilaLlenaDinamica(PilaDinamica* pp, unsigned cantBytes){

    tNodo* tmpMemNodo = (tNodo*)malloc(sizeof(tNodo));
    void* tmpMemInfo = malloc(cantBytes);

    free(tmpMemInfo);
    free(tmpMemNodo);

    return tmpMemInfo == NULL || tmpMemNodo == NULL;

}



int pilaVerTopeDinamica(PilaDinamica* pp, void* pd, unsigned cantBytes){

    if(*pp == NULL)
    {
        printf("LA PILA ESTÁ VACÍA");
        return 0;
    }

    memcpy(pd, (*pp)->dato, MINIMO(cantBytes, (*pp)->tamElem));
    return  1;
}



int pilaSacarElementoDinamica(PilaDinamica* pp, void* pd, unsigned cantBytes){

    tNodo* nodoElim = *pp;

    if(!nodoElim) ///DA QUE ESTÁ VACÍA LA PILA, por eso el if
    {
        return 0;
    }

    *pp = nodoElim->sig;
    memcpy(pd, nodoElim->dato, cantBytes);
    free(nodoElim->dato);
    free(nodoElim);
    return  1;
}
