/**
    ANSI C standard: c11
    {file}.c
    Purpose: Jacobi iterative method

   @author Esaú Peralta
   @email esau.opr@gmail.com
*/

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "numsys/matrix/matrix.h"

#define CONJ_GRADIENT_IMPORT
#include "numsys/solvers/conjugate_gradient.h"

#define CONJ_GRADIENT_MAX_ITER 1000000

static double get_alpha(double *p, double * r, double* w, int size) {
    double pr = 0, pw = 0;

    for (int i = 0; i < size; i++, p++, r++, w++) {
        pr += (*p) * (*r);
        pw += (*p) * (*w);
    }

    return pr/pw;
}

static double get_beta(double *p, double * r, int size) {
    double pr = 0, pp = 0;

    for (int i = 0; i < size; i++, p++, r++) {
        pr += (*p) * (*r);
        pp += (*p) * (*p);
    }

    return pr/pp;
}

static void make_xnext(double * x, double * p, double alpha, int size) {
    for (int i = 0; i < size; i++, x++, p++) {
        *x = (*x) + alpha * (*p);
    }
}

static double make_rnext(double * r, double * w, double alpha, int size) {
    double norm = 0;

    for (int i = 0; i < size; i++, r++, w++) {
        *r = (*r) - alpha * (*w);
        norm += (*r) * (*r);
    }

    return sqrt(norm);
}

static void make_pnext(double * p, double * r, double beta, int size) {
    for (int i = 0; i < size; i++, p++, r++) {
        *p = (*r) + beta * (*p);
    }
}

/* Solve a square symmetric matrix by Conjugate Gradient Method */
void conjugate_gradient_solver(NSMatrixSystem * msystem) {
    int size = msystem->a.rows;
    double ** a = msystem->a.items;
    double * r = msystem->b.items;
    double * p = matrixio_allocate_array_double(size);
    double * x = msystem->x.items;
    double * w = matrixio_allocate_array_double(size);
    double alpha, beta, error;

    memcpy(p, r, size * sizeof(double));

    for (int iter = 0; iter < CONJ_GRADIENT_MAX_ITER; iter++) {
        matrix_multiply_mvd(a, p, w, size, size);
        alpha = get_alpha(p, r, w, size);
        make_xnext(x, p, alpha, size);
        error = make_rnext(r, w, alpha, size);
        printf("error: %le\n", error);
        if (NS_IS_ZERO(error)) break;
        beta = get_beta(p, r, size);
        make_pnext(p, r, beta, size);
    }

    free(p);
    free(w);
}
