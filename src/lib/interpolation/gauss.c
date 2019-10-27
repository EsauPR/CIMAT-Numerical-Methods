/**
    ANSI C standard: c11
    newton.c
    Purpose: Module to compute the Gauss interpolations

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdlib.h>
#include "string.h"

#define NS_GAUSS_INTERPOLATION_IMPORT
#include "numsys/matrix/matrix.h"
#include "numsys/interpolation/divided_differences.h"


/* Return the evaluation for any point using Gauss central forward interpolation */
static double __gauss_fw_evaluation(double * coefs, int size, double s) {
    double fact = 1.0;
    double result = coefs[0];
    double s_prod = 1.0;
    double less = 0.0;
    for (int i = 0; i < size-1; i++) {
        if (i & 1) {
            less += 1;
            s_prod *= s - less;
        } else {
            s_prod *= s + less;
        }

        result += s_prod * coefs[i+1] / fact;
        fact *= i+2;
    }

    return result;
}

/* Return the evaluation for any point using Gauss backward interpolation */
static double __gauss_bw_evaluation(double * coefs, int size, double s) {
    double fact = 1.0;
    double result = coefs[0];
    double s_prod = 1.0;
    double less = 0.0;
    for (int i = 0; i < size-1; i++) {
        if (i & 1) {
            less += 1;
            s_prod *= s + less;
        } else {
            s_prod *= s - less;
        }

        result += s_prod * coefs[i+1] / fact;
        fact *= i+2;
    }

    return result;
}

/* Return the evaluation for several points using Gauss forward interpolation */
double * gauss_fw_central_diff_evaluation(double * x, double * y, int size, double h, double * values, int nvalues) {
    double * fs = matrixio_allocate_array_double(nvalues);
    double * coefs = get_forward_central_differences(y, size);

    for (int i = 0; i < nvalues; i++) {
        double s = (values[i] - x[size/2]) / h;
        fs[i] = __gauss_fw_evaluation(coefs, size, s);
    }

    free(coefs);
    return fs;
}

/* Return the evaluation for several points using Gauss backward interpolation */
double * gauss_bw_central_diff_evaluation(double * x, double * y, int size, double h, double * values, int nvalues) {
    double * fs = matrixio_allocate_array_double(nvalues);
    double * coefs = get_backward_central_differences(y, size);

    for (int i = 0; i < nvalues; i++) {
        double s = (values[i] - x[(size-1)/2]) / h;
        fs[i] = __gauss_bw_evaluation(coefs, size, s);
    }

    free(coefs);
    return fs;
}
