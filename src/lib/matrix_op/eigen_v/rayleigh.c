/**
    ANSI C standard: c11
    matrix_ejen_v.c
    Purpose: Module to get eigen vetors and
    eigen values with Rayleigh Method

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdlib.h>
#include <math.h>

#include "numsys/matrix/matrixio.h"
#include "numsys/matrix/matrix.h"

#define NSEigenV_RAYLEIGH_IMPORT
#define NSEigenV_RAYLEIGH_MAX_ITER 1000000
#include "numsys/matrix_op/eigen_v/rayleigh.h"

/*
    Compute the eigen vectors and eigen values with the Rayleigh Method
    Returns a matrix where the column i is the ith eigen vector
    The 'matrix' will contains the egein values
*/
NSMatrix matrix_eigen_rayleigh_method(NSMatrix * matrix) {

}
