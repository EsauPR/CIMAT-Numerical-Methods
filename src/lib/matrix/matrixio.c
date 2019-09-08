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
#include "numsys/matrix/matrixio.h"

/*Create the memory for a array*/
int * matrixio_allocate_array_int(int size) {
    int * dinmem = (int *)calloc(size, sizeof(int));
    if (dinmem == NULL) {
        printf("ERROR: %s\n", strerror(errno));
    }
    return dinmem;
}

/*Create the memory for a array*/
double * matrixio_allocate_array_double(int size) {
    double * dinmem = (double *)calloc(size, sizeof(double));
    if (dinmem == NULL) {
        printf("ERROR: %s\n", strerror(errno));
    }
    return dinmem;
}

/* Create the memory for a Vector */
NSVector matrixio_allocate_vector(int size) {
    NSVector vector = NSVectorDefault;
    vector.items = matrixio_allocate_array_double(size);
    vector.size = size;
    return vector;
}

/* Create the memory for a matrix */
NSMatrix matrixio_allocate_matrix(int rows, int cols) {
    NSMatrix matrix = NSMatrixDefault;
    matrix.items = (double **)calloc(rows, sizeof(double *));
    matrix.rows = rows;
    matrix.cols = cols;
    matrix.err = 0;

    if (matrix.items == NULL) {
        perror("matrixio_allocate_matrix(): ");
        exit(EXIT_FAILURE);
    }

    matrix.pointer_start = matrixio_allocate_array_double(rows * cols);
    if (matrix.pointer_start == NULL) {
        perror("matrixio_allocate_matrix(): ");
        exit(EXIT_FAILURE);
    }

    matrix.items[0] = matrix.pointer_start;
    for (int i = 1; i < rows; i++){
        matrix.items[i] = matrix.items[0] + i * cols;
    }

    return matrix;
}

NSMatrix matrixio_copy(NSMatrix matrix) {
    int rows = matrix.rows;
    int cols = matrix.cols + matrix.cols;
    NSMatrix matrix_copy = matrixio_allocate_matrix(rows, cols);
    memcpy(matrix_copy.items[0], matrix.items[0], rows * cols * sizeof(**matrix.items));
    return matrix_copy;
}

/* Liberate the matrix memory Returns the same struct values with NULL on freeded pointers */
void matrixio_free_matrix(NSMatrix * matrix) {
    if (matrix->pointer_start) {
        free(matrix->pointer_start);
        matrix->pointer_start = NULL;
    }
    if (matrix->items) {
        free(matrix->items);
        matrix->items = NULL;
    }
}

/* Liberate the vector memory */
void matrixio_free_vector(NSVector * vector) {
    if (vector->items) {
        free(vector->items);
        vector->items = NULL;
    }
}

/* Liberate the vector memory */
void matrixio_free_matrix_system(NSMatrixSystem * msystem) {
    matrixio_free_matrix(&(msystem->a));
    matrixio_free_vector(&(msystem->b));
    matrixio_free_vector(&(msystem->x));

    if (msystem->cols_perm_map) {
        free(msystem->cols_perm_map);
        msystem->cols_perm_map = NULL;
    }

    if(msystem->rows_perm_map) {
        free(msystem->rows_perm_map);
        msystem->rows_perm_map = NULL;
    }
}

/* Print a matrix*/
void matrixio_show_matrix(NSMatrix matrix) {
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            printf("%.__MATRIXIO_NDECIMALSlf ", matrix.items[i][j]);
        }
        puts("");
    }
    puts("");
}

/* Print a vector*/
void matrixio_show_vector(NSVector vector) {
    for (int i = 0; i < vector.size; i++) {
        printf("%.__MATRIXIO_NDECIMALSlf\n", vector.items[i]);
    }
    puts("");
}

/* Print a matrix system*/
void matrixio_show_matrix_system(NSMatrixSystem msystem, NS__flag_ops ops) {
    if (ops & NS__MATRIXIO_SHOW_SOL) {
        for (int i = 0; i < msystem.x.size; i++) {
            printf("x_%d: %.__MATRIXIO_NDECIMALSlf\n", msystem.x.items[i]);
        }
    } else {
        for (int i = 0; i < msystem.a.rows; i++) {
            for (int j = 0; j < msystem.a.cols; j++) {
                printf("%lf ", msystem.a.items[i][j]);
            }
            printf("%.__MATRIXIO_NDECIMALSlf\n", msystem.b.items[i]);
        }
    }
}

/* Read a matrix and put the elements in a especif location range */
void matrixio_scan_matrix(FILE *fp, double** matrix, int rows, int cols){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fscanf(fp ,"%lf", &matrix[i][j]);
        }
    }
}

/* Read a vector */
void matrixio_scan_vector(FILE *fp, double* vector, int size) {
    for (int i = 0; i < size; i++) {
        fscanf(fp ,"%lf", &vector[i]);
    }
}

/* Read a matrix from a file */
NSMatrix matrixio_fread_matrix(char *file_name) {
    int rows, cols;

    FILE *fp = fopen(file_name, "rb");
    if(fp == NULL) {
        puts(file_name);
        perror("fopen()");
        exit(EXIT_FAILURE);
    }

    fscanf(fp, "%d %d", &rows, &cols);

    NSMatrix matrix = matrixio_allocate_matrix(rows, cols);
    matrixio_scan_matrix(fp, matrix.items, rows, cols);

    fclose(fp);

    return matrix;
}

/* Read a matrix from a file */
NSVector matrixio_fread_vector(char *file_name) {
    int rows, cols;

    FILE *fp = fopen(file_name, "rb");
    if(fp == NULL) {
        puts(file_name);
        perror("fopen()");
        exit(EXIT_FAILURE);
    }

    fscanf(fp, "%d %d", &rows, &cols);

    // Vector is a matrix with dimensions rows x 1
    NSVector vector = matrixio_allocate_vector(rows);
    matrixio_scan_vector(fp, vector.items, vector.size);

    fclose(fp);

    return vector;
}

/* Read two matrices from files and put the values in a augmented matrix*/
NSMatrixSystem matrixio_fread_matrix_system(char *file1_name, char *file2_name){
    NSMatrixSystem msystem = NSMatrixSystemDefault;
    msystem.a = matrixio_fread_matrix(file1_name);
    msystem.b = matrixio_fread_vector(file2_name);
    msystem.x = matrixio_allocate_vector(msystem.b.size);

    return msystem;
}
