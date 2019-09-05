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
#include "matrix_lu.h"
#include "../linear_equations_systems_solutions/doolittle.h"

#define MATRIX_EIGEN_V_IMPORT
#include "matrix_eigen_v.h"

#define MATRIX_EIGEN_MAX_ITER 1000
#define MATRIX_EIGEN_MIN_ITER 50


static const struct matrix_eigen_scalar_products {
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


/* Compute the min eigen value and their eigen vector */
Matrix_Eigen_V matrix_inverse_potence_method(Matrix matrix) {
    Matrix_Eigen_V eigen_v = Matrix_Eigen_V_Dafault;
    SystemSolution system_solution;
    int size = matrix.rows;
    double lambda = 0.0, lambda_prev = 1 << 31;

    double * z_vector = matrixio_allocate_double_array(size);
    double * y_vector = NULL;
    Mesp mesp = Mesp_Default;

    matrix_eigen_v_randomnize(z_vector, size);
    matrix_eigen_v_normalize(z_vector, size, 0.0);

    // LU decomposition
    system_solution = matrix_lu_decomposition(matrix.content, size);
    if (system_solution.err) {
        eigen_v.err |= system_solution.err;
        solution_free(system_solution);
        return eigen_v;
    }
    solution_free(system_solution);

    for (int iter = 0; iter < MATRIX_EIGEN_MAX_ITER; iter++) {
        for (int i = 0; i < size; i++) {
            matrix.content[i][size] = z_vector[i];
        }

        matrixio_show(matrix.content, matrix.rows, matrix.cols + matrix.cols_extra);
        system_solution = doolittle_method_solve_lu(matrix);
        solution_show(system_solution);

        y_vector = system_solution.solution;
        break;

        for (int i = 0; i < size; i++) {
            mesp.yy = y_vector[i] * y_vector[i];
            mesp.zy = z_vector[i] * y_vector[i];
        }

        lambda = mesp.zy / mesp.yy;

        printf("%4d) lambda: %lf\n", iter, lambda);

        matrix_eigen_v_normalize(y_vector, size, sqrt(mesp.yy));

        free(z_vector);
        z_vector = y_vector;

        if (IS_ZERO(lambda - lambda_prev)) {
            break;
        }

        lambda_prev = lambda;
    }

    eigen_v.eigen_value = lambda;
    eigen_v.eigen_vector = z_vector;

    return eigen_v;
}
