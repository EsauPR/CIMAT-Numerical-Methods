/**
    ANSI C standard: c11
    bisection.h
    Purpose: Prototype for bisection module

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#ifndef BISECTION_H

#ifdef BISECTION_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

EXTERN double bisection_find_root(double (*function)(double), double min_value, double max_value);

#undef BISECTION_IMPORT
#undef EXTERN
#endif
