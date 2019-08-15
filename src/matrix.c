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

/*Create the memory for a array*/
double *create_dynamic_array(int size) {
    return (double *)malloc(size * sizeof(double));
}

/* Create the memory for a augmented matrix with a extra col */
double **create_matrix(int rows, int cols) {
    double **matrix = (double **)malloc(rows * sizeof(double*));

    for (int i = 0; i < rows; i++){
        matrix[i] = create_dynamic_array(cols);
    }

    return matrix;
}

/* Create a square augmented matrix with a extra col*/
double **create_square_augmented_matrix(int size) {
    return create_matrix(size, size + 1);
}

/* Liberate the matrix memory */
void free_matriz(double **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++){
        free(matrix[i]);
    }

    free(matrix);
}

/* Liberate the matrix memory */
void free_squared_augmented_matriz(double **matrix, int size) {
    free_matriz(matrix, size, size + 1);
}


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

/* Print a matrix*/
void print_matrix(double **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%lf ", matrix[i][j]);
        }
        puts("");
    }
    puts("");
}

double **read_matrix(int rows, int cols) {
    double **matrix = create_square_augmented_matrix(rows);

    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%lf", &matrix[i][j]);
        }
    }

    return matrix;
}

/* Read a augmented square matrix  */
double **read_augmented_square_matrix(int size) {
    return read_matrix(size, size + 1);
}
