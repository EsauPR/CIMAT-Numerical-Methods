/**
    ANSI C standard: c11
    backward_substitutions.c
    Purpose: Implementation for backward substitution algorithms

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#define BACKWARD_SUBSTITUTION_IMPORT
#include "backward_substitution.h"


/*
    Return array with the solution for a lower triangular matrix
    using backward substitution

    Use the flag '__MATRIX_OPS_DIAG_HAS_ONES__' to asume that the diagonal is fullfiled with ones
*/
SystemSolution solve_lower_triangular_matrix(AugmentedMatrix matrix, __flag_ops flags) {
    double **mtxa = matrix.content;
    int size = matrix.rows;

    SystemSolution system_solution = SystemSolutionDefault;
    system_solution.size = size;
    system_solution.solution = matrixio_allocate_double_array(size);
    system_solution.determinant = 1.0;

    for (int i = 0; i < size; i++) {
        system_solution.solution[i] = mtxa[i][size];
        for (int j = 0; j < i; j++) {
            system_solution.solution[i] -= mtxa[i][j] * system_solution.solution[j];
        }
        if (!(flags & __MATRIX_OPS_DIAG_HAS_ONES__)) {
            system_solution.solution[i] /= mtxa[i][i];
        }
        system_solution.determinant *= mtxa[i][i];
    }

    return system_solution;
}

/*
    Return array with the solution for a upper triangular matrix
    using backward substitution

    Use the flag '__MATRIX_OPS_DIAG_HAS_ONES__' to asume that the diagonal is fullfiled with ones
*/
SystemSolution solve_upper_triangular_matrix(AugmentedMatrix matrix, __flag_ops flags) {
    double **mtxa = matrix.content;
    int size = matrix.rows;

    SystemSolution system_solution = SystemSolutionDefault;
    system_solution.size = size;
    system_solution.solution = matrixio_allocate_double_array(size);
    system_solution.determinant = 1.0;

    for (int i = size - 1; i >= 0; i--) {
        system_solution.solution[i] = mtxa[i][size];
        for (int j = i + 1; j < size; j++) {
            system_solution.solution[i] -= mtxa[i][j] * system_solution.solution[j];
        }
        if (!(flags & __MATRIX_OPS_DIAG_HAS_ONES__)) {
            system_solution.solution[i] /= mtxa[i][i];
        }
        system_solution.determinant *= mtxa[i][i];
    }

    return system_solution;
}
