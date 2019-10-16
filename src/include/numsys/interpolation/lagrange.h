
#ifndef NS_INTERPOLATION_LAGRANGE_H
#define NS_INTERPOLATION_LAGRANGE_H

#include <stddef.h>

#ifdef NS_INTERPOLATION_LAGRANGE_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

double interpolation_lagrange(double * x, double * y, int size, double value);

#undef NS_INTERPOLATION_LAGRANGE_IMPORT
#undef EXTERN
#endif
