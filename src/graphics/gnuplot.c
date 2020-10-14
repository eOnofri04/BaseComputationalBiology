//
//  gnuplot.c
//  BaseComputationalBiology
//
//  Created by Elia Onofri on 12/10/2020.
//

#include "./graphics.h"

int plotHistogram(double *a, int n, int nb);



int plotHistogram(double *a, int n, int nb){
	int i, bin;
	double min, max, binsize;
	double *bin_right_end;
	int *qty;
	FILE *fp;
	
	min = a[0];
	max = a[0];
	
	for (i = 1; i < n; i++){
		if (a[i] < min){
			min = a[i];
		} else if (a[i] > max){
			max = a[i];
		}
	}
	
	binsize = (max-min)/nb;
	
	
	bin_right_end = allocate(nb, double);
	if (bin_right_end == NULL){
		printf("Could not allocate enough memory: %d doubles\n", nb);
		return -1;
	}
	
	qty = allocate(nb, int);
	if (qty == NULL){
		printf("Could not allocate enough memory: %d int\n", nb);
		return -1;
	}
	
	bin_right_end[0] = min + binsize;
	qty[0] = 0;
	for (i = 1; i < nb; i++){
		bin_right_end[i] = bin_right_end[i-1] + binsize;
		qty[i] = 0;
	}
	
	for (i = 0; i < n; i++){
		for (bin = 0; bin < nb; bin++){
			if (a[i] <= bin_right_end[bin]){
				qty[bin]++;
				break;
			}
			if (bin == nb-1){
				qty[bin]++;
				//printf("IMPRECISION: righ end is %lf; max should be %lf; value is %lf", bin_right_end[nb-1], max, a[i]);
			}
		}
	}
	
	fp = fopen(HIST_PLOT_PROD, "w");
	if(fp == NULL){
		printf("Could not open file: %s\n", HIST_PLOT_PROD);
		return -2;
	}
	
	for (i = 0; i < nb; i++){
		fprintf(fp, "%lf\t%lf\n", bin_right_end[i] - binsize/2, (double) qty[i]/n);
	}
	
	fclose(fp);
	
	free(bin_right_end);
	free(qty);
	
	gnuplot( HIST_PLOT_GP );
	
	return 0;
}
