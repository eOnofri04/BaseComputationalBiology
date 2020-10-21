//
//  random.c
//  BaseComputationalBiology
//
//  Created by Elia Onofri on 12/10/2020.
//

#include "./utils.h"

int randomWheelSelect(double x, double *P, int nP);

/*
 *	int randomWheelSelect(double x, double *P, int nP)
 *
 *	Given `P` a probability distribution of `nP` elements (`∑p[i] = 1.0`),
 *	 returns the index of the probability `x` belongs (i|p[i-1]<x<p[i]).
 *	If `x > ∑p[i]`, returns `-1`.
 */
int randomWheelSelect(double x, double *P, int nP){
	int i, ans=-1;
	double acc=0;
	
	for (i = 0; i < nP; i++){
		acc += P[i];
		if (x <= acc){
			ans = i;
			break;
		}
	}
	return ans;
}
