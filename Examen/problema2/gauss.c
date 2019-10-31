/**
    ANSI C standard: c11
    Purpose: Solve a square matrix by Gaussian elimination

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdlib.h>
#include "numsys/matrix/matrix.h"
#include "numsys/solvers/gaussian_elimination.h"


int main(int argc, char *argv[]) {
    if (argc < 3) {
        perror("main():: 2 Args missing");
        exit(EXIT_FAILURE);
    }

    puts("Read a");
    NSMatrix A = matrixio_fread_matrix_sparse_as_normal(argv[1]);
    puts("Read b");
    NSVector b = matrixio_fread_vector(argv[2]);
    NSVector x;
    x.size = A.rows;
    x.items = matrixio_allocate_array_double(A.rows);

    NSMatrixSystem msystem = NSMatrixSystemDefault;
    msystem.a = A;
    msystem.b = b;
    msystem.x = x;

    printf("%d %d %d %d\n", A.rows, A.cols, b.size, x.size);

    matrixio_save_matrix(msystem.a, "a.mtx");

    solver_gaussian_elimination(&msystem);
    if (msystem.err) {
        nsperror("main():", msystem.err);
        matrixio_free_matrix_system(&msystem);
        exit(EXIT_FAILURE);
    }

    matrixio_save_vector(msystem.x, "x_gauss.vec");
    matrixio_free_matrix_system(&msystem);

    return 0;
}
