set xlabel "x"
set ylabel "hist(x)"
set title "Plot"
set style fill solid
set yrange [0:1]

plot "products/hist_data.tsv" w boxes
