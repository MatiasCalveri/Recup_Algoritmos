typedef struct sNodo
{
	void* info;
	struct sNodo* der, *izq;
	size_t tamInfo;
	
}tNodo;
typedef tNodo* tArbol;


void arbol_inicializar(tArbol* pAr)
{
		*pAr = NULL;
}


.

int arbol_poner_elemento_rec(tArbol* pAr, void* pd, size_t tamDato, int(*cmp)(const void* , const void* ))
{
	Nodo* nue = (tNodo*)malloc(sizeof(tNodo)+tamDato);
	if(!nue)
	{
		printf("Memoria insuficiente");
		return ERROR;
	}
	int comparacion;
	
	if(*pAr)
	{
		if(comparacion = cmp((*pAr)->info, pd) < 0 )
		{
			arbol_poner_elemento_rec(&(*pAr)->izq, pd, cmp);
		}else if(comparacion > 0){
			arbol_poner_elemento_rec(&(*pAr)->der, pd, cmp);
		}else{ return ERROR; } ///Clave duplicada
	}
	
	nue->info = nue + 1;
	memcpy(nue->info, pd, tamDato);
	nue->izq = nue -> der = NULL;
	*pAr = nue;
	return TODO_OK;
}


int arbol_altura(const tArbol* pAr)
{
	if(*pAr)
		return ERROR;
	
	int hi = arbol_altura(&(*pAr)->izq);
	int hd = arbol_altura(&(*pAr)->der);
	return (hi>hd ? hi : hd) + 1;
}


///MI ERROR EN ESTAS DE ABAJO ES QUE PUSE QUE RETORNE INT, CUANDO TIENE QUE SER tNodo*
tNodo** nodo_mayor(tArbol* pAr)
{
	while((*pAr)->der)
		pAr = &(*pAr)->der;
	
	return (tNodo**)pAr;
}

tNodo** nodo_menor(tArbol* pAr)
{
	while((*pAr)->izq)
		pAr = &(*pAr)->izq;
	return (tNodo**)pAr;
}


tNodo** nodo_menor_rec(tArbol* pAr)
{
	if(!*pAr)
		return NULL;
	if(!(*pAr)->izq)
		return (tNodo**)pAr;
	return nodo_menor_rec(&(*pAr)->izq);	
}


int arbol_eliminar_elemento(tArbol* pAr, void* pd, size_t tamDato, int(*cmp)(const void* , const void* ))
{
	tNodo **remp, *elim;
	
	if(!*pAr)
		return ERROR;
	
	while(*pAr)
	{
		
	}
}


tNodo** arbol_buscar_raiz_rec(const tArbol* pAr, int(*cmp)(const void* , const void* ))
{
	if(!*pAr)
		return NULL;
	
	int comparar;
	if(*pAr && (comparacion = cmp(pd, (*pAr)->info)))
	{
		if(comparar < 0 )
		{
			arbol_buscar_raiz(&(*pAr)->izq, pd, cmp);
		}else 
		arbol_buscar_raiz(&(*pAr)->der, pd, cmp);
	}
	   return (tNodoArbol**)pAr;
}

///EN ESTE CASO EL CMP VA ADENTRO DEL WHILE, DISTINTO QUE EN EL CASO DE PONER 
tNodoArbol** arbol_buscar_raiz(const tArbolBinBusq *pAr, void *pd, size_t tamElem, int(*cmp)(const void*, const void*))
{
    int comparacion;

    while(*pAr && (comparacion = cmp(pd, (*pAr)->info)))
    {
        if(comparacion<0)
            pAr = &(*pAr)->izq; 
        else
            pAr = &(*pAr)->der;

        if(!*pAr)
            printf("NO SE ENCUENTRA EL ELEMENTO");
    }

    return (tNodoArbol**)pAr;
}


int arbol_eliminar_nodo(tArbolBinBusq *pAr, void *pd, size_t tamElem)
{
    tNodoArbol *elim, **remp;
    if(!*pAr)
    {
        printf("LISTO");
        return TODO_OK;
    }

    memcpy(pd, (*pAr)->info, tamElem);

    if(!((*pAr)->der) &&  !((*pAr)->izq))
    {
        free(*pAr);
        *pAr = NULL;
        return TODO_OK;
    }

    remp = ArbolAlutra(&(*pAr)->izq) > ArbolAlutra(&(*pAr)->der) ?
    mayor_nodo(&(*pAr)->izq):
    menor_nodo(&(*pAr)->der);

    elim = *pAr;

    *pAr = *remp;
    *remp = (*remp)->izq ? (*remp)->izq  : (*remp)->der;

    (*pAr)->izq = elim->izq;
    (*pAr)->der = elim->der;
    free(elim);
    return 1; ///TODO OK
}


///VERSION DEL APUNTE
unsigned cantNodosArbolBin(const tArbolBinBusq *p)
{
    if(!*p)
        return 0;

    return cantNodosArbolBin(&(*p)->izq)
         + cantNodosArbolBin(&(*p)->der)
         + 1;
}


unsigned cantNodosArbolBin(const tArbolBinBusq *p)
{
    tNodoArbol *nodo = *p;
    if(!nodo)
        return 0;

    return cantNodosArbolBin(&nodo->izq)
         + cantNodosArbolBin(&nodo->der)
         + 1;
}

unsigned cantNodosEnNivel(const tArbolBinBusq *p, unsigned nivel)
{
    if(!*p)
        return 0;

    if(nivel == 0)
        return 1;

    return cantNodosEnNivel(&(*p)->izq, nivel - 1)
         + cantNodosEnNivel(&(*p)->der, nivel - 1);
}

unsigned cantNodosHastaNivel(const tArbolBinBusq *p, unsigned nivel)
{
    if(!*p)
        return 0;

    if(nivel == 0)
        return 1;

    return 1 
         + cantNodosHastaNivel(&(*p)->izq, nivel - 1)
         + cantNodosHastaNivel(&(*p)->der, nivel - 1);
}

unsigned nodosFaltantesEnNivel(const tArbolBinBusq *p, unsigned nivel)
{
    unsigned maximos = potencia2(nivel);            // 2^nivel
    unsigned reales  = cantNodosEnNivel(p, nivel);  // nodos presentes

    if(reales >= maximos)
        return 0;

    return maximos - reales;
}



