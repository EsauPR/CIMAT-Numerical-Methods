/**
    ANSI C standard: c11
    hermite.c
    Purpose: Module to make a interpolation proccess by Hermite interpolation polinomial

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdlib.h>
#include "string.h"

#define NS_INTERPOLATION_HERMITE_IMPORT
#include "numsys/interpolation/hermite.h"
#include "numsys/interpolation/lagrange.h"


/* Compute the the Hermite polinomial and returns the evaluation for any 'value' */
double interpolation_hermite(double * x, double * y, double * dy, double size, double value) {
    double p_x_term1 = 0;
    double p_x_term2 = 0;
    for (int i = 0; i < size; i++) {
        double li_d1 = interpolation_lagrange_dlj(i, x, size, x[i]);
        double li = interpolation_lagrange_li(i, x, size, value);
        p_x_term1 += (-2 * li_d1 * value + 1 + 2 * x[i] * li_d1) * li * li * y[i];
        p_x_term2 += (value - x[i]) * li * li * dy[i];
    }

    return p_x_term1 + p_x_term2;
}
