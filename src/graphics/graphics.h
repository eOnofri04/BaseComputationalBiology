//
//  graphics.h
//  BaseComputationalBiology
//
//  Created by Elia Onofri on 12/10/2020.
//

#ifndef graphics_h
#define graphics_h

#include "../utils/utils.h"

#define GP_BIN "/usr/local/Cellar/gnuplot/5.2.8/bin/gnuplot"
#define GP_SCRIPTS_FOLDER "gnuplot-scripts/"

// CONSTANTS FILE NAMES
#define HIST_PLOT_GP "hist_plot.gp"
#define HIST_PLOT_PROD "products/hist_data.tsv"
#define XY_PLOT_GP "xy_plot.gp"
#define XY_PLOT_PROD "products/xy_data.tsv"
#define XYE_PLOT_GP "xye_plot.gp"
#define XYE_PLOT_PROD "products/xye_data.tsv"
#define D1_RANDOM_WALK "d1_random_walk.gp"
#define D2_RANDOM_WALK "d2_random_walk.gp"
#define D3_RANDOM_WALK "d3_random_walk.gp"

void gnuplot(char *script_name, char *gpargs);
void plotHistogram(double *a, int np, int nb, char *gpargs);
void plotXY(double *X, double *Y, int n, char *gpargs);
void plotFX(double *Y, int n, char *gpargs);
void plotFXE(double *Y, double *E, int n, char *gpargs);

#endif /* graphics_h */
