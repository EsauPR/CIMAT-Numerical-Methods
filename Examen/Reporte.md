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



## Problema 2

Comparación entre métodos directos e iterativos para resolver el sistema $Ax=b$ con los archivos *A_5000.mtx* y *b_5000.vec* correspondiendo a la matriz $A$ y el vector $b$ respectivamente.

### Solución

Se procedió a graficar los puntos dados de la matriz en GNU Octave para observar su distribución a lo lo largo de la matriz:

![](/home/esaup/Imágenes/Screenshot_20191030_204046.png)

Además de la observación obtenida y el resultado del proceso de restar su inversa con ella misma se obteniendo como máximo valor un cero se llegó a la conclusión que es una matriz simétrica.

También se procedió a hacer el cálculo para saber si la matriz es diagonalmente dominante comparando la norma del renglo i-ésimo (excepto el que corresponde a la diagonal) y con el valor de la diagonal correspondiente al mismo renglón, resultando que la matriz no es diagonalmente dominante.

Se procedió a realizar el cálculo de la solución con los siguientes algoritmos:

-   Método de Gauss con pivoteo
-   Método de Doolittle
-   Método de Choolesky
-   Método de Jacobi
-   Método de Gauss Seidel
-   Método de Gradiente conjugado

La siguiente tabla muestra los resultados obtenidos:

| Método        | Tiempo de ejecución | Memoria  | No. de Iteraciones | Error Medio |
| ------------- | ------------------- | -------- | ------------------ | ----------- |
| Gauss Pivoteo | 337.45s             | 196924Kb | N/A                |             |
| Doolittle     | 254.42s             | 197652Kb | N/A                |             |
| Choolesky     | 124.02s             | 197808Kb | N/A                |             |
| Jacobi        |                     |          |                    |             |
| Gauss Seidel  |                     |          |                    |             |
| Gradiente     |                     |          |                    |             |



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

#### Cálculo de los 10 valores propios más grandes

Para realizar el cálculo de los 10 valores propios más grandes se usó el algoritmo de Potencia con deflación, los 10 valores propios más grandes obtenidos son los siguientes:

```
Eigen Value  1: 5.199974e+01
Eigen Value  2: 5.199984e+01
Eigen Value  3: 5.199985e+01
Eigen Value  4: 5.199960e+01
Eigen Value  5: 5.199981e+01
Eigen Value  6: 5.199977e+01
Eigen Value  7: 5.199929e+01
Eigen Value  8: 5.199964e+01
Eigen Value  9: 5.199939e+01
Eigen Value 10: 5.199930e+01
```

Los vectores propios se encuentran en el archivo adjunto con nombre *max_eigens.txt*. Se procedió a corroborar el calculo correcto de ellos mediante con ayuda del software de GNU Octave:
$$
\phi_i = \frac{A*\phi_i}{\lambda_i}
$$
dónde $\lambda_i$ es en valor propio y $\phi_i$ es el vector propio asociado.

*Tiempo de Ejecución*: 2hr 23min 345.223 seg.

#### Cálculo de los 10 valores 

Los 10 vectores propios más pequeños se obtuvieron mediante el algoritmo de *Potencia Inversa con deflación*, con los siguientes resultados:

```
Eigen Value  1: 1.600010e+01
Eigen Value  2: 1.600084e+01
Eigen Value  3: 1.600171e+01
Eigen Value  4: 1.600075e+01
Eigen Value  5: 1.600138e+01
Eigen Value  6: 1.600258e+01
Eigen Value  7: 1.600343e+01
Eigen Value  8: 1.600291e+01
Eigen Value  9: 1.600618e+01
Eigen Value 10: 1.600440e+01
```

Los vectores propios asociados a cada valor propio se encuentran en el archivo adjunto **min_eigens.txt*. Igualmente se procedió a realizar la comprobación de los resultados mediante la ecuación $(3)$.

*Tiempo de Ejecución*: 24min 737.718 seg.



## Problema 4

