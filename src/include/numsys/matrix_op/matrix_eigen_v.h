/**
    ANSI C standard: c11
    matrix_ejen_v.h
    Purpose: Prototype for module to get eigen vetors and eigen values

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#ifndef MATRIX_EIGEN_V_H
#define MATRIX_EIGEN_V_H

#include "numsys/matrix/matrix_core.h"

#ifdef MATRIX_EIGEN_V_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

/* Struct to represent an eigen value and eigen vector */
static const struct matrix_eigen_v{
    double eigen_value;
    double * eigen_vector;
    NS__flag_err err;
} Matrix_Eigen_V_Default = {0, NULL, NS__MATRIX_ERR_NONE__};

typedef struct matrix_eigen_v Matrix_Eigen_V;

/* Compute the max eigen value and their eigen vector */
EXTERN Matrix_Eigen_V matrix_eigen_potence_method(NSMatrix * matrix);

/* Compute the min eigen value and their eigen vector */
EXTERN Matrix_Eigen_V matrix_eigen_potence_method_inverse(NSMatrix * matrix);

/* Free Matrix_Eigen_V struct */
EXTERN void matrix_eigen_free(Matrix_Eigen_V * eigen_v);


#undef MATRIX_EIGEN_V_IMPORT
#undef EXTERN
#endif
