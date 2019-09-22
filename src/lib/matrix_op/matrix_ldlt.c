#include <stddef.h>
#include <stdlib.h>
#include "numsys/matrix/matrix.h"
#include "numsys/matrix/matrixio.h"

#define MATRIX_LDLT_IMPORT
#include "numsys/matrix_op/matrix_ldlt.h"

/*
    Make a LDLt decomposition over the same matrix. L is a lower trangular matrix
    with ones over the diagonal.

    You must asume that the diagonal is ones for L and the values already computed for D

    Returns the rows permutation mapping
*/

int * matrix_ldlt_decomposition(NSMatrix * matrix) {
    int size = matrix->rows;
    int * rows_perm_map = matrixio_allocate_array_int(size);

    matrix->determinant = 1.0;

    // Set permutation map positions
    int * iter = rows_perm_map;
    for (int i = 0; i < size; i++, iter++) {
        *iter = i;
    }

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
                free(backup_row);
                return rows_perm_map;
            }
            // Restore current row and swap
            for (int j = 0; j < size; j++) {
                row_i[j] = backup_row[j];
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

    free(backup_row);
    return rows_perm_map;
}
