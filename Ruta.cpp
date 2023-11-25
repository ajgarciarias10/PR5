#include "Ruta.h"

Ruta::~Ruta() {
}

Ruta::Ruta():company(nullptr),origin(nullptr),destination(nullptr),fligthRou() {}
Ruta::Ruta(const Ruta &orig) :company(orig.company),origin(orig.origin),destination(orig.destination),fligthRou(orig.fligthRou) {}
Ruta::Ruta(Aeropuerto *destination, Aeropuerto *origin, Aerolinea *company,  list<Vuelo *> fvuelo)
        : destination(destination), origin(origin), company(company), fligthRou(fvuelo) {}



Aeropuerto *Ruta::getDestination() const {
    return destination;
}

Aeropuerto *Ruta::getOrigin()  {
    return origin;
}

Aerolinea *Ruta::getCompany()  {
    return company;
}

void Ruta::setDestination(Aeropuerto *destination) {
    Ruta::destination = destination;
}

void Ruta::setOrigin(Aeropuerto *origin) {
    Ruta::origin = origin;
}

void Ruta::setCompany(Aerolinea *company) {
    Ruta::company = company;
}
/**
 * @brief Metodo que añade el vuelo a la lista dentro de rutas flightRou
 * @param v
 * @return
 */

bool Ruta::addVuelo(Vuelo *v) {
    // Verificar que la aerolínea y los aeropuertos de origen y destino
    // coinciden con los de la ruta
    bool bool1 =v->getAirpOrigin()->getIata() == this->origin->getIata();
    bool bool2 =  v->getAirpDest()->getIata() == this->destination->getIata();
    bool bool3 =  v->getAerolinea()->getIcao() == this->company->getIcao();
    if( bool1 &&  bool2 && bool3 ){
        fligthRou.push_back(v);
        return true;
    }
    return false;

}
/**
 * @brief Obtiene el numero de vuelos
 * @return
 */
long int Ruta::getNumVuelos() {
    return fligthRou.size();
}
list<Vuelo*> Ruta::getVuelos() {
    return fligthRou;
}





