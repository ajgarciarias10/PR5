#include <iostream>
#include "VuelaFlight.h"

int main() {
    VuelaFlight vuelaFlight;
    vuelaFlight.mostrarEstadoTabla();
    try {
        Aeropuerto* aeropuerto = vuelaFlight.buscaAeropuerto("00AS");
        vuelaFlight.eliminarAeropuertoInactivo();
        cout<<aeropuerto->getIata()<<aeropuerto->getNombre()<<endl;
        vuelaFlight.eliminarAeropuerto("00AS");
        vuelaFlight.mostrarEstadoTabla();


    }catch (invalid_argument &e){
        e.what();
    }

     return 0;
}
