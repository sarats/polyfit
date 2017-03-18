#if defined(__cplusplus)
extern "C" {
#endif

#if !defined(POLYFIT_H)
#define POLYFIT_H

#if defined(USE_GSL)
#include <gsl/gsl_multifit.h>
#include <gsl/gsl_poly.h>
#endif

#include <math.h>

int polyfit(int npoints, int degree, double *xi, double *yi, double *coeff);
double polyval(double *coeff, int degree, double x);

#endif

#if defined(__cplusplus)
}
#endif
