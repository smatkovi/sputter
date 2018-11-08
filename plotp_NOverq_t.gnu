se term postscript eps enhanced color
se output "p_NOverq_t.ps"
set key autotitle columnheader
set autoscale xy
set format y "%e"
s=system('head -n 1 output.dat')
set xlabel word(s,5)
plot "output.dat" u 5:1 w l #if first number is changed the number in xlabel should be changed accordingly to have a correct label 
