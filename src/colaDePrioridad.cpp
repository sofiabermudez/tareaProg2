/*5022788*/

#include "../include/info.h"
#include "../include/utils.h"
#include "../include/colaDePrioridad.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

typedef struct elemento *NodoElem;

struct elemento {
    double prioridad;
    nat dato;
};

struct _rep_colaDePrioridad {
    NodoElem *arreglo;
    nat *posiciones;
    nat maximo;
    nat tope;
};

TColaDePrioridad crearCP(nat N) {
    TColaDePrioridad res = new _rep_colaDePrioridad;
    res->arreglo = new NodoElem[N+1];
    // for (nat i = 1; i < N+1; i++) {
    //     res->arreglo[i] = new elem;
    //     // res->arreglo[i]->prioridad = 0;
    //     // res->arreglo[i]->dato = 0;
    // }
    res->posiciones = new nat[N+1];    
    for (nat i = 1; i < N+1; i++) 
        res->posiciones[i] = 0;
    res->maximo = N;
    res->tope = 0;
    return res;
}

nat rangoCP(TColaDePrioridad cp) {
    return cp->maximo;
}

TColaDePrioridad filtradoAscendente(TColaDePrioridad cp, nat pos){
    
    while (pos > 1 && cp->arreglo[pos/2]->prioridad > cp->arreglo[pos]->prioridad) {
        NodoElem swap = cp->arreglo[pos];
        cp->arreglo[pos] = cp->arreglo[pos/2];
        cp->arreglo[pos/2] = swap;
        
        cp->posiciones[cp->arreglo[pos]->dato] = pos; 
        cp->posiciones[cp->arreglo[pos/2]->dato] = pos/2;
        pos = pos/2;
    }
    // cp->arreglo[pos] = swap;
    // cp->posiciones[swap->dato] = pos;
    return cp;
}

// TColaDePrioridad filtradoDescendente(TColaDePrioridad cp, nat pos){
//     NodoElem swap = cp->arreglo[pos];
    
//     if (2*pos != 0) {

//         nat pHijo = 2*pos;

//         do {
//             if (2*pos + 1 != 0 && cp->arreglo[2*pos+1]->prioridad < cp->arreglo[2*pos]->prioridad )
//                 pHijo = 2*pos + 1;

//             if (swap->prioridad > cp->arreglo[pHijo]->prioridad) {
//                 cp->arreglo[pos] = cp->arreglo[pHijo];
//                 cp->posiciones[cp->arreglo[pHijo]->dato] = pHijo;
//                 pos = pHijo;
//             }
//         } while (rangoCP(cp) >= 2*pos && 2*pos != 0 
//         && swap->prioridad > cp->arreglo[2*pos]->prioridad);
        
//         cp->arreglo[pos] = swap;
//         cp->posiciones[swap->dato] = pos;
//     }
//     return cp;
// }

TColaDePrioridad filtradoDescendente(TColaDePrioridad cp, nat pos){
    bool cortar = true;

    while (cp->tope >= 2*pos && cortar) {   
        nat pHijo = 2*pos;

        if (cp->tope >= 2*pos + 1 && cp->arreglo[2*pos+1]->prioridad < cp->arreglo[2*pos]->prioridad)
            pHijo = 2*pos + 1;

        // printf ("pri %2f\n", cp->arreglo[pos]->prioridad);
        // printf ("prio %2f\n", cp->arreglo[pHijo]->prioridad);

        if (cp->arreglo[pos]->prioridad > cp->arreglo[pHijo]->prioridad) {
            // printf ("hijo %d \n", cp->arreglo[pHijo]->dato);
            // printf ("pos %d \n", cp->arreglo[pos]->dato);
            // printf ("hijo %d\n", cp->posiciones[cp->arreglo[pHijo]->dato]);
            // printf ("pos %d\n", cp->posiciones[cp->arreglo[pos]->dato]);

            NodoElem swap = cp->arreglo[pos];
            cp->arreglo[pos] = cp->arreglo[pHijo];
            cp->arreglo[pHijo] = swap;

            // printf ("hijo %d\n", cp->arreglo[pHijo]->dato);
            // printf ("pos %d\n", cp->arreglo[pos]->dato);
            // printf ("pri %2f\n", cp->arreglo[pos]->prioridad);
            // printf ("prio %2f\n", cp->arreglo[pHijo]->prioridad);
            // cp->posiciones[cp->arreglo[pos]->dato] = pos;
            // cp->posiciones[cp->arreglo[pHijo]->dato] = pHijo;
            // printf ("hijo %d\n", cp->posiciones[cp->arreglo[pHijo]->dato]);
            // printf ("pos %d\n", cp->posiciones[cp->arreglo[pos]->dato]);
            pos = pHijo;
        } else 
            cortar = false;
    
    }
    return cp;
}

//si es menor la raiz voy a 2i+1, sino a 2i
//para atras i/2

TColaDePrioridad insertarEnCP(nat elem, double valor, TColaDePrioridad cp) {
    // assert (1 <= elem && elem <= rangoCP(cp) && !estaEnCP(elem, cp));
    cp->tope = cp->tope + 1;
    cp->arreglo[cp->tope] = new elemento;
    cp->arreglo[cp->tope]->dato = elem;
    cp->arreglo[cp->tope]->prioridad = valor;
    cp->posiciones[elem] = cp->tope;
    cp = filtradoAscendente(cp, cp->tope);
    return cp;
}

bool estaVaciaCP(TColaDePrioridad cp) {
    return cp->tope == 0;
}

nat prioritario(TColaDePrioridad cp) {
    assert (!estaVaciaCP(cp));
    return cp->arreglo[1]->dato;
}

TColaDePrioridad eliminarPrioritario(TColaDePrioridad cp) {
    assert (!estaVaciaCP(cp));
    // printf ("pri %d\n", cp->posiciones[cp->arreglo[1]->dato]);
    // printf ("tope %d\n", cp->posiciones[cp->arreglo[cp->tope]->dato]);
    // printf ("PRIORITARIO %d\n", prioritario(cp));
    
    NodoElem swap = cp->arreglo[1];
    cp->arreglo[1] = cp->arreglo[cp->tope];
    cp->arreglo[cp->tope] = swap;

    delete cp->arreglo[cp->tope];
    // printf ("PRIORITARIO %d\n", prioritario(cp));

    // printf ("pri %d\n", cp->posiciones[cp->arreglo[1]->dato]);
    // printf ("tope %d\n", cp->posiciones[cp->arreglo[cp->tope]->dato]);

    // cp->posiciones[cp->arreglo[cp->tope]->dato] = 1;

    // cp->posiciones[cp->arreglo[cp->tope]->dato] = 0;
    // cp->arreglo[cp->tope]->dato = 0;
    // cp->arreglo[cp->tope]->prioridad = 0;
    // delete cp->arreglo[cp->tope];
    cp->tope--;
    if(cp->tope > 1) 
        cp = filtradoDescendente(cp, 1);
    
    return cp;
}

bool estaEnCP(nat elem, TColaDePrioridad cp) {
    return (cp->posiciones[elem] <= cp->tope && cp->posiciones[elem] != 0);
}

double prioridad(nat elem, TColaDePrioridad cp) {
    assert (estaEnCP(elem, cp));
    return cp->arreglo[cp->posiciones[elem]]->prioridad;
}

TColaDePrioridad actualizarEnCP(nat elem, double valor, TColaDePrioridad cp) {
    assert (estaEnCP(elem, cp));
    nat pos = cp->posiciones[elem];
    double valorAnt = cp->arreglo[pos]->prioridad;
    cp->arreglo[pos]->prioridad = valor;
    if (valor > valorAnt)
        cp = filtradoDescendente (cp, pos);
    else  if (valor < valorAnt)
        cp = filtradoAscendente (cp, pos);

    return cp;
}

void liberarCP(TColaDePrioridad cp) {
    for (nat i = 1; i <= cp->tope; i++) 
        delete cp->arreglo[i];
    delete [] cp->arreglo;
    delete [] cp->posiciones;
    delete cp;
}
