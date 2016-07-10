set terminal png
set output 'pidr.png'

set key autotitle columnhead

num_columns = system('cat '.infile.' | awk "{ print NF }"')

plot for [i=1:num_columns-1] infile using 1:i+1 with lines

