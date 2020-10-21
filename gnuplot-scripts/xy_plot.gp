if (!exists("filename")) filename='products/xy_data.tsv'
if (!exists("title")) title='Plot'
if (!exists("xlabel")) xlabel='x'
if (!exists("ylabel")) ylabel='y'
if (!exists("datatitle")) datatitle=''

set xlabel xlabel
set ylabel ylabel
set title title
set grid

plot filename w l title datatitle
