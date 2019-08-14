/**
    ANSI C standard: c11
    matrix.cpp
    Purpose: Prototype for helper to create a liberate matrices dinamicly

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>


/*Create the memory for a array*/
double *create_dynamic_array(int size);

/* Create the memory for a augmented matrix with a extra col */
double **create_augmented_matrix(int rows, int cols);

/* Create a square augmented matrix with a extra col*/
double **create_square_augmented_matrix(int size);

/* Liberate the matrix memory */
void free_matriz(double **matrix, int rows, int cols);

/* Liberate the matrix memory */
void free_squared_augmented_matriz(double **matrix, int size);

/* Print a matrix*/
void print_matrix(double **matrix, int rows, int cols);

/* Compute the determinant for a diagonal or triangular matrix */
double get_diagonal_determinant(double **matrix, int size);

/* Read a augmented square matrix  */
double **read_augmented_square_matrix(int size);

/* Print the augmented matrix solution */
void print_result(double *result, int size);
