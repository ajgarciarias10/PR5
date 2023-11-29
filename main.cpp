#include <iostream>
#include "VuelaFlight.h"

int main() {
    VuelaFlight vuelaFlight;
    vuelaFlight.mostrarEstadoTabla();
    try {
        vuelaFlight.eliminarAeropuerto("00AS");
        vuelaFlight.mostrarEstadoTabla();
        vuelaFlight.eliminarAeropuertoInactivo();
        vuelaFlight.mostrarEstadoTabla();
    }catch (invalid_argument &e){
        e.what();
    }

     return 0;
}
