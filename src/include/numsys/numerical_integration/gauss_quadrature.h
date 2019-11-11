/**
    ANSI C standard: c11
    bisection.h
    Purpose: Prototype for numerical integration module
             using Gauss Qudrature formulas

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/



#ifndef NS_NUMERICAL_INTEGRATION_GAUSS

#ifdef NS_NUMERICAL_INTEGRATION_GAUSS_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

EXTERN double gauss_legendre_formula_1p(double (*f)(double));

EXTERN double gauss_legendre_formula_2p(double (*f)(double));

EXTERN double gauss_legendre_formula_3p(double (*f)(double));

EXTERN double gauss_legendre_formula_4p(double (*f)(double));


#undef NS_NUMERICAL_INTEGRATION_GAUSS_IMPORT
#undef EXTERN
#endif
