#include <stdio.h>
#include <stdlib.h>
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
 
  /* Build Vandermonde matrix */
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
  /* Least-squares implementation using LAPACK */
  int m = npoints, n = degree, nrhs = 1, lda = degree, ldb = 1, info;
  int i,j;
  double *A, *B, *S;
  double rcond = 1e-10;
  int rank;

  A = (double *) malloc(m*n*sizeof(double));
  B = (double *) malloc(m*sizeof(double));
  S = (double *) malloc((m<n?m:n)*sizeof(double));

  /* Build Vandermonde matrix */
  for(i=0; i < npoints; i++) {
    for(j=0; j < degree; j++) {
		A[i*lda+j] = pow(xi[i],j);
    }
	B[i] = yi[i];
  }
 
  /* Ref: http://www.netlib.org/lapack/explore-html/db/d6a/dgelsd_8f_source.html
	 lapack_int LAPACKE_dgelsd( int matrix_layout, lapack_int m, lapack_int n,
		lapack_int nrhs, double* a, lapack_int lda,
		double* b, lapack_int ldb, double* s, double rcond,
		lapack_int* rank );
  */
  info = LAPACKE_dgelsd( LAPACK_ROW_MAJOR, m, n, nrhs, A, lda,
		  B, ldb, S, rcond, &rank );

  /* info = LAPACKE_dgels( LAPACK_ROW_MAJOR, 'N', m, n, nrhs, A, lda, */
		  /* B, ldb ); */

#if defined(DEBUG)
  printf("\nCoefficients: %f %f %f ", B[0], B[1], B[2]);
  printf("\nS (singular values of A) = %f %f %f ", S[0], S[1], S[2]);
  printf("\nCondition number is S[0]/min(m,n) = %f ", S[0]/(m<n?m:n));
  printf("\nRank of matrix: %d \n", rank);
#endif  
    
  /* Pass the fitted coefficients back to calling function */
  for(i=0; i < degree; i++)
	  coeff[i] = B[i];
  
  free(A);
  free(B);
#endif

  return 0; 
}

inline double polyval(double *coeff, int degree, double x)
{
#if defined(USE_GSL)
	/* Using gsl_poly_eval for simple cases, ref: https://www.gnu.org/software/gsl/manual/html_node/Polynomial-Evaluation.html#index-gsl_005fpoly_005feval
	 * Can also use gsl_multifit_linear_est for error estimate etc. 
	 * Ref: https://www.gnu.org/software/gsl/manual/html_node/Multi_002dparameter-regression.html#index-gsl_005fmultifit_005flinear_005fest */
	return gsl_poly_eval(coeff, degree, x);
#else
	/* Implements algorithm from Numerical Recipes*/
	int i;
	double y;
	
	y = coeff[degree-1];
	for(i=degree-1; i>0; i--)
		y = y * x + coeff[i-1];

	return y;
#endif
}

