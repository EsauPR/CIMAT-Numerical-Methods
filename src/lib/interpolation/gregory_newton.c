/**
    ANSI C standard: c11
    newton.c
    Purpose: Module to compute the Gregory-Newton interpolations

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdlib.h>
#include "string.h"

#define NS_GREGORY_NEWTON_IMPORT
#include "numsys/matrix/matrix.h"
#include "numsys/interpolation/divided_differences.h"

/* Return the evaluation for any point using Gregory-Newton forward interpolation */
static double __gregory_newton_fw_evaluation (double * x, double * coefs, int size, double s, int it, int fact) {
    if (size == 1) {
        return coefs[it] / fact;
    }

    return coefs[it]/fact + (s - it) * __gregory_newton_fw_evaluation(x, coefs, size - 1, s, it+1, fact * (it+1));
}

/* Return the evaluation for any point using Gregory-Newton backward interpolation */
static double __gregory_newton_bw_evaluation(double * x, double * coefs, int size, double s, int it, int fact) {
    if (size == 1) {
        return coefs[it] / fact;
    }

    return coefs[it]/fact + (s + it) * __gregory_newton_bw_evaluation(x, coefs, size - 1, s, it+1, fact * (it+1));
}

/* Return the evaluation for several points using Gregory-Newton forward interpolation */
double * gregory_newton_fw_evaluation(double * x, double * y, int size, double h, double * values, int nvalues) {
    double * fs = matrixio_allocate_array_double(nvalues);
    double * coefs = get_forward_differences(y, size);

    for (int i = 0; i < nvalues; i++) {
        double s = (values[i] - x[0]) / h;
        fs[i] = __gregory_newton_fw_evaluation(x, coefs, size, s, 0, 1);
    }

    free(coefs);
    return fs;
}

/* Return the evaluation for several points using Gregory-Newton backward interpolation */
double * gregory_newton_bw_evaluation(double * x, double * y, int size, double h, double * values, int nvalues) {
    double * fs = matrixio_allocate_array_double(nvalues);
    double * coefs = get_backward_differences(y, size);

    for (int i = 0; i < nvalues; i++) {
        double s = (values[i] - x[size-1]) / h;
        fs[i] = __gregory_newton_bw_evaluation(x, coefs, size, s, 0, 1);
    }

    free(coefs);
    return fs;
}
