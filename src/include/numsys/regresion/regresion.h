#ifndef REGRESION_H
#include <numsys/matrix/matrix_core.h>
#ifdef REGRESION_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

/* Linear regresion */
NSVector regresion_linear(NSVector x, NSVector y);
/* Cuadratic regresion */
NSVector regresion_cuadratic(NSVector x, NSVector y);

#undef REGRESION_IMPORT
#undef EXTERN
#endif
