/**
    ANSI C standard: c11
    matrix.cpp
    Purpose: Contains helper to create a liberate matrices dinamicly

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>


/*Create the memory for a array*/
double *create_dynamic_array(int size) {
    return malloc(size * sizeof(double));
}

/* Create the memory for a augmented matrix with a extra col */
double **create_augmented_matrix(int rows, int cols) {
    double **matrix = NULL;
    matrix = malloc(rows * sizeof(double *));

    for (int i = 0; i < rows; i++){
        matrix[i] = create_dynamic_array(cols + 1);
    }

    return matrix;
}

/* Create a square augmented matrix with a extra col*/
double **create_square_augmented_matrix(int size) {
    return create_augmented_matrix(size, size);
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
