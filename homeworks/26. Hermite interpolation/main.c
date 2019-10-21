/**
    ANSI C standard: c11
    main.c
    Purpose: Hermite Interpolation example

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#include <stdlib.h>
#include <numsys/matrix/matrix.h>
#include "numsys/interpolation/hermite.h"

int main(int argc, char *argv[]) {
    if (argc < 6) {
        perror("main():: 4 Args missing");
        exit(EXIT_FAILURE);
    }

    NSVector x = matrixio_fread_vector(argv[1]);
    NSVector y = matrixio_fread_vector(argv[2]);
    NSVector dy = matrixio_fread_vector(argv[3]);

    double value = 0.5;
    printf("\nf(%lf) = %lf\n", value, interpolation_hermite(x.items, y.items, dy.items, x.size, value));

    FILE * fsamples = fopen("./samples.txt", "w");
    double delta = 0.1;
    double from = atof(argv[4]), to = atof(argv[5]);
    for (double i = from; i <= to; i+= delta) {
        fprintf(fsamples, "%f %lf\n", i, interpolation_hermite(x.items, y.items, dy.items, x.size, i));
    }

    matrixio_free_vector(&x);
    matrixio_free_vector(&y);
    matrixio_free_vector(&dy);

    fclose(fsamples);

    return 0;
}
