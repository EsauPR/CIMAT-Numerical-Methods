/**
    ANSI C standard: c11
    {file}.c
    Purpose: Jacobi iterative method

   @author Esaú Peralta
   @email esau.opr@gmail.com
*/

#include <stdlib.h>
#include <string.h>
#include <math.h>

#define CONJ_GRADIENT_IMPORT
#include "numsys/solvers/conjugate_gradient.h"

#define CONJ_GRADIENT_MAX_ITER 1000

/* Solve a square symmetric matrix by Conjugate Gradient Method */
void conjugate_gradient_solver(NSMatrixSystem * msystem) {

}
