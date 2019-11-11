# Integración Numérica

## Objetivos

1.  Implementación de la formula de Gauss-Legendre para aproximación de integrales definidas.

## Formula de Gauss-Legendre

La formula de Gauss-Legendre asume que las integrales son definidas en el intervalo de $(-1, 1)$ es decir tienen la forma:
$$
\int_{-1}^1 f(x)dx
$$
En dónde un integral de la forma $\int_{a}^b g(x)dx$ puede ser transformada a la forma anterior mediante el siguiente cambio de variable:
$$
x = \frac{b-a}{2}t+\frac{b+a}{2}
$$
La función $f(x)$ es aproximada mediante un polinomio de grado $2n+1$ 
$$
f(x) \approx a_0 + a_1x_ + a_2x^2 + \dots + a_{2n+1}x^{2n+1}
$$
y
$$
\int_{-1}^1 f(x)dx  = \sum_{i=0}^{n}\lambda_if(x_i)
$$

$$
\int_{-1}^1 (a_0 + a_1x_ + a_2x^2 + \dots + a_{2n+1}x^{2n+1})dx = 
\lambda_0(a_0 + a_1x_0 + a_2x_0^2 + \dots + a_{2n+1}x_0^{2n+1}) \\
+ \lambda_1(a_0 + a_1x_1 + a_2x_1^2 + \dots + a_{2n+1}x_1^{2n+1}) \\
\vdots \\
+ \lambda_n(a_0 + a_1x_n + a_2x_n^2 + \dots + a_{2n+1}x_n^{2n+1})
$$

Comparando ambos lados se tiene:
$$
\lambda_0 + \lambda_1 + \dots + \lambda_n = 2 \\
\lambda_0x_0 + \lambda_1x_1 + \dots + \lambda_nx_n = 0 \\
\lambda_0x_0^2 + \lambda_1x_1^2 + \dots + \lambda_nx_n^2 = \frac{2}{3} \\
\vdots \\
\lambda_0x_0^{2n+1} + \lambda_1x_1^{2n+1} + \dots + \lambda_nx_n^{2n+1} = \frac{2}{3} \\
$$
Dado que los valores para cada $x_i$ son ceros de los polinomios ortogonales de Legendre, se tienen los siguientes resultados:

**Para n+1 = 1 puntos**
$$
\int_{-1}^1 f(x)dx  = 2f(0)
$$
**Para n+1 = 2 puntos** 
$$
\int_{-1}^1 f(x)dx  = f(-\sqrt \frac{1}{3}) + f(\sqrt \frac{1}{3})
$$
**Para n+1 = 3 puntos** 
$$
\int_{-1}^1 f(x)dx = \frac{5}{9}f(-\sqrt \frac{3}{5}) + \frac{8}{9}f(0) + \frac{5}{9}f(\sqrt \frac{3}{5})
$$
**Para n+1 = 4 puntos** 
$$
\int_{-1}^1 f(x)dx = \Big(\frac{18+\sqrt30}{36}\Big) f\Big(\sqrt \frac{3 - 2.0 \sqrt {6/5}}{7}\Big) \\
+ \Big(\frac{18+\sqrt30}{36}\Big) f\Big(-\sqrt \frac{3 - 2.0 \sqrt {6/5}}{7}\Big) \\
+ \Big(\frac{18-\sqrt30}{36}\Big) f\Big(\sqrt \frac{3 + 2.0 \sqrt {6/5}}{7}\Big) \\
+ \Big(\frac{18-\sqrt30}{36}\Big) f\Big(-\sqrt \frac{3 + 2.0 \sqrt {6/5}}{7}\Big) \\
$$

### Algoritmo

```c++
// Las funciones reciben un apuntador a la función a ser evaluada
double gauss_legendre_formula_1p(double (*f)(double)) {
    return 2.0 * f(0);
}

double gauss_legendre_formula_2p(double (*f)(double)) {
    return f(-sqrt(1.0/3.0)) + f(sqrt(1.0/3.0));
}

double gauss_legendre_formula_3p(double (*f)(double)) {
    return 5.0/9.0 * f(-sqrt(5.0/9.0)) + 8.0/9.0 * f(0) + 5.0/9.0 * f(sqrt(5.0/9.0));
}

double gauss_legendre_formula_4p(double (*f)(double)) {
    return ((18.0+sqrt(30))/36.0) * f(sqrt((3.0 - 2.0*sqrt(6.0/5.0))/7.0)) +
           ((18.0+sqrt(30))/36.0) * f(-sqrt((3.0 - 2.0*sqrt(6.0/5.0))/7.0)) +
           ((18.0-sqrt(30))/36.0) * f(sqrt((3.0 + 2.0*sqrt(6.0/5.0))/7.0)) +
           ((18.0-sqrt(30))/36.0) * f(-sqrt((3.0 + 2.0*sqrt(6.0/5.0))/7.0));
}
```



## Resultados

La siguiente tabla muestra los resultados obtenidos para la aproximación del la integración de la función:
$$
\int_{-1}^1 (x^2 + sin(x)) dx \approx 0.66667
$$

| Gauss-Legendre | Resultado    | Comparativa (Newton Cotes) | Resultado    |
| -------------- | ------------ | -------------------------- | ------------ |
| n+1 = 1 puntos | 0.000000e+00 | Regla del Trapecio (n=1)   | 1.000000e+00 |
| n+1 = 2 puntos | 6.666667e-01 | Regla de Simpson 1/3 (n=2) | 6.666667e-01 |
| n+1 = 3 puntos | 6.666667e-01 | Regla de Simpson 3/8 (n=3) | 6.666667e-01 |
| n+1 = 4 puntos | 6.666667e-01 | Regla de Boole (n=4)       | 6.666667e-01 |



La siguiente tabla muestra los resultados obtenidos para la aproximación del la integración de la función:
$$
\int_{-1}^1 sin(x + \frac{1}{2}) dx \approx 0.806845
$$

| Gauss-Legendre | Resultado    | Comparativa (Newton Cotes) | Resultado    |
| -------------- | ------------ | -------------------------- | ------------ |
| n+1 = 1 puntos | 9.588511e-01 | Regla del Trapecio (n=1)   | 7.384603e-01 |
| n+1 = 2 puntos | 8.034327e-01 | Regla de Simpson 1/3 (n=2) | 8.119239e-01 |
| n+1 = 3 puntos | 8.068749e-01 | Regla de Simpson 3/8 (n=3) | 8.090721e-01 |
| n+1 = 4 puntos | 8.068452e-01 | Regla de Boole (n=4)       | 8.068148e-01 |



## Conclusiones

Ambos métodos realizan una muy buena aproximación a el valor de la integral, si bien uno exige realizar un cambio de variable para poder realizar el proceso de integración sobre otros rangos el otro te exige muchos más puntos para ser más exactos.

Sin embargo usando la fórmula de Gauss-Legendre podemos obtener un mejor aproximación con muchos menos puntos.