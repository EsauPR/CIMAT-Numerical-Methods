/**
    ANSI C standard: c11
    main.c
    Purpose: Linear Regresion

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include "numsys/matrix/matrixio.h"
#include "numsys/regresion/regresion.h"



int main(int argc, char * argv[]) {
    if (argc < 2) {
        puts("Missing args");
        return 0;
    }

    NSVector x = matrixio_fread_vector(argv[1]);
    NSVector y = matrixio_fread_vector(argv[2]);

    NSVector z = regresion_linear(x, y);

    printf("y(x) = %lfx + %lf\n", z.items[0], z.items[1]);

    matrixio_free_vector(&x);
    matrixio_free_vector(&y);
    matrixio_free_vector(&z);

    return 0;
}
