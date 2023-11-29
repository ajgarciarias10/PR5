//
// Created by AntonioJR on 25/11/2023.
//

#include "ThashAerop.h"
ThashAerop::ThashAerop(): tamlog(0),tamfis(0),sumaColisiones(0),max10(0),
                          maxColisiones(0),redisp(0),tabla(0),primoMen(0) {}
/**
 * @brief Constructor copia
 * @param origen
 */
ThashAerop::ThashAerop(const ThashAerop &origen): tamlog(origen.tamlog),tamfis(origen.tamfis),sumaColisiones(origen.sumaColisiones),max10(origen.max10),
                                                    maxColisiones(origen.maxColisiones),redisp(origen.redisp),tabla(origen.tabla),primoMen(origen.primoMen){}
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
    hx = (clave+(intento*intento)) % tamfis;
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
    h1x = clave % tamfis;
    //Calculo q<que eltamaño en primMenor
    //Todo por probar
    //Esto para evitar agrupamientos primarios y secundario
    h2x = primoMen -(clave%primoMen);
    //Calculamos con la funcion de dispersion doble
    hx = (h1x + intento * h2x) % tamfis;
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
    h1x = clave % tamfis;
    //Calculo q<que eltamaño en primMenor
    //Todo por probar
    //Esto para evitar agrupamientos primarios y secundario
    h2x = (10+(clave % (primoMen)));
    //Calculamos con la funcion de dispersion doble
    hx = (h1x + intento * h2x) % tamfis;
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
    if(numero>2){
        while(i<numero){
            if(numero%i==0){
                return false;
            }
            i++;
        }
        return true;
    }

}
/**
 * @brief Funcion donde obtienes el primo menor de la tabla
 * @param numero
 * @post si el bool es true se calcula el primo menor
 * @post si el bool es false se calcula el primo mayor
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

ThashAerop::ThashAerop(int maxElementos, float lambda):tabla(tamfis,Entrada()),tamlog(0),tamfis(0),sumaColisiones(0),max10(0),
                                                       maxColisiones(0),redisp(0){

    tamfis = qPrimoT(maxElementos/lambda, false);
    primoMen= qPrimoT(tamfis, true);
    
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
        //si esta libre o disponible metemos el dato
        if(tabla[pos].estado==LIBRE || tabla[pos].estado==DISPONIBLE){
            encontrado = true;
            tamlog++;
            tabla[pos].dato=aeropuerto;
            tabla[pos].clave=clave;
            tabla[pos].estado=OCUPADA;
            tabla[pos].iata=aeropuerto.getIata();
        }else{  //sino hay dos opciones, o que sea el mismo aeropuerto o que la casilla esta ocupada
            if (tabla[pos].dato==aeropuerto)
                return false;
            //si esta ocupada colisiones++
            else colisiones++;
        }
    }
    //al terminar actualizamos los datos de la tabla
    sumaColisiones+=colisiones;

    if(colisiones<maxColisiones)
        maxColisiones=colisiones;

    if (colisiones>10)
        max10++;

    return encontrado;
}

bool ThashAerop::borrar(unsigned long clave, const std::string &iata) {
    int colisiones=0;
    int pos=0;
    bool encontrado=false;
    while (!encontrado){
        pos= hash3(clave,colisiones);
        if(tabla[pos].estado==OCUPADA && tabla[pos].iata==iata){
            encontrado= true;
            //cambiamos el estado a disponible
            tabla[pos].estado=DISPONIBLE;
            tamlog--;
        }else{
            if(tabla[pos].estado==LIBRE) //si esta LIBRE significa que no se han metido datos posteriormente
                return false;
            else
                colisiones++;
        }
    }
    return encontrado;
}

Aeropuerto *ThashAerop::buscar(unsigned long clave, const std::string &iata) {
    int colisiones=0;
    int pos=0;
    bool encontrado=false;
    while (!encontrado){
        pos= hash3(clave,colisiones);
        if(tabla[pos].estado==OCUPADA && tabla[pos].iata==iata){
            encontrado= true;
            return &tabla[pos].dato;
        }else{
            if(tabla[pos].estado==LIBRE) //si esta LIBRE significa que no se han metido datos posteriormente
                return nullptr;
            else
                colisiones++;
        }
    }
}

unsigned long ThashAerop::numElementos() {
    return tamlog;
}

unsigned int ThashAerop::nMaxColisiones(){
    return maxColisiones;
}

unsigned int ThashAerop::numMax10(){
    return max10;
}

float ThashAerop::promedioColisiones(){
    return (float)sumaColisiones/tamlog;
}

float ThashAerop::factorCarga(){
    return (float)tamlog/tamfis;
}

void ThashAerop::mostrarEstadoTabla(){

}