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

/* Create the memory for a matrix */
double **create_matrix(int rows, int cols) {
    double **matrix = (double **)malloc(rows * sizeof(double*));

    for (int i = 0; i < rows; i++){
        matrix[i] = create_dynamic_array(cols);
    }

    return matrix;
}

/* Liberate the matrix memory */
void free_matriz(double **matrix, int rows) {
    for (int i = 0; i < rows; i++){
        free(matrix[i]);
    }

    free(matrix);
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

/* Read a matrix  */
double **read_matrix(int rows, int cols) {
    double **matrix = create_matrix(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%lf", &matrix[i][j]);
        }
    }

    return matrix;
}
