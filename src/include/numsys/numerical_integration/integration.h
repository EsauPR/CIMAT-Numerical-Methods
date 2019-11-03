/**
    ANSI C standard: c11
    bisection.h
    Purpose: Prototype for numerical integration module

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#ifndef NS_NUMERICAL_INTEGRATION

#ifdef NS_NUMERICAL_INTEGRATION_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

EXTERN double integration_get_h(double x_from, double x_to, int m);

EXTERN double * integration_generate_y(double x_from, double x_to, int m, double (*f)(double));

/* Return the value of the integration for the composite trapeze rule */
EXTERN double integration_trapeze_rule(double * y, double h, int m);

/* Return the value of the integration for the composite simpson 1/3 rule */
EXTERN double integration_simpson_1_3_rule(double * y, double h, int m);

/* Return the value of the integration for the composite simpson 3/8 rule */
EXTERN double integration_simpson_3_8_rule(double * y, double h, int m);

/* Return the value of the integration for the composite Boole rule */
EXTERN double integration_boole_rule(double * y, double h, int m);

/* Return the value of the integration for the composite Weddle rule */
EXTERN double integration_weddle_rule(double * y, double h, int m);


#undef NS_NUMERICAL_INTEGRATION_IMPORT
#undef EXTERN
#endif
