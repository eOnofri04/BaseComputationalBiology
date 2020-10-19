//
//  boyerMoore.c
//  BaseComputationalBiology
//
//  Created by Elia Onofri on 19/10/2020.
//

#include "patternRecognition.h"

int boyerMoore(char *T, int nT, char *P, int nP, int **ans);
int boyerMooreRecursive(char *T, int nT, char *P, int nP, int **ans, int nF, int *g, int *l);
int * badCharacterPrevaluaion(char *P, int nP);
int * goodSuffixPrevaluation(char *P, int nP);

int boyerMoore(char *T, int nT, char *P, int nP, int **ans){
	int *g,		// good suffix array
		*l,		// bad character array
		i,		// pointer to Text
		j,		// pointer to Pattern
		n=0,	// number of matches (to be returned)
		pg,		// numebr of character to be padded according g
		pl;		// numebr of character to be padded according l
	_Bool *idxs;
	idxs = allocate(nT, _Bool);
	if (idxs == NULL){
		printf("Could not allocate enough memory: %d _Bool\n", nT);
		exit(-1);
	}
	g = goodSuffixPrevaluation(P, nP);
	l = badCharacterPrevaluaion(P, nP);
	
	// Matching sequence
	i = 0;
	while (i + nP < nT){
		for (j = nP; j >= 0; j--){
			if (P[j] != T[i + j - 1]){
				break;
			}
		}
		idxs[i] = (j==0);
		// bad character
		// pointer should move of the delta between the first position
		// of character misplaced and the pointer position on the pattern.
		// If padding is negative, then no infos are providden
		pl = l[T[i + j - 1]] - j;
		pl = (pl < 0 ? 1 : pl);
		// good suffix
		pg = l[T[i + j - 1]] - j;
		// best amongst paddings
		i += max(pl, pg);
	}
	
	// Find the exact number of pattern occurences
	for (i = 0; i < nT; i++){
		if (idxs[i]){
			n++;
		}
	}
	// build the answer array
	*ans = allocate(n, int);
	if (ans == NULL){
		printf("Could not allocate enough memory: %d int\n", n);
		exit(-1);
	}
	j = 0;
	for (i = 0; i < nT; i++){
		if (idxs[i]){
			*ans[j] = i;
			j++;
		}
	}
	
	return n;
}

/*
 *	int * badCharacterPrevaluaion(char *P, int nP)
 *
 *	For each char in the alphabet (used as integer), a padding value is
 *  specified in the output array `f` such that `f[c] = max_k {c=P[k]}`.
 */
int * badCharacterPrevaluaion(char *P, int nP){
	int i, *f;
	f = allocate(NCHAR, int);
	if (f == NULL){
		printf("Could not allocate enough memory: %lu int\n", NCHAR);
		exit(-1);
	}
	
	for (i = 0; i < NCHAR; i++){
		f[i] = nP;
	}
	
	for (i = 0; i < nP; i++){
		f[P[i]] = nP - i - 1;
	}
	
	return f;
}

/*
 *	int * goodSuffixPrevaluation(char *P, int nP)
 *
 *	For each position `i` of the Pattern `P`, `f[i] = j` gives the padding
 *	 to be applied in order to move the `P` by preserving `i+1..nP-1` values
 *	 and changing `i`-th element.
 *	In other words `P[i+1..nP-1] = P[i+1-j..nP-1-j]` while `P[i] ≠ P[i-j]`.
 */
int * goodSuffixPrevaluation(char *P, int nP){
	int i, *f;
	//TODO
	return f;
}
