

# Integración Numérica

## Objetivos

1. Programar el Método del Trapecio
3. Programar el Método de Simpson 1/3
4. Programar el Método de Simpson 3/8
4. Programar el Método de Boole
5. Programar el Método de Weddle


## Método del Trapecio

La integral de $f(x)$ en un intervalo [a,b] dividido en $m$ partes iguales con $a = x_0$ y $b=x_m$ con un espaciado para x de $h=\frac{x_m - x_0}{m}$ está dado por:

$$
\int_a^b f(x)dx = \int_{x_0}^{x_m} f(x)dx = \int_{x_0}^{x_1}f(x)dx + \int_{x_1}^{x_2} f(x)dx + \dots + \int_{x_{m-1}}^{x_m} f(x)dx
$$

$$
\int_{x_0}^{x_m} f(x)dx \approx \frac{h}{2} \{f(x_0) + f(x_m) + 2[f(x_1)+f(x_2)+\dots+f(x_{m-1})] \}
$$

### Algoritmo

```c
/* Return the value of the integration for the composite trapeze rule */
double trapeze_rule(double * y, double h, int m) {
    double sum = 0;

    for (int i = 1; i < m; i++) {
        sum += y[i];
    }

    return h * (y[0] + y[m] + 2 * sum) / 2.0;
}
```

## Método del Simpson 1/3

La integral de $f(x)$ en un intervalo [a,b] dividido en $m$ partes iguales con $a = x_0$ y $b=x_m$ con un espaciado para x de $h=\frac{x_m - x_0}{m}$ con $m$ par está dado por:
$$
\int_a^b f(x)dx = \int_{x_0}^{x_m} f(x)dx = \int_{x_0}^{x_1}f(x)dx + \int_{x_1}^{x_2} f(x)dx + \dots + \int_{x_{m-1}}^{x_m} f(x)dx
$$

$$
\int_{x_0}^{x_m} f(x)dx \approx \frac{h}{3} \{f(x_0) + f(x_m) + 2[f(x_2)+f(x_4)+\dots+f(x_{m-2})] + 4[f(x_1)+f(x_3)+\dots+f(x_{m-1})] \}
$$

### Algoritmo

```c
/* Return the value of the integration for the composite simpson 1/3 rule */
double simpson_1_3_rule(double * y, double h, int m) {
    double even_sum = 0;
    double odd_sum = 0;

    for (int i = 1; i < m; i++) {
        if (i & 1) {
            odd_sum += y[i];
        } else {
            even_sum += y[i];
        }
    }

    return h * (y[0] + y[m] + 2 * even_sum + 4 * odd_sum) / 3.0;
}
```

## Método de Simpson 3/8

La integral de $f(x)$ en un intervalo [a,b] dividido en $m$ partes iguales con $a = x_0$ y $b=x_m$ con un espaciado para x de $h=\frac{x_m - x_0}{m}$ con $m$ múltiplo de 3 está dado por:
$$
\int_a^b f(x)dx = \int_{x_0}^{x_m} f(x)dx = \int_{x_0}^{x_1}f(x)dx + \int_{x_1}^{x_2} f(x)dx + \dots + \int_{x_{m-1}}^{x_m} f(x)dx
$$

$$
\int_{x_0}^{x_m} f(x)dx \approx \frac{3}{8}h \Big\{f(x_0) + f(x_m) + 3[f(x_1)+f(x_2)+f(x_4)+f(x_5)+\dots+f(x_{m-2})+f(x_{m-1})] \\ + 2[f(x_3)+f(x_6)+\dots+f(x_{m-3})] \Big\}
$$

### Algoritmo

```c
double simpson_3_8_rule(double * y, double h, int m) {
    double sum1 = 0;
    double sum2 = 0;

    for (int i = 1; i < m; i++) {
        if (i % 3 == 0) {
            sum2 += y[i];
        } else {
            sum1 += y[i];
        }
    }

    return 3 * h * (y[0] + y[m] + 2 * sum2 + 3 * sum1) / 8.0;
}
```

## Método de Boole

La integral de $f(x)$ en un intervalo [a,b] dividido en $m$ partes iguales con $a = x_0$ y $b=x_m$ con un espaciado para x de $h=\frac{x_m - x_0}{m}$ con $m$ múltiplo de 4 está dado por:
$$
\int_a^b f(x)dx = \int_{x_0}^{x_m} f(x)dx = \int_{x_0}^{x_1}f(x)dx + \int_{x_1}^{x_2} f(x)dx + \dots + \int_{x_{m-1}}^{x_m} f(x)dx
$$

$$
\int_{x_0}^{x_m} f(x)dx \approx 
\frac{2}{45}h[7f(x_0)+32f(x_1)+12f(x_2)+32f(x_3)+7f(x_4)] \\
+ \frac{2}{45}h[7f(x_4)+32f(x_5)+12f(x_6)+32f(x_7)+7f(x_8)] \\
\vdots \\
+ \frac{2}{45}h[7f(x_{m-4})+32f(x_{m-3})+12f(x_{m-2})+32f(x_{m-1})+7f(x_{m})]
$$

### Algoritmo

```c
double boole_rule(double * y, double h, int m) {
    double sum = 0;
    double coefs[] = {7, 32, 12, 32, 7};

    for (int i = 0; i < m; i+=4) {
        for (int j = 0; j < 5; j++){
            sum += coefs[j] * y[i+j];
        }
    }

    return 2.0 * h * sum  / 45.0;
}
```

## Método de Weddle

La integral de $f(x)$ en un intervalo [a,b] dividido en $m$ partes iguales con $a = x_0$ y $b=x_m$ con un espaciado para x de $h=\frac{x_m - x_0}{m}$ con $m$ múltiplo de 6 está dado por:
$$
\int_a^b f(x)dx = \int_{x_0}^{x_m} f(x)dx = \int_{x_0}^{x_1}f(x)dx + \int_{x_1}^{x_2} f(x)dx + \dots + \int_{x_{m-1}}^{x_m} f(x)dx
$$

$$
\int_{x_0}^{x_m} f(x)dx \approx 
\frac{h}{140}[41f(x_0)+216f(x_1)+27f(x_2)+272f(x_3)+27f(x_4)+216f(x_5)+41f(x_6)] \\
+ \frac{h}{140}[41f(x_6)+216f(x_7)+27f(x_8)+272f(x_9)+27f(x_{10})+216f(x_{11})+41f(x_{12})] \\
\vdots \\
+ \frac{h}{140}[41f(x_{m-6})+216f(x_{m-5})+27f(x_{m-4})+272f(x_{m-3})+27f(x_{m-2})+216f(x_{m-1})+41f(x_{m})]
$$

### Algoritmo

```c
double weddle_rule(double * y, double h, int m) {
    double sum = 0;
    double coefs[] = {41, 216, 27, 272, 27, 216, 41};

    for (int i = 0; i < m; i+=6) {
        for (int j = 0; j < 7; j++){
            sum += coefs[j] * y[i+j];
        }
    }

    return h * sum / 140.0;
}
```

## Resultados

Las siguientes tablas muestran el error de los resultados obtenidos para la evaluación de la función $f(x) = sin(x+\frac{1}{2})$ en el intervalo $[0, 4\pi]$, para $m = \{24, 120, 1008\}$

| Método      | Error para m = 24 | Error para m = 120 | Error para m = 1008 |
| ----------- | ----------------- | ------------------ | ------------------- |
| Trapecio    | 3.836655e-15      | 1.920072e-14       | 9.877519e-14        |
| Simpson 1/3 | 3.252922e-15      | 1.855934e-14       | 9.993066e-14        |
| Simpson 3/8 | 3.812812e-15      | 1.831567e-14       | 9.934768e-14        |
| Boole       | 3.472367e-15      | 1.722129e-14       | 1.005286e-13        |
| Weddle      | 3.587522e-15      | 1.812097e-14       | 1.007720e-13        |

## Conclusiones

El valor real del resultado de la integral definida anteriormente es cero. Podemos observar que los errores obtenidos con respecto al valor real son muy pequeños siendo así una muy buena aproximación. Sin embargo, se observa un comportamiento extraño en cuanto se incrementa el valor de $m$; en vez de disminuir como es de suponerse este error se hace más grande, lo que asocio a que para intervalos muy pequeños muchos cálculos son mayormente inexactos por la precisión del punto flotante, provocando que no sea contabilizados correctamente para el computo del resultado.

