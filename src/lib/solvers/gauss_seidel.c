/**
    ANSI C standard: c11
    {file}.c
    Purpose: Gauss Seidel iterative method

   @author Esaú Peralta
   @email esau.opr@gmail.com
*/

#include <stdlib.h>
#include <string.h>
#include <math.h>

#define GAUSS_SEIDEL_IMPORT
#include "numsys/solvers/gauss_seidel.h"

#define GAUSS_SEIDEL_MAX_ITER 1000
#define GAUSS_SEIDEL_TOLERANCE 0.000001


void gauss_seidel_solver(NSMatrixSystem * msystem) {
    int size = msystem->a.rows;

    memcpy(msystem->x.items, msystem->b.items, size * sizeof(double));

    for (int k = 0; k < GAUSS_SEIDEL_MAX_ITER; k++) {
        double error = 0.0;

        double ** a_i = msystem->a.items; // Avoid to reference a[i] each time
        double * x_i = msystem->x.items; // Avoid to reference x[i] each time
        double * b_i = msystem->b.items; // Avoid to reference b[i] each time
        for (int i = 0; i < size; i++, a_i++, x_i++, b_i++) {
            double a_ii_value = (*a_i)[i];

            if (NS_IS_ZERO(a_ii_value)) {
                msystem->err |= NS__MATRIX_ERR_NO_SOLUTION__ | NS__MATRIX_ERR_HAS_ZERO_ON_DIAG__;
                return;
            }

            double err_prev = *x_i;

            double * a_ij = *a_i; // Reference to a[i][j]
            double * x_j = msystem->x.items; // Reference to x[j]

            *x_i = *b_i;
            for (int j = 0; j < size; j++, a_ij++, x_j++){
                if (i == j) continue;
                *x_i -= (*a_ij) * (*x_j);
            }
            *x_i /= a_ii_value;

            error += ((*x_i) - err_prev) * ((*x_i) - err_prev) / ((*x_i) * (*x_i));
        }

        error = sqrt(error);
        if (k % 100 == 0) {
            printf("Iter %d, Error: %le\n", k, error);
        }

        if (isnan(error)) {
            printf("Warning:: Step %d, Error is NaN\n", k);
        }

        if (error <= GAUSS_SEIDEL_TOLERANCE) break;
    }
}
