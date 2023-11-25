//
// Created by AntonioJR on 10/11/2023.
//

#include "Vuelo.h"

const string &Vuelo::getFlightNumber() const {
    return flightNumber;
}

const string &Vuelo::getPlane() const {
    return plane;
}

const string &Vuelo::getDatoMeteo() const {
    return datoMeteo;
}

 Fecha &Vuelo::getFecha()  {
    return fecha;
}

Aeropuerto *Vuelo::getAirpOrigin() const {
    return airpOrigin;
}

Aeropuerto *Vuelo::getAirpDest() const {
    return airpDest;
}

Aerolinea *Vuelo::getAerolinea() const {
    return linkAero;
}
Vuelo::Vuelo():flightNumber(),plane(),datoMeteo(),fecha(),airpOrigin(),airpDest(),linkAero() {}
Vuelo::Vuelo(const Vuelo &orig):flightNumber(orig.flightNumber),plane(orig.plane),datoMeteo(orig.datoMeteo),fecha(orig.fecha),airpOrigin(orig.airpOrigin),airpDest(orig.airpDest),linkAero(orig.linkAero) {}
Vuelo::Vuelo(string flightNumber,string plane,string datoMeteo,Fecha fecha,Aeropuerto *airpOrigin,Aeropuerto *airpDest,Aerolinea *linkAero):flightNumber(flightNumber),plane(plane),datoMeteo(datoMeteo),fecha(fecha),airpOrigin(airpOrigin),airpDest(airpDest),linkAero(linkAero) {}
Vuelo::~Vuelo() {}

void Vuelo::setFlightNumber(const string &flightNumber) {
    Vuelo::flightNumber = flightNumber;
}

void Vuelo::setPlane(const string &plane) {
    Vuelo::plane = plane;
}

void Vuelo::setDatoMeteo(const string &datoMeteo) {
    Vuelo::datoMeteo = datoMeteo;
}

void Vuelo::setFecha( Fecha &fecha) {
    Vuelo::fecha = fecha;
}

void Vuelo::setAirpOrigin(Aeropuerto *airpOrigin) {
    Vuelo::airpOrigin = airpOrigin;
}

void Vuelo::setAirpDest(Aeropuerto *airpDest) {
    Vuelo::airpDest = airpDest;
}

void Vuelo::setLinkAero(Aerolinea *linkAero) {
    Vuelo::linkAero = linkAero;
}
