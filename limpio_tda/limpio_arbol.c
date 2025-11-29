/*******

CARGA DE ARBOL

*******/

int CargarArchivoBinOrdenadoAbiertoArolBinBusq(tArbolBinBusq* pAr, FILE* pf, size_t tamInfo)
{
    int cantReg;
    if(*pAr || !pf)
    {
        printf("ERROR AL CARGAR ACHIVO");
        return ERROR;
    } 

    fseek(pf, 0L, SEEK_END);
    cantReg = ftell(pf)/tamInfo;

    ///tengo que armar una funcion que lea el archivo bin y descomento la linea esta del return
    return cargar_arbol_desde_archivo(pAr, pf, LeerArchivo, 0, cantReg-1, tamInfo);
    ///return TODO_OK;

}

int cargar_arbol_desde_archivo(tArbol* pAr, FILE* pf, int (*leer)(void**, void*, int, unsigned), int li, int ls, unsigned tam)
{
	int mitad = (ls + li)/2;
	int r;
	
	if(li>ls)
	{
		return TODO_OK;
	}
	
	*pAr = (tNodo*)malloc(sizeof(tNodo) + tam);
	if(!*pAr)
	{
		printf("ERROR AL INICIALIZAR MEMORIA");
		return -69;
	}
	
	(*pAr)->info = *pAr + 1;
	
	if(!((*pAr)->tamInfo = leer(&(*pAr)->info, pf, mitad, tam)))
    {
        free(*pAr);
        return ERROR;
    }
	
	(*pAr)->izq  = (*pAr)->der = NULL;
	
	if((r = cargar_arbol_desde_archivo(&(*pAr)->izq, pf, leer, li, mitad-1, tam)) != TODO_OK)
        return r;

    cargar_arbol_desde_archivo(&(*pAr)->der, pf, leer, mitad+1, ls, tam);

    return TODO_OK;
}

int LeerArchivo(void** info, void* pf, unsigned pos, size_t tam)
{
    *info = malloc(tam);
    if(!*info)
    {
        printf("ERROR AL ASIGNAR MEMORIA");
        return ERROR;
    }
    fseek((FILE*)pf, pos*tam, SEEK_SET);
    return fread(*info, tam, 1,(FILE*)pf );
}




/*******

BUSQUEDA EN UN ARLBOL

*******/




int busqueda_en_arbol_de_elemento(const tArbol* pAr, void* pd, int(*cmp)(void*, void*))
{
	
	if(!*pAr || !(busqueda_en_nodo_arbol(pAr, pd, cmp))
	{
		printf("Elemento no encontrado");
		return 0;
	}
	
	memcpy(pd,(*pAr)->info, tam);
	return TODO_Ok;
}

tNodoArbol** busqueda_en_nodo_arbol(const tArbol* pAr, void* pd, int(*cmp)(void*, void*))
{
	int comparar;
	while(*pAr && (comparar = cmp(pd,(*pAr)->info)))
	{
		if(comparar < 0)
			pAr = &(*pAr)->izq;
		else
			pAr = &(*pAr)->der;
	}
	if(!*pAr)
	{
		printf("NO SE ENCONTRO ELEMENTO");
		return NULL;
	}
	
	return (tNodoArbol**)pAr;
}



/*******

NIVEL/ALTURA DE ARBOL

*******/



int ArbolAlutra(const tArbolBinBusq* pAr)
{
    if(!*pAr)
        return 0;  // árbol vacío => altura 0

    int hi = ArbolAlutra(&(*pAr)->izq);
    int hd = ArbolAlutra(&(*pAr)->der);
    return (hi > hd ? hi : hd) + 1;
}

int ArbolEsCompletoBin(const tArbolBinBusq* pAr)
{
    return ArbolEsCompletoHastaNivelBin(pAr, ArbolAlutra(pAr)-1);
}

int ArbolEsBalanceadoBin(const tArbolBinBusq* pAr)
{
    return ArbolEsCompletoHastaNivelBin(pAr, ArbolAlutra(pAr)-2);
}

int ArbolEsCompletoHastaNivelBin(const tArbolBinBusq* pAr, int n)
{
    if(!*pAr)
    {
        return n<0;
    }
    if(n==0)
    {
        return 1;
    }
    return ArbolEsCompletoHastaNivelBin(&(*pAr)->izq, n-1) &&
    ArbolEsCompletoHastaNivelBin(&(*pAr)->der, n-1);
}





/*******

ELIMINAR ELEMENTO DE UN ARBOL

*******/


int arbol_eliminar_elemento(tArbolBinBusq* pAr, void* pd, size_t tam)
{
    if(!(pAr = arbol_buscar_raiz(pAr, pd, tam, CompararInt)))
    {
        printf("No encontrado");
        return ERROR;
    }

    arbol_eliminar_nodo(pAr, pd, tam);

    return TODO_OK;
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



/*******

MOSTRAR ARBOL

*******/

void MostrarArbolConForma(const tArbolBinBusq *pAr, int nivel) {
    if(!*pAr)
        return;

    // Primero muestra la derecha
    MostrarArbolConForma(&(*pAr)->der, nivel + 1);

    // Imprime el nodo actual con indentación según el nivel
    for(int i = 0; i < nivel; i++)
        printf("    "); // 4 espacios por nivel
    printf("%d\n", *(int*)(*pAr)->info);

    // Luego muestra la izquierda
    MostrarArbolConForma(&(*pAr)->izq, nivel + 1);
}