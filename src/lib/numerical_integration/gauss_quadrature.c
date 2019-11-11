/**
    ANSI C standard: c11
    bisection.c
    Purpose: Module for numerical integration
             using Gauss Qudrature formulas

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <math.h>
#define NS_NUMERICAL_INTEGRATION_GAUSS_IMPORT
#include "numsys/numerical_integration/gauss_quadrature.h"


double gauss_legendre_formula_1p(double (*f)(double)) {
    return 2.0 * f(0);
}

double gauss_legendre_formula_2p(double (*f)(double)) {
    return f(-sqrt(1.0/3.0)) + f(sqrt(1.0/3.0));
}

double gauss_legendre_formula_3p(double (*f)(double)) {
    return 5.0/9.0 * f(-sqrt(3.0/5.0)) + 8.0/9.0 * f(0) + 5.0/9.0 * f(sqrt(3.0/5.0));
}

double gauss_legendre_formula_4p(double (*f)(double)) {
    return ((18.0+sqrt(30))/36.0) * f(sqrt((3.0 - 2.0*sqrt(6.0/5.0))/7.0)) +
           ((18.0+sqrt(30))/36.0) * f(-sqrt((3.0 - 2.0*sqrt(6.0/5.0))/7.0)) +
           ((18.0-sqrt(30))/36.0) * f(sqrt((3.0 + 2.0*sqrt(6.0/5.0))/7.0)) +
           ((18.0-sqrt(30))/36.0) * f(-sqrt((3.0 + 2.0*sqrt(6.0/5.0))/7.0));
}
