/**
    ANSI C standard: c11
    main.c
    Purpose: Numerical Intagration example for Trapeze rule

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "numsys/numerical_integration/gauss_quadrature.h"


double f(double x) {
    // return x * x + sin(x);
    return sin(x + 0.5);
}


int main() {
    puts("Numerical integration using Gauss Quadrature formulas\n");
    puts("f(x) = sin(x + 0.5)\n");

    printf("For n+1 = 1 points: %le\n", gauss_legendre_formula_1p(f));
    printf("For n+1 = 2 points: %le\n", gauss_legendre_formula_2p(f));
    printf("For n+1 = 3 points: %le\n", gauss_legendre_formula_3p(f));
    printf("For n+1 = 4 points: %le\n", gauss_legendre_formula_4p(f));

    return 0;
}
