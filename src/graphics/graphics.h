//
//  graphics.h
//  IN470
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


void plotHistogram(double *a, int np, int nb);

#endif /* graphics_h */
