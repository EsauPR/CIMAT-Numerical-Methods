#ifndef _FINITE_ELEMENT_H

#include "numsys/matrix/matrixio.h"

#ifdef _FINITE_ELEMENT_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif


void interpolation_finite_elements(NSVector x, NSVector y, NSVector * z, NSVector * phi, int partition_size, double lambda);

#undef _FINITE_ELEMENT_IMPORT
#undef EXTERN
#endif
