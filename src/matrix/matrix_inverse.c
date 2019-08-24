#include <stdlib.h>
#include "matrixLU.h"
#include "../linear_equations_systems_solutions/backward_substitution.h"

#define MATRIX_INVERSE_IMPORT
#include "matrix_inverse.h"


static Matrix matrix_inverse_get_indentity(int size) {
    Matrix matrix = allocate_matrix(size, size);

    for (int i = 0; i < size; i++) {
        matrix.content[i][i] = 1.0;
    }

    return matrix;
}


/* Compute the matrix inverse with LU factorization */
Matrix get_matrix_inverse(Matrix matrix) {
    int size = matrix.rows;
    Matrix inverse = matrix_inverse_get_indentity(size);
    SystemSolution ss = LU_decomposition(matrix.content, size);

    if (ss.state & __MATRIX_NO_LU_DECOMPOSITION__) {
        inverse.state &= __MATRIX_NO_INVERSE__ & ss.state;
        return inverse;
    }

    for (int i = 0; i < size; i++) {
        // Copy the column i to make Ax=I[:,i]
        for (int j = 0; j < size; j++) {
            matrix.content[j][size] = inverse.content[j][i];
        }
        // Solve Ly = I[:,i]
        ss.solution = solve_lower_triangular_matrix(matrix, __MATRIX_DIAG_HAS_ONES__).solution;
        // Solve Ux = y
        for (int j = 0; j < size; j++) {
            matrix.content[j][size] = ss.solution[j];
        }
        free(ss.solution);
        ss.solution = solve_upper_triangular_matrix(matrix, __MATRIX_NO_FLAGS__).solution;
        // Copy x to form A^-1[:,i]
        for (int j = 0; j < size; j++) {
            inverse.content[j][i] = ss.solution[j];
        }
        free(ss.solution);
    }

    return inverse;
}
