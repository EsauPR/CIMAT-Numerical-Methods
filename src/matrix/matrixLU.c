#include <stddef.h>
#include "matrix.h"

#define MATRIXLU_IMPORT
#include "matrixLU.h"

/*
    Make a LU decomposition over the same matrix. L is a lower trangular matrix
    with ones over the diagonal.

    You must asume that the diagonal is ones for L and the values already computed for U

    Returns a struct type SystemSolution

    If the decomposition is not possible SystemSolution.size is equal to -1
*/

SystemSolution LU_decomposition(double ** matrix, int size) {
    SystemSolution system_solution;
    system_solution.size = size;
    system_solution.solution = NULL;
    system_solution.determinant = 1.0;

    double backup_row[size + 1];

    for (int i = 0, swap_row = i; i < size; i++) {
        for (int j = 0; j < size; j++) {
            backup_row[j] = matrix[i][j];

            int limit = (j < i) ? j:i;
            for (int k = 0; k < limit; k++) {
                matrix[i][j] -= matrix[i][k] * matrix[k][j];
            }

            if (j < i) {
                matrix[i][j] /= matrix[j][j];
            }
        }

        // Swap rows to avoid division by zero
        if (matrix[i][i] == 0.0 && i < size -1) {
            // No more swaps available
            if (++swap_row == size) {
                system_solution.size = -1;
                return system_solution;
            }
            // Restore current row and swap
            for (int j = 0; j < size; j++){
                matrix[i][j] = backup_row[j];
            }
            swap_matrix_rows(matrix, i, swap_row);
            // Reset computation for the current row
            i--;
            system_solution.determinant *= -1;
            continue;
        }

        swap_row = i + 1;
        system_solution.determinant *= matrix[i][i];
    }

    return system_solution;
}