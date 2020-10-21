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

#define N 10000
#define D 3
#define SEED 0
#define Nsample 1000
#define GRANULARITY 1
#define MULTI_RANDOM_WALK "products/random_walks.tsv"

int exercise3( void ){
	int	d,		// dimensional index
		t,		// time index
		s,		// sample index
		*xs;	// progressive position of all the concurrent trajectories as
				// (x_0..x_D)..(x_0..x_D) Nsample times
	double	distance,		// euclidean distance
			*dis,			// mean square displacement
			*dis2,			// mean square displacement
			*means,
			*deviations;
	FILE *fp;	// file to store the path
	
	srand(SEED);
	
	performDiscreteRandomWalkOnFile(D, N, NULL, RANDOM_WALK_DATA);
	switch (D) {
		case 1:
			gnuplot( D1_RANDOM_WALK, "" );
			break;
			
		case 2:
			gnuplot( D2_RANDOM_WALK, "" );
			break;
			
		case 3:
			gnuplot( D3_RANDOM_WALK, "" );
			break;
			
		default:
			break;
	}
	
	// evaluate mean square Displacement
	
	dis = evaluateDiscreteRandomWalkDisplacement(D, N);
	plotFX(dis, N, "title='Square Displacement'; datatitle='RW square displacement'; xlabel='t'; ylabel='distance'");
	
	// evaluate Nsample mean square displacement and average them
	
	for (s = 1; s < Nsample; s++){
		dis2 = evaluateDiscreteRandomWalkDisplacement(D, N);
		for (t = 0; t < N; t++){
			dis[t] += dis2[t];
		}
		free( dis2 );
	}
	for (t = 0; t < N; t++){
		dis[t] /= Nsample;
	}
	
	plotFX(dis, N, "title='Square Displacement'; datatitle='square displacement mean'; xlabel='t'; ylabel='distance'");
	free( dis );
	
	// evaluate Nsample mean displacement and every GRANULARITY
	//  plot mean and variance.
	
	xs = callocate(Nsample * D, int);
	if (xs == NULL){
		printf("Could not allocate enough memory: %d int\n", Nsample * D);
		exit(-1);
	}
	means = callocate(N, double);
	if (means == NULL){
		printf("Could not allocate enough memory: %d int\n", N);
		exit(-1);
	}
	deviations = callocate(N, double);
	if (deviations == NULL){
		printf("Could not allocate enough memory: %d int\n", N);
		exit(-1);
	}
	fp = fopen(MULTI_RANDOM_WALK, "w");
	if (fp == NULL){
		printf("Could not open file: %s\n", MULTI_RANDOM_WALK);
		exit(-2);
	}
	
	for (t = 1; t < N; t++){
		// Perform the Nsample random walks
		for (s = 0; s < Nsample; s++){
			performDiscreteRandomWalk(D, 1, xs + s*D);
		}
		for (s = 0; s < Nsample; s++){
			fprintf(fp, "(");
			fprintf(fp, "%d", xs[s*D]);
			for (d = 1; d < D; d++){
				fprintf(fp, ", %d", xs[s*D+d]);
			}
			fprintf(fp, ")\t");
		}
		fprintf(fp, "\n");
		for (s = 0; s < Nsample; s++){
			distance = 0.;
			for (d = 0; d < D; d++){
				distance += pow(xs[s*D+d],2);
			}
			means[t] += sqrt(distance);
		}
		means[t] /= Nsample;
		for (s = 0; s < Nsample; s++){
			distance = 0.;
			for (d = 0; d < D; d++){
				distance += pow(xs[s*D+d],2);
			}
			deviations[t] += pow(sqrt(distance)-means[t], 2);
		}
		deviations[t] = sqrt(deviations[t]/Nsample);
	}
	
	fclose( fp );
	
	plotFXE(means, deviations, N, "title='Displacement'; datatitle='displacement mean'; errortitle='standard deviation'; xlabel='t'; ylabel='distance'");
	
	free( means );
	free( deviations );
	free( xs );
	
	return 0;
}
