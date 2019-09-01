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


/* Randomnize a vector */
static void matrix_eigen_v_randomnize(double * vector, int size) {
    srandom(time(NULL));

    for (int i = 0; i < size; i++) {
        vector[i] = (double) (random() % 100);
    }
}


/* Normalize a vector and returns the position the maximun element */
static int matrix_eigen_v_normalize(double * vector, int size, double norm) {
    double max = 0.0;
    int pos_max = 0;

    if (norm == 0.0) {
        for (int i = 0; i < size; i++) {
            norm += vector[i] * vector[i];
        }

        norm = sqrt(norm);
    }

    for (int i = 0; i < size; i++) {
        vector[i] /= norm;
        if (ABS(max) < ABS(vector[i])) {
            max = vector[i];
            pos_max = i;
        }
    }

    return pos_max;
}


/* Multiply y = a*z and return the norm of y */
static double matrix_eigen_v_multiply(double ** a, double * z, double * y, int size) {
    double norm = 0.0;

    for (int i = 0; i < size; i++) {
        y[i] = 0.0;
        for (int j = 0; j < size; j++) {
            y[i] += a[i][j] * z[j];
            norm += y[i] * y[i];
        }
    }

    return sqrt(norm);
}


/* Compute the max eigen value and their eigen vector */
Matrix_Eigen_V matrix_potence_method(Matrix matrix) {
    Matrix_Eigen_V eigen_v = Matrix_Eigen_V_Dafault;
    int size = matrix.rows;
    double * z_vector = matrixio_allocate_double_array(size);
    double * y_vector = matrixio_allocate_double_array(size);

    double lambda, norm = 0.0;
    double lambda_prev = 0.0;

    matrix_eigen_v_randomnize(z_vector, size);
    int max_pos = matrix_eigen_v_normalize(z_vector, size, norm);

    for (int iter = 0; iter < MATRIX_EIGEN_MAX_ITER; iter++) {
        norm = matrix_eigen_v_multiply(matrix.content, z_vector, y_vector, size);
        lambda = y_vector[max_pos] / z_vector[max_pos];
        printf("lambda: %lf\n", lambda);
        max_pos = matrix_eigen_v_normalize(y_vector, size, norm);
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
