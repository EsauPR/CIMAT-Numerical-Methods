/**
    ANSI C standard: c11
    Purpose: Find a root funtion using the Newton Raphson method

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../../src/root_search/newton_raphson.h"

/* f(x) = x^2 */
double f1(double x) {
    return x * x;
}

/* f(x) = x^2 - 2*/
double f2(double x) {
    return x * x - 2.0;
}

/* f(x) = sin(x)*/
double f3(double x) {
    return sin(x);
}

/* f(x) = 1 / (x^2) */
double f4(double x) {
    return 1.0 / (x * x);
}

/* f(x) = x^3 + 3x^2 */
double f5(double x) {
    return x * x * x + 3 * x * x;
}

/* f(x) = (x-3)^2 - 2*/
double f6(double x) {
    return (x-3) * (x-3) - 2.0;
}


void print_functions() {
    puts("\nChoose a function:");
    puts("\t0) Quit");
    puts("\t1) f(x) = x^2");
    puts("\t2) f(x) = x^2 - 2");
    puts("\t3) f(x) = sin(x)");
    puts("\t4) f(x) = 1 / (x^2)");
    puts("\t5) f(x) = x^3 + 3x^2");
    puts("\t6) f(x) = (x-3)^2 - 2");
}


int main() {
    int option = 0;
    double x_start;
    double (*f1p)(double) = &f1;
    double (*f2p)(double) = &f2;
    double (*f3p)(double) = &f3;
    double (*f4p)(double) = &f4;
    double (*f5p)(double) = &f5;
    double (*f6p)(double) = &f6;

    while(1) {
        print_functions();
        printf("Option: ");
        scanf("%d", &option);

        if (option == 0){
            break;
        }

        printf("Initial X: ");
        scanf("%lf", &x_start);

        switch (option){
            case 1:
                printf("Estimated zero at: %lf\n", newton_raphson_solver(f1p, x_start));
                break;
            case 2:
                printf("Estimated zero at: %lf\n", newton_raphson_solver(f2p, x_start));
                break;
            case 3:
                printf("Estimated zero at: %lf\n", newton_raphson_solver(f3p, x_start));
                break;
            case 4:
                printf("Estimated zero at: %lf\n", newton_raphson_solver(f4p, x_start));
                break;
            case 5:
                printf("Estimated zero at: %lf\n", newton_raphson_solver(f5p, x_start));
                break;
            case 6:
                printf("Estimated zero at: %lf\n", newton_raphson_solver(f6p, x_start));
                break;
            default:
                break;
        }
    }

    exit(EXIT_SUCCESS);
}
