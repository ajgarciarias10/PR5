#ifndef PRACTICA_2_RUTA_H
#define PRACTICA_2_RUTA_H
#include <string>
#include "Aeropuerto.h"
#include "Aerolinea.h"
#include <list>
#include "../PR5/Vuelo.h"
#include <iostream>
using namespace std;
/**
 *@file Ruta.h
 * @brief Practica 2 EEDD
 * @date 19/10/2023
 * @author Antonio José Garcia Arias, ajga001@red.ujaen.es
 * @author Abraham Garcia Hurtado, agh00040@red.ujaen.es
 * @return
 */
class  Aerolinea;
class Ruta {
private:
    Aeropuerto *destination;
    Aeropuerto *origin;
    Aerolinea *company;
    list<Vuelo*>fligthRou;
public:
    //Constructor por defecto
    Ruta();
    //Constructor copia
    Ruta(const Ruta &orig);
    //Constructor paramerizado
    Ruta(Aeropuerto *destination= nullptr, Aeropuerto *origin= nullptr, Aerolinea *company= nullptr,list<Vuelo*> fligthRou = list<Vuelo *>());

    //Destructor
    virtual ~Ruta();
    //Metodo que añade los vuelos a flightRou
    bool addVuelo(Vuelo *v);
    //Obtener el numero de vuelos
    long int getNumVuelos();
    //Get Vuelos
    list<Vuelo*> getVuelos();

    Aeropuerto *getDestination() const;

    Aeropuerto *getOrigin() ;

    Aerolinea *getCompany() ;

    void setDestination(Aeropuerto *destination);

    void setOrigin(Aeropuerto *origin);

    void setCompany(Aerolinea *company);

};


#endif //PRACTICA_2_RUTA_H
