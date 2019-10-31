#include <stdio.h>
#include <math.h>
#include "numsys/matrix/matrixio.h"

#define PI 3.14159

/* First derivate */
double dy(double x, double y) {
    return y + sin(x/2.0);
}


/* Second derivate */
double ddy(double x, double y) {
    return y + sin(x/2.0) + 0.5 * cos(x/2.0);
}

/* Vectors initialization */
int get_xy(double h, double ** x, double ** y) {
    int nelements = (PI * 2) / h;
    *x = matrixio_allocate_array_double(nelements + 1);
    *y = matrixio_allocate_array_double(nelements + 1);

    (*x)[0] = -PI;
    for (int i = 1; i <= nelements; i++) {
        (*x)[i] = (*x)[i-1] + h;
    }

    (*y)[0] = 0.5;
    (*y)[1] = (*y)[0] + h * ddy((*x)[0], (*y)[0]);
    (*y)[2] = (*y)[1] + h * ddy((*x)[1], (*y)[1]);

    return nelements;
}

/* Compute each point with hermite */
void compute_hermite(double * x, double * y, int nelements, double h) {
    double factor = 10;
    for (int i = 3; i < nelements; i++) {
        double p1 = 7 * dy(x[i-3], y[i-3]) + 16 * dy(x[i-2], y[i-2]) + 7 * dy(x[i-1], y[i-1]);
        double p2 = h * (ddy(x[i-3], y[i-3]) - ddy(x[i-1], y[i-1]));
        y[i] = y[i-3] + (h / factor) * (p1 + p2);
    }
}


int main() {
    double h = 0.001;
    double * x, *y;

    int nelements = get_xy(h, &x, &y);
    compute_hermite(x, y, nelements, h);

    FILE * fp = fopen("points.txt", "w");
    for (int i = 0; i < nelements; i++) {
        fprintf(fp, "%lf, %lf\n", x[i], y[i]);
    }

    fclose(fp);

    return 0;
}
