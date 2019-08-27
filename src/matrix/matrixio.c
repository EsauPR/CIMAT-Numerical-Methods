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
int *matrixio_allocate_int_array(int size) {
    int * dinmem = (int *)calloc(size, sizeof(int));
    if (dinmem == NULL) {
        printf("ERROR: %s\n", strerror(errno));
    }
    return dinmem;
}

/*Create the memory for a array*/
double *matrixio_allocate_double_array(int size) {
    double * dinmem = (double *)calloc(size, sizeof(double));
    if (dinmem == NULL) {
        printf("ERROR: %s\n", strerror(errno));
    }
    return dinmem;
}

/* Create the memory for a matrix */
Matrix matrixio_allocate(int rows, int cols) {
    Matrix matrix = Matrix_Default;
    matrix.content = (double **)calloc(rows, sizeof(double *));
    matrix.rows = rows;
    matrix.cols = cols;
    matrix.err = 0;

    if (matrix.content == NULL) {
        perror("matrixio_allocate(): ");
        exit(EXIT_FAILURE);
    }

    matrix.pointer_start = matrixio_allocate_double_array(rows * cols);
    if (matrix.pointer_start == NULL) {
        perror("matrixio_allocate(): ");
        exit(EXIT_FAILURE);
    }

    matrix.content[0] = matrix.pointer_start;
    for (int i = 1; i < rows; i++){
        matrix.content[i] = matrix.content[0] + i * cols;
    }

    return matrix;
}

Matrix matrixio_copy(Matrix matrix) {
    int rows = matrix.rows;
    int cols = matrix.cols + matrix.cols_extra;
    Matrix matrix_copy = matrixio_allocate(rows, cols);
    memcpy(matrix_copy.content[0], matrix.content[0], rows * cols * sizeof(**matrix.content));
    return matrix_copy;
}

/*
    Liberate the matrix memory
    Returns the same struct values with NULL on freeded pointers
*/
Matrix matrixio_free(Matrix matrix) {
    free(matrix.pointer_start);
    matrix.pointer_start = NULL;
    free(matrix.content);
    matrix.content = NULL;
    return matrix;
}

/* Print a matrix*/
void matrixio_show(double **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%lf ", matrix[i][j]);
        }
        puts("");
    }
    puts("");
}

/* Read a matrix and put the elements in a especif location range */
void matrixio_scan(FILE *fp, double** matrix, int from_row, int to_row, int from_col, int  to_col){
    for (int i = from_row; i < to_row; i++) {
        for (int j = from_col; j < to_col; j++) {
            fscanf(fp ,"%lf", &matrix[i][j]);
        }
    }
}

/* Read a matrix from a file */
Matrix matrixio_read(char *file_name) {
    int rows, cols;

    FILE *fp = fopen(file_name, "rb");
    if(fp == NULL) {
        puts(file_name);
        perror("fopen()");
        exit(EXIT_FAILURE);
    }

    fscanf(fp, "%d %d", &rows, &cols);

    Matrix matrix = matrixio_allocate(rows, cols);

    matrixio_scan(fp, matrix.content, 0, rows, 0, cols);
    fclose(fp);

    return matrix;
}


/* Read two matrices from files and put the values in a augmented matrix*/
AugmentedMatrix matrixio_read_augmented(char *file1_name, char *file2_name){
    int rows1, cols1;
    int rows2, cols2;

    FILE *fp1 = fopen(file1_name, "rb");
    if(fp1 == NULL) {
        puts(file1_name);
        perror("fopen()");
        exit(EXIT_FAILURE);
    }

    FILE *fp2 = fopen(file2_name, "rb");
    if (fp2 == NULL ) {
        puts(file2_name);
        perror("fopen()");
        exit(EXIT_FAILURE);
    }

    fscanf(fp1, "%d %d", &rows1, &cols1);
    fscanf(fp2, "%d %d", &rows2, &cols2);

    if (cols1 != rows2) {
        perror("matrixio_read_augmented(): Invalid matrices sizes");
        fclose(fp1);
        fclose(fp2);
        exit(EXIT_FAILURE);
    }

    Matrix matrix = matrixio_allocate(rows1, cols1 + cols2);
    matrix.cols = cols1;
    matrix.cols_extra = cols2;

    matrixio_scan(fp1, matrix.content, 0, rows1, 0, cols1);
    matrixio_scan(fp2, matrix.content, 0, rows1, cols1, cols1 + cols2);

    fclose(fp1);
    fclose(fp2);

    return matrix;
}
