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
#include "numsys/matrix/matrixio.h"
#include "numsys/matrix_op/matrix_lu.h"
#include "numsys/solvers/doolittle.h"

#define MATRIX_EIGEN_V_IMPORT
#include "numsys/matrix_op/matrix_eigen_v.h"

#define MATRIX_EIGEN_MAX_ITER 100
#define MATRIX_EIGEN_MIN_ITER 50


static const struct matrix_eigen_scalar_products {
    double yy;
    double zy;
} MESPDefault = {0.0, 0.0};
typedef struct matrix_eigen_scalar_products Mesp;


/* Randomnize a vector */
static void matrix_eigen_v_randomnize(double * vector, int size) {
    srandom(time(NULL));

    for (int i = 0; i < size; i++, vector++) {
        *vector = (double) (random() % 100) + 1.0;
    }
}


/* Normalize a vector and returns the position the maximun element */
static void matrix_eigen_v_normalize(double * vector, int size, double norm) {
    if (norm == 0.0) {
        double * vec_pos = vector;
        for (int i = 0; i < size; i++, vec_pos++) {
            norm += (*vec_pos) * (*vec_pos);
        }
        norm = sqrt(norm);
    }

    double * vec_pos = vector;
    for (int i = 0; i < size; i++, vec_pos++) {
        *vec_pos /= norm;
    }
}


/* Multiply y = a*z and return the scalars products of yy and zy */
static Mesp matrix_eigen_v_multiply(double ** a, double * z, double * y, int size) {
    Mesp mesp = MESPDefault;
    double ** a_i = a;
    double * z_i = z;
    double * y_i = y;

    for (int i = 0; i < size; i++, a_i++, z_i++, y_i++) {
        double tmp = 0.0;
        double * z_j = z;
        double * a_ij = *a_i;

        for (int j = 0; j < size; j++, z_j++, a_ij++) {
            tmp += (*a_ij) * (*z_j);
        }

        *y_i = tmp;

        mesp.yy += (*y_i) * (*y_i);
        mesp.zy += (*z_i) * (*y_i);
    }

    return mesp;
}


/* Compute the max eigen value and their eigen vector */
Matrix_Eigen_V matrix_eigen_potence_method(NSMatrix * matrix) {
    Matrix_Eigen_V eigen_v = Matrix_Eigen_V_Default;
    int size = matrix->rows;
    double lambda = 0.0, lambda_prev = 0.0;

    double * z_vector = matrixio_allocate_array_double(size);
    double * y_vector = matrixio_allocate_array_double(size);

    matrix_eigen_v_randomnize(z_vector, size);
    matrix_eigen_v_normalize(z_vector, size, 0.0);

    for (int iter = 0; iter < MATRIX_EIGEN_MAX_ITER; iter++) {
        Mesp mesp = matrix_eigen_v_multiply(matrix->items, z_vector, y_vector, size);
        lambda = mesp.yy / mesp.zy;

        // printf("%4d) lambda: %lf\n", iter, lambda);

        matrix_eigen_v_normalize(y_vector, size, sqrt(mesp.yy));
        NS_SWAP(y_vector, z_vector, double *);

        if (NS_IS_ZERO(lambda - lambda_prev)) {
            break;
        }

        lambda_prev = lambda;
    }

    eigen_v.eigen_value = lambda;
    eigen_v.eigen_vector = z_vector;

    free(y_vector);

    return eigen_v;
}


/* Compute the min eigen value and their eigen vector */
Matrix_Eigen_V matrix_eigen_potence_method_inverse(NSMatrix * matrix) {
    Matrix_Eigen_V eigen_v = Matrix_Eigen_V_Default;
    int size = matrix->rows;
    double lambda = 0.0, lambda_prev = 1 << 31;

    // System to solve with doolittle method
    NSMatrixSystem msystem = NSMatrixSystemDefault;
    msystem.a = *matrix;
    msystem.x = matrixio_allocate_vector(size);
    msystem.b = matrixio_allocate_vector(size);

    // Initial vectors
    double * x_vector = msystem.x.items;
    double * b_vector = msystem.b.items;
    matrix_eigen_v_randomnize(b_vector, size);
    matrix_eigen_v_normalize(b_vector, size, 0.0);

    // LU decomposition
    matrix_lu_decomposition(matrix);
    if (matrix->err) {
        matrixio_free_vector(&(msystem.b));
        matrixio_free_vector(&(msystem.x));
        eigen_v.err |= matrix->err;
        return eigen_v;
    }

    for (int iter = 0; iter < MATRIX_EIGEN_MAX_ITER; iter++) {
        solver_doolittle_method_lu(&msystem);
        if (msystem.err) {
            eigen_v.err |= msystem.err;
            matrixio_free_vector(&(msystem.b));
            matrixio_free_vector(&(msystem.x));
            eigen_v.eigen_vector = NULL;
            return eigen_v;
        }

        Mesp mesp = MESPDefault;
        double * x_i = x_vector;
        double * b_i = b_vector;
        for (int i = 0; i < size; i++, x_i++, b_i++) {
            mesp.yy = (*x_i) * (*x_i);
            mesp.zy = (*b_i) * (*x_i);
        }

        lambda = mesp.zy / mesp.yy;

        printf("%d) lambda: %.20lf\n", iter, lambda);

        matrix_eigen_v_normalize(x_vector, size, sqrt(mesp.yy));
        NS_SWAP(x_vector, b_vector, double *);

        if (NS_IS_ZERO(lambda - lambda_prev)) {
            break;
        }

        lambda_prev = lambda;
    }

    eigen_v.eigen_value = lambda;
    eigen_v.eigen_vector = b_vector;

    return eigen_v;
}


/* Free Matrix_Eigen_V struct */
void matrix_eigen_free(Matrix_Eigen_V * eigen_v) {
    if (eigen_v->eigen_vector) {
        free(eigen_v->eigen_vector);
        eigen_v->eigen_vector = NULL;
    }
}
