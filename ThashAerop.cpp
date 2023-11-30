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
ThashAerop::ThashAerop(const ThashAerop &orig): tamlog(orig.tamlog),tamfis(orig.tamfis),sumaColisiones(orig.sumaColisiones),max10(orig.max10),
                                                    maxColisiones(orig.maxColisiones),redisp(orig.redisp),tabla(orig.tabla),primoMen(orig.primoMen){
}

/**
 * @brief operator= de ThashAerop
 * @param orig
 * @return *this
 */
ThashAerop &ThashAerop::operator=(const ThashAerop &orig) {
    if(this!=&orig){
        tamlog=orig.tamlog;
        tamfis=orig.tamfis;
        maxColisiones=orig.maxColisiones;
        max10=orig.max10;
        sumaColisiones=orig.sumaColisiones;
        redisp=orig.redisp;
        primoMen=orig.primoMen;
        tabla=orig.tabla;
    }
    return *this;
}

/**
 * @brief Constructor inicializador
 * @param maxElementos
 * @param lambda
 */

ThashAerop::ThashAerop(int maxElementos, float lambda):tamlog(0),sumaColisiones(0),max10(0),maxColisiones(0),redisp(0){
    tamfis= qPrimoT(maxElementos/lambda, false);
    tabla.assign(tamfis,Entrada());
    primoMen= qPrimoT(tamfis, true);
}

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
    }else
        return false;

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

unsigned long ThashAerop:: djb2(unsigned char *str) {
    unsigned long hash = 5381;
    int c;
    while (c = *str++) hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

bool ThashAerop::insertar(unsigned long clave, const Aeropuerto &aeropuerto) {
    int colisiones=0;
    int pos;
    bool seEncontro= false;
    while(!seEncontro){
        //calculamos la posicion con una funcion hash
        pos=hash2(clave,colisiones);
        //si esta libre o disponible metemos el dato
        if(tabla[pos].estado==LIBRE || tabla[pos].estado==DISPONIBLE){
            seEncontro = true;
            tamlog++;
            tabla[pos] = Entrada(clave,aeropuerto,aeropuerto.getIata(),OCUPADA);
        }else{
            if (tabla[pos].dato==aeropuerto)
                return false;
            else colisiones++;
        }
    }
    actualizaColisiones(colisiones);
    return seEncontro;
}

bool ThashAerop::borrar(unsigned long clave, const std::string &iata) {
    int colisiones=0;
    int pos;
    bool seEncontro=false;
    while (!seEncontro){
        pos=hash2(clave,colisiones);
        if(tabla[pos].estado==OCUPADA && tabla[pos].iata==iata){
            seEncontro= true;
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
    return seEncontro;
}

Aeropuerto *ThashAerop::buscar(unsigned long clave, const std::string &iata) {
    int colisiones=0;
    int pos;
    bool seEncontro=false;
    while (!seEncontro){
        pos=hash2(clave,colisiones);
        if(tabla[pos].estado==OCUPADA && tabla[pos].iata==iata){
            seEncontro= true;
            return &tabla[pos].dato;
        }else{
            if(tabla[pos].estado==LIBRE) //si esta LIBRE significa que no se han metido datos posteriormente
                return nullptr;
            else
                colisiones++;
        }
    }
    return nullptr;
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

unsigned long ThashAerop::tamTabla(){
   return tamfis;
}

unsigned long ThashAerop::getTamLog() {
    return tamlog;
}

vector<Aeropuerto*> ThashAerop::getAeros() {
    vector<Aeropuerto*> aeropuertos;
    for (int i = 0; i < tabla.size(); ++i) {
        if(tabla[i].estado == OCUPADA){
            aeropuertos.push_back((tabla[i].getDato()));
        }
    };
    return  aeropuertos;
}

void ThashAerop::actualizaColisiones(int colisiones) {
    sumaColisiones+=colisiones;

    if(colisiones>maxColisiones)
        maxColisiones=colisiones;

    if (colisiones>10)
        max10++;
}