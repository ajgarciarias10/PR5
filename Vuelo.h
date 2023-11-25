//
// Created by AntonioJR on 10/11/2023.
//

#ifndef PR4_VUELO_H
#define PR4_VUELO_H
#include <string>
#include "fecha.h"
#include "Aeropuerto.h"
/**
 * @file Vuelo.h
 * @date 20/11/2023
 * @author Antonio José Garcia Arias, ajga001@red.ujaen.es
 * @author Abraham Garcia Hurtado, agh00040@red.ujaen.es
 * @brief Vuelo
 */
using  namespace std;
class  Aerolinea;
class Vuelo {
private:
    string flightNumber;
    string plane;
    string datoMeteo;
    Fecha fecha;
    Aeropuerto *airpOrigin;
    Aeropuerto *airpDest;
    Aerolinea *linkAero;
public:
    Vuelo();

    Vuelo(const Vuelo &orig);

    Vuelo(string flightNumber,string plane,string datoMeteo,Fecha fecha,Aeropuerto *airpOrigin,Aeropuerto *airpDest,Aerolinea *linkAero);

    virtual  ~Vuelo();

    const string &getFlightNumber() const;

    const string &getPlane() const;

    const string &getDatoMeteo() const;

     Fecha &getFecha() ;

    Aeropuerto *getAirpOrigin() const;

    Aeropuerto *getAirpDest() const;

    Aerolinea *getAerolinea() const;

    void setFlightNumber(const string &flightNumber);

    void setPlane(const string &plane);

    void setDatoMeteo(const string &datoMeteo);

    void setFecha( Fecha &fecha);

    void setAirpOrigin(Aeropuerto *airpOrigin);

    void setAirpDest(Aeropuerto *airpDest);

    void setLinkAero(Aerolinea *linkAero);
};


#endif //PR4_VUELO_H
