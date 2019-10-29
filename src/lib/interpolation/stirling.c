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


/* Return the evaluation for any point using Gauss backward interpolation */
static double __stirling_evaluation(double * coefs_fw, double * coefs_bw, int size, double s) {
    double fact = 1.0;
    double result = coefs_fw[0];
    double s_prod = 1.0;
    double less = 0.0;
    for (int i = 0; i < size-1; i++) {
        if (i & 1) {
            result +=  s * s * s_prod * coefs_bw[i+1] / fact;
        } else {
            result += s * s_prod * (coefs_bw[i+1] + coefs_fw[i+1]) / (2 * fact);
        }

        if (i & 1) {

            less += 1;
            s_prod *= s*s - less * less;
        }

        fact *= i+2;
    }

    return result;
}


/* Return the evaluation for several points using Gauss backward interpolation */
double * stirling_central_diff_evaluation(double * x, double * y, int size, double h, double * values, int nvalues) {
    double * fs = matrixio_allocate_array_double(nvalues);
    double * coefs_fw = get_forward_central_differences(y, size);
    double * coefs_bw = get_backward_central_differences(y, size);

    for (int i = 0; i < nvalues; i++) {
        double s = (values[i] - x[size/2]) / h;
        fs[i] = __stirling_evaluation(coefs_fw, coefs_bw, size, s);
    }

    free(coefs_fw);
    free(coefs_bw);

    return fs;
}
