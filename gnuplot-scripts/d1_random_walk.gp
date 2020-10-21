if (!exists("filename")) filename='products/randomWalkData.tsv'
if (!exists("title")) title='1D Random Walk'
if (!exists("xlabel")) xlabel='time'
if (!exists("ylabel")) ylabel='x'
if (!exists("datatitle")) datatitle='RW'

set xlabel xlabel
set ylabel ylabel
set title title
set grid

set xzeroaxis lt 7

plot filename u 0:1 w l title datatitle
