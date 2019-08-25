#include <stdlib.h>
#include "matrix_lu.h"
#include "../linear_equations_systems_solutions/backward_substitution.h"

#define MATRIX_INVERSE_IMPORT
#include "matrix_inverse.h"

/* Compute the matrix inverse with LU factorization */
Matrix matrix_inverse_get(Matrix matrix) {
    int size = matrix.rows;
    Matrix inverse = matrixio_allocate(size, size);
    SystemSolution lu_sol = matrix_lu_decomposition(matrix.content, size);

    if (lu_sol.state & __MATRIX_NO_LU_DECOMPOSITION__) {
        inverse.state &= __MATRIX_NO_INVERSE__ & lu_sol.state;
        return inverse;
    }

    for (int i = 0; i < size; i++) {
        // Copy the column i to make Ax=I[:,i]
        for (int j = 0; j < size; j++) {
            matrix.content[j][size] = (j==i)? 1.0: 0.0;
        }

        // Solve Ly = I[:,i]
        SystemSolution ss = solve_lower_triangular_matrix(matrix, __MATRIX_DIAG_HAS_ONES__);

        // Solve Ux = y
        for (int j = 0; j < size; j++) {
            matrix.content[j][size] = ss.solution[j];
        }
        solution_free(ss);
        ss = solve_upper_triangular_matrix(matrix, __MATRIX_NO_FLAGS__);

        // Copy x to form A^-1[:,i] mapping by positions map array
        for (int j = 0; j < size; j++) {
            inverse.content[j][lu_sol.rows_perm_map[i]] = ss.solution[j];
        }
        solution_free(ss);
    }

    solution_free(lu_sol);

    return inverse;
}
