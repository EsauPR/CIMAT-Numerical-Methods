/**
    ANSI C standard: c11
    matrix.cpp
    Purpose: Prototype for functions to make operations over a matrix

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#ifndef NSMATRIX_CORE_H
#define NSMATRIX_CORE_H

#include <stddef.h>

#ifdef NSMATRIX_CORE_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

/* Generic swap */
// #define NS_SWAP(x, y) do { typeof(x) swap = x; x = y; y = swap; } while (0)
#define NS_SWAP(x, y, Type)  { Type swap = x; x = y; y = swap; }

#define NS_ABS(n) (((n) < 0)? -(n):(n))

#define NS_MAX(a,b) (((a) > (b)) ? (a) : (b))

static const int NS__ARCH_64__ = 64;
static const int NS__ARCH_32__ = 32;
static const int NS__ARCH__ = sizeof(void *) * 8;

/* Epsilon value */
static const double NS__EPSILON_64__ = 2.22045E-14; // 2.22045E-16 Real value
static const double NS__EPSILON_32__ = 1.0842E-17; // 1.0842E-19 Real Value

#define NS__EPSILON__ ((NS__ARCH__ == NS__ARCH_64__)? NS__EPSILON_64__ : NS__EPSILON_32__)
#define NS_IS_ZERO(n) ((NS_ABS(n) <= NS__EPSILON__)? 1:0)

/*
    Flags to modify matrix operations or process
*/
typedef unsigned long int NS__flag_ops;
static const NS__flag_ops NS__MATRIX_OPS_NONE_ = 0;
static const NS__flag_ops NS__MATRIX_OPS_DIAG_HAS_ONES__ = 1;

/* Flags to track state and information about the matrix*/
typedef unsigned long int NS__flag_err;
static const NS__flag_err NS__MATRIX_ERR_NONE__ = 0;
static const NS__flag_err NS__MATRIX_ERR_NO_SOLUTION__ = 1;
static const NS__flag_err NS__MATRIX_ERR_NO_LU_DECOMPOSITION__ = 1 << 1;
static const NS__flag_err NS__MATRIX_ERR_NO_LDLT_DECOMPOSITION__ = 1 << 2;
static const NS__flag_err NS__MATRIX_ERR_NO_UPPER_TRIANGULAR__ = 1 << 3;
static const NS__flag_err NS__MATRIX_ERR_NO_LOWER_TRIANGULAR__ = 1 << 4;
static const NS__flag_err NS__MATRIX_ERR_NO_DIAGONAL_MATRIX__ = 1 << 5;
static const NS__flag_err NS__MATRIX_ERR_NO_SYMMETRIC__ = 1 << 6;
static const NS__flag_err NS__MATRIX_ERR_HAS_ZERO_ON_DIAG__ = 1 << 7;
static const NS__flag_err NS__MATRIX_ERR_NO_SQUARE_MATRIX__ = 1 << 8;
static const NS__flag_err NS__MATRIX_ERR_NO_INVERSE__ = 1 << 9;

/* vector */
#define __NSVectorDefaultValues {0, NULL}
static const struct numsys_Vector{
    int size;
    double * items;
} NSVectorDefault = __NSVectorDefaultValues;
typedef struct numsys_Vector NSVector;

/* Struct to represent a matrix */
#define __NSMatrixDefaultValues {0, 0, NULL, NULL, 0.0, NS__MATRIX_ERR_NONE__}
static const struct numsys_Matrix{
    int rows;
    int cols;
    double * pointer_start;
    double ** items;
    double determinant;
    NS__flag_err err;
} NSMatrixDefault = __NSMatrixDefaultValues;
typedef struct numsys_Matrix NSMatrix;

/* Represent a matrix element with the positions i,j */
#define __NSMatrixElemDefaultValues {0.0, 0, 0}
static const struct numsys_Matrix_Element {
    double value;
    int row;
    int col;
} NSMatrixElemDefault = __NSMatrixElemDefaultValues;
typedef struct numsys_Matrix_Element NSMatrixElem;

/* Struct to represent a matrix linear system Ax=b */
static const struct numsys_system {
    NSMatrix a;
    NSVector x;
    NSVector b;
    int * rows_perm_map; // Permutation mapping for rows
    int * cols_perm_map; // Permutation mapping for cols
    NS__flag_err err;
} NSMatrixSystemDefault = {__NSMatrixDefaultValues, __NSVectorDefaultValues, __NSVectorDefaultValues, NULL, NULL, 0};
typedef struct numsys_system NSMatrixSystem;

#undef NSMATRIX_CORE_IMPORT
#undef EXTERN
#endif
