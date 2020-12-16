//
//  scoreFunctions.c
//  BaseComputationalBiology
//
//  Created by Elia Onofri on 25/11/2020.
//

#include "biology.h"

double maxLysin(char *fenotype, int n);
double maxLysinPercentage(char *fenotype, int n);
double maxLysinPercentageAndLength(char *fenotype, int n, int maxlen, double alpha);

double maxLysin(char *fenotype, int n){
	int counter = 0;
	for (int i = 0; i < n; i++) counter += (fenotype[i] == 'L') ? 1 : 0;
	return counter;
}

double maxLysinPercentage(char *fenotype, int n){
	int counter = 0;
	for (int i = 0; i < n; i++) counter += (fenotype[i] == 'L') ? 1 : 0;
	return (double) counter / n;
}

double maxLysinPercentageAndLength(char *fenotype, int n, int maxlen, double alpha){
	int counter = 0;
	for (int i = 0; i < n; i++) counter += (fenotype[i] == 'L') ? 1 : 0;
	return (1-alpha) * n / maxlen + alpha * counter / n;
}
