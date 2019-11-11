/**
    ANSI C standard: c11
    main.c
    Purpose: Numerical Intagration example for Simpson 3/8

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#include <stdlib.h>
#include <math.h>
#include <numsys/matrix/matrix.h>
#include "numsys/numerical_integration/integration.h"


double f(double x) {
    return sin(x + 0.5);
}

int main(int argc, const char * argv[]) {
    if (argc < 3) {
        puts("Error: 3 args missing values");
        return 0;
    }

    const double x_from = atof(argv[1]);
    const double x_to = atof(argv[2]);
    const int m = atoi(argv[3]);

    if (m < 2 || (m % 3) != 0) {
        puts("Invalid value of m, m must be multiple of 3");
        return 0;
    }

    printf("Numerical integration for sin(x + 0.5) from %le to %le\n", x_from, x_to);

    double h = integration_get_h(x_from, x_to, m);
    double * y = integration_generate_y(x_from, x_to, m, f);
    double result = integration_simpson_3_8_rule(y, h, m);
    printf("Integration value: %le\n",result);

    free(y);

    return 0;
}
