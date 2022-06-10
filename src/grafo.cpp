/*5022788*/

#include "../include/info.h"
#include "../include/utils.h"
#include "../include/iterador.h"
#include "../include/avl.h"
#include "../include/mapping.h"
#include "../include/grafo.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

struct _rep_grafo {
    TMapping map;
    TAvl * vecinos;
    nat cantVertices;
    nat cantParejas;
    nat maxParejas;

};

TGrafo crearGrafo(nat N, nat M) {
    TGrafo res = new _rep_grafo;
    res->map = crearMap(M+1);
    res->vecinos = new TAvl[N];
    for (nat i = 0; i < N; i++) {
        res->vecinos[i] = crearAvl();
    }
    res->cantVertices = N;
    res->cantParejas = 0;
    res->maxParejas = M;
    return res;
}

nat cantidadVertices(TGrafo g) {
    return g->cantVertices;
}

bool hayMParejas(TGrafo g) {
    return g->maxParejas == g->cantParejas;
}


nat max(nat primero, nat segundo) {
    if (primero < segundo) {
        return segundo;
    } else {
        return primero;
    }
}
nat min(nat primero, nat segundo) {
    if (primero > segundo) {
        return segundo;
    } else {
        return primero;
    }
}

nat numIdentificador(nat v1, nat v2, nat vertices) {
    return (min(v1, v2) - 1) * vertices + (max(v1, v2) - 1);
}

TGrafo hacerVecinos(nat v1, nat v2, double d, TGrafo g) {
    assert (1 <= v1 && v2 <= g->cantVertices && v1 != v2 && !sonVecinos(v1, v2, g) && !hayMParejas(g) && d >= 0);
    
    nat veci = numIdentificador(v1,v2, g->cantVertices);
    g->map = asociarEnMap(veci, d, g->map);

    g->vecinos[v1-1] = insertarEnAvl(v2, g->vecinos[v1-1]);
    g->vecinos[v2-1] = insertarEnAvl(v1, g->vecinos[v2-1]);

    g->cantParejas ++;
    return g;
}

bool sonVecinos(nat v1, nat v2, TGrafo g) {
    assert (1 <= v1 && v2 <= g->cantVertices);
    nat veci = numIdentificador(v1, v2, g->cantVertices);
    return (v1 != v2 && existeAsociacionEnMap(veci, g->map));
}

double distancia(nat v1, nat v2, TGrafo g) {
    nat veci = numIdentificador(v1, v2, g->cantVertices);
    return valorEnMap(veci, g->map);
}

TIterador vecinos(nat v, TGrafo g) {
    assert (1 <= v && v <= g->cantVertices);
    return enOrdenAvl(g->vecinos[v-1]);
}

void liberarGrafo(TGrafo g) {
    for (nat i = 0; i < g->cantVertices; i++) {
        liberarAvl(g->vecinos[i]);
    }
    delete [] g->vecinos;
    liberarMap(g->map);
    delete g;
}
