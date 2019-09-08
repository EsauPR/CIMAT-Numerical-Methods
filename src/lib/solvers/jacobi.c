/**
    ANSI C standard: c11
    {file}.c
    Purpose: Jacobi iterative method

   @author Esaú Peralta
   @email esau.opr@gmail.com
*/

#include <stdlib.h>
#include <math.h>

#define JACOBI_IMPORT
#include "numsys/solvers/jacobi.h"

#define JACOBI_MAX_ITER 1000
#define JACOBI_TOLERANCE 0.000001


void jacobi_solver(NSMatrixSystem * msystem) {
    int size = msystem->a.rows;
    double **a = msystem->a.items;
    double * b = msystem->b.items;
    double * x_next = matrixio_allocate_array_double(size);
    double * x_prev = msystem->x.items;

    for (int k = 0; k < JACOBI_MAX_ITER; k++) {
        double error = 0.0;

        double ** a_i  = a; // Avoid to reference each time matrix + i
        double * x_next_i = x_next; // Avoid to reference each time x_next[i]
        double * x_prev_i = x_prev; // Avoid to reference each time x_prev[i]
        double * b_i = b; // Avoid to reference each time b[i]

        for (int i = 0; i < size; i++, a_i++, x_next_i++, x_prev_i++, b_i++) {
            double a_ii = (*a)[i];

            if (NS_IS_ZERO(a_ii)) {
                msystem->err |= NS__MATRIX_ERR_HAS_ZERO_ON_DIAG__;
                free(x_next);
                return;
            }

            double * a_ij = *a_i;
            double * x_prev_j = x_prev;

            *x_next_i = *b_i;
            for (int j = 0; j < size; j++, a_ij++, x_prev_j++){
                if (i == j) continue;
                *x_next_i -= (*a_ij) * (*x_prev_j);
            }

            *x_next_i /= a_ii;
            error += ((*x_next_i) - (*x_prev_i)) * ((*x_next_i) - (*x_prev_i)) / ((*x_next_i) * (*x_next_i));
        }

        error = sqrt(error);
        if (isnan(error)) {
            printf("Warning:: Step %d, Error is NaN\n", k);
        }

        msystem->x.items = x_next;
        NS_SWAP(x_next, x_prev, double *);

        if (error <= JACOBI_TOLERANCE) {
            break;
        }
    }

    free(x_next);
}
