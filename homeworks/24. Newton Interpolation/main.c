/**
    ANSI C standard: c11
    main.c
    Purpose: Newton Interpolation example

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#include <stdlib.h>
#include <numsys/matrix/matrix.h>
#include "numsys/interpolation/newton.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        perror("main():: 2 Args missing");
        exit(EXIT_FAILURE);
    }

    NSVector x = matrixio_fread_vector(argv[1]);
    NSVector y = matrixio_fread_vector(argv[2]);

    double * coefs = interpolation_newton(x.items, y.items, x.size);

    for (int i = 0; i < x.size; i++) {
        printf("a_%d = %.10lf\n", i, coefs[i]);
    }

    double value = 2006.0;
    printf("\nf(%lf) = %lf\n", value, interpolation_newton_evaluate(x.items, coefs, x.size, value));

    FILE * fsamples = fopen("./samples", "w");
    double delta = 0.1;

    double from = 0, to = 100;
    for (double i = from; i <= to; i+= delta) {
        fprintf(fsamples, "%lf\n", interpolation_newton_evaluate(x.items, coefs, x.size, i));
    }

    matrixio_free_vector(&x);
    matrixio_free_vector(&y);
    fclose(fsamples);

    return 0;
}
