//
//  random.c
//  IN470
//
//  Created by Elia Onofri on 12/10/2020.
//

#include "./utils.h"

int randomWheelSelect(double x, double* P, int nP);

int randomWheelSelect(double x, double* P, int nP){
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
