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
#include "gauss_seidel.h"

#define GAUSS_SEIDEL_MAX_ITER 1000
#define GAUSS_SEIDEL_TOLERANCE 0.000001


SystemSolution gauss_seidel_solver(AugmentedMatrix matrix) {
    int size = matrix.rows;
    double **mtxc = matrix.content;
    SystemSolution ss = SystemSolutionDefault;

    double * x_next = matrixio_allocate_double_array(matrix.rows);

    for (int i = 0; i < size; i++) {
        x_next[i] = mtxc[i][size];
    }

    for (int k = 0; k < GAUSS_SEIDEL_MAX_ITER; k++) {
        double error = 0.0;
        for (int i = 0; i < size; i++) {
            double err_x_prev = x_next[i];
            x_next[i] = mtxc[i][size];
            for (int j = 0; j < size; j++){
                if (i == j) continue;
                x_next[i] -= mtxc[i][j]*x_next[j];
            }

            if (IS_ZERO(mtxc[i][i])) {
                ss.err |= __MATRIX_ERR_HAS_ZERO_ON_DIAG__;
                free(x_next);
                free(x_next);
                return ss;
            }

            x_next[i] /= mtxc[i][i];
            error += (x_next[i] - err_x_prev) * (x_next[i] - err_x_prev) / (x_next[i] * x_next[i]);
        }

        error = sqrt(error);

        if (error <= GAUSS_SEIDEL_TOLERANCE) break;
        printf("%d\n", k);
    }

    ss.solution = x_next;
    ss.size = size;

    return ss;
}