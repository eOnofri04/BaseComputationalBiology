//
//  genotype.c
//  BaseComputationalBiology
//
//  Created by Elia Onofri on 04/11/2020.
//

#include "./biology.h"

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

char * generateNucleotideSequence(int n){
	char *s;
	int i;
	s = allocate(n+1, char);
	if (s == NULL){
		printf("Could not allocate enough memory: %d chars\n", n + 1);
		exit(-1);
	}
	for (i = 0; i < n; i++){
		s[i] = nucleotides[rand()%4];
	}
	s[n] = '\0';
	return s;
}

char * generateAmminoacidSequence(int n){
	char *s;
	int i;
	s = allocate(n+1, char);
	if (s == NULL){
		printf("Could not allocate enough memory: %d chars\n", n + 1);
		exit(-1);
	}
	for (i = 0; i < n; i++){
		s[i] = amminoacides[rand()%20];
	}
	s[n] = '\0';
	return s;
}

char * convertDNA2RNA(char *dna, int n){
	char *rna;
	int i;
	int nr;
	nr = min(n, (int) strlen(dna));
	rna = allocate(nr+1, char);
	if (rna == NULL){
		printf("Could not allocate enough memory: %d chars\n", nr + 1);
		exit(-1);
	}
	for (i = 0; i < nr; i++){
		switch (dna[i]) {
			case 'A': rna[i] = 'U'; break;
			case 'T': rna[i] = 'A'; break;
			case 'C': rna[i] = 'G'; break;
			case 'G': rna[i] = 'C'; break;
			default : printf("ERROR: convertDNA2RNA - %d\n", dna[i]); exit(-4);
		}
	}
	rna[nr] = '\0';
	return rna;
}

char geneticEnconding(char *triplet){
	switch (triplet[0]) {
		case 'A':
			switch (triplet[1]) {
				case 'C': return 'U';
				case 'U': return triplet[2]=='G' ? 'M' : 'I';
				case 'A': return triplet[2]=='A'||triplet[2]=='G' ? 'K' : 'N';
				case 'G': return triplet[2]=='A'||triplet[2]=='G' ? 'R' : 'S';
				default : printf("ERROR: geneticEnconding\n"); exit(-3);
			}
		case 'C':
			switch (triplet[1]) {
				case 'C': return 'P';
				case 'G': return 'R';
				case 'U': return 'L';
				case 'A': return triplet[2]=='A'||triplet[2]=='G' ? 'Q' : 'H';
				default : printf("ERROR: geneticEnconding\n"); exit(-3);
			}
			break;
			
		case 'G':
			switch (triplet[1]) {
				case 'C': return 'A';
				case 'G': return 'G';
				case 'U': return 'V';
				case 'A': return triplet[2]=='A'||triplet[2]=='G' ? 'E' : 'D';
				default : printf("ERROR: geneticEnconding\n"); exit(-3);
			}
			break;
			
		case 'U':
			switch (triplet[1]) {
				case 'C': return 'S';
				case 'U': return triplet[2]=='A'||triplet[2]=='G' ? 'L' : 'F';
				case 'A': return triplet[2]=='A'||triplet[2]=='G' ? '\0' : 'Y';
				case 'G': return triplet[2]=='A' ? '\0' : (triplet[2]=='G' ? 'W' : 'C');
				default : printf("ERROR: geneticEnconding\n"); exit(-3);
			}
			break;
		
		default : printf("ERROR: geneticEnconding\n"); exit(-3);
	}
	return 1;
}

/*
 *	int findStartEncode(char *s, int l)
 *
 *	Return the position after the first start codon (AUG/GUG) within `l` in `s`.
 *	If no start codons are found, returns `-1`
 */
int findStartEncode(char *s, int l){
	int i = 0;
	while (i <= l-3){
		if (s[i+1] == 'U'){
			if (s[i+2] == 'G'){
				if (s[i] == 'A' || s[i] == 'G'){
					return i+3;
				} else {
					i += 2;
				}
			} else {
				i += s[i+2] == 'A' ? 2 : 3;
			}
		} else {
			i++;
		}
	}
	
	return -1;
}

/*
 *	int findStopEncode(char *s, int l)
 *
 *	Return the position of the U of first STOP codon (UAG/UGA/UAA) within `l`
 *		chars in `s`.
 *	If no STOP codons are found, returns `-1`
 */
int findStopEncode(char *s, int l){
	int i = 0;
	while (i <= l-3){
		if (s[i] == 'U'){
			if (s[i+1] == 'A'){
				if (s[i+2] == 'A' || s[i+2] == 'G'){
					return i;
				} else {
					i+=2;
				}
			} else if (s[i+1] == 'G'){
				if (s[i+2] == 'A'){
					return i;
				} else {
					i+=2;
				}
			} else {
				i++;
			}
		} else {
			i++;
		}
	}
	
	return -1;
}

/*
 *	int findStopEncodeFromStart(char *s, int l)
 *
 *	Return the position of the U of first STOP codon (UAG/UGA/UAA) within `l`
 *		chars in `s` (by always performing a 3-elements step).
 *	If no STOP codons are found, returns `-1`
 */
int findStopEncodeFromStart(char *s, int l){
	int i;
	for (i=0; i <= l-3; i+=3){
		if (s[i] == 'U'){
			if (s[i+1] == 'A' && (s[i+2] == 'A' || s[i+2] == 'G')) return i;
			else if (s[i+1] == 'G' && s[i+2] == 'A') return i;
		}
	}
	return -1;
}

/*
 *	int findStopEncodeFromStartDNA(char *dna, int l)
 *
 *	Return the position of the A of first STOP codon (ATC/ACT/ATT) within `l`
 *		chars in `dna` (by always performing a 3-elements step).
 *	If no STOP codons are found, returns `-1`
 */
int findStopEncodeFromStartDNA(char *dna, int l){
	int i;
	for (i=0; i <= l-3; i+=3){
		if (dna[i] == 'A'){
			if (dna[i+1] == 'T' && (dna[i+2] == 'T' || dna[i+2] == 'C')) return i;
			else if (dna[i+1] == 'C' && dna[i+2] == 'T') return i;
		}
	}
	return -1;
}

/*
 *	char * encodeSequenceExtended(char *dna, int l)
 *
 *	Returns the fenotype sequence related the DNA sequence `dna` of length `l`.
 *	If the RNA sequence does not contains a proper stop codon, then it returns
 *		NULL. Do note that the fenotype is returned in extended version,
 *		where START and STOP codons are highlighted as ">>>" and "<<<"
 *		respectivelly and padding spaces are present.
 */
char * encodeSequenceExtended(char *dna, int l){
	int i;
	int ptr;
	char *rna;
	char *encode;
	char c;
	
	rna = convertDNA2RNA(dna, l);
	
	encode = callocate(l+1, char);
	if (encode == NULL){
		printf("Could not allocate enough memory: %d chars\n", l + 1);
		exit(-1);
	}
	
	ptr = findStartEncode(rna, l);
	for (i = 0; i < ptr-3; i++){
		encode[i] = ' ';
	}
	encode[i++] = '>';
	encode[i++] = '>';
	encode[i++] = '>';
	c = geneticEnconding(&rna[i]);
	while (c != '\0'){
		encode[i++] = ' ';
		encode[i++] = c;
		encode[i++] = ' ';
		if (i > l - 3){
			free (rna);
			return NULL;
		}
		c = geneticEnconding(&rna[i]);
	}
	encode[i++] = '<';
	encode[i++] = '<';
	encode[i++] = '<';
	while (i < l){
		encode[i++] = ' ';
	}
	encode[l] = '\0';
	
	free(rna);
	
	return encode;
}

/*
 *	int encodeSequence(char *dna, int l, char **encodePtr)
 *
 *	Collects the fenotype related to the DNA sequence `dna` of length `l` in
 *		the `encodePtr` container and return its lenght.
 *	If the RNA sequence does not contains a proper stop codon, then it collects
 *		`NULL` and returns 0.
 */
int encodeSequence(char *dna, int l, char **encodePtr){
	int i;
	int j = 0;
	int n;
	int ptrStart;
	int ptrStop;
	char *rna;
	char *encode;
	
	rna = convertDNA2RNA(dna, l);
	
	ptrStart = findStartEncode(rna, l);
	if (ptrStart == -1){
		free(rna);
		*encodePtr = NULL;
		return 0;
	}
	
	ptrStop  = findStopEncodeFromStart(&rna[ptrStart], l-ptrStart);
	if (ptrStop == -1){
		free(rna);
		*encodePtr = NULL;
		return 0;
	}
	
	n = (ptrStop-ptrStart)/3;
	encode = callocate(n+1, char);
	if (encode == NULL){
		printf("Could not allocate enough memory: %d chars\n", n + 1);
		exit(-1);
	}
	for (i = ptrStart; i < ptrStop; i+=3){
		encode[j++] = geneticEnconding(&rna[i]);
	}
	encode[n] = '\0';
	
	free(rna);
	
	*encodePtr = encode;
	
	return n;
}
