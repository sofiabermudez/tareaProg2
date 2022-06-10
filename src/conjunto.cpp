/*5022788*/

#include "../include/info.h"
#include "../include/utils.h"
#include "../include/avl.h"
#include "../include/iterador.h"
#include "../include/usoTads.h"
#include "../include/conjunto.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

struct _rep_conjunto {
    TAvl conj;
    nat min;
    nat max;
};

TConjunto crearConjunto() {
    TConjunto res = NULL;
    return res;
}

TConjunto singleton(nat elem) {
    TConjunto res = crearConjunto();
    res = new _rep_conjunto;
    // TAvl aux = crearAvl();
    // aux =  insertarEnAvl(elem, res->conj);
    // res->conj = aux;
    res->conj = crearAvl();
    // es orden 1 porque va a ser vacio el arbol.
    res->conj = insertarEnAvl(elem, res->conj); 
    res->min = elem;
    res->max = elem;
    return res;
} 

TConjunto unionDeConjuntos(TConjunto c1, TConjunto c2) {
    TConjunto conjRes = crearConjunto();
    if (!estaVacioConjunto(c1) || !estaVacioConjunto(c2)) {
        // conjRes = new _rep_conjunto;
        // conjRes->conj = crearAvl();
        
        TIterador iterC1 = iteradorDeConjunto(c1);
        TIterador iterC2 = iteradorDeConjunto(c2);
        TIterador iterAux = enAlguno (iterC1, iterC2);

        nat tamanio = cantidadEnIterador(iterAux);
        iterAux = reiniciarIterador(iterAux);
       
        ArregloNats arreglo = new nat[tamanio];
        
        for(nat i=0; tamanio > i; i++){
            arreglo[i] = actualEnIterador(iterAux);
            iterAux = avanzarIterador(iterAux);
        } 

        // nat i = 0;
        // while (estaDefinidaActual(iterAux) && tamanio > i){
        //     arreglo[i] = actualEnIterador(iterAux);
        //     iterAux = avanzarIterador(iterAux);
        //     i++;
        // }
        
        conjRes = arregloAConjunto(arreglo, tamanio);
        // conjRes->min = arreglo[0];
        // conjRes->max = arreglo[tamanio-1];

        delete [] arreglo;

        liberarIterador (iterC1);
        liberarIterador (iterC2);
        liberarIterador (iterAux);

    // } else if(!estaVacioConjunto(c1) && estaVacioConjunto(c2)) {
    //     TIterador iterC1 = iteradorDeConjunto(c1);

    //     iterC1 = reiniciarIterador(iterC1);
       
    //     nat tamanio = cardinalidad(c1);
    //     ArregloNats arreglo = new nat[tamanio];
        
    //     for(nat i=0; tamanio > i; i++){
    //         arreglo[i] = actualEnIterador(iterC1);
    //         iterC1 = avanzarIterador(iterC1);
    //     } 
    //     conjRes = arregloAConjunto(arreglo, tamanio);

    //     delete [] arreglo;

    //     liberarIterador (iterC1);

    // } else if (estaVacioConjunto(c1) && !estaVacioConjunto(c2)) {
    //     TIterador iterC2 = iteradorDeConjunto(c2);

    //     iterC2 = reiniciarIterador(iterC2);
       
    //     nat tamanio = cardinalidad(c2);
    //     ArregloNats arreglo = new nat[tamanio];
        
    //     for(nat i=0; tamanio > i; i++){
    //         arreglo[i] = actualEnIterador(iterC2);
    //         iterC2 = avanzarIterador(iterC2);
    //     } 
    //     conjRes = arregloAConjunto(arreglo, tamanio);
    //     delete [] arreglo;
    //     liberarIterador (iterC2);
    }
    return conjRes;
}

TConjunto diferenciaDeConjuntos(TConjunto c1, TConjunto c2) {
    TConjunto conjRes = crearConjunto();
    if (!estaVacioConjunto(c1) || !estaVacioConjunto(c2)) {
        // conjRes = new _rep_conjunto;
        // conjRes->conj = crearAvl();
        
        TIterador iterC1 = iteradorDeConjunto(c1);
        TIterador iterC2 = iteradorDeConjunto(c2);
        TIterador iterAux = soloEnA (iterC1, iterC2);
        
        if (cantidadEnIterador(iterAux) > 0) {
            nat tamanio = cantidadEnIterador(iterAux);
            iterAux = reiniciarIterador(iterAux);
        
            ArregloNats arreglo = new nat[tamanio];
            
            for(nat i=0; tamanio > i; i++){
                arreglo[i] = actualEnIterador(iterAux);
                iterAux = avanzarIterador(iterAux);
            } 

            // nat i = 0;
            // while (estaDefinidaActual(res) && tamanio > i){
            //     printf ("arregloo");
            //     arreglo[i] = actualEnIterador(res);
            //     res = avanzarIterador(res);
            //     i++;
            // }
            
            conjRes = arregloAConjunto(arreglo, tamanio);
            // conjRes->min = arreglo[0];
            // conjRes->max = arreglo[tamanio-1];

            delete [] arreglo;
        }
        liberarIterador (iterC1);
        liberarIterador (iterC2);
        liberarIterador (iterAux);

    // } else if(!estaVacioConjunto(c1) && estaVacioConjunto(c2)) {
    //     TIterador iterC1 = iteradorDeConjunto(c1);

    //     iterC1 = reiniciarIterador(iterC1);
       
    //     nat tamanio = cardinalidad(c1);
    //     ArregloNats arreglo = new nat[tamanio];
        
    //     for(nat i=0; tamanio > i; i++){
    //         arreglo[i] = actualEnIterador(iterC1);
    //         iterC1 = avanzarIterador(iterC1);
    //     } 
    //     conjRes = arregloAConjunto(arreglo, tamanio);

    //     delete [] arreglo;

    //     liberarIterador (iterC1);

    // } else if (estaVacioConjunto(c1) && !estaVacioConjunto(c2)) {
    //     TIterador iterC2 = iteradorDeConjunto(c2);

    //     iterC2 = reiniciarIterador(iterC2);
       
    //     nat tamanio = cardinalidad(c2);
    //     ArregloNats arreglo = new nat[tamanio];
        
    //     for(nat i=0; tamanio > i; i++){
    //         arreglo[i] = actualEnIterador(iterC2);
    //         iterC2 = avanzarIterador(iterC2);
    //     } 
    //     conjRes = arregloAConjunto(arreglo, tamanio);
    //     delete [] arreglo;
    //     liberarIterador (iterC2);
    }
    return conjRes;
}

bool perteneceAConjunto(nat elem, TConjunto c) {
    bool res = false;
    if (!estaVacioConjunto(c) && buscarEnAvl(elem, c->conj) != NULL) {
        res = true;
    }
    return res;
}

bool estaVacioConjunto(TConjunto c) {
    return c == NULL;
}

nat cardinalidad(TConjunto c) {
    if (estaVacioConjunto(c)) {
        return 0;
    } else
        return cantidadEnAvl(c->conj);
}

nat minimo(TConjunto c) {
    assert (!estaVacioConjunto(c));
    return c->min;
}

nat maximo(TConjunto c) {
    assert (!estaVacioConjunto(c));
    return c->max;
}

TConjunto arregloAConjunto(ArregloNats elems, nat n) {
    assert(n>0);
    TConjunto res = new _rep_conjunto;
    // res->conj = crearAvl();
    // for (nat i = 0; i < n ; i++) {
    //     res->conj = insertarEnAvl(elems[i], res->conj);
    // }
    res->min = elems[0];
    res->max = elems[n-1];
    res->conj = arregloAAvl (elems, n);
    // res->min = elems[0];
    // res->max = elems[n-1];
    return res;
}

// TConjunto arregloAConjuntoAux(ArregloNats elems, int prim, int ult) {
//     TConjunto res = crearConjunto();
//     if ((prim > 0) && (ult-prim)>=0) {
//         nat mitad = (ult-prim)/2 + prim; 
//         res = new _rep_conjunto;
//         res = insertarEnAvl(elems[mitad-1], res);
        
//         res->conj->derecho = arregloAConjuntoAux(elems, mitad + 1, ult);
//         res->conj->izquierdo = arregloAConjuntoAux(elems, prim, mitad-1);
//     }
   
//     return res;
// }

// TConjunto arregloAConjunto(ArregloNats elems, nat n) {
//     assert(n>0);
//     TConjunto res = crearConjunto();
//     res = arregloAAvlAux(elems, 1, n);
//     res->min = elems[0];
//     res->max = elems[n-1];
//     return res;
// }

// TIterador iteradorDeConjunto(TConjunto c) {
//     TIterador iter = crearIterador();
//     if (!estaVacioConjunto(c)) 
//         iter = enOrdenAvl(c->conj);
//     return iter;
// }
TIterador iteradorDeConjuntoAux (TAvl avl, TIterador iter) {
    if (avl != NULL) {
        nat raiz = raizAvl(avl);
        iter = iteradorDeConjuntoAux(izqAvl(avl), iter);
        iter = agregarAIterador(raiz, iter);
        iter = iteradorDeConjuntoAux(derAvl(avl), iter);
    }
    return iter;
}

TIterador iteradorDeConjunto(TConjunto c) {
    TIterador iter = crearIterador();
    if (!estaVacioConjunto(c)) 
        iter = iteradorDeConjuntoAux(c->conj, iter);
    return iter;
}


void liberarConjunto(TConjunto c) {
    if (c!= NULL) {
        liberarAvl (c->conj);
    }
    delete c;
}
