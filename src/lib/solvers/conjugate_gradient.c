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
    double rr = 0, pw = 0;

    // for (int i = 0; i < size; i++, p++, r++, w++) {
    //     pr += (*p) * (*r);
    //     pw += (*p) * (*w);
    // }

    #pragma omp parallel for reduction(+:rr) reduction(+:pw)
    for (int i = 0; i < size; i++) {
        rr += r[i] * r[i];
        pw += p[i] * w[i];
    }

    return rr/pw;
}

// static double get_beta(double *p, double * r, int size) {
//     double pr = 0, pp = 0;

//     // for (int i = 0; i < size; i++, p++, r++) {
//     //     pr += (*p) * (*r);
//     //     pp += (*p) * (*p);
//     // }

//     #pragma omp parallel for reduction(+:pr) reduction(+:pp)
//     for (int i = 0; i < size; i++) {
//         pr += p[i] * r[i];
//         pp += p[i] * p[i];
//     }

//     return pr/pp;
// }

static void make_xnext(double * x, double * p, double alpha, int size) {
    // for (int i = 0; i < size; i++, x++, p++) {
    //     *x = (*x) + alpha * (*p);
    // }

    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        x[i] = x[i] + alpha * p[i];
    }
}

static double make_rnext(double * r, double * w, double alpha, int size, double * betha) {
    // double norm = 0;

    // for (int i = 0; i < size; i++, r++, w++) {
    //     *r = (*r) - alpha * (*w);
    //     norm += (*r) * (*r);
    // }

    double rr_old = 0.0;
    double rr_new = 0.0;


    #pragma omp parallel for reduction(+:rr_old) reduction(+:rr_new)
    for (int i = 0; i < size; i++) {
        rr_old += r[i] * r[i];
        r[i] = r[i] + alpha * w[i];
        rr_new += r[i] * r[i];
    }

    *betha = rr_new / rr_old;

    return sqrt(rr_new);
}

static void make_pnext(double * p, double * r, double beta, int size) {
    // for (int i = 0; i < size; i++, p++, r++) {
    //     *p = (*r) + beta * (*p);
    // }

    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        p[i] = -r[i] + beta * p[i];
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
    double alpha, beta, error = 1.0;

    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        r[i] = -r[i];
        p[i] = -r[i];
    }


    int iter = 0;
    for (iter = 0; iter < CONJ_GRADIENT_MAX_ITER; iter++) {
        if (NS_IS_ZERO(error)) break;
        matrix_multiply_mvd(a, p, w, size, size);
        alpha = get_alpha(p, r, w, size);
        make_xnext(x, p, alpha, size);

        error = make_rnext(r, w, alpha, size, &beta);
        make_pnext(p, r, beta, size);
    }

    free(p);
    free(w);
}
