#include "VuelaFlight.h"
/**
 * @brief VuelaFlight
 */
VuelaFlight::VuelaFlight() :aeropuertos(),rutas(),airlines() {
#pragma region Carga aeropuertos
    cargaAeropuertos();
#pragma endregion
#pragma region  Carga Aerolineas
    cargaAerolineas();

#pragma  endregion
#pragma region Carga Ruta
    cargarRutas();
#pragma endregion
#pragma region Carga Vuelos
    cargarVuelos("../infovuelos_v1.csv");
#pragma endregion
#pragma region Mostrar tamaño de las estructuras de datos utilizadas
    cout<< "Tamaño Aerolineas: " << tamaAirlines() <<endl
        << "Tamaño aeropuertos: " << tamaAeropuertos() << endl
        << "Tamaño rutas: " << tamaRutas() << endl
        <<"Tamaño Vuelos: "<< tamaVuelos() << endl <<endl;
#pragma  endregion
}
/**
 * @brief Constructor parametrizado
 * @param vector
 * @param ruta
 */
VuelaFlight::VuelaFlight(vector<Aeropuerto> aeropuerto, list<Ruta> ruta ,map<string,Aerolinea> airlines):aeropuertos(aeropuerto),rutas(ruta),airlines(airlines) {}
/**
 * @brief Destructor
 */
VuelaFlight::~VuelaFlight() {
}
/**
 * @brief BuscarRutasOrigenDestino
 * @param idAerOrig
 * @param idAerDest
 * @return
 */
Ruta &VuelaFlight::buscarRutasOriDeS(string idAerOrig, string idAerDest) {
    list<Ruta>::iterator i;
    //Recorremos todos los aeropuertos
    for(i=rutas.begin(); i!=rutas.end();i++){
        //Obtenemos los datos
        string origenBusq = i->getOrigin()->getIata();
        string destinoBusq = i->getDestination()->getIata();
        //En caso de que se encuentre
        if(origenBusq==idAerOrig && destinoBusq==idAerDest)
            //Devolvemos el dato
            return *i;
    }
    throw std::invalid_argument("La ruta no ha sido encontrado" "\n" "Intente cambiar su origen y destino" );
}
/**
 * @brief BuscarRutasOrigen
 * @param idAerOrig
 * @return
 */
list<Ruta *> VuelaFlight::buscarRutasOrigen(string idAerOrig) {
    list<Ruta>::iterator i;
    list<Ruta *> lista;
    //Recorremos todos los aeropuertos
    for(i=rutas.begin(); i!=rutas.end();i++){
        //Obtenemos los datos
        string origenBusq = i->getOrigin()->getIata();
        //En caso de que se encuentre
        if(origenBusq==idAerOrig){
            //Devolvemos el dato
            //El iterador no es como un puntero y entonces lo que hacemos es devolver el dato * y su direccion &
            lista.push_back(&(*i));
        }
    }
    return  lista;


}

/**
 * @brief Buscar Aeropuerto por Pais
 * @param pais
 * @return
 */
vector<Aeropuerto * > VuelaFlight::buscarAeropuertoPais(string pais) {
    //Donde lo vamos a meter
    vector<Aeropuerto*> encontrado;
    //Recorremos el tamaño fisico
    for (int i = 0; i < aeropuertos.size(); ++i) {
        if(aeropuertos[i].getIsoPais() == pais){
            //Insertamso el vector de aeropuertos
            //Insertamos la direccion del vector ya que con los corchetes accedemos al dato pero tenemos que poner donde esta
            encontrado.push_back(&(aeropuertos[i]));
        }
    }
    return  encontrado;


}
/**
 * @brief Metodo para añadir nueva ruta
 * @param idAerOrig
 * @param idAerDest
 * @param aerolinea
 */
void VuelaFlight::addNuevaRuta(Aeropuerto* AerOrig, Aeropuerto* AerDest, Aerolinea* aerolineaEncontrada) {
            //Añadimos las rutas ya con la aerolinea  y los aeropertos
            rutas.push_back(Ruta(AerDest,AerOrig,aerolineaEncontrada));
            //d. Obtener la dirección del objeto ruta recién insertado en la lista (en la última posición).
            //e. Enlazar la aerolínea encontrada antes con la ruta anterior mediante
            //Aerolinea::linkAerolRuta.
            aerolineaEncontrada->linkAerolRuta(&(rutas.back()));

}

/**
 * @brief Constructor Copia
 * @param vl
 */

VuelaFlight::VuelaFlight(const VuelaFlight &vl) : aeropuertos(vl.aeropuertos), rutas(vl.rutas),airlines(vl.airlines){}
/**
 * @brief Añade aeropuerto
 * @param aeropuerto
 */

void VuelaFlight::añadeAeropuerto(const Aeropuerto aeropuerto) {
    aeropuertos.push_back(aeropuerto);

}
/**
 * @brief Metodo AddAerolinea
 * @param aerolinea
 */
void VuelaFlight::addAerolinea(string icao,Aerolinea aerolinea) {
    airlines.insert( pair<string , Aerolinea>(icao,aerolinea));

}
/**
 * @brief Metodo Buscar Aerolinea por Icao
 * @param icaoAerolinea
 * @return
 */
Aerolinea &VuelaFlight::buscaAerolinea(std::string icaoAerolinea) {
    map<string,Aerolinea>:: iterator it = airlines.find(icaoAerolinea);
    //El metodo find devuelve end en caso de que no encuentra nada
    if(it == airlines.end()){
        throw std::invalid_argument("No se ha encontrado la aerolinea");
    }
    //Devolvemos en caso contrario si la ha encontrado
    return  it->second;

}
/**
 * @brief Metodo que busca las Aerolineas Activas
 * @return
 */
vector<Aerolinea*> VuelaFlight::buscaAerolineasActiva() {
    //Utilizamos un iterador en el mapa
    map<string,Aerolinea>::iterator itBuscaAerolinea  ;
    //Este sera el vector de aerolineas activas
    vector<Aerolinea*> aeroActivas;
    for (itBuscaAerolinea = airlines.begin(); itBuscaAerolinea != airlines.end(); ++itBuscaAerolinea) {
        if(itBuscaAerolinea->second.isActivo()){
            //Devolvemos la direccion de memoria de la aerolinea activa
            aeroActivas.push_back(&(itBuscaAerolinea->second));
        }
    }

    return  aeroActivas;

}
/**
 * @brief Metodo que busca la Aerolinea por el pais
 * @param idPais
 * @return
 */
vector<Aerolinea*> VuelaFlight::getAerolineasPais(std::string idPais) {
    //Idem aerolineas Activas
    map<string,Aerolinea>::iterator  itBuscaAero ;
    vector<Aerolinea*> aerolineaPais;
    for (itBuscaAero = airlines.begin(); itBuscaAero != airlines.end(); ++itBuscaAero) {
        if(itBuscaAero->second.getPais() == idPais){
            aerolineaPais.push_back(&(itBuscaAero->second));
        }
    }

    return  aerolineaPais;
}
/**
 * @brief Metodo que carga las rutas que leemos
 * @param icaoRuta
 * @param origen2
 * @param destino2
 */
void VuelaFlight::addRutas(string icaoRuta, string origen2, string destino2){
#pragma  region   Buscar en tiempo logarítmico la aerolínea que hace la ruta en VuelaFlight::airlines en este caso en el mapa
    map<string ,Aerolinea>::iterator aerolineaEncontrada= airlines.find(icaoRuta);
#pragma  endregion
#pragma region Buscar en tiempo logarítmico en  PR2 + añadir nueva ruta
    //Declaro un aeropuerto
    Aeropuerto aero;
    //Seteo su iata de origen
    aero.setIata(origen2);
    //Compruebo la posicion dentro del vector dinamico en el que esta Tanto la ruta de origen con la de destino
    //Y así descubro el aeropuerto ORIGEN
    vector<Aeropuerto>::iterator  origen;
    origen = std::lower_bound(aeropuertos.begin(), aeropuertos.end(),aero);
    //Obtenemos la posicion iterada de destino
    vector<Aeropuerto>::iterator  destino;
    //Seteo su iata de destino
    aero.setIata(destino2); 
    //Y así descubro el aeropuerto destino
    destino= std::lower_bound(aeropuertos.begin(), aeropuertos.end(),aero);;
    if(&origen && &destino  && &aerolineaEncontrada){
        //Añadimos nueva ruta a partir del origen el destino y el icao
        addNuevaRuta(&(*origen), &(*destino),&aerolineaEncontrada->second);
    }
}
/**
 * @brief Metodo que ordena los aeropuertos
 */

void VuelaFlight::ordenarAeropuertos(){
    sort(aeropuertos.begin(),aeropuertos.end());
}
/**
 * @brief Metodo que devuelve el tamaño del vector
 */
long VuelaFlight::tamaAeropuertos() {
    return aeropuertos.size();
}
/**
 * @brief Metodo que devuelve el tamaño de la lista de rutas
 */
long VuelaFlight::tamaRutas() {
    return rutas.size();
}
/**
 * @brief Metodo que devuelve el tamaño del arbol
 */
long VuelaFlight::tamaAirlines() {
    return airlines.size();
}
bool VuelaFlight::registrarVuelo(std::string fNumber, std::string iataAeroOrig, std::string iataAeroDest,std::string plane, std::string datosMeteo, Fecha f) {
    //Obtenemos la aeriolinea
    map<string,Aerolinea>::iterator mapaEncuentraVuelos = airlines.find(fNumber.substr(0,3));
    //Obtenemos el aeropuerto de orgigen y el de destino
    Aeropuerto orig;
    orig.setIata(iataAeroOrig);
    vector<Aeropuerto>::iterator iteradorOrig = std::lower_bound(aeropuertos.begin(), aeropuertos.end(),orig);
    Aeropuerto dest;
    dest.setIata(iataAeroDest);
    vector<Aeropuerto>::iterator iteradorDest= std::lower_bound(aeropuertos.begin(), aeropuertos.end(),dest);
    if(mapaEncuentraVuelos!=airlines.end() && iteradorOrig!=aeropuertos.end() && iteradorDest!=aeropuertos.end()){
        Vuelo v(fNumber,plane,datosMeteo,f,&(*iteradorOrig),&(*iteradorDest),&(mapaEncuentraVuelos->second));
        mapaEncuentraVuelos->second.addVuelo(v);
        return true;
    }
    else{
        return  false;
    }


}
/**
 * @brief Metodo para cargar Vuelos pasandole un ficheroVuelos
 * @param fichVuelos
 */
void VuelaFlight::cargarVuelos(string fichVuelos) {
    ifstream is;
    stringstream  columnas;
    string fila;
#pragma region Valores Vuelos
    string flightnumber = "";
    string  departurePlane = "";
    string  arrivalPlane = "";
    string plane = "";
    string datoMeteo = "";
    string fecha = "";
#pragma endregion
    clock_t lecturaRutas = clock();
    is.open(fichVuelos); //carpeta de proyecto
    if ( is.good() ) {
        while (getline(is, fila)) {
            //¿Se ha leído una nueva fila?
            if (fila != "") {
                columnas.str(fila);
                getline(columnas, flightnumber, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, departurePlane, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, arrivalPlane, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, plane, ';');
                getline(columnas, datoMeteo, ';');
                getline(columnas, fecha, ';');
                                                    //Posicion //Longuitud
                int dia = stoi(fecha.substr(0, 2));
                int mes = stoi(fecha.substr(3, 2));
                int año = stoi(fecha.substr(6, 2));
                fila = "";
                columnas.clear();
                if(registrarVuelo(flightnumber,departurePlane,arrivalPlane,plane,datoMeteo,Fecha(dia,mes,año))){
                    tamaVuelo++;
                }
            }
        }

    } else{
        std::cout << "Error de apertura en archivo" << std::endl;
    }
    tamaVuelos();

    is.close();
    std::cout << "Tiempo lectura de los vuelos: " << ((clock() - lecturaRutas) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;

}
/**
 * @brief Metodo que carga los Aeropuertos
 */
void VuelaFlight::cargaAeropuertos() {
    ifstream is;
    stringstream  columnas;
    string fila;
    #pragma region Aeropuerto valores
        string id = "";
        string iata = "";
        string ident="";
        string tipo="";
        string nombre="";
        string latitud_str="";
        string longitud_str="";
        string continente="";
        string iso_pais="";
    #pragma endregion
    clock_t lecturaAero = clock();
    is.open("../aeropuertos_v2.csv"); //carpeta de proyecto
    if ( is.good() ) {
        while (getline(is, fila)) {
            //¿Se ha leído una nueva fila?
            if (fila != "") {
                columnas.str(fila);
                //formato de fila: id;ident;tipo;nombre;latitud;longitud;continente;iso_pais
                getline(columnas, id, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, iata, ';');
                getline(columnas, tipo, ';');
                getline(columnas, nombre, ';');
                getline(columnas, latitud_str, ';');
                getline(columnas, longitud_str, ';');
                getline(columnas, continente, ';');
                getline(columnas, iso_pais, ';');
                //  Transformamos la latitud y longitud a float
                fila = "";
                columnas.clear();
                //Insertamos en el Vector Dinamico el Aeropuerto
                añadeAeropuerto(Aeropuerto(id,iata,tipo,nombre,continente,iso_pais, UTM(stof(latitud_str),stof(longitud_str))));


            }
        }
        //Tras leer ordenamos el vector por Codigo Iata
        ordenarAeropuertos();
        is.close();
    }else{
        std::cout << "Error de apertura en archivo" << std::endl;
    }
    std::cout << "Tiempo lectura de aeropuertos: " << ((clock() - lecturaAero) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;


}
/**
 * @brief Metodo que cargaLasAerolineas
 */
void VuelaFlight::cargaAerolineas() {
    ifstream is;
    stringstream  columnas;
    string fila;
#pragma  region Aerolinea valores
    string idAerolineaStr;
    string icao = "";
    string nombreAero="";
    string pais="";
    string activo="";
#pragma endregion
    clock_t lecturaAerolineas = clock();
    is.open("../aerolineas_v1.csv"); //carpeta de proyecto
    if(is.good()){
        while (getline(is, fila)){
            //¿Se ha leído una nueva fila?
            if (fila != "") {
                columnas.str(fila);
                getline(columnas, idAerolineaStr, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, icao, ';');
                getline(columnas, nombreAero, ';');
                getline(columnas, pais, ';');
                getline(columnas, activo, ';');
                bool activoBool;
                //condición ? valor_si_verdadero : valor_si_falso;
                activo=="Y" ? activoBool = true : activoBool = false;
                int id = stoi(idAerolineaStr);
                addAerolinea(icao,Aerolinea(id,icao,nombreAero,pais,activoBool));
                fila = "";
                columnas.clear();
            }
        }
    }
    else{
        std::cout << "Error de apertura en archivo" << std::endl;
    }
    is.close();
    std::cout << "Tiempo lectura de las aerolineas: " << ((clock() - lecturaAerolineas) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;

}
/**
 * @brief Metodo que cargaLasRutas
 */
void VuelaFlight::cargarRutas() {
    ifstream is;
    stringstream  columnas;
    string fila;
#pragma region Valores Rutas
    string icaoRuta = "";
    string  origen2 = "";
    string destino2 = "";
#pragma endregion
    clock_t lecturaRutas = clock();
    is.open("../rutas_v1.csv"); //carpeta de proyecto
    if ( is.good() ) {
        while (getline(is, fila)) {
            //¿Se ha leído una nueva fila?
            if (fila != "") {
                columnas.str(fila);
                getline(columnas, icaoRuta, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, origen2, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, destino2, ';'); //leemos caracteres hasta encontrar y omitir ';'
                fila = "";
                columnas.clear();
                addRutas(icaoRuta, origen2, destino2);

            }
        }

    } else{
        std::cout << "Error de apertura en archivo" << std::endl;
    }

    is.close();
    std::cout << "Tiempo lectura de las rutas: " << ((clock() - lecturaRutas) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;


}
/**
 * @brief Devuelve el tamaño de los vuelos
 * @param nvuelos
 * @return
 */
int VuelaFlight::tamaVuelos() {
    return tamaVuelo;
}
/**
 * @brief Metodo que busca los vuelos y los devuelve
 * @param fNumber
 * @return
 */
vector<Vuelo *> VuelaFlight::buscaVuelos(string fNumber) {
    map<string,Aerolinea>::iterator  iteraAirlines;
    vector<Vuelo*> vuelosADev;
    for (iteraAirlines = airlines.begin();iteraAirlines!=airlines.end(); ++iteraAirlines) {
        vector<Vuelo*> aux = iteraAirlines->second.getVuelos(fNumber);
       //Concatenamos el vector
      vuelosADev.insert(vuelosADev.end(),aux.begin(),aux.end());
    }
    return vuelosADev;
}
/**
 * @brief BuscaVuelosOperados por icao y fecha
 * @param icaoAerolinea
 * @param f
 * @return
 */
vector<Vuelo *> VuelaFlight::vuelosOperadosPor(string icaoAerolinea, Fecha f) {
    map<string,Aerolinea>::iterator  iteraAirlines;
    vector<Vuelo*> vuelosADev;
    for (iteraAirlines = airlines.lower_bound(icaoAerolinea);iteraAirlines!=airlines.end(); ++iteraAirlines) {
      vector<Vuelo*> aux = iteraAirlines->second.getVuelos(f,f);
        //Concatenamos el vector
        vuelosADev.insert(vuelosADev.end(),aux.begin(),aux.end());
    }
    return vuelosADev;
}
/**
 * @brief Metodo que buscaVuelosDestAerop
 * @param paisOrig
 * @param iataAeroDest
 * @return
 */
set<string > VuelaFlight::buscaVuelosDestAerop(string paisOrig, string iataAeroDest) {
    //Primero obtengo los aeropuertos por pais
    list<Ruta*> rutasAeropuertosdePaisOrigen = buscarRutasPaisOrig(paisOrig);
    //Conjunto set con los identifcadores del vuelo
    set<string> identificadores;

    //Recorremos las rutas
    list<Ruta*>::iterator itrutas = rutasAeropuertosdePaisOrigen.begin();
        for (itrutas;itrutas!=rutasAeropuertosdePaisOrigen.end(); ++itrutas) {
            if(iataAeroDest == (*itrutas)->getDestination()->getIata()){
                    for (Vuelo *vuelo : (*itrutas)->getVuelos()) {
                        identificadores.insert(vuelo->getFlightNumber());
                    }
            }
        }

    return  identificadores;

}
/**
 * @brief Mismo metodo que getRutasOrig por iata pero este por pais
 * @param pOrig
 * @return
 */
list<Ruta *> VuelaFlight::buscarRutasPaisOrig(string pOrig) {
    list<Ruta>::iterator i;
    list<Ruta *> lista;
    //Recorremos todos los aeropuertos
    for(i=rutas.begin(); i!=rutas.end();i++){
        //Obtenemos los datos
        string origenBusq = i->getOrigin()->getIsoPais();
        //En caso de que se encuentre
        if(origenBusq==pOrig){
            //Devolvemos el dato

            //El iterador no es como un puntero y entonces lo que hacemos es devolver el dato * y su direccion &
            lista.push_back(&(*i));
        }
    }
    return  lista;


}

/**
 * @brief Ejercicio Por Pareja buscar Aeropuertos dentro de Aerolinea por icao
 * @param icaoAerolinea
 * @return
 */

vector<Aeropuerto *> VuelaFlight::buscaAeropuertosAerolinea(string icaoAerolinea) {
    set<Aeropuerto*> setAeros;
    vector<Aeropuerto*> vAeroports;
    vector<Vuelo*> vVuelos;
    vector<Vuelo*>::iterator itVuelos;
    Aerolinea aaero = buscaAerolinea(icaoAerolinea);
    vVuelos = aaero.getFlights();
    itVuelos = vVuelos.begin();
    for (;itVuelos!=vVuelos.end();itVuelos++) {
            setAeros.insert((*itVuelos)->getAirpOrigin());
            setAeros.insert((*itVuelos)->getAirpDest());
    }
    for (Aeropuerto *aero : setAeros) {
        vAeroports.push_back(aero);
    }
    return vAeroports;
}
