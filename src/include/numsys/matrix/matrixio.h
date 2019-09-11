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

#define NS__MATRIXIO_SHOW_SOL 1

/*Create the memory for a array*/
EXTERN int *matrixio_allocate_array_int(int size);

/*Create the memory for a array*/
EXTERN double *matrixio_allocate_array_double(int size);

/* Create the memory for a Matrix */
EXTERN NSMatrix matrixio_allocate_matrix(int rows, int cols);

/* Create the memory for a Vector */
EXTERN NSVector matrixio_allocate_vector(int size);

/* Copy the matrix memory */
EXTERN NSMatrix matrixio_copy_matrix(NSMatrix matrix);

/* Liberate the matrix memory */
EXTERN void matrixio_free_matrix(NSMatrix * matrix);

/* Liberate the vector memory */
EXTERN void matrixio_free_vector(NSVector * vector);

/* Liberate the vector memory */
EXTERN void matrixio_free_matrix_system(NSMatrixSystem * msystem);

/* Print a matrix*/
EXTERN void matrixio_show_matrix(NSMatrix matrix);

/* Print a vector*/
EXTERN void matrixio_show_vector(NSVector vector);

/* Print a matrix system*/
EXTERN void matrixio_show_matrix_system(NSMatrixSystem msystem, NS__flag_ops ops);

/* Read a matrix */
EXTERN void matrixio_scan_matrix(FILE *fp, double** matrix, int rows, int cols);

/* Read a vector */
EXTERN void matrixio_scan_vector(FILE *fp, double* vector, int size);

/* Read a matrix from a file */
EXTERN NSMatrix matrixio_fread_matrix(char * file_name);

/* Read a matrix from a file */
EXTERN NSVector matrixio_fread_vector(char *file_name);

/* Read two matrices from files and put the values in a augmented matrix*/
EXTERN NSMatrixSystem matrixio_fread_matrix_system(char * file1_name, char * file2_name);

/* Free NSEigenV struct */
EXTERN void matrixio_free_eigen_v(NSEigenV * eigen_v);

#undef MATRIXIO_IMPORT
#undef EXTERN
#endif
