
set xlabel "time"
set ylabel "x"
set title "Plot"
set grid

set xzeroaxis lt 7

plot "products/randomWalkData.tsv" u 0:1 w l title "1D-walk"
