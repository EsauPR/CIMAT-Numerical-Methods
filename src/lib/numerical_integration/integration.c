/**
    ANSI C standard: c11
    bisection.c
    Purpose: Module for numerical integration

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <numsys/matrix/matrixio.h>

#define NS_NUMERICAL_INTEGRATION_IMPORT
#include "numsys/numerical_integration/integration.h"


double integration_get_h(double x_from, double x_to, int m) {
    // printf("h: %lf\n", (x_to - x_from) / m);
    return (x_to - x_from) / m;
}

double * integration_generate_y(double x_from, double x_to, int m, double (*f)(double)) {
    double * y = matrixio_allocate_array_double(m+1);
    double delta = integration_get_h(x_from, x_to, m);

    double x = x_from;
    for (int i = 0; i <= m; i++, x += delta) {
        y[i] = f(x);
        // printf("%2d) %lf %lf\n", i, x, y[i]);
    }

    return y;
}

/* Return the value of the integration for the composite trapeze rule */
double integration_trapeze_rule(double * y, double h, int m) {
    double sum = 0;

    for (int i = 1; i < m; i++) {
        sum += y[i];
    }

    return h * (y[0] + y[m] + 2 * sum) / 2.0;
}

/* Return the value of the integration for the composite simpson 1/3 rule */
double integration_simpson_1_3_rule(double * y, double h, int m) {
    double even_sum = 0;
    double odd_sum = 0;

    for (int i = 1; i < m; i++) {
        if (i & 1) {
            odd_sum += y[i];
        } else {
            even_sum += y[i];
        }
    }

    return h * (y[0] + y[m] + 2 * even_sum + 4 * odd_sum) / 3.0;
}

/* Return the value of the integration for the composite simpson 3/8 rule */
double integration_simpson_3_8_rule(double * y, double h, int m) {
    double sum1 = 0;
    double sum2 = 0;

    for (int i = 1; i < m; i++) {
        if (i % 3 == 0) {
            sum2 += y[i];
        } else {
            sum1 += y[i];
        }
    }

    return 3 * h * (y[0] + y[m] + 2 * sum2 + 3 * sum1) / 8.0;
}

/* Return the value of the integration for the composite Boole rule */
double integration_boole_rule(double * y, double h, int m) {
    double sum = 0;
    double coefs[] = {7, 32, 12, 32, 7};

    for (int i = 0; i < m; i+=4) {
        for (int j = 0; j < 5; j++){
            sum += coefs[j] * y[i+j];
        }
    }

    return 2.0 * h * sum  / 45.0;
}

/* Return the value of the integration for the composite Weddle rule */
double integration_weddle_rule(double * y, double h, int m) {
    double sum = 0;
    double coefs[] = {41, 216, 27, 272, 27, 216, 41};

    for (int i = 0; i < m; i+=6) {
        for (int j = 0; j < 7; j++){
            sum += coefs[j] * y[i+j];
        }
    }

    return h * sum / 140.0;
}
