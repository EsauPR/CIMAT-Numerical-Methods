# Ajuste lineal y cuadrático

## Objetivos

1. Simplificar el sistema de ecuaciones que resulta de mínimos cuadrados para una recta y una función cuadrática con algunos datos propuestos por el alumno agregándoles una variación aleatoria (ruido aleatorio en los datos).
2. Programar el método de mínimos cuadrados para una recta y una función cuadrática.
3. Programar el método de elemento finito para el ajuste de los mismos datos
   que fueron usados en el problema de mínimos cuadrados.

## Ajuste Lineal y Cuadrático

Dado un conjunto de $N$ puntos $\{(x_1,y_1), ..., (x_n,y_n)\}$  podemos aproximar la relación de dependencia entres las variables dependientes $Y$ y las independientes $X$ buscando entre una familia de funciones aquella que mejor se aproxime a los datos usando el criterio del Mínimo Error Cuadrático.

### Ajuste lineal

Sea la familia de funciones de la forma $y(x) = ax + b$, para algún punto $(x_i,\ y_i)$, podemos decir que la mejor aproximación para el valor $y_i$ está dado por
$$
y_i = ax + b + \epsilon
$$
dónde $\epsilon$ es un término de error asociado a la aproximación. Usando el error cuadrático medio el error asociado para todos los puntos está dado por:
$$
E(x) = \frac{1}{2}\sum_{i=1}^N (y_i - (ax_i + b))^2
$$
con $a$ y $b$ por determinar al minimizar dicha ecuación.
$$
\underset{a,b}{\mathrm{argmin}}\ E(x) = \frac{1}{2}\sum_{i=1}^N (y_i - (ax_i + b))^2
$$
Derivando con respecto a $a$ y $b$ e igualando a cero tenemos
$$
\frac{\delta E(x)}{\delta a} = \sum_{i=1}^N(y_i - (ax_i+b))(-x_i) = \sum_{i=1}^Nax_i^2+bx_i - y_ix_i = 0
$$

$$
\frac{\delta E(x)}{\delta b} = \sum_{i=1}^N(y_i - (ax_i+b))(-1) = \sum_{i=1}^N ax_i+b - y_i = 0
$$

formando así el siguiente sistema de ecuaciones
$$
\sum_{i=1}^N y_ix_i = a\sum_{i=1}^N x_i^2 + b \sum_{i=1}^N x_i
$$

$$
\sum_{i=1}^N y_i = a\sum_{i=1}^N x_i + Nb
$$

Multiplicando $(6)$  por $N$ y $(7)$ por $\sum_{i=1}^N x_i$ tenemos
$$
N\sum_{i=1}^N y_ix_i = Na\sum_{i=1}^N x_i^2 + Nb \sum_{i=1}^N x_i
$$

$$
\sum_{i=1}^N y_i \sum_{i=1}^N x_i = a\sum_{i=1}^N x_i \sum_{i=1}^N x_i + Nb\sum_{i=1}^N x_i
$$

Al restar $(8)$ a $(9)$
$$
\sum_{i=1}^N y_i \sum_{i=1}^N x_i - N\sum_{i=1}^N y_ix_i = a\sum_{i=1}^N x_i \sum_{i=1}^N x_i - Na\sum_{i=1}^N x_i^2
$$
así
$$
a = \frac{\sum_{i=1}^N y_i \sum_{i=1}^N x_i - N\sum_{i=1}^N y_ix_i}{\sum_{i=1}^N x_i \sum_{i=1}^N x_i - N\sum_{i=1}^N x_i^2}
$$

$$
b = \frac{\sum_{i=1}^N y_i - a\sum_{i=1}^N x_i}{N}
$$

#### Ejemplo 1

Para los siguientes puntos:

![Screenshot_20191124_100540](/home/esau/Imágenes/Screenshot_20191124_100628.png)

$$
a = \frac{190*361.06020810512035 - 20*4399.876418225732}{190*190 - 20 * 2470} = 1.4583525431986295
$$

$$
b = frac{361.06020810512035 - 1.4583525431986295*190}{20} = 4.198661244869038
$$

La siguiente gráfica muestra los puntos y la recta $y(x) = 1.4583525431986295x + 4.198661244869038$



![image-20191124095942584](/home/esau/.config/Typora/typora-user-images/image-20191124095942584.png)

### Ajuste cuadrático

Sea la familia de funciones de la forma $y(x) = ax^2 + bx + c$, para algún punto $(x_i,\ y_i)$, podemos decir que la mejor aproximación para el valor $y_i$ está dado por
$$
y_i = ax^2 + bx + c + \epsilon
$$
dónde $\epsilon$ es un término de error asociado a la aproximación. El error de aproximación usando el error cuadrático medio el error para todos los puntos está dado por:
$$
E(x) = \frac{1}{2}\sum_{i=1}^N (y_i - (ax_i^2 + bx_i + c))^2
$$
con $a$, $b$ y  $c$  por determinar al minimizar dicha ecuación.
$$
\underset{a,b}{\mathrm{argmin}}\ E(x) = \frac{1}{2}\sum_{i=1}^N (y_i - (ax_i^2 + bx_i + c))^2
$$
Derivando con respecto a $a$ y $b$ e igualando a cero tenemos
$$
\frac{\delta E(x)}{\delta a} = \sum_{i=1}^N(y_i - (ax_i^2 + bx_i + c))(-x_i^2) = \sum_{i=1}^N ax_i^4 + bx_i^3 + cx_i^2 - y_ix_i^2 = 0
$$

$$
\frac{\delta E(x)}{\delta b} = \sum_{i=1}^N(y_i - (ax_i^2 + bx_i + c))(-x_i) = \sum_{i=1}^N ax_i^3 + bx_i^2 + cx_i - y_ix_i = 0
$$

$$
\frac{\delta E(x)}{\delta c} = \sum_{i=1}^N(y_i - (ax_i^2 + bx_i + c))(-1) = \sum_{i=1}^N ax_i^2 + bx_i + c - y_i = 0
$$

formando así el siguiente sistema de ecuaciones
$$
\sum_{i=1}^N y_ix_i^2 = a\sum_{i=1}^N x_i^4 + b \sum_{i=1}^N x_i^3 + c \sum_{i=1}^N x_i^2
$$

$$
\sum_{i=1}^N y_ix_i = a\sum_{i=1}^N x_i^3 + b \sum_{i=1}^N x_i^2 + c \sum_{i=1}^N x_i
$$

$$
\sum_{i=1}^N y_i = a\sum_{i=1}^N x_i^2 + b \sum_{i=1}^N x_i + cN
$$

Al resolver el sistema obtenemos que:
$$
a = \\ \frac{\Big[\sum_{i=1}^N x_i^2 - \frac{(\sum_{i=1}^N x_i)^2}{n} \Big] \Big[\sum_{i=1}^N x_i^2y_i - \frac{\sum_{i=1}^Nx_i^2 \sum_{i=1}^Ny_i}{n}\Big] - \Big[\sum_{i=1}^N x_i^3 - \frac{\sum_{i=1}^Nx_i^2 \sum_{i=1}^Nx_i}{n}\Big] \Big[\sum_{i=1}^N x_iy_i - \frac{\sum_{i=1}^Nx_i \sum_{i=1}^Ny_i}{n}\Big]}
{\Big[\sum_{i=1}^N x_i^2 - \frac{(\sum_{i=1}^N x_i)^2}{n}\Big]
\Big[\sum_{i=1}^N x_i^4 - \frac{(\sum_{i=1}^N x_i^2)^2}{n}\Big]
\Big[\sum_{i=1}^N x_i^3 - \frac{\sum_{i=1}^N x_i^2\sum_{i=1}^N x_i}{n}\Big]^2}
$$

$$
b = \\ 
\frac{\Big[\sum_{i=1}^N x_iy_i - \frac{\sum_{i=1}^N x_i \sum_{i=1}^N y_i}{n} \Big] \Big[\sum_{i=1}^N x_i^4 - \frac{(\sum_{i=1}^Nx_i^2)^2}{n}\Big] - \Big[\sum_{i=1}^N x_i^2y_i - \frac{\sum_{i=1}^Nx_i^2 \sum_{i=1}^Ny_i}{n}\Big] \Big[\sum_{i=1}^N x_i^3 - \frac{\sum_{i=1}^Nx_i^2 \sum_{i=1}^Nx_i}{n}\Big]}
{\Big[\sum_{i=1}^N x_i^2 - \frac{(\sum_{i=1}^N x_i)^2}{n}\Big]
\Big[\sum_{i=1}^N x_i^4 - \frac{(\sum_{i=1}^N x_i^2)^2}{n}\Big]
\Big[\sum_{i=1}^N x_i^3 - \frac{\sum_{i=1}^N x_i^2\sum_{i=1}^N x_i}{n}\Big]^2}
$$

$$
c = \frac{\sum_{i=1}^Ny_i - b\sum_{i=1}^Nx_i - a\sum_{i=1}^Nx_i^2}{n}
$$

#### Ejemplo 2

Para los siguientes puntos:

![Screenshot_20191124_115530](/home/esau/Imágenes/Screenshot_20191124_115530.png)

Sustituyendo en las ecuaciones $(24)$, $(25)$ y $(26)$ tenemos que 
$$
a = 1.7295330104458295
$$

$$
b = -4.444461220193719
$$

$$
c =68.10637854840562
$$

La siguiente figura muestra los puntos y el ajuste con la recta:

 $y(x) = 1.7295330104458295x^2 - 4.444461220193719x + 68.10637854840562$



![image-20191124120201868](/home/esau/.config/Typora/typora-user-images/image-20191124120201868.png)

## Ajuste Mediante Elementos finitos

Con los mismos número de puntos ($m=20$) del *Ejemplo 2* se define una partición del tamaño $n$ en un intervalo $[a,b]$ que los contenga, tal que:
$$
a = z_0 < z_1 < ... < z_{n-1} < z_n = b,\ z_j= a + jh,\ h = \frac{b-a}{n}
$$
Dónde se definen la familia de funciones lineales a pedazos $N_j(x)$ con $j=0,1,...,n$ que cumplen con:
$$
N_j(x_k) = 1,\ j = k \\
N_j(x_k) = 0,\ j \ne k
$$
Con dichas funciones se define:
$$
\Phi(x) = \sum_{j=1}^n \phi_jN_j(x)
$$
dónde $\phi_j$ son parámetros a identificar resolviendo el problema de minimización
$$
\underset{\phi_0,\phi_1,\phi_2, ...,\phi_n}{\mathrm{min}}\ 
\sum_{j=1}^m \Big[\phi_j(x_i) - y_i\Big]^2 + \lambda \int_a^b (\Phi'(x))^2dx
$$
Al derivar y sustituyendo se obtiene el sistema de ecuaciones para un elemento $k$:
$$
\begin{pmatrix}
	\sum_{i=1}^{m} N^2_k(xi) + \lambda/h & \sum_{i=1}^{m} N_{k+1}(xi)N_k(x_i) \ \lambda/h \\
	\sum_{i=1}^{m} N_{k+1}(xi)N_k(x_i) \ \lambda/h & \sum_{i=1}^{m} N^2_{k+1}(xi) + \lambda/h\\
\end{pmatrix}
\begin{pmatrix}
	\phi_k \\
	\phi_{k+1} \\
\end{pmatrix}
=
\begin{pmatrix}
	\sum_{i=1}^{m} y_iN_k(xi) \\
	\sum_{i=1}^{m} y_iN_{k+1}(xi) \\
\end{pmatrix}
$$
Reescribiendo tenemos
$$
\begin{pmatrix}
	a_k & b_k \\
	b_k & c_k \\
\end{pmatrix}
\begin{pmatrix}
	\phi_k \\
	\phi_{k+1} \\
\end{pmatrix}
=
\begin{pmatrix}
	s_k \\
	t_k \\
\end{pmatrix}
$$
Y al armar el sistema global obtenemos
$$
\begin{pmatrix}
	a_0 & b_0 & 0 & 0 & \dots & 0 & 0 \\
	b_0 & c_0 + a_1 & b_1 & 0 & \dots & 0 & 0 \\
	0 & b_1 & c_1 + a_2 & b2 & \dots & 0 & 0 \\
	0 & 0 & b_2 & c_2 + a_3 & \dots & 0 & 0 \\
	\vdots & \vdots & \vdots & \vdots & \dots & b_{k-2} &0 \\
	0 & 0 & 0 & 0 & \dots & c_{k-2} + a_{k-1} & b_{k-1} \\
	0 & 0 & 0 & 0 & \dots & b_{k-1} & c_{k-1} \\
\end{pmatrix}
\begin{pmatrix}
	\phi_0 \\
	\phi_1 \\
	\phi_2 \\
	\phi_3 \\
	\vdots \\
	\phi_{n-1} \\
	\phi_{n} \\
\end{pmatrix}
=
\begin{pmatrix}
	s_0 \\
	t_0 + s_1  \\
	t_1 + s_2  \\
	t_2 + s_3  \\
	\vdots \\
	t_{n-2}+ s_{n-1}  \\
	t_{n-1}  \\
\end{pmatrix}
$$

dónde
$$
N_k(x) = 1 - \frac{1}{h}(x - z_k)
$$

$$
N_{k+1}(x) = \frac{1}{h}(x - z_k)
$$

#### Ejemplo 3

Para los siguientes puntos puntos 

![Screenshot_20191125_020819](/home/esau/Imágenes/Screenshot_20191125_020819.png)

los valores de $\{z_k\}$ y $\{\phi_k\}$ son:

```pseudocode
z = [0.0, 0.6551724137931034, 1.3103448275862069, 1.9655172413793103, 2.6206896551724137, 3.275862068965517, 3.9310344827586206, 4.586206896551724, 5.241379310344827, 5.896551724137931, 6.551724137931034, 7.206896551724138, 7.862068965517241, 8.517241379310345, 9.172413793103448, 9.827586206896552, 10.482758620689655, 11.137931034482758, 11.793103448275861, 12.448275862068964, 13.103448275862068, 13.758620689655173, 14.413793103448276, 15.068965517241379, 15.724137931034482, 16.379310344827587, 17.03448275862069, 17.689655172413794, 18.344827586206897, 19.0]
```

```pseudocode
phi = [ 7.15802234  7.71416567  8.07099469  8.20636338  8.44563176  8.72837427 9.06295695  9.93955996 11.11602983 12.69724213 13.66086063 14.61085821 15.78224126 16.69231272 17.56675362 18.53654166 20.02745312 21.55098567 22.49891413 23.10914351 23.74607662 25.35668888 26.42063853 27.15810849 27.83103664 27.96832346 27.76670328 28.4767889  28.81314525 28.81314525]
```

La gráfica correspondiente a la interpolación es la siguiente:



![image-20191125021056906](/home/esau/.config/Typora/typora-user-images/image-20191125021056906.png)

## Conclusiones

Las 3 métodos de ajuste obtienen muy buenos resultados, sin embargo cabe mencionar que los primeros pueden ser usados cuando tenemos más de una observación ($y_i$) para algún valor en específico. Además, mientras más compleja sea la nube de puntos se podría requerir resolver el problema con otra familia de funciones, lo que implica a formular un nuevo sistema de ecuaciones.

Usando el método ajuste por elemento finito, para ajustar los valores a una serie de valores de puntos más complejos basta con jugar con los parámetros $\lambda$ y el tamaño de la partición.