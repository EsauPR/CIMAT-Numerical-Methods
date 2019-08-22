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

/* Struct to represent a linear equation system solution */
typedef struct {
    int rows;
    int cols;
    double * pointer_start;
    double ** content;
} Matrix;

typedef Matrix AugmentedMatrix;


/*Create the memory for a array*/
EXTERN double *create_dynamic_array(int size);

/* Create the memory for a matrix */
EXTERN Matrix allocate_matrix(int rows, int cols);

/* Liberate the matrix memory */
EXTERN void free_matriz(Matrix matrix);

/* Print a matrix*/
EXTERN void print_matrix(double **matrix, int rows, int cols);

/* Read a matrix and put the elements in a especif location range */
EXTERN void read_matrix(FILE *fp, double** matrix, int from_row, int to_row, int from_col, int  to_col);

/* Read two matrices and put the values in a augmented matrix*/
EXTERN AugmentedMatrix read_augmented_matrix(char* matrix1_fname, char* matrix2_fname);

#undef MATRIXIO_IMPORT
#undef EXTERN
#endif
