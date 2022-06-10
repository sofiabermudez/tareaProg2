/*5022788*/

#include "../include/info.h"
#include "../include/utils.h"
#include "../include/cadena.h"
#include "../include/usoTads.h"
#include "../include/cadena.h"
#include "../include/binario.h"
#include "../include/pila.h"
#include "../include/colaBinarios.h"
#include "../include/avl.h"
#include "../include/conjunto.h"

#include <limits.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

TConjunto interseccionDeConjuntos(TConjunto c1, TConjunto c2) {
    //a-(a-b)
    TConjunto conjRes = crearConjunto();
    TConjunto aux = diferenciaDeConjuntos(c1, c2);
    conjRes = diferenciaDeConjuntos(c1, aux);
    liberarConjunto(aux);
    return conjRes;
}

nat cantidadEnIterador(TIterador it){
    nat contador = 0;
    it = reiniciarIterador(it);
    while (estaDefinidaActual(it)) {
        contador++;
        it = avanzarIterador(it);
    }
    return contador;
} 

TIterador enAlguno(TIterador a, TIterador b) {
    TIterador res = crearIterador();
    a = reiniciarIterador(a);
    b = reiniciarIterador(b);

    while (estaDefinidaActual(a) && estaDefinidaActual(b)) {
        if (actualEnIterador(a) > actualEnIterador(b)) {
            res = agregarAIterador(actualEnIterador(b), res);
            b = avanzarIterador(b);
        } else if (actualEnIterador(a) < actualEnIterador(b)) {
            res = agregarAIterador(actualEnIterador(a), res);
            a = avanzarIterador(a);
        } else {
            res = agregarAIterador(actualEnIterador(a), res);
            b = avanzarIterador(b);
            a = avanzarIterador(a);
        }
    }

    while (estaDefinidaActual(a)) {
        res = agregarAIterador(actualEnIterador(a), res);
        a = avanzarIterador(a);
    }

    while (estaDefinidaActual(b)) {
        res = agregarAIterador(actualEnIterador(b), res);
        b = avanzarIterador(b);
    }
    
    return res;
}

TIterador soloEnA(TIterador a, TIterador b) {
    TIterador res = crearIterador();
    a = reiniciarIterador(a);
    b = reiniciarIterador(b);

    while (estaDefinidaActual(a) && estaDefinidaActual(b)) {
        if (actualEnIterador(a) > actualEnIterador(b)) {
            b = avanzarIterador(b);
        } else if (actualEnIterador(a) < actualEnIterador(b)) {
            res = agregarAIterador(actualEnIterador(a), res);
            a = avanzarIterador(a);
        } else {
            b = avanzarIterador(b);
            a = avanzarIterador(a);
        }
    }
    
    while (estaDefinidaActual(a)) {
        res = agregarAIterador(actualEnIterador(a), res);
        a = avanzarIterador(a);
    }

    return res;
}

TIterador recorridaPorNiveles(TBinario b) {
    TIterador res= crearIterador();
    if (!esVacioBinario(b)) {
    
        nat tamanio = cantidadBinario(b) + alturaBinario(b);

        TPila pila = crearPila (tamanio);
        TColaBinarios cola = crearColaBinarios();
        cola = encolar(b, cola);
        cola = encolar(NULL, cola);
        // pila = apilar(natInfo(raiz(b)), pila);
        // pila = apilar(UINT_MAX, pila);

        while (!estaVaciaColaBinarios(cola)) {
            b = frente(cola);
            cola = desencolar(cola);

            if (b == NULL && !estaVaciaColaBinarios(cola)) {
                cola = encolar (NULL, cola);
                pila = apilar(UINT_MAX, pila);

            } else if (b!=NULL){
                pila = apilar(natInfo(raiz(b)), pila);
                if (derecho(b) != NULL){
                    cola = encolar (derecho(b), cola);
                }
                if (izquierdo(b) != NULL){
                    cola = encolar (izquierdo(b), cola);
                }
            }
        }
        liberarColaBinarios(cola);

        while(!estaVaciaPila(pila)) {
            res = agregarAIterador(cima(pila), res);
            pila = desapilar(pila);
        }
        liberarPila(pila);
    }
    return res;
}


static TCadena nivelEnBinarioAux(nat l, TBinario b, nat nivel){
    TCadena res = crearCadena();

    if(!esVacioBinario(b)){
        if(nivel == l){
            res = insertarAlFinal(copiaInfo(raiz(b)), res);

        }else if(nivel < l){
            res = insertarSegmentoDespues(nivelEnBinarioAux(l, izquierdo(b), nivel+1), finalCadena(res), res);
            res = insertarSegmentoDespues(nivelEnBinarioAux(l, derecho(b), nivel+1), finalCadena(res), res);
        }
    }
    return res;
}

TCadena nivelEnBinario(nat l, TBinario b){ 
    assert(l > 0);
    return nivelEnBinarioAux(l, b, 1);
}


bool esCamino(TCadena c, TBinario b){
    bool res = true; //(alturaBinario(b) >= longitud(c)) ;

    if (!esVaciaCadena(c) && !esVacioBinario(b) && (alturaBinario(b) >= longitud(c))){

        if (natInfo(raiz(b)) == natInfo(infoCadena(inicioCadena(c), c))){


            // if (derecho(b) == NULL && izquierdo(b) == NULL && siguiente(inicioCadena(c), c) == NULL){
            //     res = true;

            if (siguiente(inicioCadena(c), c) != NULL && natInfo(raiz((b))) <= natInfo(infoCadena(siguiente(inicioCadena(c), c), c))){
                
                res = esCamino(removerDeCadena(inicioCadena(c), c), derecho(b));
                
                //res = esCamino(copiarSegmento(siguiente(inicioCadena(c), c), finalCadena(c), c), derecho(b));

            } else if (siguiente(inicioCadena(c), c) != NULL && natInfo(raiz((b))) >= natInfo(infoCadena(siguiente(inicioCadena(c), c), c))){

                res = esCamino(removerDeCadena(inicioCadena(c), c), izquierdo(b));
               
               // res = esCamino(copiarSegmento(siguiente(inicioCadena(c), c), finalCadena(c), c), izquierdo(b));

            } else if (derecho(b) != NULL || izquierdo(b) != NULL){
                res = false;
            }


        } else {
            res = false;
        }
    }else if (!esVaciaCadena(c) || !esVacioBinario(b) || (alturaBinario(b) >= longitud(c))){
        res = false;
    }

    return res;
}

bool pertenece(nat elem, TCadena cad){
    bool res = false;

    if (!esVaciaCadena(cad)){
        TLocalizador cursor = inicioCadena(cad);

        while (cursor != NULL && natInfo(infoCadena(cursor, cad)) != elem){
            cursor = siguiente(cursor, cad);
        }

        if(cursor != NULL){
            res = true;
        }
    }
    
    return res;
}

nat longitud(TCadena cad){
    nat res = 0;

    if (!esVaciaCadena(cad)){
        TLocalizador cursor = inicioCadena(cad);

        while (cursor != NULL){
            cursor = siguiente(cursor, cad);
            res++;
        }
    }
    return res;
}

bool estaOrdenadaPorNaturales(TCadena cad){
    bool res = true;

    if (!esVaciaCadena(cad) && longitud(cad) >= 2){

        TLocalizador aComparar1 = inicioCadena(cad);
        TLocalizador aComparar2 = siguiente(inicioCadena(cad), cad);

        while (aComparar2 != NULL && natInfo(infoCadena(aComparar1, cad)) <= natInfo(infoCadena(aComparar2, cad))) {
            aComparar1 = siguiente(aComparar1, cad);
            aComparar2 = siguiente(aComparar2, cad);
        }

        if (aComparar2 != NULL) {
            res = false;
        }

    }

    return res;
}

bool hayNatsRepetidos(TCadena cad){
    bool hayRep = false;

    if (!esVaciaCadena(cad) && longitud(cad) >= 2){

        TLocalizador cursor = inicioCadena (cad);

        while (cursor != NULL && !hayRep) {

            TLocalizador cursor2 = siguiente(cursor, cad);

            while (cursor2 != NULL && natInfo(infoCadena(cursor, cad)) != natInfo(infoCadena(cursor2, cad))){
                cursor2 = siguiente (cursor2, cad);
            }

            if (cursor2 == NULL){
                cursor = siguiente(cursor, cad);
            } else {
                hayRep = true;
            }
        }

    }

    return hayRep;
}

bool sonIgualesCadena(TCadena c1, TCadena c2){
    bool iguales = true;

    if (esVaciaCadena(c1) && esVaciaCadena(c2)){
        iguales = true;

    } else if (longitud(c1) != longitud(c2)){ //esVaciaCadena(c1) || esVaciaCadena(c2) 
        iguales = false;
    
    } else {
        TLocalizador cursor = inicioCadena (c1);
        TLocalizador cursor2 = inicioCadena(c2);

        while (cursor != NULL && 
        natInfo(infoCadena(cursor, c1)) == natInfo(infoCadena(cursor2, c2)) &&
        realInfo(infoCadena(cursor, c1)) == realInfo(infoCadena(cursor2, c2))) {
                cursor2 = siguiente (cursor2, c2);
                cursor = siguiente(cursor, c1);
        }

        if(cursor != NULL){
            iguales = false;
        }

    }
    return iguales;
}

TCadena concatenar(TCadena c1, TCadena c2){
    TCadena res;

    TCadena copiaC2 = copiarSegmento(inicioCadena(c2), finalCadena(c2), c2);

    if (!esVaciaCadena(c1)){
        TCadena copiaC1 = copiarSegmento(inicioCadena(c1), finalCadena(c1), c1);
         
        res = insertarSegmentoDespues(copiaC2, finalCadena(copiaC1), copiaC1);
    
    } else {
        res = copiaC2;
    }

    return res;
}

TCadena ordenar(TCadena cad){
    assert (!hayNatsRepetidos(cad));

    if (!esVaciaCadena(cad) && longitud(cad) >= 2){
        TLocalizador cursor1 = inicioCadena(cad);
        TLocalizador cursor2 = siguiente(inicioCadena(cad), cad);

        while(!esFinalCadena(cursor1, cad)){

            while(cursor2 != NULL){

                if (natInfo(infoCadena(cursor1, cad)) > natInfo(infoCadena(cursor2, cad))){
                    cad = intercambiar (cursor1, cursor2, cad);
                }
                cursor2 = siguiente(cursor2, cad);
            }

            cursor1 =  siguiente(cursor1, cad);
            cursor2 = siguiente(cursor1, cad);
        }
    }
    return cad;  
}


TCadena cambiarTodos(nat original, nat nuevo, TCadena cad){

    if (!esVaciaCadena(cad)){
        TLocalizador cursor = inicioCadena(cad);

        while(cursor != NULL){
            if (natInfo(infoCadena(cursor, cad)) == original){
                TInfo aCambiar = crearInfo(nuevo, realInfo(infoCadena(cursor, cad)));
               
                liberarInfo (infoCadena(cursor, cad));
               
                cad = cambiarEnCadena(aCambiar, cursor, cad);

            }
            cursor =  siguiente(cursor, cad);
        }

    }
    return cad;
}

TCadena subCadena(nat menor, nat mayor, TCadena cad){
    assert(estaOrdenadaPorNaturales (cad) && menor <= mayor && pertenece (menor, cad) && pertenece (mayor, cad));

    TCadena res = crearCadena();
    TLocalizador cursor = inicioCadena(cad);

    while (cursor != NULL){

        if (menor <= natInfo(infoCadena(cursor, cad)) && natInfo(infoCadena(cursor, cad)) <= mayor){
            
            TInfo aInsertar = crearInfo(natInfo(infoCadena(cursor, cad)), realInfo(infoCadena(cursor, cad)));
            res = insertarAlFinal(aInsertar, res);
        }
        cursor =  siguiente(cursor, cad);    
    }
    return res;
}