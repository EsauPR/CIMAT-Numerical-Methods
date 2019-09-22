/**
    ANSI C standard: c11
    matrix_ejen_v.c
    Purpose: Module to get eigen values by QR Method

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdlib.h>
#include <math.h>

#include "numsys/matrix/matrixio.h"
#include "numsys/matrix/matrix.h"
#include "numsys/matrix_op/matrix_qr.h"

#define NS_EIGEN_V_SUBSPACE_ITERATION_IMPORT

#include "numsys/matrix_op/eigen_v/qr.h"

#define NS_EIGEN_V_SUBSPACE_ITERATION_MAX_ITER 100000
#define NS_EIGEN_V_SUBSPACE_ITERATION_MIN_ITER 100


/*
    Multiply matrix a* x b = c and save the result in the matrix c
    a* is the transpose matrix of a
*/
static void multiply_qta(double ** q, double ** a, double ** s, int qrows, int qcols) {
    for (int i = 0; i < qcols; i++) {
        for (int j = 0; j < qrows; j++) {
            s[i][j] = 0;
            for (int k = 0; k < qrows; k++) {
                s[i][j] += q[k][i] * a[k][j];
            }
        }
    }
}

/* Normalize the each column of the matriz p */
static void normalize_p(double ** p, int rows, int cols){
    double * norm = matrixio_allocate_array_double(cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++){
            norm[j] += p[i][j] * p[i][j];
        }
    }

    for (int i = 0; i < cols; i++) {
        norm[i] = sqrt(norm[i]);
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++){
            p[i][j] /= norm[j];
        }
    }

    free(norm);
}

/*
    Compute the n eigen vectors and eigen values with the Subspace Iteration Method
    A will be reduced to a matrix that contains the eigen values
    Returns a matrix where each column is a eigen vector
*/
NSMatrix matrix_eigen_subspace_iteration_method(NSMatrix * matrix, int neigen) {
    NSMatrix * A = matrix;
    NSMatrix P = matrixio_allocate_matrix(A->rows, neigen);
    NSMatrix Q = matrixio_allocate_matrix(A->rows, neigen);
    NSMatrix R = matrixio_allocate_matrix(neigen, neigen);
    NSMatrix LAMBDA = R;
    NSMatrix QtA = matrixio_allocate_matrix(neigen, A->rows);

    matrix_randomnize_v(P.items[0], A->rows * neigen);

    for (int iter = 0; iter < NS_EIGEN_V_SUBSPACE_ITERATION_MAX_ITER; iter++) {
        // QR decomposition
        matrix_qr_decomposition(&P, &R);
        NS_SWAP(P.items, Q.items, double **);
        NS_SWAP(P.pointer_start, Q.pointer_start, double *);
        // LAMBDA = Q*AQ
        multiply_qta(Q.items, A->items, QtA.items, Q.rows, Q.cols);
        matrix_multiply_mmd(QtA.items, Q.items, LAMBDA.items, QtA.rows, QtA.cols, Q.cols);
        // P = AQ
        matrix_multiply_mmd(A->items, Q.items, P.items, A->rows, A->cols, Q.cols);
        // When there is only one eigen value to compute
        // the matrix LAMBDA is always diagonal
        // With NS_EIGEN_V_SUBSPACE_ITERATION_MIN_ITER we make sure that
        // it converges to the eigen value
        if (matrix_verify_diagonal(LAMBDA) == NS__MATRIX_ERR_NONE__ && iter >= NS_EIGEN_V_SUBSPACE_ITERATION_MIN_ITER) break;
    }
    // P contains the eigen vector without normalization
    normalize_p(P.items, P.rows, P.cols);

    matrixio_free_matrix(A);
    matrixio_free_matrix(&Q);
    matrixio_free_matrix(&QtA);

    *A = LAMBDA;

    return P;
}
