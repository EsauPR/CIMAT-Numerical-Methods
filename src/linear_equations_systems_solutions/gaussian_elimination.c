/**
    ANSI C standard: c11
    gaussian_elimination.c
    Purpose: Implementation guassian elimination algorithm

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>

#include "../matrix.h"
#include "backward_substitution.h"

#define GAUSSIAN_ELIMINATION_IMPORT
#include "gaussian_elimination.h"


/* Solve a square matrix by gaussian elimination without pivot */
double *solve_by_simple_gaussian_elimination(double **matrix, int size) {
    for (int j = 0; j < size; j++) {
        // Replaze the pivots with value zero
        if (matrix[j][j] == 0) {
            matrix_point mp = find_matrix_max_element(matrix, j + 1, j, size - 1, j);

            if (mp.value == 0.0) {
                return NULL; // There is not solution
            }

            swap_matrix_rows(matrix, size + 1, j, mp.row);
        }
        // Create the row pivot
        for (int k = size; k >= j; k--) {
            matrix[j][k] /=  matrix[j][j];
        }

        // Make zeros all the elements under of the pivot
        for (int i = j + 1; i < size; i++) {
            for (int k = size; k >= j; k--) {
                matrix[i][k] =  matrix[i][k] - matrix[j][k] * matrix[i][j];
            }
        }
    }

    return solve_upper_triangular_matrix(matrix, size);
}
