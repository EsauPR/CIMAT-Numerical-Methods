# Implementación de Algoritmos para Solución de Sistemas de Ecuaciones Lineales

## Descripción

Existen diversos métodos para resolver Sistema de Ecuaciones Lineales, su uso y eficiencia depedende en gran medida de las propiedades y carácteristica que tenga su representación matricial correspondiente.

Durante esta primera entrega se implementaron diversos algoritmos de solución para ciertas matrices en especial.

1. Solución de una matriz diagonal

2. Solución de una matriz triangular superior mediante sustitución hacia atrás

3. Solucion de una matriz triangular inferior mediante sustitución hacia atrás

4. Solución mediante Eliminación Gaussiana

5. Solución mediante Eliminación Gaussiana con Pivoteo

6. Solución mediante el Método de Doolittle

7. Solución mediante el Método de Cholesky

8. Generación de la matrix Inversa mediante el Metodo de Cholesky

Nótese que para todos los casos anteriores las matrices usadas son cuadradas.

## Solución de una Matriz Diagonal

Dada una Matriz Diagonal de la forma:

$$
\begin{pmatrix} 
	a_{0,0} & 0 & ... & 0 \\
	0 & a_{1,1} & ... & 0 \\
	... & ... & ... & ... \\
	0 & 0 & ... & a_{n,n} \\
\end{pmatrix}
\begin{pmatrix} 
	x_{0} \\
	x_{1} \\
	... \\
	x_{n} \\
\end{pmatrix}
=
\begin{pmatrix} 
	b_{0} \\
	b_{1} \\
	... \\
	b_{n} \\
\end{pmatrix}
$$

La solución para cada $x_i$ está dada por	
$$
x_i = \frac{b_i}{a_{i,i}}, i \in [0, 1, ..., n]
$$
