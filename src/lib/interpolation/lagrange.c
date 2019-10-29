/**
    ANSI C standard: c11
    lagrange.c
    Purpose: Module to make a interpolation proccess by Lagrange interpolation polinomial

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdlib.h>
#include "string.h"

#define NS_INTERPOLATION_LAGRANGE_IMPORT
#include "numsys/interpolation/lagrange.h"


/* Compute the l_i term of lagrange polinomail for any 'value' */
double interpolation_lagrange_li(int i, double * x, int size, double value) {
    double l_i = 1.0;
    for (int j = 0; j < size; j++){
        if (j != i){
            l_i *= (value - x[j]) / (x[i] - x[j]);
        }
    }

    return l_i;
}

/* Compute the derivate of the l_i term of lagrange polinomail for any 'value' */
double interpolation_lagrange_dlj(int j, double * x, int size, double value) {
    double dl_j = 0.0;
    for (int i = 0; i < size; i++) {
        if (i == j) continue;
        double sub1 = 1.0;
        for (int m = 0; m < size; m++) {
            if (m == i || m == j) continue;
            sub1 *= (value - x[m]) / (x[j] - x[m]);
        }
        dl_j += sub1 / (x[j]  - x[i]);
    }

    return dl_j;
}

/* Compute the lagrange interpolation and return the evaluation of the 'value' */
double interpolation_lagrange(double * x, double * y, int size, double value) {
    double p_x = 0.0;

    for (int i = 0; i < size; i++) {
        double l_i = interpolation_lagrange_li(i, x, size, value);
        p_x += y[i] * l_i;
    }

    return p_x;
}
