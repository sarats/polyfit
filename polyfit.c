#include "polyfit.h"
 
int polyfit(int npoints, int degree, double *xi, double *yi, double *coeff) 
{
#if defined(USE_GSL)
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
 
  /* Ref: https://www.gnu.org/software/gsl/manual/html_node/Multi_002dparameter-regression.html#index-gsl_005fmultifit_005flinear */
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
#else
  /* Placeholder for naive backup version */
  
  
#endif

  return 0; 
}

double polyval(double *coeff, int degree, double x)
{
#if !defined(USE_GSL)
	/* Using gsl_poly_eval for simple cases, ref: https://www.gnu.org/software/gsl/manual/html_node/Polynomial-Evaluation.html#index-gsl_005fpoly_005feval
	 * Can also use gsl_multifit_linear_est for error estimate etc. 
	 * Ref: https://www.gnu.org/software/gsl/manual/html_node/Multi_002dparameter-regression.html#index-gsl_005fmultifit_005flinear_005fest */
	return gsl_poly_eval(coeff, degree, x);
#else
	/* Backup version: 
	 * implements algorithm from Numerical Recipes*/
	int i;
	double y;
	
	y = coeff[degree-1];
	for( i=degree-1; i>0; i--)
		y = y * x + coeff[i-1];

	return y;
#endif

}

