#include <iostream>
#include "VuelaFlight.h"

int main() {
    try {
        VuelaFlight vuelaFlight;
        vuelaFlight.mostrarEstadoTabla();

        // vuelaFlight.eliminarAeropuerto("00AS");
        // vuelaFlight.mostrarEstadoTabla();
        vuelaFlight.eliminarAeropuertoInactivo();
        // vuelaFlight.mostrarEstadoTabla();
    #pragma  region Prueba de Rendimiento 1
        vector<Aeropuerto*> aeros =  vuelaFlight.getAeropuertos();
        vector<int> numerosAleos;
        for (int i = 0; i < 1000000; ++i) {
            int random=rand();
            
        }
    #pragma endregion


    }catch (invalid_argument &e){
        e.what();
    }

     return 0;
}
