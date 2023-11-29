#include "VuelaFlight.h"
/**
 * @brief VuelaFlight
 */
VuelaFlight::VuelaFlight() : airports(76368,0.7),routesOrig(),routesDest(),airlines() {

    cargaAeropuertos("aeropuertos_v3.csv");
    cargaAerolineas("aerolineas_v1.csv");
    cargarRutas("rutas_v1.csv");
    cargarVuelos("infovuelos_v1.csv");

    cout<< "Tamaño Aerolineas: " << tamaAirlines() <<endl
        << "Tamaño aeropuertos: " << tamaAeropuertos() << endl
        << "Tamaño rutas: " << tamaRutasOrig() << endl
        <<"Tamaño Vuelos: "<< tamaVuelos() << endl <<endl;
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
    multimap<string,Ruta>::iterator origen=routesOrig.find(idAerOrig);
    if(origen!=routesOrig.end()){
        for ( ; origen!=routesOrig.end() ; origen++) {
            if (origen->second.getOrigin()->getIata()==idAerOrig &&
            origen->second.getDestination()->getIata()==idAerDest)
                return *(&origen->second);
        }
    }

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
    Ruta* r=&routesOrig.insert(orig)->second;
    pair<string,Ruta*> dest(AerDest->getIata(),r);
    routesDest.insert(dest);
    aerolineaEncontrada->linkAerolRuta(r);

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

void VuelaFlight::addAeropuerto(const Aeropuerto aeropuerto) {
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
    if(&orig && &dest  && aerolineaEncontrada!=airlines.end()){
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
    map<string,Aerolinea>::iterator mapaEncuentraVuelos;
    mapaEncuentraVuelos=airlines.find(fNumber.substr(0,3));
    //Obtenemos el aeropuerto de origen y el de destino
    //Buscamos el aeropuerto de origen
    Aeropuerto *orig = airports.buscar(airports.djb2((unsigned  char*) iataAeroOrig.c_str()),iataAeroOrig);
    //Buscamos el aeropuerto de destino
    Aeropuerto *dest = airports.buscar(airports.djb2((unsigned  char*) iataAeroDest.c_str()),iataAeroDest);
    if(mapaEncuentraVuelos!=airlines.end() && &orig!= nullptr && &dest!= nullptr){
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
    clock_t lecturaRutas = clock();

    ifstream is;
    stringstream  columnas;
    string fila;

    string flightnumber = "";
    string  departurePlane = "";
    string  arrivalPlane = "";
    string plane = "";
    string datoMeteo = "";
    string fecha = "";

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
void VuelaFlight::cargaAeropuertos(string fichAeropuertos) {
    clock_t lecturaAero = clock();

    ifstream is;
    stringstream  columnas;
    string fila;

    string id = "";
    string iata = "";
    string tipo="";
    string nombre="";
    string latitud_str="";
    string longitud_str="";
    string continente="";
    string iso_pais="";

    is.open(fichAeropuertos); //carpeta de proyecto
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
                //Insertamos en la tabla hash
                addAeropuerto(Aeropuerto(id,iata,tipo,nombre,continente,iso_pais, UTM(stof(latitud_str),stof(longitud_str))));
            }
        }
        //Tras leer ordenamos el vector por Codigo Iata
        is.close();
    }else{
        std::cout << "Error de apertura en archivo" << std::endl;
    }
    std::cout << "Tiempo lectura de aeropuertos: " << ((clock() - lecturaAero) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
}
/**
 * @brief Metodo que cargaLasAerolineas
 */
void VuelaFlight::cargaAerolineas(string fichAerolineas) {
    clock_t lecturaAerolineas = clock();

    ifstream is;
    stringstream  columnas;
    string fila;

    string idAerolineaStr;
    string icao = "";
    string nombreAero="";
    string pais="";
    string activo="";

    is.open(fichAerolineas); //carpeta de proyecto
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
void VuelaFlight::cargarRutas(string fichRutas) {
    clock_t lecturaRutas = clock();

    ifstream is;
    stringstream  columnas;
    string fila;

    string icaoRuta = "";
    string  origen2 = "";
    string destino2 = "";

    is.open(fichRutas); //carpeta de proyecto
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
/**
 * @brief Metodo que muestra el estado de la tabla
 */
void VuelaFlight::mostrarEstadoTabla() {
    cout<<"------------ESTADO DE LA TABLA HASH------------"<<endl;
    cout<<"El numero maximo de colisiones es: "<<airports.nMaxColisiones()<<endl;
    cout<<"El numero de veces que se superan 10 colisiones es: "<<airports.numMax10()<<endl;
    cout<<"El promedio de colisiones es: "<<airports.promedioColisiones()<<endl;
    cout<<"El factor de carga es: "<<airports.factorCarga()<<endl;
    cout<<"El tam de la tabla es: "<<airports.tamTabla()<<endl;
    cout<<"La tabla tiene: "<<airports.getTamLog()<<" elementos"<<endl;

}
/**
 * @brief Metodo que eliminaElAeropuerto
 * @param IATA
 */
void VuelaFlight::eliminarAeropuerto(string IATA) {

    map<string,Aerolinea>::iterator  itAerolinea;
    for (itAerolinea = airlines.begin(); itAerolinea!= airlines.end() ; ++itAerolinea) {
            itAerolinea->second.bajaAeropuerto(IATA);
    }

    multimap<string,Ruta*>::iterator  itRutasDest;
    for (itRutasDest = routesDest.begin(); itRutasDest!= routesDest.end() ; ++itRutasDest) {
        if(itRutasDest->second->getDestination()->getIata() == IATA ||
                itRutasDest->second->getOrigin()->getIata() == IATA) {
            routesDest.erase(itRutasDest);
        }
    }
    multimap<string,Ruta>::iterator  itRutasOrigen;
    for (itRutasOrigen = routesOrig.begin(); itRutasOrigen!= routesOrig.end() ; ++itRutasOrigen) {
       if(itRutasOrigen->second.getOrigin()->getIata() == IATA) {
           routesOrig.erase(itRutasOrigen);
       }
    }

    if(!airports.borrar(airports.djb2((unsigned  char*) IATA.c_str()),IATA )){
        throw invalid_argument("Se cagó encima el borrado");
    }


}

Aeropuerto *VuelaFlight::buscaAeropuerto(string IATAAirport) {
    Aeropuerto* aeropuerto = airports.buscar(airports.djb2((unsigned  char*) IATAAirport.c_str()),IATAAirport);
    if(aeropuerto){
        return  aeropuerto;
    }
    return nullptr;
}

void VuelaFlight::eliminarAeropuertoInactivo() {
    cout<<"Eliminando inactivos: "<<endl;
    vector<Aeropuerto*> vaeropuerto=getAeropuertos();
    for (int i = 0; i < vaeropuerto.size(); ++i) {
        list<Ruta*> lista=buscarRutasOrigen(vaeropuerto[i]->getIata());
        if (lista.empty()) {
            //cout << i + 1 << endl;
            //eliminarAeropuerto(vaeropuerto[i]->getIata());
            airports.borrar(airports.djb2((unsigned  char*) vaeropuerto[i]->getIata().c_str()),vaeropuerto[i]->getIata() );
        }
    }
}

vector<Aeropuerto *> VuelaFlight::getAeropuertos() {
    return  airports.getAeros();
}
