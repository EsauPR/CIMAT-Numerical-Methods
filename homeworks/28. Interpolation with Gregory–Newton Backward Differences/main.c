/**
    ANSI C standard: c11
    main.c
    Purpose: Gauss interpolation with central forward differences

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#include <stdlib.h>
#include <numsys/matrix/matrix.h>
#include "numsys/interpolation/gregory_newton.h"

int main(int argc, char *argv[]) {
    if (argc < 5) {
        perror("main():: 4 Args missing");
        exit(EXIT_FAILURE);
    }

    NSVector x = matrixio_fread_vector(argv[1]);
    NSVector y = matrixio_fread_vector(argv[2]);
    double h = atof(argv[3]);
    NSVector x_samples = matrixio_fread_vector(argv[4]);

    matrixio_show_vector(x);
    matrixio_show_vector(y);
    matrixio_show_vector(x_samples);
    printf("h = %lf\n", h);

    double * y_samples = gregory_newton_bw_evaluation(x.items, y.items, x.size, h, x_samples.items, x_samples.size);
    FILE * fsamples = fopen("./y_samples.txt", "w");
    fprintf(fsamples, "%d 1\n", x_samples.size);
    for (int i = 0; i < x_samples.size; i++) {
        printf("f(%lf) = %lf\n", x_samples.items[i], y_samples[i]);
        fprintf(fsamples, "%lf\n", y_samples[i]);
    }
    fclose(fsamples);

    matrixio_free_vector(&x);
    matrixio_free_vector(&y);
    matrixio_free_vector(&x_samples);
    free(y_samples);

    return 0;
}
