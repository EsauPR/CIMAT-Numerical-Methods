/**
    ANSI C standard: c11
    newton_raphson.h
    Purpose: Prototype for newton_raphson module

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#ifndef NEWTON_RAPHSON_H

#ifdef NEWTON_RAPHSON_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

EXTERN double newton_raphson_solver(double (*function)(double), double x_start);

#undef NEWTON_RAPHSON_IMPORT
#undef EXTERN
#endif
