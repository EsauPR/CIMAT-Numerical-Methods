/**
    ANSI C standard: c11
    matrix_ejen_v.c
    Purpose: Module to get eigen vetors and eigen values

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "matrixio.h"

#define MATRIX_EIGEN_V_IMPORT
#include "matrix_eigen_v.h"

#define MATRIX_EIGEN_MAX_ITER 1000
#define MATRIX_EIGEN_MIN_ITER 50


static struct matrix_eigen_scalar_products{
    double yy;
    double zy;
} Mesp_Default = {0.0, 0.0};
typedef struct matrix_eigen_scalar_products Mesp;

/* Randomnize a vector */
static void matrix_eigen_v_randomnize(double * vector, int size) {
    srandom(time(NULL));

    for (int i = 0; i < size; i++) {
        vector[i] = (double) (random() % 100) + 1.0;
    }
}


/* Normalize a vector and returns the position the maximun element */
static void matrix_eigen_v_normalize(double * vector, int size, double norm) {
    if (norm == 0.0) {
        for (int i = 0; i < size; i++) {
            norm += vector[i] * vector[i];
        }
        norm = sqrt(norm);
    }

    for (int i = 0; i < size; i++) {
        vector[i] /= norm;
    }
}


/* Multiply y = a*z and return the norm of y */
static Mesp matrix_eigen_v_multiply(double ** a, double * z, double * y, int size) {
    Mesp mesp = Mesp_Default;
    double tmp;

    for (int i = 0; i < size; i++) {
        tmp = 0.0;
        for (int j = 0; j < size; j++) {
            tmp += a[i][j] * z[j];
        }
        y[i] = tmp;
        mesp.yy += tmp * tmp;
        mesp.zy += tmp * z[i];
    }

    return mesp;
}


/* Compute the max eigen value and their eigen vector */
Matrix_Eigen_V matrix_potence_method(Matrix matrix) {
    Matrix_Eigen_V eigen_v = Matrix_Eigen_V_Dafault;
    int size = matrix.rows;
    double lambda = 0.0, lambda_prev = 0.0;

    double * z_vector = matrixio_allocate_double_array(size);
    double * y_vector = matrixio_allocate_double_array(size);

    matrix_eigen_v_randomnize(z_vector, size);
    matrix_eigen_v_normalize(z_vector, size, 0.0);

    for (int iter = 0; iter < MATRIX_EIGEN_MAX_ITER; iter++) {
        Mesp mesp = matrix_eigen_v_multiply(matrix.content, z_vector, y_vector, size);
        lambda = mesp.yy / mesp.zy;

        printf("%4d) lambda: %lf\n", iter, lambda);

        matrix_eigen_v_normalize(y_vector, size, sqrt(mesp.yy));
        SWAP(y_vector, z_vector);

        if (IS_ZERO(lambda - lambda_prev)) {
            break;
        }

        lambda_prev = lambda;
    }

    eigen_v.eigen_value = lambda;
    eigen_v.eigen_vector = z_vector;

    free(y_vector);

    return eigen_v;
}
