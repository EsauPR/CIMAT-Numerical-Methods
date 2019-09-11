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
#include "numsys/matrix_op/eigen_v/jacobi.h"

/*
    Compute the eigen vectors and eigen values with the Jacobi method
    Returns a matrix where the column i is the ith eigen vector
    The 'matrix' will contains the egein values
*/
NSMatrix matrix_eigen_jacobi_method(NSMatrix * matrix) {
    double ** a = matrix->items;
    int size = matrix->rows;
    NSMatrix midentity = matrix_create_identity(size);

    int step = 1;
    while(1) {
        NSMatrixElem elem = matrix_find_max_element(a, 0, size, 0, size, NS__MATRIX_OPS_EXCLUDE_DIAG_);
        if (NS_IS_ZERO(elem.value)) break;

        int i = elem.row, j = elem.col;

        double theta = atan2(2.0 * a[i][j], a[i][i] - a[j][j]) / 2.0;
        printf("%d %lf\n", step++, theta);

        double cos_theta = cos(theta);
        double sin_theta = sin(theta);

        for (int l = 0, m = 0; l < size; l++) {
            a[l][i] = a[l][i] * cos_theta + a[l][j] * sin_theta;
            a[l][j] = -a[l][i] * sin_theta + a[l][j] * cos_theta;

            a[i][m] = a[i][m] * cos_theta + a[j][m] * sin_theta;
            a[j][m] = -a[i][m] * sin_theta + a[j][m] * cos_theta;
        }

    }

    return midentity;
}
