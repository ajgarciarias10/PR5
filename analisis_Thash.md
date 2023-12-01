# Análisis de tablas de dispersión

* *Abraham García Hurtado*
* *Antonio José García Arias*

## Tamaño de tabla: 112327
| función                      | máximo de colisiones | factor de carga |   promedio de colisiones    |
|------------------------------|:--------------------:|:---------------:|:---------------------------:|
| Hash1(Dispersion Cuadratica) |         170          |     0.6795      |            7.46491            |
| Hash2(Dispersion Doble)      |        28         |      0.679516      |             1.15284            |
| Hash3(Dispersion Doble)      |        33         |      0.679516      |              0.868227            |
## Tamaño de tabla: 117497
| función                      | máximo de colisiones |  factor de carga  |   promedio de colisiones    |
|------------------------------|:--------------------:|:-----------------:|:---------------------------:|
| Hash1(Dispersion Cuadratica) |        123         |       0.649617       |            4.99548            |
| Hash2(Dispersion Doble)      |        36554         |       0.649617       |            1.60154            |
| Hash3(Dispersion Doble)      |        28         |       0.649617       |            0.73699        |

## Justificación de la configuración elegida
Hemos optado por la funcion de hash3 ya que obtenemos un promedio de colisiones menor y un maximo de colisiones menor, lo que hace que el programa sea mas eficiente.
## Programa prueba 2
Tiempo lectura de la prueba 2 con tabla: 0.359 segs.
Tiempo lectura de la prueba 2 con el mapa : 0.799 segs.
Como se puede observar en esta prueba de busqueda con las diferentes estructuras de datos.
Podemos ver que es mejor realizar la busqueda con una tabla Hash que con un mapa.