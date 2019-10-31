/**
    ANSI C standard: c11
    Purpose: Problema 1 del examen

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#include <stdlib.h>
#include "numsys/matrix/matrix.h"
#include "numsys/matrix_op/matrix_inverse.h"


int main(int argc, char *argv[]) {
    if (argc < 3) {
        perror("main():: 2 Args missing");
        exit(EXIT_FAILURE);
    }

    NSMatrixSystem msystem = matrixio_fread_matrix_system(argv[1], argv[2]);

    NSMatrix matrix_copy = matrixio_copy_matrix(msystem.a);
    NSMatrix inverse = matrix_inverse_get(&matrix_copy);
    matrixio_save_matrix(inverse, "INV_1000.mtx");


    NSVector x = matrix_multiply_mv(inverse, msystem.b);

    matrixio_save_vector(x, "X_1000.vec");


    matrixio_free_matrix_system(&msystem);
    matrixio_free_matrix(&matrix_copy);
    matrixio_free_matrix(&inverse);

    return 0;
}
