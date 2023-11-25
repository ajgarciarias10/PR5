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
        private:
            unsigned long  clave;
            Aeropuerto dato;
            string iata;
            //enum dato de tipo constante que la utilizo en este caso para definir el estaod de las celdas
                             // 0= ocupada 1 =libre 2= disponible
            enum estadoCelda {ocupada,libre,disponible};
            estadoCelda estado;

        public:
        Entrada():clave(0),iata(""),dato(Aeropuerto()),estado(libre){};
        //Destructor
        virtual ~Entrada(){};
    };
    //Definimos un vector que se llamara contenido tabla
    vector<Entrada> contTabla;
    //Funcion de dispersion doble
    unsigned int hash(unsigned  long clave ,int intento);
    //Funcion para ver si es primo
    bool esPrimo(int numero);
    //Funcion q primo <t
    int qPrimoT(int tamanoFisico,bool menorOmayor);

public:
    //Constructor por defecto
    ThashAerop();
    //Constructor copia
    ThashAerop(const ThashAerop &origen);
    //Constructor que construye la tabla garantizando un factor de carga determinado
    ThashAerop(int maxElementos, float lambda=0.7);
    //Destructor
    ~ThashAerop();
    

};


#endif //PR5_THASHAEROP_H
