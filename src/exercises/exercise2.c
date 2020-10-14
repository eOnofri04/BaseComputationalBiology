//
//  exercise.c
//  BaseComputationalBiology
//
//  Created by Elia Onofri on 14/10/2020.
//

#include "exercise.h"

#define filename "inputs/exercise2/text.txt"

int exercise2(){
	int i;
	char cset[26] =  {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	double *freqUL = NULL, *freqL = NULL, accUL=0, accL=0;
	evalFileAlphabethFrequency(filename, &freqUL);
	evalFileFrequencyFromSet(filename, &freqL, cset, 26);
	for (i = 0; i < 26; i++){
		printf("%c/%c: %lf - %lf :%c\n", i+65, i+97, freqUL[i], freqL[i], cset[i]);
		accUL+=freqUL[i];
		accL+=freqL[i];
	}
	printf("\nULcase sum: %lf - %lf :mus esac L\n\n", accUL, accL);
	
	return 0;
}
