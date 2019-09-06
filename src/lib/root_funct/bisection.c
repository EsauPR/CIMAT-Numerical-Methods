/**
    ANSI C standard: c11
    bisection.c
    Purpose: Bisection module

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include "numsys/matrix/matrix_core.h"

#define BISECTION_IMPORT
#include "numsys/root_funct/bisection.h"

/* Returns the a value sign */
static int bisection_get_sign(double value) {
    return (value < 0)? 0 : 1;
}

/* Bisection method to find a funtion root */
double bisection_find_root(double (*function)(double), double x_min, double x_max) {
    double x_middle = 0.0;
    int iter = 1;

    if (x_min >= x_max) {
        puts("Error:: Invalid range");
        return x_middle;
    }

    if (bisection_get_sign(function(x_min)) == bisection_get_sign(function(x_max))) {
        puts("Error:: Range values with same sign");
        return x_middle;
    }

    while(1) {
        x_middle = (x_min + x_max) / 2.0;

        if (IS_ZERO(function(x_middle)) || IS_ZERO(x_min - x_max)) {
            return x_middle;
        }

        if (bisection_get_sign(function(x_middle)) == bisection_get_sign(function(x_min))) {
            x_min = x_middle;
        }

        if (bisection_get_sign(function(x_middle)) == bisection_get_sign(function(x_max))) {
            x_max = x_middle;
        }

        iter++;
    }

    return x_middle;
}
