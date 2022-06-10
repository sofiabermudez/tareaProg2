/*5022788*/

#include "../include/info.h"
#include "../include/utils.h"
#include "../include/cadena.h"
#include "../include/usoTads.h"
#include "../include/colCadenas.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

// typedef struct nodo *NodoColCad;

// struct nodo {
//     TCadena elem;
//     NodoColCad siguiente;
// };

// typedef TCadena *ArregloCad;

struct _rep_colCadenas {
    TCadena* arreglo;
    nat largo;
};

TColCadenas crearColCadenas(nat M) {
    assert (M > 0);
    TColCadenas res = new _rep_colCadenas;
    res->arreglo = new TCadena[M];
    res->largo = M;
    for (nat i = 0; i < M; i++) {
        res->arreglo[i] = crearCadena();
    }
    return res;
}

TColCadenas insertarEnColCadenas(TInfo info, nat pos, TColCadenas col) {
    // assert(pos >= col->largo);
    assert(col->largo > pos);
    TCadena cad = col->arreglo[pos];
        
    if (esVaciaCadena(col->arreglo[pos])){
        col->arreglo[pos] = insertarAlFinal(info, col->arreglo[pos]);
        
    } else {
        col->arreglo[pos] = insertarAntes(info, inicioCadena(cad), cad);
    }
    return col;
}

bool estaEnColCadenas(nat dato, nat pos, TColCadenas col) {
    if (col->largo >= pos){
        TCadena cad = col->arreglo[pos];
        // TLocalizador aux = inicioCadena(cad);
        // while (natInfo(infoCadena(aux, cad)) != dato && aux != NULL) {
        //     aux = siguiente(aux, cad);
        // }
        // return natInfo(infoCadena(aux, cad)) == dato;
        return pertenece(dato, cad);
    } else {
        return false;
    }
}

TInfo infoEnColCadenas(nat dato, nat pos, TColCadenas col) {
    assert(estaEnColCadenas(dato, pos, col));
    
    TInfo res = NULL;
    TCadena cad = col->arreglo[pos];
    TLocalizador aux = inicioCadena(cad);

    while (aux != NULL && natInfo(infoCadena(aux, cad)) != dato) {
        aux = siguiente(aux, cad);    
    }
    res = infoCadena(aux, cad);
    return res;
}

TColCadenas removerDeColCadenas(nat dato, nat pos, TColCadenas col) {
    assert(estaEnColCadenas(dato, pos, col));

    TCadena cad = col->arreglo[pos];
    TLocalizador aux = inicioCadena(cad);

    while (natInfo(infoCadena(aux, cad)) != dato) {
        aux = siguiente(aux, cad);
    }
    cad = removerDeCadena(aux, cad);
    col->arreglo[pos] = cad;
    return col;
}

void liberarColCadenas(TColCadenas col) {
    for (nat i = 0; i < col->largo; i++) {
        liberarCadena(col->arreglo[i]);
    }
    delete [] col->arreglo;
    delete col;

}
