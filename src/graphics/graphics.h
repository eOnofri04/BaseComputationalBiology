//
//  graphics.h
//  BaseComputationalBiology
//
//  Created by Elia Onofri on 12/10/2020.
//

#ifndef graphics_h
#define graphics_h

#include "../utils/utils.h"

#define gnuplot(x) system("/usr/local/Cellar/gnuplot/5.2.8/bin/gnuplot "" -p 'gnuplot-scripts/"x"'")

// CONSTANTS FILE NAMES
#define HIST_PLOT_GP "hist_plot.gp"
#define HIST_PLOT_PROD "products/hist_data.tsv"
#define XY_PLOT_GP "xy_plot.gp"
#define XY_PLOT_PROD "products/xy_data.tsv"
#define D1_RANDOM_WALK "d1_random_walk.gp"
#define D2_RANDOM_WALK "d2_random_walk.gp"

int plotHistogram(double *a, int np, int nb);
int plotXY(double *X, double *Y, int n);
int plotFX(double *Y, int n);

#endif /* graphics_h */
