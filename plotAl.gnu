se term postscript eps enhanced color
se output "Hysteresis.ps"
set key autotitle columnheader
set autoscale xy
set format y "%e"
s=system('head -n 1 Al.txt')
set xlabel word(s,2)
plot "Al.txt" u 2:3 w l #if first number is changed the number in xlabel should be changed accordingly to have a correct label 
