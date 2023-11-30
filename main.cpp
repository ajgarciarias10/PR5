#include <iostream>
#include "VuelaFlight.h"

int main() {
    try {
        VuelaFlight vuelaFlight;
        cout<<endl<<"Estado tabla tras cargar los datos: ";
        vuelaFlight.mostrarEstadoTabla();
        vuelaFlight.eliminarAeropuerto("00AS");
        cout<<endl<<"Estado tabla tras elimnar el aeropuerto 00AS";
        vuelaFlight.mostrarEstadoTabla();
        vuelaFlight.eliminarAeropuertoInactivo();
        cout<<endl<<"Estado tabla tras eliminar aeropuertos inactivos";
        vuelaFlight.mostrarEstadoTabla();
        VuelaFlight tabla068(0.68);
        VuelaFlight tabla065(0.65);
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
