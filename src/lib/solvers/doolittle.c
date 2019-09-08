/**
    ANSI C standard: c11
    {file}.c
    Purpose: {Description}

   @author Esaú Peralta
   @email esau.opr@gmail.com
*/

#include <stdlib.h>
#include "numsys/matrix_op/matrix_lu.h"
#include "numsys/solvers/bwfw_substitution.h"

#define DOOLITTLE_IMPORT
#include "numsys/solvers/doolittle.h"


/* Solve a LUx=B, the matrix must be a LU matrix */
void solver_doolittle_method_lu(NSMatrixSystem * msystem) {
    int size = msystem->a.rows;
    // Solve Ly = b where L has a diagonal with ones
    solver_forward_substitution(msystem, NS__MATRIX_OPS_DIAG_HAS_ONES__);
    if (msystem->err) {
        return;
    }
    // Solve Ux = y
    NS_SWAP(msystem->x.items, msystem->b.items, double *)
    solver_backward_substitution(msystem, NS__MATRIX_OPS_NONE_);
}


/* Solve a square matrix by Doolittle method */
void solver_doolittle_method(NSMatrixSystem * msystem) {
    int size = msystem->a.rows;

    int * row_perm_map = matrix_lu_decomposition(&(msystem->a));
    free(row_perm_map); // Unnecessary perm map

    if (msystem->a.err) {
        msystem->err |= msystem->a.err | NS__MATRIX_ERR_NO_SOLUTION__;
        return;
    }

    // Backup the determinant this is modified by other solvers
    double determinant = msystem->a.determinant;

    solver_doolittle_method_lu(msystem);
    if (msystem->err) {
        msystem->err |= NS__MATRIX_ERR_NO_SOLUTION__;
        return;
    }

    msystem->a.determinant = determinant;
}
