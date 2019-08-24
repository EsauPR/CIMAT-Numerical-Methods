/**
    ANSI C standard: c11
    matrix.cpp
    Purpose: Prototype for helper to create a liberate matrices dinamicly

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#ifndef MATRIXIO_H
#define MATRIXIO_H

#include <stdio.h>

#ifdef MATRIXIO_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif


/*
    Flags to know matrix state or information
*/
static const unsigned char __NO_STATE__ = 0;


/* Struct to represent a linear equation system solution */
static const struct Matrix{
    int rows;
    int cols;
    double * pointer_start;
    double ** content;
    unsigned char state;

} Matrix_Default = {0, 0, NULL, NULL, __NO_STATE__};

typedef struct Matrix Matrix;
typedef Matrix AugmentedMatrix;


/* Types to allocate memory */
typedef enum {
    __CHAR_SIZE = sizeof(char),
    __T_INT = sizeof(int),
    __T_FLOAT = sizeof(float),
    __T_DOUBLE = sizeof(double),
} __TYPE_SIZE;


/*Create the memory for a array*/
EXTERN double *allocate_array(int size, __TYPE_SIZE type_size);

/* Create the memory for a matrix */
EXTERN Matrix allocate_matrix(int rows, int cols, __TYPE_SIZE type_size);

/* Liberate the matrix memory */
EXTERN void free_matriz(Matrix matrix);

/* Print a matrix*/
EXTERN void print_matrix(double **matrix, int rows, int cols);

/* Read a matrix and put the elements in a especific location range */
EXTERN void read_matrix(FILE *fp, double** matrix, int from_row, int to_row, int from_col, int  to_col);

/* Read two matrices and put the values in a augmented matrix*/
EXTERN AugmentedMatrix read_augmented_matrix(char* matrix1_fname, char* matrix2_fname);

#undef MATRIXIO_IMPORT
#undef EXTERN
#endif
