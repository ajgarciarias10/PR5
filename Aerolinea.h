#ifndef PRACTICA_3_AEROLINEA_H
#define PRACTICA_3_AEROLINEA_H
#include <string>
#include "Ruta.h"
#include <vector>
#include <list>
#include <deque>
#include <map>
#include "../PR5/Vuelo.h"
#include "fecha.h"
/**
 * @file Aerolinea.h
 * @date 20/11/2023
 * @author Antonio José Garcia Arias, ajga001@red.ujaen.es
 * @author Abraham Garcia Hurtado, agh00040@red.ujaen.es
 * @brief Aerolinea
 */
using  namespace  std;
class Ruta;
class Aerolinea {
private:
    unsigned int id;
    string icao;
    string nombre;
    string pais;
    bool activo;
    deque<Ruta*> aerorutas;
    multimap<string ,Vuelo> flights;
public:
    //Constructor por defecto
    Aerolinea();
    //Constructor copia
    Aerolinea(const Aerolinea &orig);
    //Constructor paramerizado
    Aerolinea(int id, string icao, string nombre ,string pais, bool activo);
    //Destrcutor
    ~Aerolinea();
    //Metodo que devuelve los aeropuertos de origen
    vector<Aeropuerto*>getAeropuertosOrig();
    //Metodo que devuelve todas las rutas cuya aeropuerto de origen tenga ese mismo iata
    deque<Ruta*> getRutasAeropuerto(string iataAirport);
    //Enlaza Aerolina con Aeroroutes
    void linkAerolRuta(Ruta *r);
    //Operator<
    bool operator<(const Aerolinea &orig) const;
    //Operador>
    bool  operator>(const Aerolinea &orig) const;
    //Getter Id
    unsigned int getId() const;
    //Setter Id
    void setId(unsigned int id);
    //Getter Icao
    const string &getIcao() const;
    //Setter Icao
    void setIcao(const string &icao);
    //Getter Nombre
    const string &getNombre() const;
    //Setter Nombre
    void setNombre(const string &nombre);
    //Getter Pais
    const string &getPais() const;
    //Setter Pais
    void setPais(const string &pais);
    //Getter Activo
    bool isActivo() const;
    //Setter Activo
    void setActivo(bool activo);
    //Getter de variable privada aeroruta
    const deque<Ruta *> &getAerorutas() const;
    //Setter Aerorutas
    void setAerorutas(const deque<Ruta *> &aerorutas);
    //Metodo añadir Vuelo
    Vuelo* addVuelo(Vuelo &v);
    //Metodo para obtenerLosVuelos por flightNumber
    vector<Vuelo*>getVuelos(string fNumber);
    //Metodo para obtenerlos por una fecha determinada
    vector<Vuelo*>getVuelos(Fecha fIni, Fecha fFin);
    //Metodo para obtener el numero de los vuelos
    long int getNumVuelos();
    vector<Vuelo*>getFlights();
};




#endif //PRACTICA_3_AEROLINEA_H
