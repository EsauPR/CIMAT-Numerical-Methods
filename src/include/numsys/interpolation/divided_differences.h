/**
    ANSI C standard: c11
    newton.c
    Purpose: Prototype for module to compute the divided diferences

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#ifndef NS_DIVIDED_DIFFERENCES_H
#define NS_DIVIDED_DIFFERENCES_H

#include <stddef.h>

#ifdef NS_DIVIDED_DIFFERENCES_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

/* Return the coefficients of Newton divided Differences to make interpolations */
EXTERN double * get_newton_devided_differences(double * x, double *  y, int n);

/* Return the coefficients of Forward Differences to make interpolations */
EXTERN double * get_forward_differences(double * y, int n);

/* Return the coefficients of Backward Differences to make interpolations */
EXTERN double * get_backward_differences(double * y, int n);

/* Return the coefficients of Forward Central Differences to make interpolations */
EXTERN double * get_forward_central_differences(double * y, int n);

/* Return the coefficients of Backward Central Differences to make interpolations */
EXTERN double * get_backward_central_differences(double * y, int n);


#undef NS_DIVIDED_DIFFERENCES_IMPORT
#undef EXTERN
#endif
