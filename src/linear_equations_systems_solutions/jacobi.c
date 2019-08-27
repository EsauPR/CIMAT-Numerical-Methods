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
#include "jacobi.h"

#define JACOBI_MAX_ITER 1000
#define JACOBI_TOLERANCE 0.000001


SystemSolution jacobi_solver(AugmentedMatrix matrix) {
    int size = matrix.rows;
    double **mtxc = matrix.content;
    double * x_next = matrixio_allocate_double_array(matrix.rows);
    double * x_prev = matrixio_allocate_double_array(matrix.rows);
    SystemSolution ss = SystemSolutionDefault;

    for (int i = 0; i < size; i++) {
        x_prev[i] = mtxc[i][size];
    }

    for (int k = 0; k < JACOBI_MAX_ITER; k++) {
        double error = 0.0;
        for (int i = 0; i < size; i++) {
            if (IS_ZERO(mtxc[i][i])) {
                ss.err |= __MATRIX_ERR_NO_SOLUTION__ | __MATRIX_ERR_HAS_ZERO_ON_DIAG__;
                return ss;
            }
            x_next[i] = mtxc[i][size];
            for (int j = 0; j < size; j++){
                if (i == j) continue;
                x_next[i] -= mtxc[i][j]*x_prev[j];
            }

            if (IS_ZERO(mtxc[i][i])) {
                ss.err |= __MATRIX_ERR_HAS_ZERO_ON_DIAG__;
                free(x_prev);
                free(x_prev);
                return ss;
            }

            x_next[i] /= mtxc[i][i];
            error += (x_next[i] - x_prev[i]) * (x_next[i] - x_prev[i]) / (x_next[i] * x_next[i]);
        }

        error = sqrt(error);

        if (error <= JACOBI_TOLERANCE) break;

        SWAP(x_next, x_prev);
    }

    ss.solution = x_next;
    ss.size = size;

    free(x_prev);

    return ss;
}
