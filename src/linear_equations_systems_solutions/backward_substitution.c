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

*/
SystemSolution solve_lower_triangular_matrix(double **matrix, int size) {
    SystemSolution system_solution;
    system_solution.size = size;
    system_solution.solution = create_dynamic_array(size);
    system_solution.determinant = matrix[0][0];

    system_solution.solution[0] = matrix[0][size] / matrix[0][0];

    for (int i = 1; i < size; i++) {
        system_solution.solution[i] = matrix[i][size];
        for (int j = 0; j < i; j++) {
            system_solution.solution[i] -= matrix[i][j] * system_solution.solution[j];
        }
        system_solution.solution[i] /= matrix[i][i];
        system_solution.determinant *= matrix[i][i];
    }

    return system_solution;
}

/*
    Return array with the solution for a upper triangular matrix
    using backward substitution
*/
SystemSolution solve_upper_triangular_matrix(double **matrix, int size) {
    SystemSolution system_solution;
    system_solution.size = size;
    system_solution.solution = create_dynamic_array(size);
    system_solution.determinant = matrix[0][0];

    system_solution.solution[size - 1] = matrix[size - 1][size] / matrix[size - 1][size - 1];

    for (int i = 2; i <= size; i++) {
        system_solution.solution[size - i] = matrix[size - i][size];
        for (int j = 1; j < i; j++) {
            system_solution.solution[size - i] -= matrix[size - i][size - j] * system_solution.solution[size - j];
        }
        system_solution.solution[size - i] /= matrix[size - i][size - i];
        system_solution.determinant *= matrix[i - 1][i - 1];
    }

    return system_solution;
}
