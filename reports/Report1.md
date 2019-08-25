# Implementación de Algoritmos para Solución de Sistemas de Ecuaciones Lineales

## Descripción

Existen diversos métodos para resolver Sistema de Ecuaciones Lineales, su uso y eficiencia depedende en gran medida de las propiedades y característica que tenga su representación matricial correspondiente.

Durante esta primera entrega se implementaron diversos algoritmos de solución para ciertas matrices en especial.

1. Solución de una matriz diagonal

2. Solución de una matriz triangular superior mediante sustitución hacia atrás

3. Solución de una matriz triangular inferior mediante sustitución hacia atrás

4. Solución mediante Eliminación Gaussiana

5. Solución mediante Eliminación Gaussiana con Pivoteo

6. Solución mediante el Método de Doolittle

7. Solución mediante el Método de Cholesky

8. Generación de la matriz Inversa mediante el Método de Cholesky

Notemos que para todos los casos anteriores las matrices usadas son cuadradas.

## Solución de una Matriz Diagonal

Dada una Matriz Diagonal de la forma $Ax = b$:

$$
\begin{pmatrix} 
	a_{0,0} & 0 & 0 & \dots & 0 \\
	0 & a_{1,1} & 0 & \dots & 0 \\
	0 & 0 & a_{2,2} & \dots & 0 \\
	\vdots & \vdots & \vdots & \vdots & \vdots \\
	0 & 0 & 0 & \dots & a_{n,n} \\
\end{pmatrix}
\begin{pmatrix} 
	x_{0} \\
	x_{1} \\
	x_{2} \\
	\vdots \\
	x_{n} \\
\end{pmatrix}
=
\begin{pmatrix} 
	b_{0} \\
	b_{1} \\
	b_{2} \\
	\vdots \\
	b_{n} \\
\end{pmatrix}
$$

La solución para cada $x_i$ está dada por:
$$
x_i = \frac{b_i}{a_{i,i}}, i \in [0, 1, ..., n]
$$

### Algoritmo

```
n -> Tamaño de la matriz
a[n][n] -> Matriz A
b[n] -> Vector b
x[n] -> Vector solución de tamaño n

Desde i=0 hasta n:
	x[i] = b[i] / a[i][i]
```

### Ejemplo de prueba

#### Entrada

Matriz *A*:

```
4 4

1.0 0.0 0.0 0.0
0.0 2.0 0.0 0.0
0.0 0.0 3.0 0.0
0.0 0.0 0.0 4.0
```

Matriz *b*:

```
4 1

1.0
2.0
3.0
4.0
```

#### Salida

```
1.000000 0.000000 0.000000 0.000000 1.000000
0.000000 2.000000 0.000000 0.000000 2.000000
0.000000 0.000000 3.000000 0.000000 3.000000
0.000000 0.000000 0.000000 4.000000 4.000000

X_1 = 1.000000
X_2 = 1.000000
X_3 = 1.000000
X_4 = 1.000000

Determinant: 24.000000
```

### Observaciones y mejoras

- Dado que la propiedad de la matriz en este caso es ser diagonal la implementación de la solución es sumamente sencilla.
- Se se sabe de antemano que la matriz es una matriz diagonal puede ser guardado en un arreglo de tamaño *n* sin el caso así lo permite.

## Solución de una matriz triangular superior mediante sustitución hacia atrás

Dada una matriz de la forma $Ax = b$ de la forma:
$$
\begin{pmatrix} 
	a_{0,0} & a_{0,1} & a_{0,2} & ... & a_{0,n} \\
	0 & a_{1,1} & a_{1,2} & ... & a_{1,n} \\
	0 & 0 & a_{2,2} & ... & a_{1,n} \\
	\vdots & \vdots & \vdots & \vdots & \vdots \\
	0 & 0 & 0 & ... & a_{n,n} \\
\end{pmatrix}
\begin{pmatrix} 
	x_{0} \\
	x_{1} \\
	x_{2} \\
	\vdots \\
	x_{n} \\
\end{pmatrix}
=
\begin{pmatrix} 
	b_{0} \\
	b_{1} \\
	b_{2} \\
	\vdots \\
	b_{n} \\
\end{pmatrix}
$$
La solución para cada $x_i$ está dada por:
$$
x_i = \frac{b_i - \sum_{j=i+1}^{n} a_{i,j}x_j}{a_{i,i}}, i \in [n, n-1, ..., 0]
$$

### Algoritmo

```
n -> Tamaño de la matriz
a[n][n] -> Matriz A
b[n] -> Vector b
x[n] -> Vector solución de tamaño n

Desde i=n hasta 0:
	sol[i] = b[i]
	Desde j = i+i hasta n:
		sol[i] = soli[i] - (a[i][j] * x[j])
	sol[i] = sol[i] / a[i][i]
```

### Observaciones y mejoras

- Dado que solo se usa la mitad de la matriz, en vez de usar un una matriz de tamaño $n x n$ podemos usar un arreglo de tamaño $\frac{n * (n+1)}{2}$, cuyo i-ésimo renglón tendría tamaña $n-i, i \in [0, 1, ...,  n]$.
- 