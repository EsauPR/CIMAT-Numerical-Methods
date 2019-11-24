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

#### Ejemplo

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

#### Ejemplo

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

La siguiente figura muestra los puntos y el ajuste con la recta $y(x) = 1.7295330104458295x^2 - 4.444461220193719x + 68.10637854840562$

![image-20191124120201868](/home/esau/.config/Typora/typora-user-images/image-20191124120201868.png)

