/**
    ANSI C standard: c11
    backward_substitutions.c
    Purpose: Implementation for backward substitution algorithms

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#include <stdio.h>

#include "../matrix/matrixio.h"
#include "../matrix/matrix.h"

#define BACKWARD_SUBSTITUTION_IMPORT
#include "backward_substitution.h"


/*
    Return array with the solution for a lower triangular matrix
    using backward substitution

    Use the flag 'diag_with_ones' to asume that the diagonal is fullfiled with ones
*/
SystemSolution solve_lower_triangular_matrix(AugmentedMatrix matrix, __flag_t flags) {
    double **mtxa = matrix.content;
    int size = matrix.rows;

    SystemSolution system_solution;
    system_solution.size = size;
    system_solution.solution = create_dynamic_array(size);
    system_solution.determinant = mtxa[0][0];

    system_solution.solution[0] = mtxa[0][size];
    if (!(flags & __DIAGONAL_HAS_ONES__)) {
        system_solution.solution[0] /= mtxa[0][0];
    }

    for (int i = 1; i < size; i++) {
        system_solution.solution[i] = mtxa[i][size];
        for (int j = 0; j < i; j++) {
            system_solution.solution[i] -= mtxa[i][j] * system_solution.solution[j];
        }
        if (!(flags & __DIAGONAL_HAS_ONES__)) {
            system_solution.solution[i] /= mtxa[i][i];
        }
        system_solution.determinant *= mtxa[i][i];
    }

    return system_solution;
}

/*
    Return array with the solution for a upper triangular matrix
    using backward substitution

    Use the flag 'diag_with_ones' to asume that the diagonal is fullfiled with ones
*/
SystemSolution solve_upper_triangular_matrix(AugmentedMatrix matrix, __flag_t flags) {
    double **mtxa = matrix.content;
    int size = matrix.rows;

    SystemSolution system_solution;
    system_solution.size = size;
    system_solution.solution = create_dynamic_array(size);
    system_solution.determinant = mtxa[0][0];

    system_solution.solution[size - 1] = mtxa[size - 1][size];
    if (!(flags & __DIAGONAL_HAS_ONES__)) {
        system_solution.solution[size - 1] /= mtxa[size - 1][size - 1];
    }

    for (int i = 2; i <= size; i++) {
        system_solution.solution[size - i] = mtxa[size - i][size];
        for (int j = 1; j < i; j++) {
            system_solution.solution[size - i] -= mtxa[size - i][size - j] * system_solution.solution[size - j];
        }
        if (!(flags & __DIAGONAL_HAS_ONES__)) {
            system_solution.solution[size - i] /= mtxa[size - i][size - i];
        }
        system_solution.determinant *= mtxa[i - 1][i - 1];
    }

    return system_solution;
}
