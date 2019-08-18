/**
    ANSI C standard: c11
    matrix.cpp
    Purpose: Prototype for helper to create a liberate matrices dinamicly

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#ifndef MATRIXIO_H
#define MATRIXIO_H

#ifdef MATRIXIO_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif




/*Create the memory for a array*/
EXTERN double *create_dynamic_array(int size);

/* Create the memory for a matrix */
EXTERN double **create_matrix(int rows, int cols);

/* Liberate the matrix memory */
EXTERN void free_matriz(double **matrix, int rows);

/* Print a matrix*/
EXTERN void print_matrix(double **matrix, int rows, int cols);

/* Read a matrix  */
EXTERN double **read_matrix(int rows, int cols);

#undef MATRIXIO_IMPORT
#undef EXTERN
#endif
