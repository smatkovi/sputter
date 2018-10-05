se term postscript eps enhanced color
se output "p_NOverY.ps"
set key autotitle columnheader
set autoscale xy
set format y "%e"
s=system('head -n 1 output.dat')
set xlabel word(s,9)
plot "output.dat" u 9:1 w l #if first number is changed the number in xlabel should be changed accordingly to have a correct label 
