//
//  exercise1.c
//  BaseComputationalBiology
//
//  Created by Elia Onofri on 12/10/2020.
//

/* *****************************************************************************
 *	Usage of random number generation and gnuplot software.
 *	Encode the following:
 *	 - Generation of events with specific given distribution;
 *	 - RouletteWheelSelection to select events with given discrete distribution;
 *	 - evaluate principal statistics (mean, variance) and relative histogram.
 **************************************************************************** */

#include "./exercise.h"

#define SEED (long)1234
#define NBIN 10
#define N    100000

int exercise1() {
	int i, np;
	srand48(SEED);
	double *a, *b, *P;
	double acc;
	FILE *fp;
	char *filename;
	filename = "inputs/exercise1/probabilities.tsv";
	
	fprintf(stdout, "-------------------------------------\n");
	fprintf(stdout, "Parameters are:\n");
	fprintf(stdout, " - Number of bins: %d\n", NBIN);
	fprintf(stdout, " - Number of sampled elements: %d\n", N);
	fprintf(stdout, " - Simulation seed: %lu\n", SEED);
	fprintf(stdout, "-------------------------------------\n");
	
	a = allocate(N, double);
	if (a == NULL){
		fprintf(stderr, "Could not allocate enough memory: %d doubles\n", N);
		return -1;
	}
	
	for (i = 0; i < N; i++){
		a[i] = drand48();
	}
	
	fprintf(stdout, "\nMean:\t%lf\n", evalMean(a, N) );
	fprintf(stdout, "\nVariance:\t%lf\n", evalVariance(a, N) );
	plotHistogram(a, N, NBIN, "title='Histogram of Random Values'");
	
	fp = fopen(filename, "r");
	if(fp == NULL){
		fprintf(stderr, "Could not open file: %s\n", filename);
		return -2;
	}

	fscanf(fp, "%d", &np);
	P = allocate(np, double);
	if (P == NULL){
		fprintf(stderr, "Could not allocate enough memory: %d doubles\n", np);
		return -1;
	}
	
	for (i = 0; i < np; i++){
		fscanf(fp, "%lf", &P[i]);
	}
	fclose(fp);
	
	acc = 0;
	for (i = 0; i < np; i++){
		acc += P[i];
	}
	if (acc != 1.0){
		return 2;
	}
	
	b = allocate(N, double);
	if (b == NULL){
		fprintf(stderr, "Could not allocate enough memory: %d doubles\n", N);
		return -1;
	}
	
	for (i = 0; i < N; i++){
		b[i] = randomWheelSelect(a[i], P, np);
	}
	
	fprintf(stdout, "\nMean:\t%lf\n", evalMean(b, N) );
	fprintf(stdout, "\nVariance:\t%lf\n", evalVariance(b, N) );
	plotHistogram(b, N, np, "title='Histogram of Random Wheel'");
	
	free(a);
	free(b);
	free(P);
	
	return 1;
}

