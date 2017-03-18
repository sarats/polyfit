#if !defined(POLYFIT_H)
#define POLYFIT_H

#include <gsl/gsl_multifit.h>
#include <gsl/gsl_poly.h>
#include <math.h>

int polyfit(int npoints, int degree, double *xi, double *yi, double *coeff);
double polyval(double *coeff, int degree, double x);

#endif
