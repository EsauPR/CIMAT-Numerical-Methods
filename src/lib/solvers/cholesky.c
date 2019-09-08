/**
    ANSI C standard: c11
    {file}.c
    Purpose: {Description}

   @author Esaú Peralta
   @email esau.opr@gmail.com
*/

#include <stdlib.h>
#include "numsys/matrix_op/matrix_ldlt.h"
#include "numsys/solvers/bwfw_substitution.h"

#define CHOLESKY_IMPORT
#include "numsys/solvers/cholesky.h"


void solver_cholesky_method(NSMatrixSystem * msystem) {
    int size = msystem->a.rows;
    double **matrix = msystem->a.items;

    matrix_ldlt_decomposition(&(msystem->a));
    if (msystem->a.err) {
        msystem->err |= msystem->a.err | NS__MATRIX_ERR_NO_SOLUTION__;
        return;
    }
    // Backup the determinant
    double determinat = msystem->a.determinant;

    // Multiply L x D in the same matrix, this LD is matriz is a lower traingular matrix
    for (int i = 1; i < size; i++) {
        for (int j = 0; j < i; j++){
            matrix[i][j] *= matrix[j][j];
        }
    }
    // Solve Ly = b where L has a diagonal with ones
    solver_forward_substitution(msystem, NS__MATRIX_OPS_NONE_);
    // Solve Ux = y
    NS_SWAP(msystem->x.items, msystem->b.items, double *);
    solver_backward_substitution(msystem, NS__MATRIX_OPS_DIAG_HAS_ONES__);

    msystem->a.determinant = determinat;
}
