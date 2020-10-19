//
//  randomWalks.c
//  BaseComputationalBiology
//
//  Created by Elia Onofri on 19/10/2020.
//

#include "randomWalks.h"

void performRandomWalk(int D, int N, char *filename);
double * evaluateRandomWalkDisplacement(int D, int N);

void performRandomWalk(int D, int N, char *filename){
	FILE *fp;	// file to store position in time
	int *pos,	// position at a given point in time
		t,		// temporal counter
		d;		// dimensional counter
	
	pos = callocate(D, int);
	if (pos == NULL){
		printf("Could not allocate enough memory: %d int\n", D);
		exit(-1);
	}
	fp = fopen(filename, "w");
	if(fp == NULL){
		printf("Could not open file: %s\n", filename);
		exit(-2);
	}
	
	for (d = 0; d < D; d++){
		fprintf(fp, "%d\t", pos[d]);
	}
	fprintf(fp, "\n");
	
	for (t = 0; t < N; t++){
		pos[pickRandomInteger(0, D-1)] += pickRandomInteger(0, 1) * 2 - 1;
		for (d = 0; d < D; d++){
			fprintf(fp, "%d\t", pos[d]);
		}
		fprintf(fp, "\n");
	}
	
	fclose(fp);
	free(pos);
	
	return ;
}


double * evaluateRandomWalkDisplacement(int D, int N){
	int *pos,	// position at a given point in time
		t,		// temporal counter
		d;		// dimensional counter
	double *dis;// displacement array
	pos = callocate(D, int);
	if (pos == NULL){
		printf("Could not allocate enough memory: %d int\n", D);
		exit(-1);
	}
	dis = callocate(N, double);
	if (dis == NULL){
		printf("Could not allocate enough memory: %d double\n", N);
		exit(-1);
	}
	
	for (t = 0; t < N; t++){
		pos[pickRandomInteger(0, D-1)] += pickRandomInteger(0, 1) * 2 - 1;
		for (d = 0; d < D; d++){
			dis[t] += pow(pos[d], 2);
		}
		dis[t] /= D;
	}
	
	return dis;
}
