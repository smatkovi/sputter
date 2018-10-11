se term postscript eps enhanced color
se output "HysteresisVan.ps"
set key autotitle columnheader
set autoscale xy
set format y "%e"
s=system('head -n 1 Van.txt')
set xlabel word(s,5)
plot "Van.txt" u 5:3 w l #if first number is changed the number in xlabel should be changed accordingly to have a correct label 
