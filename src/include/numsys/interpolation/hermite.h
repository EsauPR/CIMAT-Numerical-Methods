/**
    ANSI C standard: c11
    hermite.c
    Purpose: Prototype for module to make a interpolation proccess by Hermite interpolation polinomial

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#ifndef NS_INTERPOLATION_HERMITE_H
#define NS_INTERPOLATION_HERMITE_H

#include <stddef.h>

#ifdef NS_INTERPOLATION_HERMITE_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

/* Compute the the Hermite polinomial and returns the evaluation for any 'value' */
EXTERN double interpolation_hermite(double * x, double * y, double * dy, double size, double value);

#undef NS_INTERPOLATION_HERMITE_IMPORT
#undef EXTERN
#endif
