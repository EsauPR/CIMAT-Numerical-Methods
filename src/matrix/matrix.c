/**
    ANSI C standard: c11
    matrix.cpp
    Purpose: Contains helper to create a liberate matrices dinamicly

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#define MATRIX_IMPORT
#include "matrix.h"

/* Find the max element into a matrix range */
MatrixElement find_matrix_max_element(double ** matrix, int from_row, int to_row, int from_col, int to_col) {
    MatrixElement mp;

    mp.value = matrix[from_row][from_col];
    mp.row = from_row;
    mp.col = from_col;

    for (int i = from_row; i < to_row; i++) {
        for (int j = from_col; j < to_col; j++) {
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
void swap_matrix_rows(double **matrix, int row_1, int row_2) {
    SWAP(matrix[row_1], matrix[row_2]);
}
