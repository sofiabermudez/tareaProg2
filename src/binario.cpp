/*5022788*/

#include "../include/info.h"
#include "../include/utils.h"
#include "../include/cadena.h"
#include "../include/binario.h"
#include "../include/avl.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

struct _rep_binario {
    TInfo raiz;
    TBinario derecho;
    TBinario izquierdo;
}; 

TBinario avlABinario(TAvl a) {
    TBinario res = crearBinario();

    if (a == NULL) {
        res = NULL;

    } else {
        TInfo dato = crearInfo(raizAvl(a), 0); 
        res = new _rep_binario;
        res->raiz = dato;
        res->derecho = avlABinario(derAvl(a));
        res->izquierdo = avlABinario(izqAvl(a));
    }
    return res;
}

TBinario binarioBalanceadoAux(ArregloNats elems, int prim, int ult) {
    TBinario res = crearBinario();

    if ((prim > 0) && (ult-prim)>=0) {
        nat mitad = (ult-prim)/2 + prim; 
        TInfo info = crearInfo(elems[mitad-1], 0);
        res = new _rep_binario;
        res->raiz = info;
        
        res->derecho = binarioBalanceadoAux(elems, mitad + 1, ult);
        res->izquierdo = binarioBalanceadoAux(elems, prim, mitad-1);
    }

    return res;
}

TBinario binarioBalanceado(ArregloNats elems, nat n){
    assert (n > 0); 
    TBinario res = crearBinario();
    res = binarioBalanceadoAux(elems, 1, n);

    return res;
}


TBinario crearBinario(){ return NULL; }


TBinario insertarEnBinario(TInfo i, TBinario b){
    assert(esVacioBinario(buscarSubarbol(natInfo(i), b)));

    if(b == NULL){

        TBinario nuevo = new _rep_binario;
        nuevo->raiz = i;
        nuevo->derecho = nuevo->izquierdo = NULL;

        b = nuevo;

        // b = new _rep_binario;
        // b->raiz = i;
        // b->derecho = b->izquierdo = NULL;

        // nuevo = NULL;
        // delete nuevo;
        
    } else {
        if (natInfo(b->raiz) > natInfo(i)){
            b->izquierdo = insertarEnBinario(i, b->izquierdo);

        } else{
            b->derecho = insertarEnBinario(i, b->derecho);
        }
    }
    
    return b;
}

TInfo mayor(TBinario b){
    assert(!esVacioBinario(b));

    TInfo res;
    
    if (derecho(b) != NULL) {
        res = mayor(derecho(b));

    } else {
        res = raiz(b);
    }

    return res;
}

TBinario removerMayor(TBinario b){
    assert(!esVacioBinario(b));
    
    if (derecho(b) == NULL) {
        if(esVacioBinario(izquierdo(b))){
            delete b;
            b=NULL;
        
        }else{
            TBinario aBorrar = b;
            b = izquierdo(b);
            delete aBorrar;
            // NO ES NECESARIO LIBERAR INFO PORQUE LO HACER PRINCIPAL
            // EN REMOVER DE BINARIO NO LO HACE PRINCIPAL
        }  

    } else {
        b->derecho = removerMayor(derecho(b));
    }

    return b;
}

TBinario removerDeBinario(nat elem, TBinario b){
    assert(!esVacioBinario(buscarSubarbol(elem, b)));

    if (natInfo(b->raiz) < elem){
        b->derecho = removerDeBinario(elem, b->derecho);

    }else if (natInfo(b->raiz) > elem){
        b->izquierdo = removerDeBinario(elem, b->izquierdo);

    } else{
        if (esVacioBinario(izquierdo(b)) && esVacioBinario(derecho(b))){
            liberarInfo(raiz(b));
            delete b;
            b = NULL;

        }else if (esVacioBinario(izquierdo(b))) {        
            TBinario aBorrar = b;
            b = derecho(b);
            liberarInfo(raiz(aBorrar));
            delete aBorrar;

        } else if(esVacioBinario(derecho(b))) {
            TBinario izq = b;
            b = izquierdo(b);
            liberarInfo(raiz(izq));
            delete izq;

    // LIBERO LA INFO ANTES DE ELIMINARLO

        } else {
            liberarInfo(raiz(b));
            b->raiz = mayor(izquierdo(b));
            b->izquierdo = removerMayor(izquierdo(b));
        }
    }

    return b;
}

void liberarBinario(TBinario b){
    if (b != NULL){
        liberarBinario (derecho(b));
        liberarBinario (izquierdo(b));
        liberarInfo(raiz(b));
  
    }
    delete b;
}

bool esVacioBinario(TBinario b){
    return b == NULL;
}

bool esAvlAux(nat &altura, TBinario b){
    bool res = true; 

    if (!esVacioBinario(b)){
        nat alturaDer = altura;
        nat alturaIzq = altura;

        if (esVacioBinario(derecho(b)) && esVacioBinario(izquierdo(b))){
            altura++;

        } else if (!esVacioBinario(derecho(b)) && !esVacioBinario(izquierdo(b))){

            res = (esAvlAux(alturaDer, derecho(b)) && esAvlAux(alturaIzq, izquierdo(b))
                    && ((((alturaIzq - alturaDer) < 2) && (alturaDer <= alturaIzq))
                        || ((alturaDer - alturaIzq) < 2 && (alturaIzq < alturaDer))) );
                
            if(alturaIzq < alturaDer){
                altura = alturaDer + 1;
            }else{
                altura = alturaIzq + 1;
            }

        } else if (esVacioBinario(derecho(b)) && !esVacioBinario(izquierdo(b))){
            res = (esAvlAux(alturaIzq, izquierdo(b)) && ((alturaIzq ) < 2));
            altura = alturaIzq +1;

        } else if (!esVacioBinario(derecho(b)) && esVacioBinario(izquierdo(b))){
            res = (esAvlAux(alturaDer, derecho(b)) && ((alturaDer ) < 2));
            altura = alturaDer + 1;
        }  

    }
    return res;
}

bool esAvl(TBinario b){
    nat altura = 0;
    
    return esAvlAux(altura, b);
}

TInfo raiz(TBinario b){
    assert(!esVacioBinario(b));
    return b->raiz;
}

TBinario izquierdo(TBinario b){
    assert(!esVacioBinario(b));
    return b->izquierdo;
}

TBinario derecho(TBinario b){
    assert(!esVacioBinario(b));
    return b->derecho;
}

TBinario buscarSubarbol(nat elem, TBinario b){
    TBinario res = b;

    if(!esVacioBinario(b) && natInfo(raiz(b)) != elem){
        
        if (natInfo(b->raiz) > elem){
            res = buscarSubarbol(elem, b->izquierdo);
        } else{
            res = buscarSubarbol(elem, b->derecho);
        }
        
    }

    return res;
}

static nat alturaBinarioAux(nat altura, TBinario b){
    if (!esVacioBinario (b)){
        nat alturaDer = alturaBinarioAux(altura, derecho(b));
        nat alturaIzq = alturaBinarioAux(altura, izquierdo(b));
        
        if (alturaDer > alturaIzq){
            altura = alturaDer + 1;
        } else {
            altura = alturaIzq +1;
        }
    }
    return altura;
}

nat alturaBinario(TBinario b){
    return alturaBinarioAux(0, b);
}

static nat cantidadBinarioAux (nat cantidad, TBinario b){

    if (!esVacioBinario(b)){
        cantidad = 1 + cantidadBinarioAux(cantidad, derecho(b)) + cantidadBinarioAux(cantidad, izquierdo(b));
    }
    return cantidad;
}

nat cantidadBinario(TBinario b){

    return cantidadBinarioAux (0, b);
}

static double sumaUltimosPositivosAux (nat &i, TBinario b){
    double res = 0;

    if (!esVacioBinario(b) && i > 0) {

        res = res + sumaUltimosPositivosAux(i, derecho(b));

        if (realInfo(raiz(b)) > 0 && i > 0){
            res = res + realInfo(raiz(b));
            i--;
        }

        if (i > 0) {
            res = res + sumaUltimosPositivosAux(i, izquierdo(b));
        }
    }

    return res;
}

// static void contador (nat &cont){
//     cont--;
// }

//Me pide los ultimos elementos (los que tengan el natural mas grande)
// y ademaslos reales sean positivos

double sumaUltimosPositivos(nat i, TBinario b){

    return sumaUltimosPositivosAux(i, b);
    
}

TCadena linealizacionAux(TBinario b, TCadena &cad) {
    if (!esVacioBinario(b)){
        linealizacionAux (izquierdo(b), cad);
        insertarAlFinal(copiaInfo(raiz(b)), cad);
        linealizacionAux (derecho(b), cad);
    }
    return cad;
}

TCadena linealizacion(TBinario b){
    TCadena res = crearCadena();

    if (!esVacioBinario(b)){
        // if (esVacioBinario(izquierdo(b)) && esVacioBinario(derecho(b))) {
        //     res = insertarAlFinal(copiaInfo(mayor(b)), res);

        // } else {
            
        res = insertarSegmentoDespues(linealizacion(izquierdo(b)), finalCadena(res), res);
        res = insertarAlFinal(copiaInfo(raiz(b)), res);
        res = insertarSegmentoDespues(linealizacion(derecho(b)), finalCadena(res), res);
    

    }
    // linealizacionAux(b, res);
    return res;
}

TBinario menores(double cota, TBinario b){
    TBinario res = crearBinario();

    if(!esVacioBinario(b)){
        TBinario menDer = menores(cota, derecho(b));
        TBinario menIzq = menores(cota, izquierdo(b));

        if(realInfo(raiz(b)) < cota){
            res = insertarEnBinario(copiaInfo(raiz(b)), res);
            res->izquierdo = menIzq;
            res->derecho = menDer;

        } else if (esVacioBinario(menDer)) {
            res = menIzq;

        } else if (esVacioBinario(menIzq)) {
            res = menDer;

        // cuando la raiz no entra en menores
        } else{
            res = insertarEnBinario(copiaInfo(mayor(menIzq)), res);
            //res->raiz = mayor(izquierdo(b));

            res->izquierdo = removerMayor(menIzq);
            res->derecho = menDer;
        }
    }

    return res;
}

static void imprimirBinarioAux(nat prof, TBinario b) {

    if(b != NULL){
        
        if (derecho(b) != NULL){
            imprimirBinarioAux(prof+1, derecho(b));
        } 
        
        nat guion = prof;
        while (guion != 0 ){
            printf ("-");
            guion--;
        }

        printf("(%d,%.2f)", natInfo(b->raiz), realInfo(b->raiz));
            printf("\n");


        if (izquierdo(b) != NULL){
            imprimirBinarioAux(prof+1, izquierdo(b));
        }

    } 

}

void imprimirBinario(TBinario b){

    printf("\n");
    imprimirBinarioAux(0,  b);

}