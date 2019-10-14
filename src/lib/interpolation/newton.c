/**
    ANSI C standard: c11
    newton.c
    Purpose: Module to make a interpolation proccess by Newton interpolation polinomial

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdlib.h>
#include "string.h"

#define NS_INTERPOLATION_NEWTON_IMPORT
#include "numsys/matrix/matrix.h"
#include "numsys/interpolation/newton.h"

double * interpolation_newton(double * x, double * y, int size) {
    int ndots = (size * (size + 1)) / 2;
    double * div_table = matrixio_allocate_array_double(ndots);
    double * coefs = matrixio_allocate_array_double(size);

    memcpy(div_table, y, sizeof(double) * size);

    int coef_index = 0;
    for (int i = 0, inc = size, index = size; i < ndots - 1; i+=inc, inc --) {
        int x1 = 0;
        int x2 = coef_index + 1;
        for (int j = 0; j < inc - 1; j++, x1++, x2++) {
            div_table[index++] = (div_table[i+j+1] - div_table[i+j]) / (x[x2] - x[x1]);
        }

        coefs[coef_index++] = div_table[i];
    }
    coefs[coef_index] = div_table[ndots - 1];

    free(div_table);

    return coefs;
}


double interpolation_newton_evaluate(double * x, double * coefs, int size, double value) {
    if (size == 1) {
        return coefs[0];
    }

    return coefs[0] + (value - x[0]) * interpolation_newton_evaluate(x + 1, coefs + 1, size - 1, value);
}
