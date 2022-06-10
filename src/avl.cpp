/*5022788*/

#include "../include/info.h"
#include "../include/utils.h"
#include "../include/avl.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

struct _rep_avl {
    nat elem;
    TAvl derecho;
    TAvl izquierdo;
    nat altura;
    nat cantElem;
};

TAvl crearAvl() {
    return NULL;
}

bool estaVacioAvl(TAvl avl){
    return avl == NULL;
}

nat maximo(nat primero, nat segundo) {
    if (primero < segundo) {
        return segundo;
    } else {
        return primero;
    }
}

void rotarDer (TAvl &avl) {
    TAvl y = avl->izquierdo;
    TAvl x = y->derecho;

    y->derecho = avl;
    avl->izquierdo = x;

    avl->altura = maximo(alturaDeAvl(avl->izquierdo), alturaDeAvl(avl->derecho)) + 1;
    y->altura = maximo(alturaDeAvl(y->izquierdo), alturaDeAvl(y->derecho)) + 1;
    avl->cantElem = cantidadEnAvl(avl->izquierdo) + cantidadEnAvl(avl->derecho) +1;

    avl = y;
}

void rotarIzq (TAvl &avl){
    TAvl y = avl->derecho;
    TAvl x = y->izquierdo;

    y->izquierdo = avl;
    avl->derecho = x;

    avl->altura = maximo(alturaDeAvl(avl->izquierdo), alturaDeAvl(avl->derecho)) + 1;
    y->altura = maximo(alturaDeAvl(y->izquierdo), alturaDeAvl(y->derecho)) + 1;
    avl->cantElem = cantidadEnAvl(avl->izquierdo) + cantidadEnAvl(avl->derecho) +1;

    avl = y;
}


TAvl insertarEnAvl(nat elem, TAvl avl) {
    assert(estaVacioAvl(buscarEnAvl(elem, avl)));

    if(avl == NULL) {
        TAvl nuevo = new _rep_avl;
        nuevo->elem = elem;
        nuevo->derecho = nuevo->izquierdo = NULL;
        nuevo->altura = 1;
        nuevo->cantElem = 1;
        avl = nuevo;

    } else {

        if(elem < raizAvl(avl)) {
            avl->izquierdo = insertarEnAvl(elem, avl->izquierdo);
            avl->altura = maximo(alturaDeAvl(avl->izquierdo), alturaDeAvl(avl->derecho)) + 1;

            int difAlturaIzq = alturaDeAvl(avl->izquierdo) - alturaDeAvl(avl->derecho);
            if (difAlturaIzq > 1) {
                if (alturaDeAvl(avl->izquierdo->izquierdo) > alturaDeAvl(avl->izquierdo->derecho)) {
                    rotarDer(avl);
                } else {
                    rotarIzq(avl->izquierdo);
                    rotarDer(avl);
                }
            }
                        

        } else {
            avl->derecho = insertarEnAvl(elem, avl->derecho);
            avl->altura = maximo(alturaDeAvl(avl->izquierdo), alturaDeAvl(avl->derecho)) + 1;

            int difAltura = alturaDeAvl(avl->derecho) - alturaDeAvl(avl->izquierdo);
            if (difAltura > 1) {
                if (alturaDeAvl(avl->derecho->derecho) > alturaDeAvl(avl->derecho->izquierdo)) {
                    rotarIzq(avl);
                } else {
                    rotarDer(avl->derecho);
                    rotarIzq(avl);
                }
            }

        }
        avl->cantElem = cantidadEnAvl(avl->izquierdo) + cantidadEnAvl(avl->derecho) +1;
    
    }
    return avl;
}

TAvl buscarEnAvl(nat elem, TAvl avl) {
    TAvl res = avl;
    
    if(!estaVacioAvl(avl) && raizAvl(avl) != elem){
        
        if (avl->elem > elem){
            res = buscarEnAvl(elem, avl->izquierdo);
        } else{
            res = buscarEnAvl(elem, avl->derecho);
        }
    }
    return res;
}

nat raizAvl(TAvl avl) {
    return avl->elem;
}

TAvl izqAvl(TAvl avl) {
    return avl->izquierdo;
}

TAvl derAvl(TAvl avl) {
    return avl->derecho;
}

nat cantidadEnAvl(TAvl avl) {
    nat res = 0;
    if (avl != NULL) {
        res = avl->cantElem;
    }
    return res;
}

nat alturaDeAvl(TAvl avl){
    nat res = 0;
    if (avl != NULL) {
        res = avl->altura;
    }
    return res;
}

TIterador enOrdenAvlAux(TAvl avl, TIterador iter) {
    if (avl != NULL) {
        nat raiz = raizAvl(avl);
        iter = enOrdenAvlAux(avl->izquierdo, iter);
        iter = agregarAIterador(raiz, iter);
        iter = enOrdenAvlAux(avl->derecho, iter);
    }
    return iter;
}

TIterador enOrdenAvl(TAvl avl) {
    TIterador iter = crearIterador();
    // iter = NULL;
    iter = enOrdenAvlAux(avl, iter);
    return iter;
}


// TAvl arregloAAvl(ArregloNats elems, nat n) {
//     assert(n>0); //&& elems ord creciente estricta
//     TAvl res = crearAvl();
//     for (nat i = 0; i < n ; i++) {
//         res = insertarEnAvl(elems[i], res);
//     }
//     return res;
// }

TAvl arregloAAvlAux(ArregloNats elems, int prim, int ult) {
    TAvl res = crearAvl();
    if ((prim > 0) && (ult-prim)>=0) {
        nat mitad = (ult-prim)/2 + prim; 
        res = new _rep_avl;
        res->elem  = elems[mitad-1];

        // res = insertarEnAvl(elems[mitad-1], res);
        
        res->derecho = arregloAAvlAux(elems, mitad + 1, ult);
        res->izquierdo = arregloAAvlAux(elems, prim, mitad-1);
        res->altura = maximo(alturaDeAvl(res->izquierdo), alturaDeAvl(res->derecho)) + 1;
    }
   
    return res;
}

TAvl arregloAAvl(ArregloNats elems, nat n) {
    assert(n>0);
    TAvl res = crearAvl();
    res = arregloAAvlAux(elems, 1, n);
    res->cantElem = n;
    return res;
}

TAvl avlMinAux (nat h, nat &cant, TAvl avl) {
    if (h > 0) {
        if (h==1) {
            avl = insertarEnAvl(cant, avl);
            // avl = new _rep_avl;
            // avl->elem = cant;
            // avl->altura = 1;
            cant++;

        } else {
            avl = insertarEnAvl(cant, avl);
            // avl = ew _rep_avl;
            // avl->elnem = cant;
            avl->izquierdo = avlMinAux(h-1, cant, izqAvl(avl));
            avl->elem = cant;
            cant++;
            avl->derecho = avlMinAux(h-2, cant, derAvl(avl));
            // avl->altura = maximo(alturaDeAvl(avl->izquierdo), alturaDeAvl(avl->derecho)) + 1;

        }
    }
    return avl;
}

TAvl avlMin(nat h) {
    TAvl res = crearAvl();
    nat cant = 1;
    res = avlMinAux (h, cant, res);
    return res;
}


void liberarAvl(TAvl avl) {
    if (avl != NULL){
        liberarAvl(avl->derecho);
        liberarAvl(avl->izquierdo); 
    }
    delete avl;
}
