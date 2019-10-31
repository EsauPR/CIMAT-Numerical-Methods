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

| Método        | Tiempo de ejecución | Memoria  | No. de Iteraciones | Error        |
| ------------- | ------------------- | -------- | ------------------ | ------------ |
| Gauss Pivoteo | 337.45s             | 196924Kb | N/A                | 1.5973x10^-8 |
| Doolittle     | 254.42s             | 197652Kb | N/A                | 1.5973x10^-8 |
| Choolesky     | 124.02s             | 197808Kb | N/A                | 1.5973x10^-8 |
| Jacobi        | 344.51s             | 90860Kb  | 1000               | 3.68345x10^6 |
| Gauss Seidel  | 156.19s             | 90792Kb  | 5000               | 1.4094x10^5  |
| Gradiente     | 9.14s               | 90888Kb  | 1138               | 1.5973x10^-8 |

Los métodos que más inconvenientes presentaron fueron los dos iterativos de Jacobi y Gauss Seidel puesto que como se vió la matriz no es diagonalmente dominante por tanto la convergencia no es garantizada, aunque con el método de Gauss-Seidel se obtuvieron valores relativamente cercanos.

El mejor método fue el de Gradiente conjugado, con un tiempo de ejecución de 9.15 segundos obteniendo un error de $3.052713e^{-11}$.

El método de directo de Gauss a pesar de ser uno de los conocidos es uno de los menos eficientes sin embargo la solución es asegurada al igual que los los demás algoritmos exactos, en cambio como se vió los iterativos tienen convergencia bajo ciertas condiciones las cuales siempre no pueden ser cumplidas, exceptuando al el método de gradiente que ha demostrado ser bastante eficiente con muy buenos resultados de aproximación.

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

### Desarrollo del polinomio de Hermite

El polinomio de Hermite es definido como aquel que interpola $n+1$ puntos de una función $f(x)$ y $f'(x)$, así entonces el el polinomio requerido es de grado $\le 2n+1$, que satisface $2(n+1)$ restricciones en $n+1$ puntos $x_i: i=0,1,2, ..., n$:
$$
P_{2n+1}(x_i) = f(x) \\
P'_{2n+1}(x_i) = f'(x) \\
$$
Expresando el polinomio en términos de los puntos anteriores tenemos que:
$$
P_{2n+1}(x_i) = \sum_{i=0}^{n}u_i(x)P_{2n+1}(x_i) + \sum_{i=0}^{n}v_i(x)P_{2n+1}(x_i) \\
= \sum_{i=0}^{n}u_i(x)f(x_i) + \sum_{i=0}^{n}v_i(x)f'(x_i)
$$
en donde $u_i(x)$ y $v_i(x)$ son polinomios de grado $\le 2n+1$, pudiendo expresarlos en términos de los coeficientes del polinomio de Lagrange $l_i(x)$:
$$
u_i(x) = (a_ix+b_i)l^2(x)
$$

$$
v_i(x) = (c_ix+d_i)l^2(x)
$$

dónde $l_i$ está dado por:
$$
l_i(x) = \prod_{k=0, k\ne i}^{n} \frac{x-x_k}{x_i-x_k}
$$
y $a_i$, $b_i$, $c_i$. $d_i$ son constantes que como se demostró en la *tarea 12* están determinadas por:
$$
a_i = -2l'_i(x_i),\ b_i = 1 + 2x_il'_i(x_i), \ c_i = 1, \ d_i = -x_i
$$
y sustituyendo en la ecuación $6$ y $7$ tenemos:
$$
u_i(x) = (-2l'_i(x_i)x+1+2x_il'_i(x_i))l^2_i(x)
$$

$$
v_i(x) = (x-x_i)l^2_i(x)
$$

y así sustituyendo en la ecuación $5$ tenemos:
$$
P_{2n+1}(x_i) = \sum_{i=0}^{n}u_i(x)f(x_i) + \sum_{i=0}^{n}v_i(x)f'(x_i) \\
= \sum_{i=0}^{n}(-2l'_i(x_i)x+1+2x_il'_i(x_i))l^2_i(x)f(x_i) + \sum_{i=0}^{n}(x-x_i)l^2_i(x)f'(x_i)
$$

### Desarrollo del método de integración del polinomio de Hermite de 3 pasos

El polinomio de Hermite que pasa por los puntos:
$$
(x_0 , y_0), (x_1 , y_1), (x_2, y_2 ), (x_0 , f_0 ), (x_1 , f_1 ), (x_2 , f_2 ), fi = f(xi , yi)
$$
