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


SystemSolution jacobi_solver(AugmentedMatrix matrix) {
    int size = matrix.rows;
    double **mtxc = matrix.items;
    double * x_next = matrixio_allocate_array_double(matrix.rows);
    double * x_prev = matrixio_allocate_array_double(matrix.rows);
    SystemSolution ss = SystemSolutionDefault;

    for (int i = 0; i < size; i++) {
        x_prev[i] = mtxc[i][size];
    }

    for (int k = 0; k < JACOBI_MAX_ITER; k++) {
        double error = 0.0;
        for (int i = 0; i < size; i++) {
            if (NS_IS_ZERO(mtxc[i][i])) {
                ss.err |= NS__MATRIX_ERR_NO_SOLUTION__ | NS__MATRIX_ERR_HAS_ZERO_ON_DIAG__;
                return ss;
            }
            x_next[i] = mtxc[i][size];
            for (int j = 0; j < size; j++){
                if (i == j) continue;
                x_next[i] -= mtxc[i][j]*x_prev[j];
            }

            if (NS_IS_ZERO(mtxc[i][i])) {
                ss.err |= NS__MATRIX_ERR_HAS_ZERO_ON_DIAG__;
                free(x_prev);
                free(x_prev);
                return ss;
            }

            x_next[i] /= mtxc[i][i];
            error += (x_next[i] - x_prev[i]) * (x_next[i] - x_prev[i]) / (x_next[i] * x_next[i]);
        }

        error = sqrt(error);
        if (isnan(error)) {
            printf("Warning:: Step %d, Error is NaN\n", k);
        }

        if (error <= JACOBI_TOLERANCE) break;

        NS_SWAP(x_next, x_prev, double *);
    }

    ss.solution = x_next;
    ss.size = size;

    free(x_prev);

    return ss;
}
