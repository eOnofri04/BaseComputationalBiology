//
//  main.c
//  BaseComputationalBiology
//
//  Created by Elia Onofri on 19/10/2020.
//

#include "./exercise.h"
#include "../src/utils/utils.h"

int main( void ){
	int ans;
	clock_t start, stop;
	fprintf(stdout, "Start computation...\n");
	start = clock();
	ans = exercise5(&maxLysinPercentageAndLength);
	stop = clock();
	fprintf(stdout, "Computation terminate with code %d\n", ans);
	fprintf(stdout, "Elapsed time: %lf seconds\n\n", 1.*(stop - start)/CLOCKS_PER_SEC);
}
