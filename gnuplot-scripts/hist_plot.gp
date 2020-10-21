if (!exists("filename")) filename='products/hist_data.tsv'
if (!exists("title")) title='Histogram'
if (!exists("xlabel")) xlabel='x'
if (!exists("ylabel")) ylabel='hist(x)'
if (!exists("datatitle")) datatitle=''

set xlabel xlabel
set ylabel ylabel
set title title

set style fill solid
set yrange [0:1]

plot filename w boxes title datatitle
