#include <iostream>
#include "VuelaFlight.h"

int main() {
    VuelaFlight vuelaFlight;
    vuelaFlight.mostrarEstadoTabla();
    try {
        vuelaFlight.eliminarAeropuertoInactivo();
        vuelaFlight.mostrarEstadoTabla();
        vuelaFlight.eliminarAeropuerto("00AS");

    }catch (invalid_argument &e){
        e.what();
    }

     return 0;
}
