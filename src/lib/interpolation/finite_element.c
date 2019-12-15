/**
    ANSI C standard: c11
    finite_element.c
    Purpose: Interpolation by finite element

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include "numsys/solvers/cholesky.h"

#define _FINITE_ELEMENT_IMPORT
#include "numsys/interpolation/finite_element.h"


static double n_k(double z_k, double x_i, double h) {
    if(! (z_k <= x_i && x_i < z_k+h)) {
        return 0.0;
    }

    return 1.0 - (x_i - z_k) / h;
}


static double n_k1(double z_k, double x_i, double h) {
    if (! (z_k <= x_i && x_i < z_k+h)) {
        return 0;
    }

    return (x_i - z_k) / h;
}


static double ak(double z_k, double h, NSVector x, double lambda) {
    double _sum = 0.0;
    for (int i = 0; i < x.size; i++) {
        _sum += n_k(z_k, x.items[i], h) * n_k(z_k, x.items[i], h);
    }

    return _sum + lambda / h;
}


static double bk(double z_k, double h, NSVector x, double lambda) {
    double _sum = 0.0;
    for (int i = 0; i < x.size; i++) {
        _sum += n_k(z_k, x.items[i], h) * n_k1(z_k, x.items[i], h);
    }

    return _sum - lambda / h;
}



static double ck(double z_k, double h, NSVector x, double lambda) {
    double _sum = 0.0;
    for (int i = 0; i < x.size; i++) {
        _sum += n_k1(z_k, x.items[i], h) * n_k1(z_k, x.items[i], h);
    }

    return _sum + lambda / h;
}



static double sk(double z_k, double h, NSVector x, NSVector y) {
    double _sum = 0.0;
    for (int i = 0; i < x.size; i++) {
        _sum += y.items[i] * n_k(z_k, x.items[i], h);
    }

    return _sum;
}



static double tk(double z_k, double h, NSVector x, NSVector y) {
    double _sum = 0.0;
    for (int i = 0; i < x.size; i++) {
        _sum += y.items[i] * n_k1(z_k, x.items[i], h);
    }

    return _sum;
}


static void set_system(NSMatrix * a, NSVector * b, NSVector z, NSVector x, NSVector y, double h, double lambda) {
    for (int k = 0; k < z.size - 1; k++) {
        a->items[k][k] += ak(z.items[k], h, x, lambda);
        a->items[k][k+1] = a->items[k+1][k] = bk(z.items[k], h, x, lambda);
        a->items[k+1][k+1] = ck(z.items[k], h, x, lambda);

        b->items[k] += sk(z.items[k], h, x, y);
        b->items[k+1] = tk(z.items[k], h, x, y);
    }
}


void interpolation_finite_elements(NSVector x, NSVector y, NSVector * z, NSVector * phi, int partition_size, double lambda) {
    double _a = x.items[0];
    double _b = x.items[x.size - 1];
    double h = (_b - _a) / (partition_size - 1);
    // printf("h: %lf\n", h);


    *z = matrixio_allocate_vector(partition_size);
    for (int i = 0; i < partition_size; i++, z->items[i] = _a + i*h);

    NSMatrix a = matrixio_allocate_matrix(z->size, z->size);
    NSVector b = matrixio_allocate_vector(z->size);

    set_system(&a, &b, *z, x, y, h, lambda);
    // matrixio_show_matrix(a);

    NSMatrixSystem msystem = NSMatrixSystemDefault;
    msystem.a = a;
    msystem.b = b;
    msystem.x = matrixio_allocate_vector(z->size);

    solver_cholesky_method(&msystem);

    *phi = msystem.x;

    matrixio_free_matrix(&msystem.a);
    matrixio_free_vector(&msystem.b);
}
