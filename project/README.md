# Dibujado de Grafos mediante Stress Majorization

## Objetivo

Implementation del proceso de Stress Majorization para el dibujado de grafos.

## Compilación

``` bash
$ make
```

## Ejecución

### Entrada

El ejecutable generado recibe dos argumentos de entrada

- El archivo que contiene la descripción de la matriz a procesar en formato *mtx*, debe estar limpia de los comentarios del encabezado
- El parámetro opcional *-w* si dicha matriz contiene un tercer parámetro dispues de las coordenadas


Ejemplo 1, la matriz no contiene un tercer dato a parte de las coordenadas

``` bash
$ ./main ./main inputs/dwt_1005/dwt_1005.mtx
```


Ejemplo 2, la matriz contiene un tercer dato a parte de las coordenadas

``` bash
$ ./main inputs/cage9/cage9.mtx -w
```

### Salida

Layout del dibujado del grafo correspondiente
