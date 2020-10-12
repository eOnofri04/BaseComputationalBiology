//
//  esercizio1.c
//  IN470
//
//  Created by Elia Onofri on 12/10/2020.
//

#include "esercizi.h"

#define SEED 0
#define NBIN 10
#define N 100000
#define NP 5

int esercizio1() {
	int i, np;
	srand48(SEED);
	double *a, *b, *P;
	double acc;
	FILE *fp;
	
	a = (double *) malloc(sizeof(double) * N);
	for (i = 0; i < N; i++){
		a[i] = drand48();
	}
	
	printf("\nMean:\t%lf\n", evalMean(a, N) );
	printf("\nVariance:\t%lf\n", evalVariance(a, N) );
	plotHistogram(a, N, NBIN);
	
	fp = fopen("inputs/esercizio1/probabilities.tsv", "r");
	fscanf(fp, "%d", &np);
	P = (double *) malloc(sizeof(double) * np);
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
	
	b = (double *) malloc(sizeof(double) * N);
	for (i = 0; i < N; i++){
		b[i] = randomWheelSelect(a[i], P, np);
	}
	
	printf("\nMean:\t%lf\n", evalMean(b, N) );
	printf("\nVariance:\t%lf\n", evalVariance(b, N) );
	plotHistogram(b, N, np);
	
	free(a);
	free(b);
	free(P);
	
	return 1;
}

