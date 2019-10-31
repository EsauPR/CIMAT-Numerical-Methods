# Exámen - Métodos Numéricos

**Oscar Esaú Peralta Rosales**

## Problema 1

Solución al sistema de ecuaciones lineales $Ax = b$, con las matrices $A$ *1000.mtx* y $b$ *1000.vec* y cálculo

### Cálculo de la inversa de la matriz

Para obtener la inversa de la matriz se usó el Método de Doolittle para resolver el sistema de ecuaciones generado por cada columna de la matriz inversa:

La i-ésima columna de la matriz $A'$ estará dado por la solución de:
$$
A'[:][i] = LUI[:][i], i \in [1,n]
$$
Al usar este método se necesita realizar una fatorización $LU$ y resolver 1000 sistemas de ecuaciones con dos matrices triangulares.

La matriz inversa se generó en el archivo *INV_1000.mtx* como se indicó. Se procedió a comprobar realizando la multiplicación de la matriz inversa por la matriz original y verificando que la diagonal fueran solo número 1’s, se verificó además que los elementos fuera de la diagonal fueran ceros o muy cercanos a cero, en este caso en orden de magnitud aproximadamente de $e-9$.

*Tiempo de Ejecución*: 7.234 seg.

### Cálculo de la solución del sistema

Para realizar el cálculo de la  solución del sistema antes descrito se aprovechó el cálculo de la matriz inversa $A' $ realizado previamente obteniendo el vector solución como $x = A^tb$.

La solución se generó en el archivo *X_1000.vec* como se indicó en el problema.

## Problema 3

Obtener los 10 valores propios más grandes y los 10 valores propios más chicos de una matriz cuyos renglones están determinados por:
$$
−4x_{i−2} − 8x_{i−1} + 40x_i − 8x_{i+1} − 4x_{i+2}\ para\ i = 1, 2, 3, \dots, 2000
$$
Dada la ecuación anterior se procedió a generar una matriz cuadrada de dimensiones $2000 x 2000$ mediante el siguiente código en **C**:

```c
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define SIZE 2001

int MATRIX[SIZE][SIZE];

int main(int argc, char const *argv[]) {
    int xs[5];
    int xv[5] = {-4, -8, 40, -8, -4 };

    for (int i = 1; i < SIZE; i++) {
        xs[0] = i - 2;
        xs[1] = i - 1;
        xs[2] = i;
        xs[3] = i + 1;
        xs[4] = i + 2;

        for (int j = 0; j < 5; j++) {
            if(xs[j] >= 0 && xs[j] < SIZE ) {
                MATRIX[i][xs[j]] = xv[j];
            }
        }
    }
    
    return 0;
}
```

La matriz generada consta de 1 banda de ancho 5 sobre la diagonal.

![image-20191030202442966](/home/esaup/Documentos/CIMAT/Métodos Numéricos/Numerical-Methods/Examen/image-20191030202442966.png)

Para realizar el cálculo de los 