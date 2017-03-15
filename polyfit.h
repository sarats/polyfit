#ifndef _POLYGIT_H
#define _POLYGIT_H

#include <gsl/gsl_multifit.h>
#include <math.h>
int polynomialfit(int obs, int degree, 
		   double *dx, double *dy, double *store); /* n, p */

#endif

