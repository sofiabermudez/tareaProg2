/*5022788*/

#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

struct nodoCadena {
    TInfo dato;
    TLocalizador anterior;
    TLocalizador siguiente;
};

struct _rep_cadena {
    TLocalizador inicio;
    TLocalizador final;
};

bool esLocalizador(TLocalizador loc){
    return loc != NULL;
}

TCadena crearCadena(){
    TCadena res = new _rep_cadena;
    res->inicio = res->final = NULL;
    return res;
}

void liberarCadena(TCadena cad){
    TLocalizador aBorrar;
    while (cad->inicio != NULL) {
        aBorrar = cad->inicio;
        cad->inicio = cad->inicio->siguiente;
        liberarInfo(aBorrar->dato);
        delete aBorrar;
    }
    delete cad;
}

bool esVaciaCadena(TCadena cad){
    return cad->inicio == NULL;
}

TLocalizador inicioCadena(TCadena cad){
    //TLocalizador res;
    if (esVaciaCadena(cad)){
        return NULL;
    } else {
        return cad->inicio;
    }
}

TLocalizador finalCadena(TCadena cad){
    if (esVaciaCadena(cad)){
        return NULL;
    } else {
        return cad->final;
    }
}

TInfo infoCadena(TLocalizador loc, TCadena cad){
    assert(localizadorEnCadena(loc, cad));
    return loc->dato;
}

TLocalizador siguiente(TLocalizador loc, TCadena cad){
    assert(localizadorEnCadena(loc, cad));
    if (esFinalCadena(loc, cad)){
        return NULL;
    } else{
        return loc->siguiente;
    }
}

TLocalizador anterior(TLocalizador loc, TCadena cad){
    assert(localizadorEnCadena(loc, cad));
    if (esInicioCadena(loc, cad)){
        return NULL;
    } else{
        return loc->anterior;
    }
}

bool esFinalCadena(TLocalizador loc, TCadena cad){
    if (esVaciaCadena(cad)){
        return false;
    } else{
        return loc == finalCadena(cad);
    }
}

bool esInicioCadena(TLocalizador loc, TCadena cad){
    if (esVaciaCadena(cad)){
        return false;
    } else{
        return loc == inicioCadena(cad);
    }}

TCadena insertarAlFinal(TInfo i, TCadena cad){
    TLocalizador locAux = new nodoCadena;
    locAux -> dato = i;
    if (esVaciaCadena(cad)){
        cad->inicio = locAux;
        cad->final = locAux;
        locAux->siguiente = NULL;
        locAux->anterior = NULL;
    } else {
        cad->final->siguiente = locAux;
        locAux->anterior = cad->final;
        cad->final = locAux;
        locAux->siguiente = NULL;
    }
    // Creo que esas 2 lineas no son necesarias, sin ellas no hay perdida de memoria.
    // locAux = NULL;
    // delete locAux;
    return cad;
}

TCadena insertarAntes(TInfo i, TLocalizador loc, TCadena cad){
    assert(localizadorEnCadena(loc, cad));
    TLocalizador aInsertar = new nodoCadena;
    aInsertar->dato = i; 

    if (esInicioCadena(loc, cad)){
        cad->inicio->anterior = aInsertar;
        aInsertar->siguiente = cad->inicio;
        cad->inicio = aInsertar;
        aInsertar->anterior = NULL;

    } else {
        loc->anterior->siguiente = aInsertar;
        aInsertar->anterior = loc->anterior;
        loc->anterior = aInsertar;
        aInsertar->siguiente = loc;
    }
    // aInsertar = NULL;
    // delete aInsertar;
    return cad;
}

TCadena removerDeCadena(TLocalizador loc, TCadena cad){
    assert(localizadorEnCadena(loc, cad));

    if (esInicioCadena(loc, cad) && esFinalCadena(loc, cad)){ 
        //si es el unico elemento
        cad->inicio = NULL;
        loc->siguiente = NULL;
        cad->final = NULL;
        loc->anterior = NULL;

    } else if (esInicioCadena(loc, cad)){
        cad->inicio = cad->inicio->siguiente;
        cad->inicio->anterior = NULL;
        loc->siguiente = NULL;

    } else if (esFinalCadena(loc, cad)){
        cad->final = cad->final->anterior;
        cad->final->siguiente = NULL;
        loc->anterior = NULL;

    } else {
        loc->anterior->siguiente = loc->siguiente;
        loc->siguiente->anterior = loc->anterior;
        loc->siguiente = NULL;
        loc->anterior = NULL;
        
    }
    liberarInfo(loc->dato);
    delete loc;
    return cad;
}

void imprimirCadena(TCadena cad){

    if (!esVaciaCadena(cad)){
        TLocalizador locAux = inicioCadena(cad);
        while (locAux != NULL){
            printf("(%d,%.2f)", natInfo(locAux->dato), realInfo(locAux->dato));
            locAux = siguiente(locAux, cad);
        }
    }    
    // } else {
    //     printf("\n");
    // }
    printf("\n");
}

TLocalizador kesimo(nat k, TCadena cad){
    nat contador = 1;
    TLocalizador res = NULL;

    // creo que no es necesario chequear si la cadena es vacía
    if (!esVaciaCadena(cad) && k > 0 ) { 

        TLocalizador locAux = inicioCadena(cad);

        while (!esFinalCadena(locAux, cad) && k > contador) {
            contador++;
            locAux = siguiente(locAux, cad);
                  
        }
        if(k == contador){
            res = locAux;
        }
    }
    return res;
}

bool localizadorEnCadena(TLocalizador loc, TCadena cad){
    bool res = false;
    if (!esVaciaCadena(cad)) {
        TLocalizador locAux = inicioCadena(cad);
        while (!esFinalCadena(locAux, cad) && (locAux != loc)) {
                locAux = siguiente(locAux, cad);
        }
        res = (loc == locAux);
    }
    
    return res;
}

bool precedeEnCadena(TLocalizador loc1, TLocalizador loc2, TCadena cad){
    bool res = false;

    if (!esVaciaCadena(cad)) {
        if (loc1 == loc2){
            res = true;
        }else{
            TLocalizador cursor = inicioCadena (cad);
            while(cursor != loc1 && cursor != loc2 && !esFinalCadena(cursor, cad)){
                cursor = siguiente(cursor, cad);
            }
            if (cursor == loc1){
                while(cursor != loc2 && !esFinalCadena(cursor, cad)){
                    cursor = siguiente(cursor, cad);
                }

                res = (cursor==loc2);
            } else {
                res = false;
            }
                
        }
    }
    return res;
}

TCadena insertarSegmentoDespues(TCadena sgm, TLocalizador loc, TCadena cad){
    assert(esVaciaCadena(cad) || localizadorEnCadena(loc, cad));

    if (!esVaciaCadena(sgm)){
        if (esVaciaCadena(cad)){
            // cad = sgm;
            cad->inicio = inicioCadena(sgm);
            cad->final = finalCadena(sgm);

        // si esta en el inicio loc, se inserta despues de loc, no antes
        // } else if(esInicioCadena(loc, cad)){
        //     TLocalizador locAux = inicioCadena(cad);

        //     inicioCadena(cad)->anterior = finalCadena(sgm);
        //     finalCadena(sgm)->siguiente = locAux;
        //     cad->inicio = inicioCadena(sgm);

        //     delete locAux;

        } else if(esFinalCadena(loc, cad)){

            finalCadena(cad)->siguiente = inicioCadena(sgm);
            inicioCadena(sgm)->anterior = finalCadena(cad);
            cad->final = finalCadena(sgm);

        } else{

            // TLocalizador locAux = siguiente(loc, cad);

            siguiente(loc, cad)->anterior = finalCadena(sgm);
            finalCadena(sgm)->siguiente = siguiente(loc, cad);
           
            loc->siguiente = inicioCadena(sgm);
            inicioCadena(sgm)->anterior = loc;            

        }
        sgm->inicio = NULL;
        sgm->final = NULL;
        delete sgm;
    
    } else {
        delete sgm;
    }

    return cad;
}

TCadena copiarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad){
    assert(esVaciaCadena(cad) || precedeEnCadena(desde, hasta, cad));

    TCadena res = crearCadena();

    if (!esVaciaCadena(cad)){

        if (desde == hasta){
            insertarAlFinal(copiaInfo(infoCadena(desde, cad)), res);
        } else {
            TLocalizador locAux = desde;

            while (locAux != hasta){
                insertarAlFinal(copiaInfo(infoCadena(locAux, cad)), res);
                locAux = siguiente(locAux, cad);
            }

            insertarAlFinal(copiaInfo(infoCadena(locAux, cad)), res);
        }

    }
    return res;

}

TCadena borrarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad){
    assert(esVaciaCadena(cad) || precedeEnCadena(desde, hasta, cad));

    if (!esVaciaCadena(cad)){

        // if (desde == hasta){
        //     removerDeCadena(desde, cad);
        // } else {
            TLocalizador locAux = desde;

            while (locAux != hasta){
                TLocalizador aux = siguiente(locAux, cad);
                removerDeCadena(locAux, cad);
                locAux = aux;
            }
            removerDeCadena(locAux, cad);

    }
    return cad;

}

TCadena cambiarEnCadena(TInfo i, TLocalizador loc, TCadena cad){
    assert(localizadorEnCadena(loc, cad));
    loc->dato = i;
    return cad;
}

TCadena intercambiar(TLocalizador loc1, TLocalizador loc2, TCadena cad){
    assert(localizadorEnCadena (loc1, cad) && localizadorEnCadena (loc2, cad));

    TInfo datoLoc = loc1->dato;
    
    loc1->dato = loc2->dato;
    loc2->dato = datoLoc;
 
    return cad;
}

TLocalizador siguienteClave(nat clave, TLocalizador loc, TCadena cad){
    assert(esVaciaCadena(cad) || localizadorEnCadena(loc, cad));

    TLocalizador res = NULL;

    if (!esVaciaCadena(cad)){
        while(!esFinalCadena(loc, cad) && natInfo(infoCadena(loc, cad)) != clave ){
            loc = siguiente(loc, cad);
        }

        if (!esFinalCadena(loc, cad) || natInfo(infoCadena(loc, cad)) == clave) {
            res = loc;
        }
    }
  
    return res;
}

TLocalizador anteriorClave(nat clave, TLocalizador loc, TCadena cad){
    assert(esVaciaCadena(cad) || localizadorEnCadena(loc, cad));

    TLocalizador res = NULL;

    if (!esVaciaCadena(cad)){
        while(natInfo(infoCadena(loc, cad)) != clave && !esInicioCadena(loc, cad)){
            loc = anterior(loc, cad);
        }

        if (!esInicioCadena(loc, cad) || natInfo(infoCadena(loc, cad)) == clave) {
            res = loc;
        }
    }
  
    return res;
}

TLocalizador menorEnCadena(TLocalizador loc, TCadena cad){
    assert(localizadorEnCadena(loc, cad));
    
    TLocalizador locAux = loc;

    while (loc != NULL){

        if (natInfo(infoCadena(loc, cad)) < natInfo(infoCadena(locAux, cad))){
            locAux = loc;
        }

        loc = siguiente(loc, cad);
    }    

    return locAux;
}