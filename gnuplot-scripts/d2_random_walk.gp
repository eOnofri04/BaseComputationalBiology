set xlabel "x"
set ylabel "y"
set zlabel "time"
set title "Plot"
set zrange [0:1000]
set grid

set zzeroaxis lt 7

#set arrow from 0,0,0 to 0,0,1000 linecolor "red"


splot "products/randomWalkData.tsv" u 1:2:0 w l
