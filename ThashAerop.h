//
// Created by AntonioJR on 25/11/2023.
//
#include "string"
#include "Aeropuerto.h"
#include "vector"
using  namespace std;
#ifndef PR5_THASHAEROP_H
#define PR5_THASHAEROP_H

/**
 *@file ThashAerop.h
 * @brief Practica 5 EEDD
 * @date 25/11/2023
 * @author Antonio José Garcia Arias, ajga001@red.ujaen.es
 * @author Abraham Garcia Hurtado, agh00040@red.ujaen.es
 * @return
 */

enum EstadoCelda {LIBRE,OCUPADA,DISPONIBLE};
class ThashAerop {

private:
    //Tamaño del vector sin signo long el entero mas grande
    //Numero de colisiones
    //Numero maximo de colisiones
    //Maximo numero de intentos
    //Tamaño redispersion
    unsigned long int tamalog,tamafis,nCols,nMaxCols,nMax10Cols,tmRedisp;
    //Primo menor
    int primoMen;
    //Definimos lo que tiene la tabla Hash
    class  Entrada{
        public:
            unsigned long  clave;
            Aeropuerto dato;
            string iata;
            EstadoCelda estado;
            Entrada():clave(0),iata(""),dato(Aeropuerto()),estado(LIBRE){};
            //Destructor
            virtual ~Entrada(){};
    };
    //Definimos un vector que se llamara tabla
    vector<Entrada> tabla;
    unsigned long tamfis;
    unsigned long tamlog;
    //numero del intento con mas colisiones
    unsigned long maxColisiones;
    //numero de intentos que superan las 10 colisiones
    unsigned long max10;
    //suma de todas las colisiones
    unsigned long sumaColisiones;
    unsigned long redisp;

    //Funcion para ver si es primo
    bool esPrimo(int numero);
    //Funcion q primo <t
    int qPrimoT(int tamanoFisico,bool menorOmayor);

    //Funcion de dispersion cuadratica
    unsigned int hash1(unsigned  long clave ,int intento);
    //Funcion de dispersion doble
    unsigned int hash2(unsigned  long clave ,int intento);
    //Funcion de dispersion doble 2
    unsigned int hash3(unsigned  long clave ,int intento);

public:
    //Constructor por defecto
    ThashAerop();
    //Constructor copia
    ThashAerop(const ThashAerop &origen);
    //Constructor que construye la tabla garantizando un factor de carga determinado
    ThashAerop(int maxElementos, float lambda=0.7);
    //Destructor
    ~ThashAerop();

    unsigned long djb2(unsigned char *str);

    bool insertar(unsigned long clave, const Aeropuerto &aeropuerto);
    bool borrar(unsigned long clave, const std::string &id);
};


#endif //PR5_THASHAEROP_H
