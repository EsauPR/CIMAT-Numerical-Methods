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

/* Generic swap */
#define SWAP(x, y) do { typeof(x) SWAP = x; x = y; y = SWAP; } while (0)

#define ABS(n) ((n < 0)? (-n):(n))

/* Represent a matrix element with the positions i,j */
typedef struct matrix_MatrixElement{
    double value;
    int row;
    int col;
} MatrixElement;


/*Create the memory for a array*/
EXTERN double *create_dynamic_array(int size);

/* Create the memory for a augmented matrix with a extra col */
EXTERN double **create_matrix(int rows, int cols);

/* Liberate the matrix memory */
EXTERN void free_matriz(double **matrix, int rows, int cols);

/* Liberate the matrix memory */
EXTERN void free_squared_augmented_matriz(double **matrix, int size);

/* Find the max element into a matrix range */
EXTERN MatrixElement find_matrix_max_element(double ** matrix, int from_row, int from_col, int to_row, int to_col);

/* Swap matrix columns */
EXTERN void swap_matrix_cols(double **matrix, int col_size, int col_1, int col_2);

/* Swap matrix rows */
EXTERN void swap_matrix_rows(double **matrix, int row_size, int row_1, int row_2);

/* Print a matrix*/
EXTERN void print_matrix(double **matrix, int rows, int cols);

/* Read a augmented square matrix  */
EXTERN double **read_matrix(int rows, int cols);
/* Read a augmented square matrix  */
EXTERN double **read_augmented_square_matrix(int size);

#undef MATRIX_IMPORT
#undef EXTERN
#endif
