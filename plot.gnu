se term postscript eps enhanced color
se output "YOverq_0.ps"
set key autotitle columnheader
set autoscale xy
s=system('head -n 1 output.dat')
set xlabel word(s,8)
plot "output.dat" u 8:9 w l #if first number is changed the number in xlabel should be changed accordingly to have a correct label 
