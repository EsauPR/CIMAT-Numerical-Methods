
/**
    ANSI C standard: c11
    lagrange.c
    Purpose: Prototype for module to make a interpolation proccess by Lagrange interpolation polinomial

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#ifndef NS_INTERPOLATION_LAGRANGE_H
#define NS_INTERPOLATION_LAGRANGE_H

#include <stddef.h>

#ifdef NS_INTERPOLATION_LAGRANGE_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

/* Compute the lagrange interpolation and return the evaluation of the 'value' */
EXTERN double interpolation_lagrange(double * x, double * y, int size, double value);

/* Compute the l_i term of lagrange polinomail for any 'value' */
EXTERN double interpolation_lagrange_li(int i, double * x, int size, double value);

/* Compute the derivate of the l_i term of lagrange polinomail for any 'value' */
EXTERN double interpolation_lagrange_dlj(int j, double * x, int size, double value);

#undef NS_INTERPOLATION_LAGRANGE_IMPORT
#undef EXTERN
#endif
