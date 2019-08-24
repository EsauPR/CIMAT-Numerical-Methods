#include <stddef.h>
#include "matrix.h"
#include "../matrix/matrixio.h"

#define MATRIXLUDLT_IMPORT
#include "matrixLDLt.h"

/*
    Make a LDLt decomposition over the same matrix. L is a lower trangular matrix
    with ones over the diagonal.

    You must asume that the diagonal is ones for L and the values already computed for D

    Returns a struct type SystemSolution

    If the decomposition is not possible SystemSolution.size is equal to -1
*/

SystemSolution LDLt_decomposition(double ** matrix, int size) {
    SystemSolution system_solution = SystemSolutionDefault;
    system_solution.size = size;
    system_solution.solution = NULL;
    system_solution.determinant = 1.0;

    // double backup_row[size + 1];

    // for (int i = 0, swap_row = i; i < size; i++) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j <= i; j++) {
            // backup_row[j] = matrix[i][j];

            int limit = (i == j)? i:j;
            for (int k = 0; k < limit; k++) {
                matrix[i][j] -= matrix[i][k] * matrix[j][k] * matrix[k][k];
                matrix[j][i] = matrix[i][j];
            }

            if (i != j) {
                matrix[i][j] /= matrix[j][j];
                matrix[j][i] = matrix[i][j];
            }
        }

        // // Swap rows to avoid division by zero
        // if (matrix[i][i] == 0.0 && i < size) {
        //     // No more swaps available
        //     if (++swap_row >= size) {
        //         system_solution.state &= __MATRIX_NO_LDLT_DECOMPOSITION__ & __SOLUTION_NO_EXISTS__;
        //         return system_solution;
        //     }
        //     // Restore current row and swap
        //     for (int j = 0; j < size; j++) {
        //         matrix[i][j] = backup_row[j];
        //     }
        //     swap_matrix_rows(matrix, i, swap_row);
        //     // Reset computation for the current row
        //     i--;
        //     system_solution.determinant *= -1;
        //     continue;
        // }

        // swap_row = i + 1;
        system_solution.determinant *= matrix[i][i];
    }

    print_matrix(matrix, size, size);
    return system_solution;
}
