//
//  mutations.c
//  BaseComputationalBiology
//
//  Created by Elia Onofri on 02/12/2020.
//

#include "biology.h"

int punctualMutationInplace(char **geno_ptr, double mutProb);
void subMutationInplace(char *genotype);
char * insMutation(char *genotype);
char * delMutation(char *genotype);

/*
 *	int punctualMutationInplace(char **geno_ptr, double mutProb)
 *
 *	Perform a punctual mutation (ins/del/sub) with probability `mutProb` on the
 *	 specified `genotype`. The mutation is applied in place.
 *	The function returns the increment in length.
 */
int punctualMutationInplace(char **geno_ptr, double mutProb){
	int x;
	char *old = *geno_ptr;
	
	x = drand48() <= mutProb ? rand()%3 : -1;
	switch (x) {
		case -1:
			return 0;
		
		case 0:
			subMutationInplace(*geno_ptr);
			return 0;
			
		case 1:
			*geno_ptr = insMutation(*geno_ptr);
			free(old);
			return +1;
			
		case 2:
			*geno_ptr = delMutation(*geno_ptr);
			free(old);
			return -1;

		default:
			break;
	}
	return 0;
}

/*
 *	void subMutationInplace(char *genotype)
 *
 *	Performs a substitution mutation uniformly at random over the specified
 *	 genotype. Mutation is performed in place.
 */
void subMutationInplace(char *genotype){
	unsigned long len, pos;
	char mut;
	
	len = strlen(genotype);
	pos = rand()%len;
	do{
		mut = nucleotides[rand()%4];
	} while (mut == genotype[pos]);
	genotype[pos] = mut;
	return;
}

/*
 *	char * insMutation(char *genotype)
 *
 *	Performs a insertion mutation uniformly at random over the specified
 *	 `genotype`.
 *	The function returns the new genotype.
 */
char * insMutation(char *genotype){
	unsigned long len, pos, i;
	char *mut;
	
	len = strlen(genotype);
	pos = rand()%len;
	
	mut = allocate(len+2, char);
	if (mut == NULL){
		fprintf(stderr, "ERROR in: insMutation\n");
		fprintf(stderr, "Could not allocate enough memory: %lu chars\n", len + 2);
		exit(-1);
	}
	
	for (i = 0; i < pos; i++) {
		mut[i] = genotype[i];
	}
	mut[pos] = nucleotides[rand()%4];
	for (i = pos; i < len; i++) {
		mut[i+1] = genotype[i];
	}
	mut[len+1] = '\0';
	return mut;
}

/*
 *	char * delMutation(char *genotype)
 *
 *	Performs a deletion mutation uniformly at random over the specified
 *	 `genotype`.
 *	The function returns the new genotype.
 */
char * delMutation(char *genotype){
	unsigned long len, pos, i;
	char *mut;
	
	len = strlen(genotype);
	pos = rand()%len;
	
	mut = allocate(len, char);
	if (mut == NULL){
		fprintf(stderr, "ERROR in: delMutation\n");
		fprintf(stderr, "Could not allocate enough memory: %lu chars\n", len);
		exit(-1);
	}
	
	for (i = 0; i < pos; i++) {
		mut[i] = genotype[i];
	}
	for (i = pos+1; i < len; i++) {
		mut[i-1] = genotype[i];
	}
	mut[len-1] = '\0';
	return mut;
}
