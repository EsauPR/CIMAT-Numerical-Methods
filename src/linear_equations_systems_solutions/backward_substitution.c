/**
    ANSI C standard: c11
    backward_substitutions.c
    Purpose: Implementation for backward substitution algorithms

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#include <stdio.h>
#include "../matrix.h"

#define BACKWARD_SUBSTITUTION_IMPORT
#include "backward_substitution.h"


/*
    Return array with the solution for a lower triangular matrix
    using backward substitution

*/
double *solve_lower_triangular_matrix(double **matrix, int size) {
    double * result = create_dynamic_array(size);
    result[0] = matrix[0][size] / matrix[0][0];

    for (int i = 1; i < size; i++) {
        result[i] = matrix[i][size];
        for (int j = 0; j < i; j++) {
            result[i] -= matrix[i][j] * result[j];
        }
        result[i] /= matrix[i][i];
    }

    return result;
}

/*
    Return array with the solution for a upper triangular matrix
    using backward substitution
*/
double *solve_upper_triangular_matrix(double **matrix, int size) {
    double * result = create_dynamic_array(size);
    result[size - 1] = matrix[size - 1][size] / matrix[size - 1][size - 1];

    for (int i = 2; i <= size; i++) {
        result[size - i] = matrix[size - i][size];
        for (int j = 1; j < i; j++) {
            result[size - i] -= matrix[size - i][size - j] * result[size - j];
        }
        result[size - i] /= matrix[size - i][size - i];
    }

    return result;
}
