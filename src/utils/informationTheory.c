//
//  informationTheory.c
//  BaseComputationalBiology
//
//  Created by Elia Onofri on 14/10/2020.
//

#include "utils.h"

double shannonEntropy(int *f, int n);
double trueDiversity(int *f, int n, int q);
double * evalFileFrequency(char *filename);
double * evalFileFrequencyFromSet(char *filename, char *cset, int m);
double * evalFileAlphabethFrequency(char *filename);

/*
 *	double ShannonEntropy(int* a, int n)
 *
 *	Evaluates the entropy of the array of frequencies `f` (of length `n`)
 *	It skips an entry when f[i] = 0;
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
 *	double trueDiversity(int *f, int n, int q)
 *
 *	Evaluates the `q`-th true diversity over frequencies `f` (of length `n`)
 */
double trueDiversity(int *f, int n, int q){
	int i;
	double H = 0;
	
	for (i = 0; i < n; i++) {
		H += pow(f[i], q);
	}
	return pow(H, (double) 1/(q-1));
}

/*
 *	double * evalFileFrequency(char *filename)
 *
 *	Returns the frequency of the chars contained in the file specified by
 *	 `filename` as an array size sizeof(char).
 */
double * evalFileFrequency(char *filename){
	int ch, i, n=0;
	double *f;
	FILE *fp;
	
	f = callocate(NCHAR, double);
	if (f == NULL){
		printf("Could not allocate enough memory: %lu doubles\n", NCHAR);
		exit(-1);
	}
	
	fp = fopen(filename, "r");
	
	if(fp == NULL){
		printf("Could not open file: %s\n",filename);
		exit(-2);
	}
	
	while( (ch = fgetc(fp)) != EOF ){
		f[(int) ch]++;
		n++;
	}
	
	for (i = 0; i < NCHAR; i++){
		f[i] /= n;
	}
	
	fclose(fp);
	
	return f;
}

/*
 *	double * evalFileFrequencyFromSet(char *filename, char *cset, int m)
 *
 *	Returns the frequency of the chars in `cset` contained in the file
 *	 specified by `filename` as an array size m.
 */
double * evalFileFrequencyFromSet(char *filename, char *cset, int m){
	int ch, i, j, n=0;
	double *f;
	FILE *fp;
	
	f = callocate(m, double);
	if (f == NULL){
		printf("Could not allocate enough memory: %d doubles\n", m);
		exit(-1);
	}
	
	fp = fopen(filename, "r");
	
	if(fp == NULL){
		printf("Could not open file: %s\n",filename);
		exit(-2);
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
	
	fclose(fp);
	
	return f;
}


/*
 *	double * evalFileAlphabethFrequency(char *filename)
 *
 *	Returns the frequency of the chars `a/A-z/Z contained in the file
 *	 specified by `filename` as an array size 26.
 */
double * evalFileAlphabethFrequency(char *filename){
	int ch, i, n=0, m=26;
	double *f;
	FILE *fp;
	
	f = callocate(m, double);
	if (f == NULL){
		printf("Could not allocate enough memory: %d doubles\n", m);
		exit(-1);
	}
	
	fp = fopen(filename, "r");
	
	if(fp == NULL){
		printf("Could not open file: %s\n",filename);
		exit(-2);
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
	
	fclose(fp);
	
	return f;
}
