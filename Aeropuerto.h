
#ifndef PRACTICA_1B_AEROPUERTO_H
#define PRACTICA_1B_AEROPUERTO_H

#include <string>
#include "../PR5/UTM.h"
#include "stdexcept"
#include "algorithm"
using namespace  std;

/**
 * @file Aeropuerto.h
 * @brief Practica 2 EEDD
 * @date 19/10/2023
 * @author Antonio José Garcia Arias, ajga001@red.ujaen.es
 * @author Abraham Garcia Hurtado, agh00040@red.ujaen.es
 * @param argc
 * @param argv
 * @return
 */
class Aeropuerto {
private:
    string id;
    string iata;
    string tipo;
    string nombre;
    string continente;
    string iso_pais;
    UTM posicion;

public:

    UTM getUtm() const;

    void setUtm(UTM &utm);

    const std::string &getId() const;

    void setId(const std::string &id);

    const std::string &getIata() const;

    void setIata(const std::string &iata);

    const std::string &getTipo() const;

    void setTipo(const std::string &tipo);

    const std::string &getNombre() const;

    void setNombre(const std::string &nombre);

    const std::string &getContinente() const;

    void setContinente(const std::string &continente);

    const std::string &getIsoPais() const;

    void setIsoPais(const std::string &isoPais);

    Aeropuerto(std::string id, std::string iata, std::string tipo,
               std::string nombre,  std::string continente,  std::string isoPais,const UTM &pos);

    Aeropuerto(const Aeropuerto& orig);

    Aeropuerto &operator=(const Aeropuerto &orig);

    Aeropuerto();

    bool operator==(const Aeropuerto &orig)const ;

    bool operator<(const Aeropuerto &orig)const;

    bool operator>(const Aeropuerto &orig)const;

    virtual ~Aeropuerto();
};

#endif //PRACTICA_1B_AEROPUERTO_H
