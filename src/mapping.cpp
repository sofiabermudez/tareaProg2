/*5022788*/

#include "../include/info.h"
#include "../include/utils.h"
#include "../include/cadena.h"
#include "../include/mapping.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

struct _rep_mapping {
    TCadena * arreglo;
    nat cantElem;
    nat tamanio;
};

TMapping crearMap(nat M) {
    TMapping res = new _rep_mapping;
    res->arreglo = new TCadena[M];
    for (nat i = 0; i < M; i++) {
        res->arreglo[i] = crearCadena();
    }
    res->cantElem = 0;
    res->tamanio = M;
    return res;
}

nat hash_pos (nat clave, nat tope) {
    return (clave % tope);
}

TMapping asociarEnMap(nat clave, double valor, TMapping map) {
    assert (!estaLlenoMap(map) && !existeAsociacionEnMap(clave, map));
    nat pos = hash_pos(clave, map->tamanio);
    TInfo dato = crearInfo(clave, valor);
    map->arreglo[pos] = insertarAlFinal(dato, map->arreglo[pos]);
    map->cantElem++;
    return map;
}

TMapping desasociarEnMap(nat clave, TMapping map) {
    assert (existeAsociacionEnMap(clave, map));
    nat pos = hash_pos(clave, map->tamanio);
    map->arreglo[pos] = removerDeCadena(inicioCadena(map->arreglo[pos]), map->arreglo[pos]);
    map->cantElem--;
    return map;
}

bool existeAsociacionEnMap(nat clave, TMapping map) {
    // return (siguienteClave(clave, inicioCadena(map->arreglo[clave]), map->arreglo[clave]) != NULL);
    nat pos = hash_pos(clave, map->tamanio);
    
    // bool res = false;
    TLocalizador locAux = inicioCadena(map->arreglo[pos]);
    // while (locAux != NULL && !res) {
    //     if(natInfo(infoCadena(locAux, map->arreglo[pos])) == clave) {
    //         res = true;
    //     } else {
    //         locAux = siguiente(locAux, map->arreglo[pos]);
    //     }
    // }

    return siguienteClave(clave, locAux, map->arreglo[pos]) != NULL;

    // return inicioCadena(map->arreglo[clave]) != NULL;

}

double valorEnMap(nat clave, TMapping map) {
    assert (existeAsociacionEnMap(clave, map));
    nat pos = hash_pos(clave, map->tamanio);

    TLocalizador locAux = inicioCadena(map->arreglo[pos]);
    // while (locAux != NULL && natInfo(infoCadena(locAux, map->arreglo[pos])) != clave) {
    //     locAux = siguiente(locAux, map->arreglo[pos]);
        
    // }

    locAux = siguienteClave(clave, locAux, map->arreglo[pos]);
    return realInfo(infoCadena(locAux, map->arreglo[pos]));
}

bool estaLlenoMap(TMapping map) {
    return map->cantElem == map->tamanio;
}

void liberarMap(TMapping map) {
    for (nat i = 0; i < map->tamanio; i++) {
        liberarCadena(map->arreglo[i]);
    }
    delete [] map->arreglo;
    delete map;
}
