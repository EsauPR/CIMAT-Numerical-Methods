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
#include "numsys/matrix/matrix_core.h"

#ifdef MATRIXIO_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif


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

/* Read a matrix and put the elements in a especif location range */
EXTERN void matrixio_scan(FILE *fp, double** matrix, int from_row, int to_row, int from_col, int  to_col);

/* Read a matrix from a file */
Matrix matrixio_read(char * file_name);

/* Read two matrices from files and put the values in a augmented matrix*/
EXTERN AugmentedMatrix matrixio_read_augmented(char * file1_name, char * file2_name);

#undef MATRIXIO_IMPORT
#undef EXTERN
#endif
