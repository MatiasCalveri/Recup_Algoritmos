
/*******

INICIALIZACION DE LISTA

*******/


void ListaCrear(tLista* pl)
{
    *pl = NULL;
}



/*******

CARGA DE LISTA

*******/


int ListaPonerAlFinal(tLista* pl, const void* pd, size_t tam)
{

    if(*pl)
    {
      while(*pl)
      {
        pl = &(*pl)->nSig;
      }
    }
    tNodo* nue = (tNodo*)malloc(sizeof(tNodo)+tam);
    if(!nue)
    {
        printf("ERROR MEMORIA");
        return -1;
    }
    nue->info = nue+1;
    memcpy(nue->info, pd, tam);
    nue->tamInfo = tam;
    nue->nSig = NULL;
    nue->nAnt = *pl;
    if(*pl)
    {
        (*pl)->nSig = nue;
    }

    *pl = nue;

    return 1;
}



int ListaPonerAlComienzo(tLista* pl, const void* pd, size_t tam)
{
    tNodo* nue = (tNodo*)malloc(sizeof(tNodo) + tam);
    if(!nue)
    {
        printf("FALTA DE MEMORIA");
        return  -1;
    }
    nue->info = nue+1;
    memcpy(nue->info, pd, tam);
    nue->tamInfo = tam;

    nue->nSig = *pl;
    nue->nAnt = NULL;

   if (*pl) ///SI ESTÁ VACIO SE SALTEA EL IF
   {
        (*pl)->nAnt = nue;
   }
    *pl = nue;

    return 1;
}


/*******

VACIAR O SACAR DE LISTA

*******/


int ListaSacarPriLista(tLista* pl, void* pd, size_t tam)
{
    tNodo* elim = *pl;
    if(!elim)
    {
        return 0; ///LISTA VACIA
    }
    memcpy(pd, elim->info, tam);
    *pl = elim->nSig;
    if(*pl)
        (*pl)->nAnt = NULL; //si la lista no quedó vacía, el nuevo primer nodo sigue teniendo nAnt apuntando al nodo eliminado.
    free(elim);
    return 1;
}

void ListaVaciar(tLista* pl)
{
    tNodo* elim;
    while(*pl)
    {
        elim = *pl;
        *pl = elim->nSig;
        free(elim);
    }
    *pl = NULL;
}

int ListaSacarPriLista(tLista* pl, void* pd, size_t tam)
{
    tNodo* elim = *pl;
    if(!elim)
    {
        return 0; ///LISTA VACIA
    }
    memcpy(pd, elim->info, tam);
    *pl = elim->nSig;
    if(*pl)
        (*pl)->nAnt = NULL; //si la lista no quedó vacía, el nuevo primer nodo sigue teniendo nAnt apuntando al nodo eliminado.
    free(elim);
    return 1;
}

void ListaVaciar(tLista* pl)
{
    tNodo* elim;
    while(*pl)
    {
        elim = *pl;
        *pl = elim->nSig;
        free(elim);
    }
    *pl = NULL;
}


/*******

ORDENAR O PONER EN ORDEN DE LISTA

*******/

void ListaOrdenarSeleccion(tLista* pl, int (*cmp)(const void*, const void*))
{
    if (*pl == NULL || (*pl)->nSig == NULL) {
        return;  // Lista vacía o con un solo elemento, no es necesario ordenar
    }

    tNodo* inicio = *pl;
    while (inicio != NULL) {
        tNodo* minNodo = inicio;
        tNodo* actual = inicio->nSig;

        // Buscar el nodo mínimo a partir de 'inicio'
        while (actual != NULL) {
            if (cmp(actual->info, minNodo->info) < 0) {
                minNodo = actual;
            }
            actual = actual->nSig;
        }

        // Si el nodo mínimo no es el nodo de 'inicio', intercambiamos
        if (minNodo != inicio) {
            void* temp = inicio->info;
            size_t tempTam = inicio->tamInfo;

            inicio->info = minNodo->info;
            inicio->tamInfo = minNodo->tamInfo;

            minNodo->info = temp;
            minNodo->tamInfo = tempTam;
        }

        inicio = inicio->nSig;  // Avanzamos al siguiente nodo
    }
}



int poner_ord_lista(tLista* pl, const void* pd, size_t tam, int (*cmp)(const void*,const void*))
{
    tNodo* aux_sig = *pl;
    tNodo* aux_ant = aux_sig ? aux_sig->nAnt : NULL;
    tNodo* nue;
    while(aux_sig && cmp(pd, aux_sig->info)>0)
    {
        aux_ant = aux_sig;
        aux_sig = aux_sig->nSig;
    }

    while(aux_ant && cmp(pd, aux_ant->info)<0)
    {
        aux_sig = aux_ant;
        aux_ant = aux_ant->nAnt;
    }

    if((aux_sig && !cmp(pd, aux_sig->info)) || (aux_ant && !cmp(pd, aux_ant->info)))
    {
        return -1; ///DUPLICADO
    }

    nue = (tNodo*)malloc(sizeof(tNodo)+ tam);
    if(!nue)
    {
        return -2; ///FALTA MEMORIA
    }
    nue->info = nue+1;

    memcpy(nue->info, pd, tam);
    nue->tamInfo = tam;
    return 1;
}



int poner_ord_lista(tLista* pl, const void* pd, size_t tam,
                    int (*cmp)(const void*, const void*))
{
    tNodo* act = *pl;
    tNodo* ant = NULL;
    tNodo* nue;

    while(act && cmp(pd, act->info) > 0)
    {
        ant = act;
        act = act->nSig;
    }

    // Duplicado
    if(act && cmp(pd, act->info) == 0)
        return -1;

    nue = malloc(sizeof(tNodo) + tam);
    if(!nue)
        return -2;

    nue->info = nue + 1;
    memcpy(nue->info, pd, tam);
    nue->tamInfo = tam;

    nue->nAnt = ant;
    nue->nSig = act;

    if(ant)
        ant->nSig = nue;
    else
        *pl = nue;          // inserta al inicio

    if(act)
        act->nAnt = nue;    // inserta antes de act

    return 1;
}

int lista_insertar_ordenado(tLista* pl, const void* pd, size_t tam,int (*cmp)(const void*, const void*))
{
    tNodo* act = *pl;
    tNodo* ant = NULL;
    tNodo* nue;

    // Buscar punto de inserción
    while(act && cmp(pd, act->info) > 0)
    {
        ant = act;
        act = act->nSig;
    }

    // Duplicado
    if(act && cmp(pd, act->info) == 0)
        return 0;

    // Crear nodo
    nue = malloc(sizeof(tNodo) + tam);
    if(!nue)
        return -1;

    nue->info = nue + 1;
    memcpy(nue->info, pd, tam);
    nue->tamInfo = tam;

    // Enganches
    nue->nAnt = ant;
    nue->nSig = act;

    if(ant)
        ant->nSig = nue;
    else
        *pl = nue;          // nuevo primero

    if(act)
        act->nAnt = nue;   // si no era el último

    return 1;
}