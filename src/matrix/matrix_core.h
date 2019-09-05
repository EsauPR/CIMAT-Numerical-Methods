/**
    ANSI C standard: c11
    matrix.cpp
    Purpose: Prototype for functions to make operations over a matrix

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#ifndef MATRIX_CORE_H
#define MATRIX_CORE_H

#include <stddef.h>

#ifdef MATRIX_CORE_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

/* Generic swap */
// #define SWAP(x, y) do { typeof(x) swap = x; x = y; y = swap; } while (0)
#define SWAP(x, y, Type)  { Type swap = x; x = y; y = swap; }

#define ABS(n) (((n) < 0)? -(n):(n))

#define MAX(a,b) (((a) > (b)) ? (a) : (b))

static const int __ARCH_64__ = 64;
static const int __ARCH_32__ = 32;
static const int __ARCH__ = sizeof(void *) * 8;

/* Epsilon value */
static const double __EPSILON_64__ = 2.22045E-14; // 2.22045E-16 Real value
static const double __EPSILON_32__ = 1.0842E-17; // 1.0842E-19 Real Value

#define __EPSILON__ ((__ARCH__ == __ARCH_64__)? __EPSILON_64__ : __EPSILON_32__)
#define IS_ZERO(n) ((ABS(n) <= __EPSILON__)? 1:0)

/*
    Flags to modify matrix operations or process
*/
typedef unsigned long int __flag_ops;
static const __flag_ops __MATRIX_OPS_NONE_ = 0;
static const __flag_ops __MATRIX_OPS_DIAG_HAS_ONES__ = 1;

/* Flags to track state and information about the matrix*/
typedef unsigned long int __flag_err;
static const __flag_err __MATRIX_ERR_NONE__ = 0;
static const __flag_err __MATRIX_ERR_NO_SOLUTION__ = 1;
static const __flag_err __MATRIX_ERR_NO_LU_DECOMPOSITION__ = 1 << 1;
static const __flag_err __MATRIX_ERR_NO_LDLT_DECOMPOSITION__ = 1 << 2;
static const __flag_err __MATRIX_ERR_NO_UPPER_TRIANGULAR__ = 1 << 3;
static const __flag_err __MATRIX_ERR_NO_LOWER_TRIANGULAR__ = 1 << 4;
static const __flag_err __MATRIX_ERR_NO_DIAGONAL_MATRIX__ = 1 << 5;
static const __flag_err __MATRIX_ERR_NO_SYMMETRIC__ = 1 << 6;
static const __flag_err __MATRIX_ERR_HAS_ZERO_ON_DIAG__ = 1 << 7;
static const __flag_err __MATRIX_ERR_NO_SQUARE_MATRIX__ = 1 << 8;
static const __flag_err __MATRIX_ERR_NO_INVERSE__ = 1 << 9;


/* Struct to represent a linear equation system solution */
static const struct matrix_Matrix{
    int rows;
    int cols;
    int cols_extra; // Extra cols to form a augmented matrix
    double * pointer_start;
    double ** content;
    __flag_err err;

} Matrix_Default = {0, 0, 0, NULL, NULL, __MATRIX_ERR_NONE__};

typedef struct matrix_Matrix Matrix;
typedef Matrix AugmentedMatrix;

/* Represent a matrix element with the positions i,j */
static const struct matrix_MatrixElement {
    double value;
    int row;
    int col;
} MatrixElementDefault = {0.0, 0, 0};

typedef struct matrix_MatrixElement MatrixElement;

#undef MATRIX_CORE_IMPORT
#undef EXTERN
#endif
