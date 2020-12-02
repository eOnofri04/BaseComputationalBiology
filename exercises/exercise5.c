//
//  exercise5.c
//  BaseComputationalBiology
//
//  Created by Elia Onofri on 18/11/2020.
//

/* *****************************************************************************
 *	Perform an evolutionary simulation on random population of `POP_N` entities
 *
 *	Generate `POP_N` random genotypes of length `START_LEN` and append START
 *		codon at the beginning and STOP condon at the end.
 *		Make sure no STOP codons are present in between.
 *		These are the initial population.
 *	Repeat the following steps SIM_STEP times:
 *	- Mutate each genotype with a punctual mutation (ins-del-sub)
 *		in a random location evenly distributed betwen [3..l-4] (not in first)
 *	- Translate to RNA each genotype
 *	- Encode fenotype for each RNA
 *	- Kill any fenotype with length < MIN_LEN
 *	- Apply a score function to each fenotype
 *	- Normalize the scores as a probability distribution `Preproduce`
 *	- Reproduce `POP_N` entities population by randomly sampling between mutated
 *		genotypes with probabilities given from `Preproduce`
 **************************************************************************** */

#include "./exercise.h"

#define SIM_STEP  10 // living time of the simulations
#define START_LEN 60   // initial length of nucleotides + START & STOP codons
#define MIN_LEN   10   // minimum number of protein
#define POP_N     100  // entities number within the population
#define SEED      1234
#define SCORES_FILENAME "products/scores_simulation.tsv"

int exercise5(double (*score)(char *, int)){
	char *genotypes[POP_N];
	char *nextgenos[POP_N];
	char *fenotype;
	int i;
	int t;
	int len;
	int select;
	double Preproduce[POP_N];
	FILE *fp;
	
	srand48(SEED);
	
	// Population generation
	for (i = 0; i < POP_N; i++){
		len = START_LEN;
		do {
			genotypes[i] = generateNucleotideSequence(len);
		} while (findStopEncodeFromStartDNA(&genotypes[i][3], len - 3) != -1);
		// Prepend START codon (AUG RNA)
		genotypes[i][0] = 'T';
		genotypes[i][1] = 'A';
		genotypes[i][2] = 'C';
		// Append STOP codon (UGA RNA)
		genotypes[i][len-3] = 'A';
		genotypes[i][len-2] = 'C';
		genotypes[i][len-1] = 'T';
	}
	
	fp = fopen(SCORES_FILENAME, "w");
	
	for (t = 0; t < SIM_STEP; t++){
		// Mutate (not first step) & evaluare score
		for (i = 0; i < POP_N; i++){
			if (t > 0){
				// mutation
				punctualMutationInplace(&(genotypes[i]), 0.5);
			}
			len = encodeSequence(genotypes[i], (int) strlen(genotypes[i]), &fenotype);
			Preproduce[i] = (len < MIN_LEN) ? 0 : score(fenotype, len);
			fprintf(fp, "%lf\t", Preproduce[i]);
			free(fenotype);
		}
		fprintf(fp, "\n");
		// Normalise the score
		normalizeInPlace(Preproduce, POP_N);
		// Generate next population
		for (i = 0; i < POP_N; i++){
			select = randomWheelSelect(drand48(), Preproduce, POP_N);
			nextgenos[i] = strdup(genotypes[select]);
		}
		// Update current population to next population
		for (i = 0; i < POP_N; i++){
			free(genotypes[i]);
			genotypes[i] = nextgenos[i];
		}
		
	}
	
	for (i = 0; i < POP_N; i++){
		free(genotypes[i]);
	}
	
	fclose(fp);
	
	return 0;
}
