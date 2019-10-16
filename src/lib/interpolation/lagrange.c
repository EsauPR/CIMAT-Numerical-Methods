/**
    ANSI C standard: c11
    lagrange.c
    Purpose: Module to make a interpolation proccess by Newton interpolation polinomial

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdlib.h>
#include "string.h"

#define NS_INTERPOLATION_LAGRANGE_IMPORT
#include "numsys/interpolation/lagrange.h"


// static double interpolation_lagrange_li(int i, double * x, int size, double value) {
//     double l_i = 1.0;
//     for (int j = 0; j < size; j++){
//         if (j != i){
//             l_i *= (value - x[j]) / (x[i] - x[j]);
//         }
//     }

//     return l_i;
// }

// static double interpolation_lagrange_li_d1(int i, double * x, int size, double value) {
//     double l_i = 1.0;
//     for (int j = 0; j < size; j++){
//         if (j != i){
//             l_i *= (value - x[j]) / (x[i] - x[j]);
//         }
//     }

//     return l_i;
// }

// static double interpolation_lagrange_li_d2(int i, double * x, int size, double value) {
//     double l_i = 1.0;
//     for (int j = 0; j < size; j++){
//         if (j != i){
//             l_i *= (value - x[j]) / (x[i] - x[j]);
//         }
//     }

//     return l_i;
// }


double interpolation_lagrange(double * x, double * y, int size, double value) {
    double p_x = 0.0;

    for (int i = 0; i < size; i++) {
        double l_i = 1.0;
        for (int j = 0; j < size; j++){
            if (j != i){
                l_i *= (value - x[j]) / (x[i] - x[j]);
            }
        }
        p_x += y[i] * l_i;
    }

    return p_x;
}
