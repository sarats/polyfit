#include "polyfit.h"
 
int polyfit(int npoints, int degree, double *xi, double *yi, double *coeff) 
{
  int i, j;
  double chisq;
  gsl_matrix *cov, *X;
  gsl_vector *y, *c;
 
  /* Initialize workspace */
  gsl_multifit_linear_workspace *ws;
  ws = gsl_multifit_linear_alloc(npoints, degree);

  X = gsl_matrix_alloc(npoints, degree);
  y = gsl_vector_alloc(npoints);
  c = gsl_vector_alloc(degree);
  cov = gsl_matrix_alloc(degree, degree);
 
  for(i=0; i < npoints; i++) {
    for(j=0; j < degree; j++) {
      gsl_matrix_set(X, i, j, pow(xi[i], j));
    }
    gsl_vector_set(y, i, yi[i]);
  }
 
  gsl_multifit_linear(X, y, c, cov, &chisq, ws);
 
  /* Pass the fitted coefficients back to calling function */
  for(i=0; i < degree; i++)
  {
    coeff[i] = gsl_vector_get(c, i);
  }
 
  gsl_matrix_free(X);
  gsl_matrix_free(cov);
  gsl_vector_free(y);
  gsl_vector_free(c);
  gsl_multifit_linear_free(ws);

  return 0; 
}

double polyval(double *coeff, int degree, double x)
{
	return gsl_poly_eval(coeff, degree, x);
}

