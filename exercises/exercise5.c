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
 *	- Apply a score function to each fenotype (given as an input)
 *	- Normalize the scores as a probability distribution `Preproduce`
 *	- Reproduce `POP_N` entities population by randomly sampling between mutated
 *		genotypes with probabilities given from `Preproduce`
 *
 *	Extract and plot the following statistics in term of simulation steps
 *	- Average score function
 *	- Average length of the fenotype
 *	- True diversity index
 *	- Shannon diversity index
 *
 **************************************************************************** */

#include "./exercise.h"

#define SIM_STEP  10000// living time of the simulations
#define START_LEN 60   // initial length of nucleotides + START & STOP codons
#define MUT_PROB  0.2  // probability in having a punctual mutation
#define MIN_LEN   10   // minimum number of protein
#define POP_N     250  // entities number within the population
#define ALPHA     0.75 // balanceness in score function
#define Q         3    // true diversity index parameter
#define SEED      (long) 1234
//#define SEED      (unsigned) time(NULL)
#define AVGSCORES_FILENAME "products/avg_scores_simulation.tsv"
#define TRUEDIV_FILENAME   "products/true_diversity_simulation.tsv"
#define SHANNON_FILENAME   "products/shannon_simulation.tsv"
#define AVGLEN_FILENAME    "products/avg_len_simulation.tsv"
#define SCORES_FILENAME    "products/scores_simulation.tsv"

int exercise5(double (*score)(char *, int, int, double)){
	char *genotypes[POP_N];
	char *nextgenos[POP_N];
	char *binFenotype[POP_N];
	char *fenotype;
	int i;
	int j; // iterator over freqGenotype
	int maxj;
	int t;
	int len;
	int select;
	int maxlen; // accumulator to deduce the maximum length in the future round
	int maxlenprev = START_LEN/3; // max lenght is prevaluated from the previous round
	int onePercent = SIM_STEP/100;
	double avglen;
	double avgscore;
	double Preproduce[POP_N];
	double freqFenotypes[POP_N];
	FILE *fp, *fp_avg_len, *fp_avg_score, *fp_shannon, *fp_truediv;
	
	fprintf(stdout, "-------------------------------------\n");
	fprintf(stdout, "Parameters are:\n");
	fprintf(stdout, " - Number of simulation steps: %d\n", SIM_STEP);
	fprintf(stdout, " - Initial nucleotides length: %d\n", START_LEN);
	fprintf(stdout, " - Minimum number of proteins: %d\n", MIN_LEN);
	fprintf(stdout, " - Score alpha parameter: %lf\n", ALPHA);
	fprintf(stdout, " - Mutation probability: %lf\n", MUT_PROB);
	fprintf(stdout, " - True diversity index: %d\n", Q);
	fprintf(stdout, " - Population size: %d\n", POP_N);
	fprintf(stdout, " - Simulation seed: %lu\n", SEED);
	fprintf(stdout, "-------------------------------------\n");
	
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
	
	// statistics files
	fp = fopen(SCORES_FILENAME, "w");
	fp_avg_len = fopen(AVGLEN_FILENAME, "w");
	fp_avg_score = fopen(AVGSCORES_FILENAME, "w");
	fp_truediv = fopen(TRUEDIV_FILENAME, "w");
	fp_shannon = fopen(SHANNON_FILENAME, "w");
	if (fp == NULL){
		fprintf(stderr, "Could not open file: %s\n", SCORES_FILENAME);
		exit(-2);
	}
	if (fp_avg_len == NULL){
		fprintf(stderr, "Could not open file: %s\n", AVGLEN_FILENAME);
		exit(-2);
	}
	if (fp_avg_score == NULL){
		fprintf(stderr, "Could not open file: %s\n", AVGSCORES_FILENAME);
		exit(-2);
	}
	if (fp_truediv == NULL){
		fprintf(stderr, "Could not open file: %s\n", TRUEDIV_FILENAME);
		exit(-2);
	}
	if (fp_shannon == NULL){
		fprintf(stderr, "Could not open file: %s\n", SHANNON_FILENAME);
		exit(-2);
	}
	
	// begin simulation
	for (t = 0; t < SIM_STEP; t++){
		
		// completion print
		if (t % onePercent == 0){
			fprintf(stdout, "\r%d%%", t/onePercent);
			fflush(stdout);
		}
		
		// initialization statistics parameters
		avglen = 0;
		avgscore = 0;
		maxj = 0;
		for (j = 0; j < POP_N; j++){
			freqFenotypes[j] = 0;
			binFenotype[j] = NULL;
		}
		
		// extract statistics on current population
		for (i = 0; i < POP_N; i++){
			len = encodeSequence(genotypes[i], (int) strlen(genotypes[i]), &fenotype);
			
			// average accumulators incrementation
			avglen += len;
			avgscore += score(fenotype, len, maxlenprev, ALPHA);
			
			// frequences evaluations
			for (j = 0; j < maxj; j++){
				if (strcmp(binFenotype[j], fenotype) == 0){
					freqFenotypes[j]++;
					break;
				}
			}
			if (j == maxj){
				binFenotype[maxj] = callocate(len+1, char);
				if (binFenotype[maxj] == NULL){
					fprintf(stderr, "ERROR in: binFenotype[maxj] allocation.\n");
					fprintf(stderr, "Could not allocate enough memory: %d char\n", len+1);
					exit(-1);
				}
				/*
				 for (j = 0; j <= len; j++){
					binFenotype[maxj][j] = fenotype[j];
				}
				 */
				strcpy(binFenotype[maxj], fenotype);
				freqFenotypes[maxj] = 1;
				maxj++;
			}
			
			free(fenotype);
		}
		
		avglen /= POP_N;
		fprintf(fp_avg_len, "%d\t%lf\n", t, avglen);
		
		avgscore /= POP_N;
		fprintf(fp_avg_score, "%d\t%lf\n", t, avgscore);
		
		for (j = 0; j < maxj; j++){
			freqFenotypes[j] /= POP_N;
		}
		
		fprintf(fp_truediv, "%d\t%lf\n", t, trueDiversity(freqFenotypes, maxj, Q));
		fprintf(fp_shannon, "%d\t%lf\n", t, shannonEntropy(freqFenotypes, maxj));
		
		maxlen = 0;
		
		// Mutate (not first step) & evaluare score
		for (i = 0; i < POP_N; i++){
			if (t > 0){
				// mutation
				punctualMutationInplace(&(genotypes[i]), MUT_PROB);
			}
			len = encodeSequence(genotypes[i], (int) strlen(genotypes[i]), &fenotype);
			Preproduce[i] = (len < MIN_LEN) ? 0 : score(fenotype, len, maxlenprev+1, ALPHA);
			
			maxlen = max(len, maxlen);
			fprintf(fp, "%lf\t", Preproduce[i]);
			
			free(fenotype);
		}
		
		maxlenprev = maxlen;
		
		fprintf(fp, "\n");
		// Normalise the score
		normalizeInPlace(Preproduce, POP_N);
		// Generate next population
		for (i = 0; i < POP_N; i++){
			double x = drand48();
			select = randomWheelSelect(x, Preproduce, POP_N);
			if (select == -1){
				double acc = 0;
				for (i = 0; i < POP_N; i++){
					acc += Preproduce[i];
				}
				fprintf(stderr, "\nERROR in: generate next population step\n");
				fprintf(stderr, "Accumulator is: %1.20lf\n", acc);
				fprintf(stderr, "selected value is: %1.20lf\n", x);
				exit(10);
			}
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
	fclose(fp_avg_len);
	fclose(fp_avg_score);
	fclose(fp_truediv);
	fclose(fp_shannon);
	
	gnuplot( XY_PLOT_GP, "filename='"AVGSCORES_FILENAME"'; title='Data Fitness on Score Function'; datatitle='avg fenotype'; xlabel='t'; ylabel='score'");
	gnuplot( XY_PLOT_GP, "filename='"AVGLEN_FILENAME"'; title='Fenotype Length'; datatitle='avg fenotype'; xlabel='t'; ylabel='no. amminoacids'");
	gnuplot( XY_PLOT_GP, "filename='"TRUEDIV_FILENAME"'; title='True Diversity Index'; datatitle='data'; xlabel='t'; ylabel='diversity index'");
	gnuplot( XY_PLOT_GP, "filename='"SHANNON_FILENAME"'; title='Shannon Entropy Index'; datatitle='data'; xlabel='t'; ylabel='diversity index'");
	
	return 0;
}
