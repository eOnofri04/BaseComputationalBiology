//
//  exercise4.c
//  BaseComputationalBiology
//
//  Created by Elia Onofri on 21/10/2020.
//

/* *****************************************************************************
 *	Reppresent nucleotides as strings
 *	- Generate random genotypes of arbitrary length;
 *	- Genetic code implementation
 *	 - START and STOP codons
 *	- Protein encoding (genotype > phenotype)
 *	 - String representation as amminoacids
 *	 – reading frame & nucleotides sequences
 *	- generation of genotypes and its translations.
 **************************************************************************** */

#include "./exercise.h"

#define SEED (long)1234

int exercise4 ( void ){
	srand(SEED);
	int l = 100, ptr, i;
	char *n, *m, c;
	
	fprintf(stdout, "-------------------------------------\n");
	fprintf(stdout, "Parameters are:\n");
	fprintf(stdout, " - Simulation seed: %lu\n", SEED);
	fprintf(stdout, "-------------------------------------\n");
	
	fprintf(stdout, "A amminoacids sequence: %s\n", generateAmminoacidSequence(l));
	n = generateNucleotideSequence(l);
	fprintf(stdout, "A DNA sequence: %s\n", n);
	m = convertDNA2RNA(n, l);
	fprintf(stdout, "A RNA sequence: %s\n", m);
	
	//   ->>>111222<<<---
//	m = "GAUGAUGGUAUAAUGU";
//	l = 16;
	ptr = findStartEncode(m, l);
	fprintf(stdout, "Analisys of:\n%s\n", m);
	for (i = 0; i < ptr-3; i++){
		fprintf(stdout, " ");
	}
	fprintf(stdout, ">>>");
	c = geneticEnconding(&m[ptr]);
	while (c != '\0'){
		fprintf(stdout, " %c ", c);
		ptr += 3;
		c = geneticEnconding(&m[ptr]);
	}
	fprintf(stdout, "<<<\n");
	return 0;
}
