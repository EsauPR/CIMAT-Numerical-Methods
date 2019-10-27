/**
    ANSI C standard: c11
    newton.c
    Purpose: Prototype for module to compute Gregory-Newton interpolations

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#ifndef NS_GREGORY_NEWTON_H
#define NS_GREGORY_NEWTON_H

#include <stddef.h>

#ifdef NS_GREGORY_NEWTON_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

/* Return the evaluation for several points using Gregory-Newton forward interpolation */
EXTERN double * gregory_newton_fw_evaluation(double * x, double * y, int size, double h, double * values, int nvalues);

/* Return the evaluation for several points using Gregory-Newton backward interpolation */
EXTERN double * gregory_newton_bw_evaluation(double * x, double * y, int size, double h, double * values, int nvalues);

#undef NS_GREGORY_NEWTON_IMPORT
#undef EXTERN
#endif
