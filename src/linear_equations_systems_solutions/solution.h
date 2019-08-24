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


/*
    Flags to know the solution state or information
*/
static const unsigned char __SOLUTION_NO_STATE__ = 0;
static const unsigned char __SOLUTION_NO_EXISTS__ = 1;


/* Struct to represent a linear equation system solution */
static const struct solution_SystemSolution {
    int size;
    int * rows_perm_map;
    int * cols_perm_map;
    double determinant;
    double * solution;
    unsigned char state;
} SystemSolutionDefault = {0, NULL, NULL, 1.0, NULL, __SOLUTION_NO_STATE__};

typedef struct solution_SystemSolution SystemSolution;

/* Return a pointer array to track a permutation mapping */
EXTERN int* create_permutation_map(int size);

// /* Sort a array using the permutation mapping */
// EXTERN void *sort_array_by_perm_map(int *array, int* permutation_map, int size);

// /* Sort the matrix rows using a permutation mapping */
// EXTERN void *sort_matix_rows_by_perm_map(int *array, int* permutation_map, int size);


/* Free the solution struct for a linear equation system*/
EXTERN void free_system_solution(SystemSolution * system_solution);

/* Print the solution for a linear equation system*/
EXTERN void print_system_solution(SystemSolution system_solution);


#undef SOLUTION_IMPORT
#undef EXTERN
#endif
