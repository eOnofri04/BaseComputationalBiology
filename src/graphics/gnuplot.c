//
//  gnuplot.c
//  BaseComputationalBiology
//
//  Created by Elia Onofri on 12/10/2020.
//

#include "./graphics.h"

void gnuplot(char *script_name, char *gpargs);
void plotHistogram(double *a, int n, int nb, char *gpargs);
void plotXY(double *X, double *Y, int n, char *gpargs);
void plotFX(double *Y, int n, char *gpargs);
void plotFXE(double *Y, double *E, int n, char *gpargs);


/*
 *
 *
 *	Evaluates the gnuplot `script` located in GP_SCRIPTS_FOLDER.
 *	Optional argument can be passed via `gpargs`:
 *	 - `title='...'`
 *	 - `filename='...'`
 *	 - `xlabel='...'`
 *	 - `ylabel='...'`
 *	 - `zlabel='...'`
 *	 - `datatitle='...'`
 *	 - `errortitle='...'`
 */
void gnuplot(char *script, char *gpargs){
	// call to binary
	char cmd[511] = GP_BIN;
	// optional arguments ` -e "..."`
	strcat(cmd, " -e \"");
	strcat(cmd, gpargs);
	strcat(cmd, "\"");
	// substain flag ` -p`
	strcat(cmd, " -p");
	// launch script ` '...'`
	strcat(cmd, " '");
	strcat(cmd, GP_SCRIPTS_FOLDER);
	strcat(cmd, script);
	strcat(cmd, "'");
	// command evaluation
	system(cmd);
}

/*
 *	void plotHistogram(double *a, int n, int nb, char *gpargs)
 *
 *	Plots the histogram of the `n` data in `a` by aggregating them in `nb`
 *	 equal bins and saving the data in `HIST_PLOT_PROD`.
 */
void plotHistogram(double *a, int n, int nb, char *gpargs){
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
		exit(-1);
	}
	
	qty = allocate(nb, int);
	if (qty == NULL){
		printf("Could not allocate enough memory: %d int\n", nb);
		exit(-1);
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
		exit(-2);
	}
	
	for (i = 0; i < nb; i++){
		fprintf(fp, "%lf\t%lf\n", bin_right_end[i] - binsize/2, (double) qty[i]/n);
	}
	
	fclose(fp);
	
	free(bin_right_end);
	free(qty);
	
	gnuplot( HIST_PLOT_GP, gpargs );
	
	return ;
}

/*
 *	void plotXY(double *X, double *Y, int n, char *gpargs)
 *
 *	Plots the `n` sample `(X[i], Y[i])` by saving data in `XY_PLOT_PROD`.
 */
void plotXY(double *X, double *Y, int n, char *gpargs){
	int i;
	FILE *fp;
	
	fp = fopen(XY_PLOT_PROD, "w");
	if(fp == NULL){
		printf("Could not open file: %s\n", XY_PLOT_PROD);
		exit(-2);
	}
	
	for (i = 0; i < n; i++){
		fprintf(fp, "%lf\t%lf\n", X[i], Y[i]);
	}
	
	fclose(fp);
	
	gnuplot( XY_PLOT_GP, gpargs );
	
	return ;
}

/*
 *	void plotFX(double *Y, int n, char *gpargs)
 *
 *	Plots the `n` sample `(i, Y[i])` by saving data in `XY_PLOT_PROD`.
 */
void plotFX(double *Y, int n, char *gpargs){
	int i;
	FILE *fp;
	
	fp = fopen(XY_PLOT_PROD, "w");
	if(fp == NULL){
		printf("Could not open file: %s\n", XY_PLOT_PROD);
		exit(-2);
	}
	
	for (i = 0; i < n; i++){
		fprintf(fp, "%lf\t%lf\n", (double) i, Y[i]);
	}
	
	fclose(fp);
	
	gnuplot( XY_PLOT_GP, gpargs );
	
	return ;
}

/*
 *	void plotFXE(double *Y, double *E, int n, char *gpargs)
 *
 *	Plots the `n` sample `(i, Y[i])` and the errors specified in `E`
 *	 by saving data in `XYE_PLOT_PROD`.
 */
void plotFXE(double *Y, double *E, int n, char *gpargs){
	int i;
	FILE *fp;
	
	fp = fopen(XYE_PLOT_PROD, "w");
	if(fp == NULL){
		printf("Could not open file: %s\n", XYE_PLOT_PROD);
		exit(-2);
	}
	
	for (i = 0; i < n; i++){
		fprintf(fp, "%lf\t%lf\t%lf\n", (double) i, Y[i], E[i]);
	}
	
	fclose(fp);
	
	gnuplot( XYE_PLOT_GP, gpargs );
	
	return ;
}
