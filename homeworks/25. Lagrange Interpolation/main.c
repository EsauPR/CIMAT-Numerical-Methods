/**
    ANSI C standard: c11
    main.c
    Purpose: lagrange Interpolation example

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#include <stdlib.h>
#include <numsys/matrix/matrix.h>
#include "numsys/interpolation/lagrange.h"

int main(int argc, char *argv[]) {
    if (argc < 5) {
        perror("main():: 2 Args missing");
        exit(EXIT_FAILURE);
    }

    NSVector x = matrixio_fread_vector(argv[1]);
    NSVector y = matrixio_fread_vector(argv[2]);

    double value = 2006.0;
    printf("\nf(%lf) = %lf\n", value, interpolation_lagrange(x.items, y.items, x.size, value));

    FILE * fsamples = fopen("./samples.txt", "w");
    double delta = 0.1;
    double from = atof(argv[3]), to = atof(argv[4]);
    for (double i = from; i <= to; i+= delta) {
        fprintf(fsamples, "%f %lf\n", i, interpolation_lagrange(x.items, y.items, x.size, i));
    }

    matrixio_free_vector(&x);
    matrixio_free_vector(&y);

    fclose(fsamples);

    return 0;
}
