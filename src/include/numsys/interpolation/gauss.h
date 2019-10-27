/**
    ANSI C standard: c11
    newton.c
    Purpose: Prototype for module to compute Gauss interpolations

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#ifndef NS_GAUSS_INTERPOLATION_H
#define NS_GAUSS_INTERPOLATION_H

#include <stddef.h>

#ifdef NS_GAUSS_INTERPOLATION_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

/* Return the evaluation for several points using Gauss forward interpolation */
EXTERN double * gauss_fw_central_diff_evaluation(double * x, double * y, int size, double h, double * values, int nvalues);

/* Return the evaluation for several points using Gauss backward interpolation */
EXTERN double * gauss_bw_central_diff_evaluation(double * x, double * y, int size, double h, double * values, int nvalues);

#undef NS_GAUSS_INTERPOLATION_IMPORT
#undef EXTERN
#endif
