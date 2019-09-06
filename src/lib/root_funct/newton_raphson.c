/**
    ANSI C standard: c11
    newton_raphson.c
    Purpose: Bisection module

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <math.h>
#include "numsys/matrix/matrix_core.h"

#define NEWTON_RAPHSON_IMPORT
#include "numsys/root_funct/newton_raphson.h"

#define N_R_DELTHA_X 0.0001
#define N_R_MAX_ITER 1000


/* Return the line slope by derivate definition */
static double newton_raphson_get_slope(double (*f)(double), int x) {
    return (f(x + N_R_DELTHA_X) - f(x)) / N_R_DELTHA_X;
}

/* Newton Raphson method to find a funtion root */
double newton_raphson_solver(double (*f)(double), double x_start) {
    double x = x_start, x_next;
    for (int i = 0; i < N_R_MAX_ITER; i++) {
        x_next = x - f(x) / newton_raphson_get_slope(f, x);
        if (isnan(x_next)) {
            puts("Warn:: Nan obtained");
            return x;
        }

        if (IS_ZERO(x - x_next)) {
            return x_next;
        }

        if (i + 1 == N_R_MAX_ITER) {
            puts("Warn:: Limit of iterations reached");
        }

        x = x_next;
    }

    return x_next;
}
