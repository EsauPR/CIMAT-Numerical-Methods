/**
    ANSI C standard: c11
    regresion.c
    Purpose: Implemetation for regresion formules

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <numsys/matrix/matrixio.h>

#define REGRESION_IMPORT
#include "numsys/regresion/regresion.h"

/* Linear regresion */
NSVector regresion_linear(NSVector x, NSVector y) {
    int n = x.size;
    double sx = 0, sy = 0, sxy = 0, sxx = 0;

    for (int i = 0; i < n; i++) {
        sx += x.items[i];
        sy += y.items[i];
        sxy += x.items[i] * y.items[i];
        sxx += x.items[i] * x.items[i];
    }

    double a = (sx*sy - n*sxy) / (sx*sx - n * sxx);
    double b = (sy - a*sx) / n;

    NSVector coefs = NSVectorDefault;
    coefs.size = 2;
    coefs.items = matrixio_allocate_array_double(2);
    coefs.items[0] = a;
    coefs.items[1] = b;

    return coefs;
}

/* Cuadratic regresion */
NSVector regresion_cuadratic(NSVector x, NSVector y) {
    int n = x.size;
    double sx = 0, sy = 0, sxy = 0, sx2 = 0, sx4 = 0, sx3 = 0, sx2y = 0;

    for (int i = 0; i < n; i++) {
        sx += x.items[i];
        sy += y.items[i];
        sxy += x.items[i] * y.items[i];
        sx2 += x.items[i] * x.items[i];
        sx3 += x.items[i] * x.items[i] * x.items[i];
        sx4 += x.items[i] * x.items[i] * x.items[i] * x.items[i];
        sx2y += x.items[i] * x.items[i] * y.items[i];
    }

    double b = ((sxy - sx*sy/n) * (sx4 - sx2*sx2/n) - (sx2y - sx2*sy/n) * (sx3 - sx2*sx/n)) / ((sx2 - sx*sx/n) * (sx4 - sx2*sx2/n) - (sx3 - sx2*sx/n) * (sx3 - sx2*sx/n));
    double a = ((sx2 - sx*sx/n) * (sx2y - sx2*sy/n) - (sx3 - sx2*sx/n) * (sxy - sx*sy/n)) / ((sx2 - sx*sx/n) * (sx4 - sx2*sx2/n) - (sx3 - sx2*sx/n) * (sx3 - sx2*sx/n));
    double c = (sy - b*sx - a*sx2) / n;

    NSVector coefs = NSVectorDefault;
    coefs.size = 3;
    coefs.items = matrixio_allocate_array_double(3);
    coefs.items[0] = a;
    coefs.items[1] = b;
    coefs.items[2] = c;

    return coefs;
}
