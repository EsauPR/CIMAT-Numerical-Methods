/**
    ANSI C standard: c11
    Purpose: Solver for a matrix system Ax=b by Conjugate Gradient Method
    A must be symmetric

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#include <stdlib.h>
#include <numsys/matrix/matrix.h>
#include "numsys/solvers/conjugate_gradient.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        perror("main():: 2 Args missing");
        exit(EXIT_FAILURE);
    }

    NSMatrix A = matrixio_fread_matrix_sparse_as_normal(argv[1]);
    NSVector b = matrixio_fread_vector(argv[2]);
    NSVector x;
    x.size = A.rows;
    x.items = matrixio_allocate_array_double(A.rows);

    NSMatrixSystem msystem = NSMatrixSystemDefault;
    msystem.a = A;
    msystem.b = b;
    msystem.x = x;

    conjugate_gradient_solver(&msystem);

    if (msystem.err) {
        nsperror("main():", msystem.err);
        matrixio_free_matrix_system(&msystem);
        exit(EXIT_FAILURE);
    }

    matrixio_save_vector(msystem.x, "x_gradient.vec");
    matrixio_free_matrix_system(&msystem);

    return 0;
}
