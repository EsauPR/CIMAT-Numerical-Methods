#include <stddef.h>
#include "numsys/matrix/matrix.h"

#define MATRIX_LU_IMPORT
#include "numsys/matrix_op/matrix_lu.h"


/*
    Make a LU decomposition over the same matrix. L is a lower trangular matrix
    with ones over the diagonal.

    You must asume that the diagonal is ones for L and the values already computed for U

    Returns a vector with the mapping for rows permutations with size matrix.rows
*/
int * matrix_lu_decomposition(NSMatrix * matrix) {
    int size = matrix->rows;
    int * rows_perm_map = matrixio_allocate_array_int(size);
    double * row_backup = matrixio_allocate_array_double(size);

    matrix->determinant = 1.0;

    for (int i = 0, swap_row = i; i < size; i++) {
        for (int j = 0; j < size; j++) {
            row_backup[j] = matrix->items[i][j];

            double tmp = 0.0;
            int limit = (j < i) ? j:i;
            for (int k = 0; k < limit; k++) {
                tmp += matrix->items[i][k] * matrix->items[k][j];
            }
            matrix->items[i][j] -= tmp;

            if (j < i) {
                matrix->items[i][j] /= matrix->items[j][j];
            }
        }

        // Swap rows to avoid division by zero
        double diag_value = matrix->items[i][i];
        if (NS_IS_ZERO(diag_value) && i < size - 1) {
            // No more swaps available
            if (++swap_row >= size) {
                matrix->err |= NS__MATRIX_ERR_NO_LU_DECOMPOSITION__;
                return rows_perm_map;
            }
            // Restore current row and swap
            double * row_i = matrix->items[i];
            for (int j = 0; j < size; j++) {
                row_i[j] = row_backup[j];
            }
            matrix_swap_rows(*matrix, i, swap_row);
            NS_SWAP(rows_perm_map[i], rows_perm_map[swap_row], int);
            // Reset computation for the current row
            i--;
            matrix->determinant *= -1;
            continue;
        }

        swap_row = i + 1;
        matrix->determinant *= diag_value;
    }

    free(row_backup);

    return rows_perm_map;
}
