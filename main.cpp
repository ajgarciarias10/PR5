#include <iostream>
#include "VuelaFlight.h"

int main() {
    try {
        VuelaFlight vuelaFlight;

    #pragma region Entrenamiento
        VuelaFlight tabla068(0.68);
        VuelaFlight tabla065(0.65);
    #pragma endregion
/*
         #pragma  region Prueba de Rendimiento 1
        vector<Aeropuerto*> aeros =  vuelaFlight.getAeropuertos();
        VuelaFlight prueba2(0.65);
        clock_t tiempoprueba2= clock();
        for (int i = 0; i < 1000000; ++i) {
            prueba2.buscaAeropuerto(aeros[(rand()%aeros.size())]->getIata());
        }
        std::cout << "Tiempo lectura de la prueba 2 con tabla: " << ((clock() - tiempoprueba2) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
        //vamos a probarlo con una lista
        list<Aeropuerto*> lista_prueba2;
        list<Aeropuerto*>::iterator itLista;
        clock_t tiempoprueba2lista= clock();
        for (int i = 0; i < aeros.size(); ++i) {
            lista_prueba2.push_back(aeros[i]);
        }
        for (int i = 0; i < 1000000; ++i) {
            std::lower_bound(lista_prueba2.begin(), lista_prueba2.end(),aeros[(rand()%aeros.size())]);
        }
        std::cout << "Tiempo lectura de la prueba 2 con lista: " << ((clock() - tiempoprueba2lista) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;


#pragma endregion
  */
    #pragma region Programa de prueba 2
        vuelaFlight.mostrarEstadoTabla();
        Aeropuerto* aeropuerto = vuelaFlight.buscaAeropuerto("00AS");
        if(aeropuerto){
            cout<< "Nombre: " << aeropuerto->getNombre() <<  " IATA: " << aeropuerto->getIata()<<
                " Pais: "<<  aeropuerto->getIsoPais()  <<endl;
            vuelaFlight.eliminarAeropuerto("00AS");
            Aeropuerto* aeropuerto2 = vuelaFlight.buscaAeropuerto("00AS");
            if(!aeropuerto2){
               cout<< " Ha sido borrado con exito " <<endl;
               cout << "Realizando reinserccion del aeropuerto"<<endl;
               vuelaFlight.addAeropuerto(*aeropuerto);
               vuelaFlight.mostrarEstadoTabla();
               vuelaFlight.eliminarAeropuertoInactivo();
               vuelaFlight.mostrarEstadoTabla();
            }
        }
        else {
            cout << "No existe" << endl;
        }
    #pragma endregion
#pragma  region Redispersion
        cout<<endl<<"---------------REDISPERSION---------------"<<endl;
        VuelaFlight tabla01(0.75);
       // vuelaFlight.mostrarEstadoTabla();
#pragma  endregion
    }catch (invalid_argument &e){
        e.what();
    }

     return 0;
}
