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


/*Create the memory for a array*/
EXTERN int *matrixio_allocate_int_array(int size);

/*Create the memory for a array*/
EXTERN double *matrixio_allocate_double_array(int size);

/* Create the memory for a matrix */
EXTERN Matrix matrixio_allocate(int rows, int cols);

/* Copy the matrix memory */
EXTERN Matrix matrixio_copy(Matrix matrix);

/*
    Liberate the matrix memory
    Returns the same struct values with NULL on freeded pointers
*/
EXTERN Matrix matrixio_free(Matrix matrix);

/* Print a matrix*/
EXTERN void matrixio_show(double ** matrix, int rows, int cols);

/* Read a matrix from a file */
Matrix matrixio_read(char * file_name);

/* Read two matrices from files and put the values in a augmented matrix*/
EXTERN AugmentedMatrix matrixio_read_augmented(char * file1_name, char * file2_name);

#undef MATRIXIO_IMPORT
#undef EXTERN
#endif
