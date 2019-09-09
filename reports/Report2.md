# Implementación de Algoritmos para Soluciones Iterativas,  búsqueda de Raíces de Funciones y obtención de Valores y Vectores Propios

## Descripción

Se realizó la implementación de los siguientes algoritmos:

1. Algoritmo de Jacobi para solución de sistema lineales de ecuaciones.
2. Algoritmos de Gauss-Seidel para solución de sistema lineales de ecuaciones.
3. Algoritmo de Bisección para encontrar raíces de funciones.
4. Algoritmo de Newton-Raphson para encontrar raíces de funciones.
5. Algoritmo Método de Potencia para encontrar el valor y vector propio más grande de una matriz.

## Algoritmo de Jacobi para solución de sistema lineales de ecuaciones.

El Método de Jacobi es un método iterativo para encontrar soluciones a sistemas de ecuaciones lineales de la forma $Ax= b$. Se define como sigue:

Sea una matriz cuadrada a $A_{nxn}$, $A$ se puede escribir de la forma:
$$
A = L+ D + U
$$

Dónde,
$$
A = 
\begin{pmatrix}
	a_{1,1} & a_{1,2} & ... & a_{1,n} \\
	a_{2,1} & a_{2,2} & ... & a_{2,n} \\
	\vdots & \vdots & \vdots & \vdots \\
	a_{n,1} & a_{n,2} & ... & a_{n,n} \\
\end{pmatrix}
$$

$$
L =
\begin{pmatrix}
	1 & 0 & ... & 0 \\
	a_{2,1} & 1 & ... & 0 \\
	\vdots & \vdots & \vdots & \vdots \\
	a_{n,1} & a_{n,2} & ... & 1 \\
\end{pmatrix}
$$

$$
D =
\begin{pmatrix}
	a_{1,1} & 0 & ... & 0 \\
	0 & a_{2,2} & ... & 0 \\
	\vdots & \vdots & \vdots & \vdots \\
	0 & 0 & ... & a_{n,n} \\
\end{pmatrix}
$$

$$
U = 
\begin{pmatrix}
	0 & a_{1,2} & ... & a_{1,n} \\
	0 & 0 & ... & a_{2,n} \\
	\vdots & \vdots & \vdots & \vdots \\
	0 & 0 & ... & 0 \\
\end{pmatrix}
$$

Donde $D$ es una matriz diagonal, $L$ es una matriz triangular inferior y $U$ es una matriz triangular superior. Así sea
$$
R = L + U
$$
y del sistema $Ax = b$ se tiene:
$$
Dx + Rx  = b
$$

$$
x = D^{-1}(b - Rx)
$$

Expresando la ecuación 3 de forma iterativa tenemos:
$$
x^{(k)} = D^{-1}(b - Rx^{(k-1)})
$$
Desglosando la función:
$$
x^{(k)}_i = \frac{1}{a_{ii}}(b_i - \sum_{j=1, j \neq i}^{n} a_{ij}x_{j}^{(k-1)}), i = 1,2,...,n
$$


### Pseudocódigo

```pseudocode
n -> Tamaño de la matrix
a[n][n] -> Matrix a
b[n] -> Vector b
xprev[n] -> Vector solucion previo
xnext[n] -> Vector solucion siguiente
MAX_ITER -> Número máximo de iteraciones
EPSILON -> Valor máximo de error esperado

xprev = b
for iter in [0, MAX_ITER]:
	error = 0.0
	for i in [0, n]:
		xnext[i] = b[i]
		for j in [0, n]:
			if i == j: continue
			xnext[i] -= a[i][j] * xprev[j]
		xnext[i] /= a[i][i]
		error += (xnext[i] - xprev[i]) ^ 2 / xnext[i] ^ 2
	error = sqrt(error)
	xprev = xnext
	if error <= EPSILON:
		break
	
xnext <- Contiene la solución
```

### Ejemplo de prueba

#### Entrada

Matriz A:

```
3 3
4.000000 -1.000000 0.000000 
-1.000000 4.000000 -1.000000 
0.000000 -1.000000 4.000000 
```

Matrix B;

```
2.0000000000
6.0000000000
2.0000000000
```

#### Salida

```
x_0: 1.0000004768
x_1: 2.0000002384
x_2: 1.0000004768
```

### Observaciones y mejoras

- Debido a la división en la fórmula podemos tener problemas si existe un cero sobre la diagonal, así que antes de empezar a implementar el algoritmo podemos realizar un pivoteo sobre las filas para evitar la existencia de ceros sobre la diagonal.
- En las primera iteraciones usando el como entrada la matriz *M_BIG.txt*  hay un overflow sobre el cálculo del error debido a que se divide sobre números muy pequeños, pero en las iteraciones sucesivas el error se corrige al aproximarse los valores de los vectores $xprev$ y $xnext$.

## Algoritmos de Gauss-Seidel para solución de sistema lineales de ecuaciones.

El Método de Gauss-Seidel es un método iterativo para encontrar soluciones a sistemas de ecuaciones lineales de la forma $Ax= b$.

Se define como sigue:
Sea una matriz cuadrada a $A_{nxn}$, $A$ se puede escribir de la forma:
$$
A = L+ D + U
$$

Dónde,
$$
A = 
\begin{pmatrix}
	a_{1,1} & a_{1,2} & ... & a_{1,n} \\
	a_{2,1} & a_{2,2} & ... & a_{2,n} \\
	\vdots & \vdots & \vdots & \vdots \\
	a_{n,1} & a_{n,2} & ... & a_{n,n} \\
\end{pmatrix}
$$

$$
L =
\begin{pmatrix}
	1 & 0 & ... & 0 \\
	a_{2,1} & 1 & ... & 0 \\
	\vdots & \vdots & \vdots & \vdots \\
	a_{n,1} & a_{n,2} & ... & 1 \\
\end{pmatrix}
$$

$$
D =
\begin{pmatrix}
	a_{1,1} & 0 & ... & 0 \\
	0 & a_{2,2} & ... & 0 \\
	\vdots & \vdots & \vdots & \vdots \\
	0 & 0 & ... & a_{n,n} \\
\end{pmatrix}
$$

$$
U = 
\begin{pmatrix}
	0 & a_{1,2} & ... & a_{1,n} \\
	0 & 0 & ... & a_{2,n} \\
	\vdots & \vdots & \vdots & \vdots \\
	0 & 0 & ... & 0 \\
\end{pmatrix}
$$

Donde $D$ es una matriz diagonal, $L$ es una matriz triangular inferior y $U$ es una matriz triangular superior. Así sea
$$
R = L + D
$$
y del sistema $Ax = b$ se tiene:
$$
Rx  = b - Ux
$$

$$
x = R^{-1}(b - Ux)
$$

Expresando la ecuación 3 de forma iterativa tenemos:
$$
x^{(k)} = R^{-1}(b - Ux^{(k-1)})
$$
Desglosando la función:
$$
x^{(k)}_i = \frac{1}{a_{ii}}(b_i - \sum_{j=1}^{i-1} a_{ij}x_{j}^{(k)} - \sum_{j=i+1}^{n} a_{ij}x_{j}^{(k-1)}), i = 1,2,...,n
$$

### Pseudocódigo

Observando la formula de arriba podemos notar que solo se necesitan los $x_i$ previos a la iteración $i$ actual, así que podemos usar solo vector para almacenarlos.

```pseudocode
n -> Tamaño de la matrix
a[n][n] -> Matrix a
b[n] -> Vector b
xnext[n] -> Vector solucion siguiente
MAX_ITER -> Número máximo de iteraciones
EPSILON -> Valor máximo de error esperado

xnext = b
for iter in [0, MAX_ITER]:
	error = 0.0
	for i in [0, n]:
		err_prev = xnext[i]
		xnext[i] = b[i]
		for j in [0, n]:
			if i == j: continue
			xnext[i] -= a[i][j] * xnext[j]
		xnext[i] /= a[i][i]
		error += (xnext[i] - err_prev[i]) ^ 2 / xnext[i] ^ 2
	error = sqrt(error)
	if error <= EPSILON:
		break
	
xnext <- Contiene la solución
```

### Ejemplo de prueba

#### Entrada

Matriz A:

```
3 3
4.000000 -1.000000 0.000000 
-1.000000 4.000000 -1.000000 
0.000000 -1.000000 4.000000 
```

Matrix B;

```
2.0000000000
6.0000000000
2.0000000000
```

#### Salida

```
x_0: 1.0000004768
x_1: 2.0000002384
x_2: 1.0000004768
```

### Observaciones y mejoras

- Debido a la división en la fórmula podemos tener problemas si existe un cero sobre la diagonal, así que antes de empezar a implementar el algoritmo podemos realizar un pivoteo sobre las filas para evitar la existencia de ceros sobre la diagonal.
- En las primera iteraciones usando el como entrada la matriz *M_BIG.txt*  hay un overflow sobre el cálculo del error debido a que se divide sobre números muy pequeños, pero en las iteraciones sucesivas el error se corrige al aproximarse los valores de los vectores $xprev$ y $xnext$.