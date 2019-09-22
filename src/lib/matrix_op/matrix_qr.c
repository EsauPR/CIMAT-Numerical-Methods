#include <stdlib.h>
#include <stddef.h>
#include <math.h>

#include "numsys/matrix/matrix.h"

#define MATRIX_QR_IMPORT
#include "numsys/matrix_op/matrix_qr.h"


/*
    Make a QR decomposition of a matrix 'A'
    The matrix 'R' will contain the values for R
    and A will contain the values for 'Q'
*/
void matrix_qr_decomposition(NSMatrix * A, NSMatrix * R) {
    int rows = A->rows;
    int cols = A->cols;
    double ** a = A->items;
    double ** q = a; // Alias to a

    double ** r = R->items;
    double * a_tmp = matrixio_allocate_array_double(rows);

    for (int j = 0; j < cols; j++) {
        // Compute r_ij
        for (int i = 0; i < j; i++) {
            double sum = 0;
            for (int k = 0; k < rows; k++) {
                sum += q[k][i] * a[k][j];
            }
            r[i][j] = sum;
            r[j][i] = 0;
        }
        // Compute a*_j
        double a_tmp_norm = 0;
        for (int i = 0; i < rows; i++) {
            double sum = 0;
            for (int k = 0; k < j; k++) {
                sum += r[k][j] * q[i][k];
            }
            a_tmp[i] = a[i][j] - sum;

            a_tmp_norm += a_tmp[i] * a_tmp[i];
        }
        // Compute r_jj
        a_tmp_norm = sqrt(a_tmp_norm);
        r[j][j] = a_tmp_norm;
        // Compute q_j
        for (int i = 0; i < rows; i++) {
            q[i][j] = a_tmp[i] / a_tmp_norm;
        }
    }

    free(a_tmp);
}
