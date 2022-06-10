/*5022788*/

#include "../include/pila.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

struct _rep_pila {
    nat tamanio;
    nat tope;
    ArregloNats arreglo;
};

TPila crearPila(nat tamanio){
    assert (tamanio > 0);
    TPila res = new _rep_pila;
    res->tamanio = tamanio;
    res->arreglo = new nat[tamanio];
    res->tope = 0;
    return res; 
}

TPila apilar(nat num, TPila p) {
    assert(!estaLlenaPila(p));
    p->arreglo [p->tope] = num;
    p->tope++;
    return p;
}

TPila desapilar(TPila p) {
    assert (!estaVaciaPila(p));
    // delete [p->tope] p->arreglo;
    p->tope--;
    return p;
}

void liberarPila(TPila p) {
    delete [] p->arreglo;
    delete p;

}

bool estaVaciaPila(TPila p) {
    return p->tope == 0;
}

bool estaLlenaPila(TPila p) {
    return p->tope == p->tamanio;
}

nat cima(TPila p) {
    return p->arreglo [p->tope-1]; // -1 porque los arreglos arrancan en 0
}