//
//  exercise3.c
//  BaseComputationalBiology
//
//  Created by Elia Onofri on 16/10/2020.
//

/* *****************************************************************************
 *	Write the computer code to simulate a 1D random walk
 *	 - Plot the position xt at time t
 *	 - Compute the mean square displacement
 *	 - Plot the mean square displacement averaged over many random walks
 *	Modify the code to do the same simulation but for a 2D random walk
 *	 - Plot the position (xt,yt) at time t
 *	 - Compute the mean square displacement
 *	 - Plot the mean square displacement averaged over many random walks
 **************************************************************************** */

#include "./exercise.h"

#define N 1000
#define SEED 1234
#define Nsample 1

int exercise3( void ){
	int i, j;
	double *dis, *dis2;
	srand(SEED);
	
	// 1D
	
	performRandomWalk(1, N, RANDOM_WALK_DATA);
	gnuplot( D1_RANDOM_WALK );
	
	// evaluate Nsample displacement and average them
	dis = evaluateRandomWalkDisplacement(1, N);
	for (i = 1; i < Nsample; i++){
		dis2 = evaluateRandomWalkDisplacement(1, N);
		for (j = 0; j < N; j++){
			dis[j] += dis2[j];
		}
		free( dis2 );
	}
	for (j = 0; j < N; j++){
		dis[j] /= Nsample;
	}
	
	plotFX(dis, N);
	
	free( dis );
	
	// 2D
	
	performRandomWalk(2, N, RANDOM_WALK_DATA);
	gnuplot( D2_RANDOM_WALK );
	
	// evaluate Nsample displacement and average them
	dis = evaluateRandomWalkDisplacement(2, N);
	for (i = 1; i < Nsample; i++){
		dis2 = evaluateRandomWalkDisplacement(2, N);
		for (j = 0; j < N; j++){
			dis[j] += dis2[j];
		}
		free( dis2 );
	}
	for (j = 0; j < N; j++){
		dis[j] /= Nsample;
	}
	
	plotFX(dis, N);
	
	free( dis );
	
	return 0;
}
