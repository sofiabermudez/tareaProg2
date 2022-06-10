/*5022788*/

#include "../include/info.h"
#include "../include/utils.h"
#include "../include/iterador.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

typedef struct nodo *NodoIter;

struct nodo {
    nat elem;
    NodoIter siguiente;
};

struct _rep_iterador {
    NodoIter inicio;
    NodoIter final; 
    NodoIter actual;
    bool reiniciado;
};

TIterador crearIterador() {
    TIterador res = new _rep_iterador;
    res->inicio = res->final = res->actual = NULL;
    res->reiniciado = false;
    return res;
}

TIterador agregarAIterador(nat elem, TIterador iter){
    NodoIter aAgregar = new nodo;
    aAgregar->elem = elem;
    aAgregar->siguiente = NULL;
                
    if (!iter->reiniciado){
        if (iter->inicio  == NULL){
            iter->inicio = iter->final = aAgregar;

        } else {
            iter->final->siguiente = aAgregar;
            iter->final = aAgregar;
        }
    }

    return iter;
}

TIterador reiniciarIterador(TIterador iter){
    iter->actual = iter->inicio;
    iter->reiniciado = true;

    return iter;
}

TIterador avanzarIterador(TIterador iter){
    if (estaDefinidaActual(iter)){
        if (iter->actual != iter->final) {
            iter->actual = iter->actual->siguiente;
        }else{
            iter->actual = NULL;
        }
    }
    return iter;
}

nat actualEnIterador(TIterador iter){
    return iter->actual->elem;
}

bool estaDefinidaActual(TIterador iter){
    return iter->actual != NULL;
}

void liberarIterador(TIterador iter){
    NodoIter aBorrar;
    while(iter->inicio != NULL) {
        aBorrar = iter->inicio;
        iter->inicio = iter->inicio->siguiente;
        delete aBorrar;
    }
    delete iter;
}