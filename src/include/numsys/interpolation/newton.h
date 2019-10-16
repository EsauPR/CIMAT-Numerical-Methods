
#ifndef NS_INTERPOLATION_NEWTON_H
#define NS_INTERPOLATION_NEWTON_H

#include <stddef.h>

#ifdef NS_INTERPOLATION_NEWTON_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

double * interpolation_newton(double * x, double * y, int size);

double interpolation_newton_evaluate(double * x, double * coefs, int size, double value);

#undef NS_INTERPOLATION_NEWTON_IMPORT
#undef EXTERN
#endif
