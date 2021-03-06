if (!exists("filename")) filename='products/randomWalkData.tsv'
if (!exists("title")) title='2D Random Walk'
if (!exists("xlabel")) xlabel='x'
if (!exists("ylabel")) ylabel='y'
if (!exists("zlabel")) zlabel='time'
if (!exists("datatitle")) datatitle='RW'

set xlabel xlabel
set ylabel ylabel
set zlabel zlabel
set title title
set grid

set zzeroaxis lt 7

#set arrow from 0,0,0 to 0,0,1000 linecolor "red"

splot filename u 1:2:0 w l title datatitle
