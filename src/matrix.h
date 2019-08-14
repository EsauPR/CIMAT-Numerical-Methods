/**
    ANSI C standard: c11
    matrix.cpp
    Purpose: Prototype for helper to create a liberate matrices dinamicly

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#ifndef MATRIX_H
#define MATRIX_H

#ifdef MATRIX_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

/*Create the memory for a array*/
EXTERN double *create_dynamic_array(int size);

/* Create the memory for a augmented matrix with a extra col */
EXTERN double **create_augmented_matrix(int rows, int cols);

/* Create a square augmented matrix with a extra col*/
EXTERN double **create_square_augmented_matrix(int size);

/* Liberate the matrix memory */
EXTERN void free_matriz(double **matrix, int rows, int cols);

/* Liberate the matrix memory */
EXTERN void free_squared_augmented_matriz(double **matrix, int size);

/* Print a matrix*/
EXTERN void print_matrix(double **matrix, int rows, int cols);

/* Compute the determinant for a diagonal or triangular matrix */
EXTERN double get_diagonal_determinant(double **matrix, int size);

/* Read a augmented square matrix  */
EXTERN double **read_augmented_square_matrix(int size);

/* Print the augmented matrix solution */
EXTERN void print_result(double *result, int size);

#undef MATRIX_IMPORT
#undef EXTERN
#endif
