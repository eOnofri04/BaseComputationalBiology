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

#define SEED 1234

int exercise4 ( void ){
	srand(SEED);
	int l = 100, ptr, i;
	char *n, *m, c;
	
	printf("A amminoacids sequence: %s\n", generateAmminoacidSequence(l));
	n = generateNucleotideSequence(l);
	printf("A DNA sequence: %s\n", n);
	m = convertDNA2RNA(n, l);
	printf("A RNA sequence: %s\n", m);
	
	//   ->>>111222<<<---
//	m = "GAUGAUGGUAUAAUGU";
//	l = 16;
	ptr = findStartEncode(m, l);
	printf("Analisys of:\n%s\n", m);
	for (i = 0; i < ptr-3; i++){
		printf(" ");
	}
	printf(">>>");
	c = geneticEnconding(&m[ptr]);
	while (c != '\0'){
		printf(" %c ", c);
		ptr += 3;
		c = geneticEnconding(&m[ptr]);
	}
	printf("<<<\n");
	return 0;
}
