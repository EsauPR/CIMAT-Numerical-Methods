/**
    ANSI C standard: c11
    matrix_ejen_v.c
    Purpose: Module to get eigen vetors and eigen values

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "numsys/matrix/matrixio.h"
#include "numsys/matrix/matrix.h"
#include "numsys/matrix_op/matrix_lu.h"
#include "numsys/solvers/doolittle.h"

#define MATRIX_EIGEN_V_IMPORT
#include "numsys/matrix_op/matrix_eigen_v.h"

#define MATRIX_EIGEN_MAX_ITER 100
#define MATRIX_EIGEN_MIN_ITER 50


static const struct matrix_eigen_scalar_products {
    double yy;
    double zy;
} NS_MESPDefault = {0.0, 0.0};
typedef struct matrix_eigen_scalar_products NS_MESP;


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
static NS_MESP matrix_eigen_v_multiply(double ** a, double * z, double * y, int size) {
    NS_MESP mesp = NS_MESPDefault;
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

/* Return the scalar product from z and y: y.y, z.z and z.y */
static NS_MESP matrix_eigen_compute_scalar_product(double * y, double * z, int size) {
    NS_MESP mesp = NS_MESPDefault;
    for (int i = 0; i < size; i++, y++, z++) {
        mesp.yy += (*y) * (*y);
        mesp.zy += (*z) * (*y);
    }
    return mesp;
}


/* Free Matrix_Eigen_V struct */
void matrix_eigen_free(Matrix_Eigen_V * eigen_v) {
    if (eigen_v->eigen_vector) {
        free(eigen_v->eigen_vector);
        eigen_v->eigen_vector = NULL;
    }
}

/* Make the deflation process over the vector */
static void matrix_eigen_deflation(Matrix_Eigen_V * eigenvs, int neigen, double * vector, int vsize) {
    double mag;
    for (int k = 0; k < neigen; k++) {
        mag = 0.0;
        for (int i = 0; i < vsize; i++) {
            mag += vector[i] * eigenvs[k].eigen_vector[i];
        }

        for (int i = 0; i < vsize; i++) {
            vector[i] -= mag * eigenvs[k].eigen_vector[i];
        }
    }
}

/* Compute the max eigen value and their eigen vector */
Matrix_Eigen_V matrix_eigen_pow_method(NSMatrix * matrix) {
    Matrix_Eigen_V * eigenvs = matrix_eigen_pow_method_dfl(matrix, 1);
    Matrix_Eigen_V eigen_v = eigenvs[0];
    free(eigenvs);
    return eigen_v;
}

/* Compute the min eigen value and their eigen vector */
Matrix_Eigen_V matrix_eigen_pow_method_inv(NSMatrix * matrix) {
    Matrix_Eigen_V * eigenvs = matrix_eigen_pow_method_inv_dfl(matrix, 1);
    Matrix_Eigen_V eigen_v = eigenvs[0];
    free(eigenvs);
    return eigen_v;
}

/*
    Compute the n eigen values and their eigen vectors through
    deflation process with the pow method
*/
Matrix_Eigen_V * matrix_eigen_pow_method_dfl(NSMatrix * matrix, const int neigen) {
    int size = matrix->rows;
    NS_MESP mesp = NS_MESPDefault;

    // Array for eigen vectors and eigen values
    Matrix_Eigen_V * eigenvs = (Matrix_Eigen_V *) malloc(neigen * sizeof(Matrix_Eigen_V));
    if (eigenvs == NULL) {
        perror("matrix_eigen_pow_method_dfl()");
        return eigenvs;
    }

    double * y_vector = matrixio_allocate_array_double(size);

    for (int eiter = 0; eiter < neigen; eiter++) {
        // mesp = NS_MESPDefault;
        eigenvs[eiter] = Matrix_Eigen_V_Default;
        double lambda = 0.0, lambda_prev = 0.0;
        double * z_vector = matrixio_allocate_array_double(size);
        matrix_eigen_v_randomnize(z_vector, size);

        for (int iter = 0; iter < MATRIX_EIGEN_MAX_ITER; iter++) {
            matrix_eigen_deflation(eigenvs, eiter, z_vector, size);
            matrix_eigen_v_normalize(z_vector, size, 0.0);
            mesp = matrix_eigen_v_multiply(matrix->items, z_vector, y_vector, size);
            lambda = mesp.yy / mesp.zy;

            NS_SWAP(y_vector, z_vector, double *);
            if (NS_IS_ZERO(lambda - lambda_prev)) {
                break;
            }
            lambda_prev = lambda;
        }

        // Normalize and save eigen value/vector
        matrix_eigen_v_normalize(z_vector, size, sqrt(mesp.yy));;
        eigenvs[eiter].eigen_vector = z_vector;
        eigenvs[eiter].eigen_value = lambda;
    }

    free(y_vector);

    return eigenvs;
}


/*
    Compute the n eigen values and their eigen vectors through
    deflation process with the inverse pow method
*/
Matrix_Eigen_V * matrix_eigen_pow_method_inv_dfl(NSMatrix * matrix, const int neigen) {
    int size = matrix->rows;
    NS_MESP mesp = NS_MESPDefault;

    // Array for eigen vectors and eigen values
    Matrix_Eigen_V * eigenvs = (Matrix_Eigen_V *) malloc(neigen * sizeof(Matrix_Eigen_V));
    if (eigenvs == NULL) {
        perror("matrix_eigen_pow_method_dfl()");
        return NULL;
    }

    // System to solve with doolittle method
    NSMatrixSystem msystem = NSMatrixSystemDefault;
    msystem.a = *matrix;
    msystem.x = matrixio_allocate_vector(size);
    msystem.b = matrixio_allocate_vector(size);

    double * y_vector = matrixio_allocate_array_double(size);

    // LU decomposition
    int * row_maping = matrix_lu_decomposition(matrix);
    free(row_maping);
    if (matrix->err) {
        matrixio_free_vector(&(msystem.b));
        matrixio_free_vector(&(msystem.x));
        nsperror("matrix_lu_decomposition():", matrix->err);
        return NULL;
    }

    for (int eiter = 0; eiter < neigen; eiter++) {
        eigenvs[eiter] = Matrix_Eigen_V_Default;
        mesp = NS_MESPDefault;
        double lambda = 0.0, lambda_prev = 0.0;
        double * z_vector = matrixio_allocate_array_double(size);
        matrix_eigen_v_randomnize(z_vector, size);

        for (int iter = 0; iter < MATRIX_EIGEN_MAX_ITER; iter++) {
            matrix_eigen_deflation(eigenvs, eiter, z_vector, size);
            matrix_eigen_v_normalize(z_vector, size, sqrt(mesp.yy));
            // Solve Ay=z
            memcpy(msystem.b.items, z_vector, size * sizeof(double));
            solver_doolittle_method_lu(&msystem);
            if (msystem.err) {
                nsperror("solver_doolittle_method_lu():", msystem.err);
                free(y_vector);
                free(z_vector);
                matrixio_free_vector(&(msystem.b));
                matrixio_free_vector(&(msystem.x));
                return eigenvs;
            }
            // Move solution to y_vector
            NS_SWAP(y_vector, msystem.x.items, double *);

            mesp = matrix_eigen_compute_scalar_product(y_vector, z_vector, size);
            lambda = mesp.zy / mesp.yy;
            // printf("%d) lambda: %.20lf\n", iter, lambda);
            NS_SWAP(y_vector, z_vector, double *);

            if (NS_IS_ZERO(lambda - lambda_prev)) {
                break;
            }
            lambda_prev = lambda;
        }
        // Normalize and save eigen value/vector
        matrix_eigen_v_normalize(z_vector, size, sqrt(mesp.yy));;
        eigenvs[eiter].eigen_vector = z_vector;
        eigenvs[eiter].eigen_value = lambda;
    }

    free(y_vector);
    matrixio_free_vector(&(msystem.b));
    matrixio_free_vector(&(msystem.x));

    return eigenvs;
}
