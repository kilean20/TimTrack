#!/usr/bin/gnuplot

set xlabel "x"
set ylabel "p_x"

plot "xDataMadX" title 'horizontal phase-space' with points pt 3
set terminal pngcairo size 350,262 enhanced font 'Verdana,10'
set output 'xDataMadX.png'
plot "xDataMadX" title 'horizontal phase-space' with points pt 3

set xlabel "v_0 t"
set ylabel "{/Symbol d}_0"
set output 'sDataMadX.png'
plot "sDataMadX" title 'Synchro-Phase-Space' 

