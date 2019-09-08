#include <stdlib.h>
#include "numsys/matrix_op/matrix_lu.h"
#include "numsys/solvers/bwfw_substitution.h"

#define MATRIX_INVERSE_IMPORT
#include "numsys/matrix_op/matrix_inverse.h"

/* Compute the matrix inverse with LU factorization */
Matrix matrix_inverse_get(AugmentedMatrix matrix) {
    int size = matrix.rows;
    Matrix inverse = matrixio_allocate_matrix(size, size);
    SystemSolution lu_sol = matrix_lu_decomposition(matrix.items, size);

    if (lu_sol.err & NS__MATRIX_ERR_NO_LU_DECOMPOSITION__) {
        inverse.err |= NS__MATRIX_ERR_NO_INVERSE__ | lu_sol.err;
        return inverse;
    }

    for (int i = 0; i < size; i++) {
        // Copy the column i to make Ax=I[:,i]
        for (int j = 0; j < size; j++) {
            matrix.items[j][size] = (j==i)? 1.0: 0.0;
        }

        // Solve Ly = I[:,i]
        SystemSolution ss = solver_forward_substitution(matrix, NS__MATRIX_OPS_DIAG_HAS_ONES__);

        // Solve Ux = y
        for (int j = 0; j < size; j++) {
            matrix.items[j][size] = ss.solution[j];
        }
        solution_free(ss);
        ss = solver_backward_substitution(matrix, NS__MATRIX_OPS_NONE_);

        // Copy x to form A^-1[:,i] mapping by positions map array
        for (int j = 0; j < size; j++) {
            inverse.items[j][lu_sol.rows_perm_map[i]] = ss.solution[j];
        }
        solution_free(ss);
    }

    solution_free(lu_sol);

    return inverse;
}
