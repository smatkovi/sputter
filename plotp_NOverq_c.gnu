se term postscript eps enhanced color
se output "p_NOverq_c.ps"
set key autotitle columnheader
set autoscale xy
set format y "%e"
s=system('head -n 1 output.dat')
set xlabel word(s,6)
plot "output.dat" u 6:1 w l #if first number is changed the number in xlabel should be changed accordingly to have a correct label 
