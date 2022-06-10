/*5022788*/

#include "../include/colaBinarios.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo *NodoCola;

struct nodo {
    TBinario valor;
    NodoCola sig;
};

struct _rep_colaBinarios {
    NodoCola ultimo;
    NodoCola primero;
};

TColaBinarios crearColaBinarios() {
    TColaBinarios res = new _rep_colaBinarios;
    res->primero = res->ultimo = NULL;
    return res;
}

TColaBinarios encolar(TBinario b, TColaBinarios c) {
    NodoCola res = new nodo;
    res->valor = b;
    res->sig = NULL;
    if (c->primero == NULL) {
        c->primero = res;
    }else {
        c->ultimo->sig = res;
    }
    c->ultimo = res;
    return c;
}

TColaBinarios desencolar(TColaBinarios c) {
    assert (!estaVaciaColaBinarios(c));
    NodoCola aBorrar = c->primero;
    c->primero = c->primero->sig;
    delete aBorrar;
    return c;
}

void liberarColaBinarios(TColaBinarios c){
    while (c->primero != NULL) {
        c = desencolar (c);
    }
    delete c;
}

bool estaVaciaColaBinarios(TColaBinarios c) {
    return (c->primero == NULL);
}

TBinario frente(TColaBinarios c) {
    assert (!estaVaciaColaBinarios(c));
    return c->primero->valor;
}