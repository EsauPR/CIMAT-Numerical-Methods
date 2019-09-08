#include <stdlib.h>
#include "numsys/matrix_op/matrix_lu.h"
#include "numsys/solvers/bwfw_substitution.h"

#define MATRIX_INVERSE_IMPORT
#include "numsys/matrix_op/matrix_inverse.h"

/* Compute the matrix inverse with LU factorization */
NSMatrix matrix_inverse_get(NSMatrix * matrix) {
    int size = matrix->rows;
    NSMatrix inverse = matrixio_allocate_matrix(size, size);

    int * rows_perm_map = matrix_lu_decomposition(matrix);
    if (matrix->err & NS__MATRIX_ERR_NO_LU_DECOMPOSITION__) {
        inverse.err = matrix->err = NS__MATRIX_ERR_NO_INVERSE__ | matrix->err;
        free(rows_perm_map);
        return inverse;
    }

    NSMatrixSystem msystem = NSMatrixSystemDefault;
    msystem.a = *matrix;
    msystem.x = matrixio_allocate_vector(size);
    msystem.b = matrixio_allocate_vector(size);

    for (int i = 0; i < size; i++) {
        // Copy the column i to make Ax=I[:,i]
        for (int j = 0; j < size; j++) {
            msystem.b.items[j] = (j==i)? 1.0: 0.0;
        }
        // Solve Ly = I[:,i]
        solver_forward_substitution(&msystem, NS__MATRIX_OPS_DIAG_HAS_ONES__);

        // Solve Ux = y
        NS_SWAP(msystem.x.items, msystem.b.items, double *)
        solver_backward_substitution(&msystem, NS__MATRIX_OPS_NONE_);

        // Copy x to form A^-1[:,i] mapping by positions map array
        for (int j = 0; j < size; j++) {
            inverse.items[j][rows_perm_map[i]] = msystem.x.items[j];
        }
    }

    free(rows_perm_map);
    matrixio_free_vector(&(msystem.x));
    matrixio_free_vector(&(msystem.b));

    return inverse;
}
