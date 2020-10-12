//
//  gnuplot.c
//  IN470
//
//  Created by Elia Onofri on 12/10/2020.
//

#include "./graphics.h"

void plotHistogram(double *a, int n, int nb);



void plotHistogram(double *a, int n, int nb){
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
	
	
	bin_right_end = (double *) malloc(sizeof(double) * nb);
	qty = (int *) malloc(sizeof(int) * nb);
	
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
	
	for (i = 0; i < nb; i++){
		fprintf(fp, "%lf\t%lf\n", bin_right_end[i] - binsize/2, (double) qty[i]/n);
	}
	
	fclose(fp);
	
	free(bin_right_end);
	free(qty);
	
	gnuplot( HIST_PLOT_GP );
}
