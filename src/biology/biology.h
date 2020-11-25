//
//  biology.h
//  BaseComputationalBiology
//
//  Created by Elia Onofri on 04/11/2020.
//

#ifndef biology_h
#define biology_h

#include "../utils/utils.h"

// from biology.c
#define amminoacides "ACDEFGHIKLMNPQRSTVWY"
#define nucleotides "ACGT"
char * generateNucleotideSequence(int n);
char * generateAmminoacidSequence(int n);
char * convertDNA2RNA(char *dna, int n);
char geneticEnconding(char *triplet);
int findStartEncode(char *rna, int l);
int findStopEncode(char *rna, int l);
int findStopEncodeFromStart(char *rna, int l);
int findStopEncodeFromStartDNA(char *dna, int l);
char * encodeSequenceExtended(char *s, int l);
int encodeSequence(char *dna, int l, char **encodePtr);

// from scoreFunctions.c
double maxLysin(char *fenotype, int n);

#endif /* biology_h */
