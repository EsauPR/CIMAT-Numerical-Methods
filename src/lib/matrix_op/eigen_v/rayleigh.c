/**
    ANSI C standard: c11
    matrix_ejen_v.c
    Purpose: Module to get eigen vetors and
    eigen values with Rayleigh Method

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdlib.h>
#include <math.h>

#include "numsys/matrix/matrixio.h"
#include "numsys/matrix/matrix.h"

#define NSEigenV_RAYLEIGH_IMPORT
#define NSEigenV_RAYLEIGH_MAX_ITER 1000000
#include "numsys/matrix_op/eigen_v/rayleigh.h"
#include "numsys/solvers/doolittle.h"


/* Improve the eigen vector and eigen value given with the Rayleigh Method */
void matrix_eigen_rayleigh_method(NSMatrix * matrix, NSEigenV * eigenv) {
    int size = matrix->rows;

    double ** a = matrix->items;
    double * xprev = eigenv->eigen_vector;
    double * xnext = matrixio_allocate_array_double(size);

    double lambda = 0.0, lambda_prev = 1.0;

    for (int k = 0; k < NSEigenV_RAYLEIGH_MAX_ITER; k++) {

        lambda = 0.0;
        for (int i = 0; i < size; i++) {
            xnext[i] = 0.0;
            for (int j = 0; j < size; j++) {
                xnext[i] += a[i][j] * xprev[j];
            }
            lambda += xprev[i] * xnext[i];
        }

        matrix_normalize_v(xnext, size);
        NS_SWAP(xnext, xprev, double *);

        if (NS_IS_ZERO(NS_ABS(lambda) - NS_ABS(lambda_prev))) break;

        lambda_prev = lambda;
    }

    free(xnext);
    eigenv->eigen_vector = xprev;
    eigenv->eigen_value = lambda;
}
