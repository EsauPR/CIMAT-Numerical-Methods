/**
    ANSI C standard: c11
    matrix_ejen_v.c
    Purpose: Module to get eigen vetors and eigen values
    with Jacobi Method

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdlib.h>
#include <math.h>

#include "numsys/matrix/matrixio.h"
#include "numsys/matrix/matrix.h"

#define NSEigenV_JACOBI_IMPORT
#define NSEigenV_JACOBI_MAX_ITER 1000000
#include "numsys/matrix_op/eigen_v/jacobi.h"

/*
    Compute the eigen vectors and eigen values with the Jacobi method
    Returns a matrix where the column i is the ith eigen vector
    The input 'matrix' will contains the egein values for each eigen vector
*/
NSMatrix matrix_eigen_jacobi_method(NSMatrix * matrix) {
    double ** a = matrix->items;
    int size = matrix->rows, max_iter = NSEigenV_JACOBI_MAX_ITER;
    NSMatrix identity = matrix_create_identity(size);

    while(max_iter--) {
        NSMatrixElem elem = matrix_find_max_element(a, 0, size, 0, size, NS__MATRIX_OPS_EXCLUDE_DIAG_);
        int i = elem.row, j = elem.col;
        if (NS_IS_ZERO(elem.value)) break;

        double theta = atan2(2.0 * a[i][j], a[i][i] - a[j][j]) / 2.0;
        double cos_theta = cos(theta);
        double sin_theta = sin(theta);

        for (int l = 0; l < size; l++) {
            double a_li = a[l][i];
            a[l][i] = a_li * cos_theta + a[l][j] * sin_theta;
            a[l][j] = -a_li * sin_theta + a[l][j] * cos_theta;

            double i_li = identity.items[l][i];
            identity.items[l][i] = i_li * cos_theta + identity.items[l][j] * sin_theta;
            identity.items[l][j] = -i_li * sin_theta + identity.items[l][j] * cos_theta;
        }

        for (int m = 0; m < size; m++) {
            double a_im = a[i][m];
            a[i][m] = a_im * cos_theta + a[j][m] * sin_theta;
            a[j][m] = -a_im * sin_theta + a[j][m] * cos_theta;
        }
    }

    return identity;
}


static NSMatrixElem find_max_element_band(NSMatrix * matrix, int band_size) {
    NSMatrixElem mp = NSMatrixElemDefault;

    for (int j = 0; j < matrix->cols; j++) {
        for (int i = -(band_size / 2); i <= band_size / 2; i++) {
            if (i == 0) continue;

            int ii = j + i;
            if (ii < 0 || ii >= matrix->rows) continue;

            if (NS_ABS(matrix->items[ii][j]) > NS_ABS(mp.value)) {
                mp.value = matrix->items[ii][j];
                mp.row = ii;
                mp.col = j;
            }
        }
    }

    return mp;
}

NSMatrix matrix_eigen_jacobi_method_band(NSMatrix * matrix, int band_size) {
    double ** a = matrix->items;
    int size = matrix->rows, max_iter = NSEigenV_JACOBI_MAX_ITER;
    NSMatrix identity = matrix_create_identity(size);

    while(max_iter--) {
        // NSMatrixElem elem = matrix_find_max_element(a, 0, size, 0, size, NS__MATRIX_OPS_EXCLUDE_DIAG_);
        NSMatrixElem elem = find_max_element_band(matrix, band_size);
        int i = elem.row, j = elem.col;
        if (NS_IS_ZERO(elem.value)) break;

        double theta = atan2(2.0 * a[i][j], a[i][i] - a[j][j]) / 2.0;
        double cos_theta = cos(theta);
        double sin_theta = sin(theta);

        for (int l = 0; l < size; l++) {
            double a_li = a[l][i];
            a[l][i] = a_li * cos_theta + a[l][j] * sin_theta;
            a[l][j] = -a_li * sin_theta + a[l][j] * cos_theta;

            double i_li = identity.items[l][i];
            identity.items[l][i] = i_li * cos_theta + identity.items[l][j] * sin_theta;
            identity.items[l][j] = -i_li * sin_theta + identity.items[l][j] * cos_theta;
        }

        for (int m = 0; m < size; m++) {
            double a_im = a[i][m];
            a[i][m] = a_im * cos_theta + a[j][m] * sin_theta;
            a[j][m] = -a_im * sin_theta + a[j][m] * cos_theta;
        }
    }

    return identity;
}
