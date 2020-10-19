//
//  randomWalks.h
//  BaseComputationalBiology
//
//  Created by Elia Onofri on 19/10/2020.
//

#ifndef randomWalks_h
#define randomWalks_h

#include "../utils/utils.h"

#define RANDOM_WALK_DATA "products/randomWalkData.tsv"

// from randomWalks.c
void performRandomWalk(int D, int N, char *filename);
double * evaluateRandomWalkDisplacement(int D, int N);

#endif /* randomWalks_h */
