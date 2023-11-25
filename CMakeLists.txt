cmake_minimum_required(VERSION 3.26)
project(PR5)

set(CMAKE_CXX_STANDARD 17)

add_executable(PR5 main.cpp  Ruta.h Ruta.cpp VuelaFlight.cpp VuelaFlight.h  UTM.cpp UTM.h Aeropuerto.cpp Aerolinea.cpp Aeropuerto.h Aerolinea.h
        Vuelo.cpp Vuelo.h  fecha.cpp fecha.h
        ThashAerop.cpp
        ThashAerop.h)
