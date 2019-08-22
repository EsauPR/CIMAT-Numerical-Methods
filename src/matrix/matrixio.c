/**
    ANSI C standard: c11
    matrix.cpp
    Purpose: Contains helper to create a liberate matrices dinamicly

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "matrixio.h"

/*Create the memory for a array*/
double *create_dynamic_array(int size) {
    double * dinmem = (double *)malloc(size * sizeof(double));
    if (dinmem == NULL) {
        printf("ERROR: %s\n", strerror(errno));
    }
    return dinmem;
}

/* Create the memory for a matrix */
double **create_matrix(int rows, int cols) {
    double **matrix = (double **)malloc(rows * sizeof(double*));

    if (matrix == NULL) {
        printf("ERROR: %s\n", strerror(errno));
    }

    matrix[0] = create_dynamic_array(rows * cols);

    for (int i = 1; i < rows; i++){
        matrix[i] = matrix[0] + i * cols;
    }

    return matrix;
}

/* Liberate the matrix memory */
void free_matriz(double **matrix) {
    free(matrix[0]);
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

/* Read a matrix and put the elements in a especif location range */
void read_matrix(FILE *fp, double** matrix, int from_row, int to_row, int from_col, int  to_col){
    for (int i = from_row; i < to_row; i++) {
        for (int j = from_col; j < to_col; j++) {
            fscanf(fp ,"%lf", &matrix[i][j]);
        }
    }
}


/* Read two matrices and put the values in a augmented matrix*/
AugmentedMatrix read_augmented_matrix(char *matrix1_fname, char *matrix2_fname){
    AugmentedMatrix matrix;
    matrix.content = NULL;
    matrix.rows = 0;
    matrix.cols = 0;

    int rows1, cols1;
    int rows2, cols2;

    FILE *fp1 = fopen(matrix1_fname, "r");
    if(fp1 == NULL) {
        perror("fopen()");
        fclose(fp1);
        exit(EXIT_FAILURE);
    }

    FILE *fp2 = fopen(matrix2_fname, "r");
    if (fp2 == NULL ) {
        perror("fopen()");
        fclose(fp2);
        exit(EXIT_FAILURE);
    }

    fscanf(fp1, "%d %d", &rows1, &cols1);
    fscanf(fp2, "%d %d", &rows2, &cols2);

    matrix.content = create_matrix(rows1, cols1 + cols2);
    matrix.rows = rows1;
    matrix.cols = cols1 + cols2;

    read_matrix(fp1, matrix.content, 0, rows1, 0, cols1);
    read_matrix(fp2, matrix.content, 0, rows1, cols1, cols1 + cols2);

    fclose(fp1);
    fclose(fp2);

    return matrix;
}
