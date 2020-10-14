//
//  utils.h
//  BaseComputationalBiology
//
//  Created by Elia Onofri on 12/10/2020.
//

#ifndef utils_h
#define utils_h


// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../graphics/graphics.h"

// Global Macros Definition
#define debug(x) printf("DEBUG %d", x);
#define hi printf("Hello, World!\n")
#define ln printf("\n")

// Global Constants
#define ERR 0.0000000001     // 10^-10, default max error

// from allocations.c
#define allocate(num, type) ((type*)malloc(num * sizeof(type)))
#define callocate(num, type) ((type*)calloc(num, sizeof(type)))

// from informationTheory.c
#define NCHAR sizeof(char)
double shannonEntropy(int *f, int n);
int evalFileFrequency(char *filename, double **f);
int evalFileFrequencyFromSet(char *filename, double **f, char *cset, int m);
int evalFileAlphabethFrequency(char *filename, double **f);

// from operands.c
#define max(a,b) a>=b?a:b
#define isApproxZero(x) fabs(x) < ERR
#define isApprox(x, y) fabs(x - y) < ERR
double evalMean(double *a, int n);
double evalVariance(double *a, int n);

// from random.c
#define Random(x, y) (x + ((double) rand()/RAND_MAX)*(y-x))
int randomWheelSelect(double x, double* P, int nP);

#endif /* utils_h */
