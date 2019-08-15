/**
    ANSI C standard: c11
    solution.h
    Purpose: Prototype for solution module

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#ifndef SOLUTION_H
#define SOLUTION_H

#ifdef SOLUTION_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

/* Struct to represent a linear equation system solution */
typedef struct solution_SystemSolution {
    int size;
    double * solution;
    double determinat;
} SystemSolution;


/* Print the solution for a linear equation system*/
EXTERN void print_system_solution(SystemSolution system_solution);


#undef SOLUTION_IMPORT
#undef EXTERN
#endif
