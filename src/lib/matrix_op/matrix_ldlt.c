#include <stddef.h>
#include "numsys/matrix/matrix.h"
#include "numsys/matrix/matrixio.h"

#define MATRIX_LDLT_IMPORT
#include "numsys/matrix_op/matrix_ldlt.h"

/*
    Make a LDLt decomposition over the same matrix. L is a lower trangular matrix
    with ones over the diagonal.

    You must asume that the diagonal is ones for L and the values already computed for D

    Returns a struct type SystemSolution

    If the decomposition is not possible SystemSolution.size is equal to -1
*/

void matrix_ldlt_decomposition(NSMatrix * matrix) {
    int size = matrix->rows;
    matrix->determinant = 1.0;

    double * backup_row = matrixio_allocate_array_double(size);

    for (int i = 0, swap_row = i; i < size; i++) {
        // Avoid to reference the matrix->items + i each time
        double * row_i = matrix->items[i];

        for (int j = 0; j <= i; j++) {
            // Avoid to reference the matrix->items + j each time
            double * row_j = matrix->items[j];
            backup_row[j] = row_i[j];

            double sum = 0.0;
            int limit = (i == j)? i:j;
            for (int k = 0; k < limit; k++) {
                sum += row_i[k] * row_j[k] * matrix->items[k][k];
            }
            row_i[j] -= sum;

            if (i != j) {
                row_i[j] /= row_j[j];
            }

            row_j[i] = row_i[j];
        }

        // Swap rows to avoid division by zero
        double diag_value = row_i[i];
        if (NS_IS_ZERO(diag_value) && i < size) {
            // No more swaps available
            if (++swap_row >= size) {
                matrix->err |= NS__MATRIX_ERR_NO_LDLT_DECOMPOSITION__;
                return;
            }
            // Restore current row and swap
            for (int j = 0; j < size; j++) {
                row_i[j] = backup_row[j];
            }
            matrix_swap_rows(*matrix, i, swap_row);
            // Reset computation for the current row
            i--;
            matrix->determinant *= -1;
            continue;
        }

        swap_row = i + 1;
        matrix->determinant *= diag_value;
    }
}
