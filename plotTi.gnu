se term postscript eps enhanced color
se output "HysteresisTi.ps"
set key autotitle columnheader
set autoscale xy
set format y "%e"
s=system('head -n 1 Ti.txt')
set xlabel word(s,2)
plot "Ti.txt" u 2:3 w l #if first number is changed the number in xlabel should be changed accordingly to have a correct label 
