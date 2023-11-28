//
// Created by AntonioJR on 25/11/2023.
//

#include "ThashAerop.h"
ThashAerop::ThashAerop(): tamalog(0),tamafis(0),nCols(0),nMax10Cols(0),
                          nMaxCols(0),tmRedisp(0),tabla(0),primoMen(0) {}
/**
 * @brief Constructor copia
 * @param origen
 */
ThashAerop::ThashAerop(const ThashAerop &origen): tamalog(origen.tamalog),tamafis(origen.tamafis),nCols(origen.nCols),nMax10Cols(origen.nMax10Cols),
                                                    nMaxCols(origen.nMaxCols),tmRedisp(origen.tmRedisp),tabla(origen.tabla),primoMen(origen.primoMen){}
/**
 * @brief Destructor
 */
ThashAerop::~ThashAerop() {}

/**
 * @brief Funcion de dispersion cuadratica
 * @param clave
 * @param intento
 * @return
 */
unsigned int ThashAerop::hash1(unsigned long clave, int intento) {
    unsigned int hx;
    hx = (clave+(intento*intento)) % tamafis;
    return hx;
}
/**
 * @brief Funcion de dispersion doble
 * @param clave
 * @param intento
 * @return
 */
unsigned int ThashAerop::hash2(unsigned long clave, int intento) {
    unsigned int h1x,h2x,hx;
    //Obtenemos la posicion del dato
    h1x = clave % tamafis;
    //Calculo q<que eltamaño en primMenor
    //Todo por probar
    //Esto para evitar agrupamientos primarios y secundario
    h2x = primoMen -(clave%primoMen);
    //Calculamos con la funcion de dispersion doble
    hx = (h1x + intento * h2x) % tamafis;
    //Devolvemos el calculo
    return  hx;
}

/**
 * @brief Funcion de dispersion doble 2
 * @param clave
 * @param intento
 * @return
 */
unsigned int ThashAerop::hash3(unsigned long clave, int intento) {
    unsigned int h1x,h2x,hx;
    //Obtenemos la posicion del dato
    h1x = clave % tamafis;
    //Calculo q<que eltamaño en primMenor
    //Todo por probar
    //Esto para evitar agrupamientos primarios y secundario
    h2x = (10+(clave % (primoMen)));
    //Calculamos con la funcion de dispersion doble
    hx = (h1x + intento * h2x) % tamafis;
    //Devolvemos el calculo
    return  hx;
}

/**
 * @brief Funcion para ver si un numero es primo
 * @param numero
 * @return
 */
bool ThashAerop::esPrimo(int numero) {
    int i=2;
    //Para que sea primo tiene que ser distinto de 1 y de 0
    if(numero <=1){
        //Mientras el numero su resto no sea cero
        //Buscare si es divisible
        while (numero%i!=0){
            i++;
        }
        return (i==numero);
    }
    else {
        return false;
    }
}
/**
 * @brief Funcion donde obtienes el primo menor de la tabla
 * @param numero
 * @return
 */
int ThashAerop::qPrimoT(int tamanoFisico,bool menorOmayor) {
    if (menorOmayor){
        while (!esPrimo(tamanoFisico)) {
            tamanoFisico--;
        }
        return tamanoFisico;
    }else{
        while (!esPrimo(tamanoFisico)) {
            tamanoFisico++;
        }
        return tamanoFisico;
    }
}

ThashAerop::ThashAerop(int maxElementos, float lambda):tabla(tamafis,Entrada()),tamalog(0),tamafis(0),nCols(0),nMax10Cols(0),
                                                       nMaxCols(0),tmRedisp(0){
    tamafis = qPrimoT(maxElementos/lambda, false);
    primoMen= qPrimoT(tamafis, true);
    
}

unsigned long ThashAerop:: djb2(unsigned char *str) {
    unsigned long hash = 5381;
    int c;
    while (c = *str++) hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

bool ThashAerop::insertar(unsigned long clave, const Aeropuerto &aeropuerto) {
    int colisiones=0;
    int pos;
    bool encontrado= false;
    while(!encontrado){
        pos= hash3(clave,colisiones);
        if(tabla[pos].estado==LIBRE || tabla[pos].estado==DISPONIBLE){
            encontrado = true;
            tamalog++;
            tabla[pos].dato=aeropuerto;
            tabla[pos].clave=clave;
            tabla[pos].estado=OCUPADA;
            tabla[pos].iata=aeropuerto.getIata();
        }
    }

}
