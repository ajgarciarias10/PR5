#include "Aeropuerto.h"
#include "Ruta.h"
#include <vector>
#include <list>
#include <deque>
#include <map>
#include <set>
#include "time.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#ifndef PRACTICA_2_VUELAFLIGHT_H
#define PRACTICA_2_VUELAFLIGHT_H
/**
 * @file VuelaFlight.h
 * @date 20/11/2023
 * @author Antonio José Garcia Arias, ajga001@red.ujaen.es
 * @author Abraham Garcia Hurtado, agh00040@red.ujaen.es
 * @brief Vuela Flight
 */

class VuelaFlight {
private:
    long int tamaVuelo= 0;
    //Metodo para cargarVuelos
    void  cargarVuelos(string fichVuelos);
   //Metodo para cargarAeropuertos
    void cargaAeropuertos();
   //Metodo para cargarAerolineas
    void cargaAerolineas();
    //Metodo para cargarRutas
    void cargarRutas();
    //Declaramos los metodo publicos y constructores
    vector<Aeropuerto> aeropuertos;
    list<Ruta> rutas;
    map<string,Aerolinea> airlines;
public:
    //Constructor por defecto
    VuelaFlight();
    //Constructor copia
    VuelaFlight(const VuelaFlight &vl);
    //Constructor parametrizado
    VuelaFlight(vector<Aeropuerto> aeropuerto, list<Ruta> ruta ,map<string,Aerolinea> airlines);
    //Destructor VuelaFlight
    ~VuelaFlight();
    //Metodos que tenemos que utilizar en esta practica
    //BuscarRutaDeOrigenDestino
    Ruta& buscarRutasOriDeS(string idAerOrig,string idAerDest);
    //BuscarRutasDeOrigen
    list<Ruta*> buscarRutasOrigen (string idAerOrig);
    //Buscar AeropuertoPais
    vector<Aeropuerto*> buscarAeropuertoPais(string pais);
    //AñadirNuevoAeropuerto
    void añadeAeropuerto(const Aeropuerto aeropuerto);
    //AñadirNuevaRuta
    void addNuevaRuta(Aeropuerto* AerOrig, Aeropuerto* AerDest, Aerolinea* aerolineaEncontrada);
    //Añade Aerolinea
    void addAerolinea(string icao, Aerolinea aerolinea);
    //Buscar Aerolinea por icao
    Aerolinea &buscaAerolinea(string icaoAerolinea);
    //Buscar Aerolinea activa
    vector<Aerolinea*> buscaAerolineasActiva();
    //Metodo que obtiene la aerolineas por el Pais
    vector<Aerolinea*> getAerolineasPais(string idPais);
    //Metodo que Carga las Rutas
    void addRutas(string icaoRuta, string origen2, string destino2);
    //Metodo que ordenar Aeropuertos
    void ordenarAeropuertos();
    //Devuelve el tamaño de aeropuertos
    long tamaAeropuertos ();
    //Devuelve el tamaño de rutas
    long tamaRutas();
    //Devuelve el tamaño del Arbol
    long tamaAirlines();
    //Metodo para registrar un vuelo
    bool registrarVuelo(string fNumber, string iataAeroOrig, string iataAeroDest, string plane ,string datosMeteo, Fecha f);
    //Metodo que devuelve el tamaño de los vuelos
    int tamaVuelos();
    //Metodo que buscaLosVuelos por su numero de vuelo
    vector<Vuelo*> buscaVuelos(string fNumber);
    //Metodo que busca los vuelos operador por icao y fecha
    vector<Vuelo*>vuelosOperadosPor(string icaoAerolinea,Fecha f);
    //Metodo que busca los Vuelos de destinoPor Aeropuerto
    set<string> buscaVuelosDestAerop(string paisOrig, string iataAeroDest);
    //Metodo util para obtenerRutas en funcnion del paisDeOrigen
    list<Ruta*>buscarRutasPaisOrig(string pOrig);
    //Metodo que buscaAeropuertosAerolineas por icao
    vector<Aeropuerto *>buscaAeropuertosAerolinea(string icaoAerolinea);
};


#endif //PRACTICA_2_VUELAFLIGHT_H
