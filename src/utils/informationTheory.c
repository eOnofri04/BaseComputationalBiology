//
//  informationTheory.c
//  BaseComputationalBiology
//
//  Created by Elia Onofri on 14/10/2020.
//

#include "utils.h"

double shannonEntropy(int *f, int n);
int evalFileFrequency(char *filename, double **f);
int evalFileFrequencyFromSet(char *filename, double **f, char *cset, int m);
int evalFileAlphabethFrequency(char *filename, double **f);

/*
 * ShannonEntropy(int* a, int n)
 * Evaluates the entropy of the array of frequencies `f` (of length `n`)
 * It skips when f[i] = 0;
 */
double shannonEntropy(int *f, int n){
	int i;
	double H = 0;
	
	for (i = 0; i < n; i++) {
		if (f[i] != 0){
			H = f[i]*log(f[i]);
		}
	}
	
	return -H;
}

/*
 * evalFileFrequency(char *filename, double *f)
 * Evaluate the frequency of the chars contained in the file specified
 * by `filename` and populates the array `f` (of length sizeof(char))
 * with the frequencies found.
 * The method return:
 *   `0` if everything goes well
 *  `-1` if allocation related issues occurred
 *  `-2` if file related issues occurred
 */
int evalFileFrequency(char *filename, double **f1){
	int ch, i, n=0;
	double *f;
	FILE *fp;
	
	f = callocate(NCHAR, double);
	if (f == NULL){
		printf("Could not allocate enough memory: %lu doubles\n", NCHAR);
		return -1;
	}
	
	fp = fopen(filename, "r");
	
	if(fp == NULL){
		printf("Could not open file: %s\n",filename);
		return -2;
	}
	
	while( (ch = fgetc(fp)) != EOF ){
		f[(int) ch]++;
		n++;
	}
	
	for (i = 0; i < NCHAR; i++){
		f[i] /= n;
	}
	
	*f1 = f;
	
	return 0;
}

/*
 * evalFileFrequencyFromSet(char *filename, double *f, char *cset, int m)
 * Evaluate the frequency of the chars in `cset` contained in the file
 * specified by `filename` and populates the array `f` (of length `m`)
 * with the frequencies found.
 * The method return:
 *   `0` if everything goes well
 *  `-1` if allocation related issues occurred
 *  `-2` if file related issues occurred
 */
int evalFileFrequencyFromSet(char *filename, double **f1, char *cset, int m){
	int ch, i, j, n=0;
	double *f;
	FILE *fp;
	
	f = callocate(m, double);
	if (f == NULL){
		printf("Could not allocate enough memory: %d doubles\n", m);
		return -1;
	}
	
	fp = fopen(filename, "r");
	
	if(fp == NULL){
		printf("Could not open file: %s\n",filename);
		return -2;
	}
	
	while( (ch = fgetc(fp)) != EOF ){
		for (j = 0; j <= m; j++){
			if (ch == cset[j]){
				f[j]++;
				n++;
			}
		}
	}
	
	for (i = 0; i < m; i++){
		f[i] /= n;
	}
	
	*f1 = f;
	
	return 0;
}


/*
 * evalFileAlphabethFrequency(char *filename, double *f)
 * Evaluate the frequency of the chars `a/A-z/Z` contained in the file
 * specified by `filename` and populates the array `f` (of length `26`)
 * with the frequencies found.
 * The method return:
 *   `0` if everything goes well
 *  `-1` if allocation related issues occurred
 *  `-2` if file related issues occurred
 */
int evalFileAlphabethFrequency(char *filename, double **f1){
	int ch, i, n=0, m=26;
	double *f;
	FILE *fp;
	
	f = callocate(m, double);
	if (f == NULL){
		printf("Could not allocate enough memory: %d doubles\n", m);
		return -1;
	}
	
	fp = fopen(filename, "r");
	
	if(fp == NULL){
		printf("Could not open file: %s\n",filename);
		return -2;
	}
	
	while( (ch = fgetc(fp)) != EOF ){
		if (ch >= 65 && ch <= 90){
			f[ch-65]++;
			n++;
		} else if (ch >= 97 && ch <= 122){
			f[ch-97]++;
			n++;
		}
		
	}
	
	for (i = 0; i < m; i++){
		f[i] /= n;
	}
	
	*f1 = f;
	
	return 0;
}
