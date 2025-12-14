void colaCrear(tCola* pCola)
{
    pCola->nIni = NULL;
    pCola->nFin = NULL;
}

int colaLLena(tCola* pCola, unsigned cantBytes)
{
    tNodo* aux = (tNodo*)malloc(sizeof(tNodo));
    void* dato = malloc(cantBytes);
    free(aux);
    free(dato);

    return aux==NULL || dato==NULL;
}

int colaPoner(tCola* pCola, void* dato, unsigned cantBytes)
{
    tNodo* aux = (tNodo*)malloc(sizeof(tNodo));

    if( aux==NULL || (aux->dato = malloc(cantBytes)) == NULL)
    {
        return 0; ///NO HAY ESPACIO EN MEM
    }

    memcpy(aux->dato, dato, cantBytes);
    aux->tamDato = cantBytes;

    if(pCola->nFin)///SI EL ULTIMO ELEMNTO DE LA COLA TIENE ELEMENTO GUARDADO ENTRA POR VERDADERO...
    {
        pCola->nFin->nSig = aux;
    }
    else
    {
        pCola->nIni = aux;
    }
    pCola->nFin = aux;
    return 1;
}


void colaVaciar(tCola* pCola)
{
    while(pCola->nIni)
    {
        tNodo* aux = pCola->nIni;
        pCola->nIni = aux->nSig;

        free(aux->dato);
        free(aux);
    }
    free(pCola);
}

int colaSacarElemento(tCola* pCola, void* dato, unsigned cantBytes)
{
    tNodo* aux = pCola->nIni;
    if(!aux)
		
    {
        return 0;
    }
    pCola->nIni = aux->nSig;

    memcpy(dato, aux->dato, MINIMO(aux->tamDato, cantBytes));
    free(aux->dato);
    free(aux);

    if(pCola->nIni == NULL)
        pCola->nFin = NULL;

    return 1;
}

int colaVacia(tCola* pCola)
{
    return pCola->nIni == NULL;
}


///ARMANDO TODO PARA EL FINAL
int cola_poner_elemento(tCola* pCol, void* pd, size_t tamDato)
{
    tNodo* nue = (tNodo*)malloc(sizeof(tNodo)+tamDato);
    if(!nue)
    {
        return SIN_MEM;
    }

    nue->info = nue + 1;
    memcpy(nue->info, pd, tamDato);
    nue->tamInfo = tamDato;
    if(!pCol->nPri)
	{
		pCol->nPri = nue;
	}else
	{         
	pCol->nUlt->nSig = nue;
    }
	
    pCol->nUlt = nue;
    return TODO_OK;
}


int cola_sacar_elemento(tCola* pCol, void* pd, size_t tamDato)
{
	tNodo* elim = pCol->nPri;
	memcpy(pd, elim->info, tamDato);
	pCol->nPri = elim->nSig;
	free(elim);
	
	if(pCol->nPri == NULL)
		pCol->nUlt = NULL;
	
	return TODO_OK;
}