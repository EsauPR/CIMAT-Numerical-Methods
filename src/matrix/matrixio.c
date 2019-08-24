/**
    ANSI C standard: c11
    matrix.cpp
    Purpose: Contains helper to create a liberate matrices dinamicly

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MATRIXIO_IMPORT
#include "matrixio.h"


/*Create the memory for a array*/
int *allocate_int_array(int size) {
    int * dinmem = (int *)calloc(size, sizeof(int));
    if (dinmem == NULL) {
        printf("ERROR: %s\n", strerror(errno));
    }
    return dinmem;
}

/*Create the memory for a array*/
double *allocate_double_array(int size) {
    double * dinmem = (double *)calloc(size, sizeof(double));
    if (dinmem == NULL) {
        printf("ERROR: %s\n", strerror(errno));
    }
    return dinmem;
}

/* Create the memory for a matrix */
Matrix allocate_matrix(int rows, int cols) {
    Matrix matrix = Matrix_Default;
    matrix.content = (double **)calloc(rows, sizeof(double *));
    matrix.rows = rows;
    matrix.cols = cols;
    matrix.state = 0;

    if (matrix.content == NULL) {
        perror("allocate_matrix(): ");
        exit(EXIT_FAILURE);
    }

    matrix.pointer_start = allocate_double_array(rows * cols);
    if (matrix.pointer_start == NULL) {
        perror("allocate_matrix(): ");
        exit(EXIT_FAILURE);
    }

    matrix.content[0] = matrix.pointer_start;
    for (int i = 1; i < rows; i++){
        matrix.content[i] = matrix.content[0] + i * cols;
    }

    return matrix;
}

Matrix copy_matriz(Matrix matrix) {
    Matrix matrix_copy = allocate_matrix(matrix.rows, matrix.cols);
    memcpy(matrix_copy.content[0], matrix.content[0], matrix.rows * matrix.cols * sizeof(**matrix.content));
    return matrix_copy;
}

/*
    Liberate the matrix memory
    Returns the same struct values with NULL on freeded pointers
*/
Matrix free_matriz(Matrix matrix) {
    free(matrix.pointer_start);
    matrix.pointer_start = NULL;
    free(matrix.content);
    matrix.content = NULL;
    return matrix;
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
    int rows1, cols1;
    int rows2, cols2;

    FILE *fp1 = fopen(matrix1_fname, "r");
    if(fp1 == NULL) {
        perror("fopen()");
        exit(EXIT_FAILURE);
    }

    FILE *fp2 = fopen(matrix2_fname, "r");
    if (fp2 == NULL ) {
        perror("fopen()");
        exit(EXIT_FAILURE);
    }

    fscanf(fp1, "%d %d", &rows1, &cols1);
    fscanf(fp2, "%d %d", &rows2, &cols2);

    Matrix matrix = allocate_matrix(rows1, cols1 + cols2);

    read_matrix(fp1, matrix.content, 0, rows1, 0, cols1);
    read_matrix(fp2, matrix.content, 0, rows1, cols1, cols1 + cols2);

    fclose(fp1);
    fclose(fp2);

    return matrix;
}
