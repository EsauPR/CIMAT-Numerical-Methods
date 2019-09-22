/**
    ANSI C standard: c11
    matrix_ejen_v.c
    Purpose: Module to get eigen values by QR Method

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdlib.h>

#include "numsys/matrix/matrixio.h"
#include "numsys/matrix/matrix.h"
#include "numsys/matrix_op/matrix_qr.h"

#define NS_EIGEN_V_QR_IMPORT
#define NS_EIGEN_V_QR_MAX_ITER 10000
#include "numsys/matrix_op/eigen_v/qr.h"
