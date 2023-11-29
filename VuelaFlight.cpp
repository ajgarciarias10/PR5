#include "VuelaFlight.h"
/**
 * @brief VuelaFlight
 */
VuelaFlight::VuelaFlight() :airports(),routesOrig(),routesDest(),airlines() {
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
        << "Tamaño rutas: " << tamaRutasOrig() << endl
        <<"Tamaño Vuelos: "<< tamaVuelos() << endl <<endl;
#pragma  endregion
}
/**
 * @brief Constructor parametrizado
 * @param vector
 * @param ruta
 */
VuelaFlight::VuelaFlight(ThashAerop aeropuerto, multimap<string,Ruta> rutasorig, multimap<string,Ruta*> rutasdes ,map<string,Aerolinea> airlines):
        airports(aeropuerto),airlines(airlines),routesDest(rutasdes),routesOrig(rutasorig) {}
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
    multimap<string,Ruta>::iterator origen;
    origen=routesOrig.find(idAerOrig);
    if(origen!=routesOrig.end()){
        multimap<string,Ruta*>::iterator destino=routesDest.find(idAerDest);
        if(destino != routesDest.end())
            for (; origen!=routesOrig.end(); ++origen) {
                if (origen->second.getDestination()->getIata()==idAerDest)
                    return *(destino->second);
            }
    }else
        throw invalid_argument("Error::buscarRutasOriDeS:No se ha encontrado la ruta");
}
/**
 * @brief BuscarRutasOrigen
 * @param idAerOrig
 * @return
 */
list<Ruta *> VuelaFlight::buscarRutasOrigen(string idAerOrig) {
    multimap<string,Ruta>::iterator i;
    list<Ruta *> lista;
    //Recorremos todos los aeropuertos
    for(i=routesOrig.begin(); i!=routesOrig.end();i++){
        //En caso de que se encuentre
        if(i->second.getOrigin()->getIata()==idAerOrig){
            lista.push_back(&((*i).second));
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
    Ruta ruta(AerDest,AerOrig,aerolineaEncontrada);
    pair<string,Ruta> orig(AerOrig->getIata(),ruta);
    pair<string,Ruta*> dest(AerDest->getIata(),&ruta);

    routesOrig.insert(orig);
    routesDest.insert(dest);
    //este ns lo que hay que hacer, esta hecho provisional
    aerolineaEncontrada->linkAerolRuta(&(ruta));

}

/**
 * @brief Constructor Copia
 * @param vl
 */

VuelaFlight::VuelaFlight(const VuelaFlight &vl) : airports(vl.airports), routesDest(vl.routesDest),routesOrig(vl.routesOrig),airlines(vl.airlines){}
/**
 * @brief Añade aeropuerto
 * @param aeropuerto
 */

void VuelaFlight::añadeAeropuerto(const Aeropuerto aeropuerto) {
    airports.insertar(airports.djb2( (unsigned  char*) aeropuerto.getIata().c_str()),aeropuerto);
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
    //Buscamos el aeropuerto de origen
    Aeropuerto *orig = airports.buscar(airports.djb2((unsigned  char*) origen2.c_str()),origen2);
    //Buscamos el aeropuerto de destino
    Aeropuerto *dest = airports.buscar(airports.djb2((unsigned  char*) destino2.c_str()),destino2);
    if(&orig && &dest  && &aerolineaEncontrada){
        //Añadimos nueva ruta a partir del origen el destino y el icao
        addNuevaRuta(&(*orig), &(*dest),&aerolineaEncontrada->second);
    }
}

/**
 * @brief Metodo que devuelve el tamaño del vector
 */
long VuelaFlight::tamaAeropuertos() {
    return airports.numElementos();
}
/**
 * @brief Metodo que devuelve el tamaño de la lista de rutas de origen
 */
long VuelaFlight::tamaRutasOrig() {
    return routesOrig.size();
}

/**
 * @brief Metodo que devuelve el tamaño de la lista de rutas de destino
 */
long VuelaFlight::tamaRutasDest() {
    return routesDest.size();
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
    //Buscamos el aeropuerto de origen
    Aeropuerto *orig = airports.buscar(airports.djb2((unsigned  char*) iataAeroOrig.c_str()),iataAeroOrig);
    //Buscamos el aeropuerto de destino
    Aeropuerto *dest = airports.buscar(airports.djb2((unsigned  char*) iataAeroDest.c_str()),iataAeroDest);
    if(mapaEncuentraVuelos!=airlines.end() && orig!= nullptr && dest!= nullptr){
        Vuelo v(fNumber,plane,datosMeteo,f,&(*orig),&(*dest),&(mapaEncuentraVuelos->second));
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
    multimap<string,Ruta>::iterator i;
    list<Ruta *> lista;
    //Recorremos todos los aeropuertos
    for(i=routesOrig.begin(); i!=routesOrig.end();i++){
        //Obtenemos los datos
        string origenBusq = i->second.getOrigin()->getIsoPais();
        //En caso de que se encuentre
        if(origenBusq==pOrig){
            //Devolvemos el dato

            //El iterador no es como un puntero y entonces lo que hacemos es devolver el dato * y su direccion &
            lista.push_back(&(i->second));
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
