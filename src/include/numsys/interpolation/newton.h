/**
    ANSI C standard: c11
    newton.c
    Purpose: Prototype for module to make a interpolation proccess by Newton interpolation polinomial

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#ifndef NS_INTERPOLATION_NEWTON_H
#define NS_INTERPOLATION_NEWTON_H

#include <stddef.h>

#ifdef NS_INTERPOLATION_NEWTON_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

/*
    Newton interpolation with Divided Diferences
    Returns an array with the Divided Diferences values
*/
double * interpolation_newton(double * x, double * y, int size);

/* Evaluate a point using the Divided Diferences values */
double interpolation_newton_evaluate(double * x, double * coefs, int size, double value);

#undef NS_INTERPOLATION_NEWTON_IMPORT
#undef EXTERN
#endif
