/**
    ANSI C standard: c11
    matrix.cpp
    Purpose: Contains helper to create a liberate matrices dinamicly

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"


/* Find the max element into a matrix range */
MatrixElement find_matrix_max_element(double ** matrix, int from_row, int from_col, int to_row, int to_col) {
    MatrixElement mp;

    mp.value = matrix[from_row][from_col];
    mp.row = from_row;
    mp.col = from_col;

    for (int i = from_row; i <= to_row; i++) {
        for (int j = from_col; j <= to_col; j++) {
            if (ABS(matrix[i][j]) > ABS(mp.value)) {
                mp.value = matrix[i][j];
                mp.row = i;
                mp.col = j;
            }
        }
    }

    return mp;
}

/* Swap matrix columns */
void swap_matrix_cols(double **matrix, int col_size, int col_1, int col_2) {
    for (int i = 0; i < col_size; i++){
        SWAP(matrix[i][col_1], matrix[i][col_2]);
    }
}

/* Swap matrix rows */
void swap_matrix_rows(double **matrix, int row_size, int row_1, int row_2) {
    for (int i = 0; i < row_size; i++){
        SWAP(matrix[row_1][i], matrix[row_2][i]);
    }
}

/* Restore a matrix row in a range */
void restore_matrix_row(double **matrix, double *backup_row, int row, int from, int to) {
    for (int i = from; i <= to; i++) {
        matrix[row][i] = backup_row[i];
    }
}


/*
    Make a LU decomposition over the same matrix. L is a lower trangular matrix
    with ones over the diagonal.

    You must asume that the diagonal is ones for L and the values already computed for U

    Returns a struct type SystemSolution

    If the decomposition is not possible SystemSolution.size is equal to -1
*/

SystemSolution LU_decomposition(double ** matrix, int size) {
    SystemSolution system_solution;
    system_solution.size = size;
    system_solution.solution = NULL;
    system_solution.determinant = matrix[0][0];

    double backup_row[size + 1];

    for (int i = 1; i < size; i++) {
        matrix[i][0] /= matrix[0][0];
    }

    for (int i = 1, swap_row = 1; i < size; i++) {
        for (int j = 1; j < size; j++) {
            backup_row[j] = matrix[i][j];

            int limit = (j < i) ? j:i;
            for (int k = 0; k < limit; k++) {
                matrix[i][j] -= matrix[i][k] * matrix[k][j];
            }

            if (j < i) {
                matrix[i][j] /= matrix[j][j];
            }
        }

        // Swap rows to avoid division by zero
        if (matrix[i][i] == 0.0 && i < size -1) {
            // No more swaps available
            if (swap_row++ == size) {
                system_solution.size = -1;
                return system_solution;
            }

            // Restore current row and swap
            SWAP(matrix[i][0], matrix[swap_row][0]);
            SWAP(matrix[i][size], matrix[swap_row][size]);
            for (int j = 1; j < size; j++){
                matrix[i][j] = backup_row[j];
                SWAP(matrix[i][j], matrix[swap_row][j]);
            }

            i--; // Reset computation for the current row
            system_solution.determinant *= -1;
            continue;
        }

        swap_row = i;
        system_solution.determinant *= matrix[i][i];
    }

    return system_solution;
}
