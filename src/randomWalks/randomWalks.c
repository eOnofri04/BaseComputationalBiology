//
//  randomWalks.c
//  BaseComputationalBiology
//
//  Created by Elia Onofri on 19/10/2020.
//

#include "randomWalks.h"

void performDiscreteRandomWalkOnFile(int D, int N, int *x, char *filename);
int * performDiscreteRandomWalk(int D, int N, int *x);
double * evaluateDiscreteRandomWalkDisplacement(int D, int N);


/*
 *	performRandomWalkOnFile(int D, int N, int *x, char *filename)
 *	The function performs a `N`-step random walk in the discrete `D`-dimensional
 *	space, starting on `x` (if not specified, x = 0..0).
 *	The position are saved in the file specified by `filename`.
 *  The final position is also stored in `x`.
 */
void performDiscreteRandomWalkOnFile(int D, int N, int *x, char *filename){
	FILE *fp;	// file to store position in time
	int t,		// temporal counter
		d;		// dimensional counter
	
	if (x == NULL){
		x = callocate(D, int);
		if (x == NULL){
			printf("Could not allocate enough memory: %d int\n", D);
			exit(-1);
		}
	}
    
	fp = fopen(filename, "w");
	if(fp == NULL){
		printf("Could not open file: %s\n", filename);
		exit(-2);
	}
	
	for (d = 0; d < D; d++){
		fprintf(fp, "%d\t", x[d]);
	}
	fprintf(fp, "\n");
	
	for (t = 0; t < N; t++){
		x[pickRandomInteger(0, D-1)] += pickRandomInteger(0, 1) * 2 - 1;
		for (d = 0; d < D; d++){
			fprintf(fp, "%d\t", x[d]);
		}
		fprintf(fp, "\n");
	}
	
    fclose(fp);
	
	return ;
}

/*
 *  performRandomWalk(int D, int N, int *x)
 *  The function performs a `N`-step random walk in the discrete `D`-dimensional
 *   space, starting on `x` (if not specified, x = 0..0).
 *  The position time-by-time are returned as a N,D matrix.
 *  The final position is also stored in `x`.
 */
int * performDiscreteRandomWalk(int D, int N, int *x){
    int *pos,     // position matrix T,D
        t,        // temporal counter
        d;        // dimensional counter
    
    pos = allocate((N+1)*D, int);
    if (pos == NULL){
        printf("Could not allocate enough memory: %d int\n", N*D);
        exit(-1);
    }
    
    for (d = 0; d < D; d++){
		pos[d] = (x == NULL ? 0 : x[d]);
    }
    
    for (t = 1; t < N+1; t++){
        for (d = 0; d < D; d++){
            pos[t*D+d] = pos[(t-1)*D+d];
        }
        pos[t*D+pickRandomInteger(0, D-1)] += pickRandomInteger(0, 1) * 2 - 1;
    }
    
    for (d = 0; d < D; d++){
        x[d] = pos[(N)*D+d];
    }
    
    return pos;
}

/*
 *	double * evaluateDiscreteRandomWalkDisplacement(int D, int N)
 *	The function performs a `N`-step random walk in the discrete `D`-dimensional
 *   space, and return the displacement at each step.
 */
double * evaluateDiscreteRandomWalkDisplacement(int D, int N){
	int *pos,	// position at a given point in time
		t,		// temporal counter
		d;		// dimensional counter
	double *dis;// displacement array
	pos = callocate(D, int);
	if (pos == NULL){
		printf("Could not allocate enough memory: %d int\n", D);
		exit(-1);
	}
	dis = callocate(N+1, double);
	if (dis == NULL){
		printf("Could not allocate enough memory: %d double\n", N);
		exit(-1);
	}
	
	for (t = 1; t < N+1; t++){
		pos[pickRandomInteger(0, D-1)] += pickRandomInteger(0, 1) * 2 - 1;
		for (d = 0; d < D; d++){
			dis[t] += pow(pos[d], 2);
		}
		dis[t] /= D;
	}
	
	free( pos );
	
	return dis;
}
