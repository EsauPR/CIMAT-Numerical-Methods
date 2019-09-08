/**
    ANSI C standard: c11
    {file}.c
    Purpose: Gauss Seidel iterative method

   @author Esaú Peralta
   @email esau.opr@gmail.com
*/

#include <stdlib.h>
#include <math.h>

#define GAUSS_SEIDEL_IMPORT
#include "numsys/solvers/gauss_seidel.h"

#define GAUSS_SEIDEL_MAX_ITER 1000
#define GAUSS_SEIDEL_TOLERANCE 0.000001


SystemSolution gauss_seidel_solver(AugmentedMatrix matrix) {
    int size = matrix.rows;
    double **mtxc = matrix.items;
    double * x_next = matrixio_allocate_array_double(matrix.rows);
    SystemSolution ss = SystemSolutionDefault;

    for (int i = 0; i < size; i++) {
        x_next[i] = mtxc[i][size];
    }

    for (int k = 0; k < GAUSS_SEIDEL_MAX_ITER; k++) {
        double error = 0.0;
        for (int i = 0; i < size; i++) {
            if (NS_IS_ZERO(mtxc[i][i])) {
                ss.err |= NS__MATRIX_ERR_NO_SOLUTION__ | NS__MATRIX_ERR_HAS_ZERO_ON_DIAG__;
                return ss;
            }
            double err_x_prev = x_next[i];
            x_next[i] = mtxc[i][size];
            for (int j = 0; j < size; j++){
                if (i == j) continue;
                x_next[i] -= mtxc[i][j]*x_next[j];
            }

            x_next[i] /= mtxc[i][i];
            error += (x_next[i] - err_x_prev) * (x_next[i] - err_x_prev) / (x_next[i] * x_next[i]);
        }

        error = sqrt(error);
        if (isnan(error)) {
            printf("Warning:: Step %d, Error is NaN\n", k);
        }

        if (error <= GAUSS_SEIDEL_TOLERANCE) break;
    }

    ss.solution = x_next;
    ss.size = size;

    return ss;
}
