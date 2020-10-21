if (!exists("filename")) filename='products/xye_data.tsv'
if (!exists("title")) title='Plot'
if (!exists("xlabel")) xlabel='x'
if (!exists("ylabel")) ylabel='y'
if (!exists("datatitle")) datatitle='data'
if (!exists("errortitle")) errortitle='error bars'

set xlabel xlabel
set ylabel ylabel
set title title
set grid

plot filename u 1:2:3 w e title errortitle,\
	 "" u 1:2 w l title datatitle
