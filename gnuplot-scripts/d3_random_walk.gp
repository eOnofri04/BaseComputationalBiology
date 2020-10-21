if (!exists("filename")) filename='products/randomWalkData.tsv'
if (!exists("title")) title='3D Random Walk'
if (!exists("xlabel")) xlabel='x'
if (!exists("ylabel")) ylabel='y'
if (!exists("zlabel")) zlabel='z'
if (!exists("datatitle")) datatitle='RW'

set xlabel xlabel
set ylabel ylabel
set zlabel zlabel
set title title
set grid

set xzeroaxis lt 5
set yzeroaxis lt 6
set zzeroaxis lt 7

splot filename u 1:2:3 w l title datatitle
