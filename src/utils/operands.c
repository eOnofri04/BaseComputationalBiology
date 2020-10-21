//
//  operands.c
//  BaseComputationalBiology
//
//  Created by Elia Onofri on 12/10/2020.
//

#include "./utils.h"

double evalMean(double *a, int n);
double evalVariance(double *a, int n);

/*
 *	double evalMean(double *a, int n)
 *
 *	Returns the mean of vector `a` of length `n`
 */
double evalMean(double *a, int n){
	int i;
	double m = 0;
	for (i = 0; i < n; i++){
		m += a[i];
	}
	return m/n;
}


/*
 *	double evalVariance(double *a, int n)
 *
 *	Returns the variance of vector `a` of length `n`
 */
double evalVariance(double *a, int n){
	int i;
	double m = evalMean(a, n);
	double v = 0;
	
	for (i = 0; i < n; i++){
		v += pow((a[i] - m), 2);
	}
	return v/n;
}
