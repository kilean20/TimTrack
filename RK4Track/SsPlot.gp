set xlabel "turn number [{/Symbol \264}10^4]"
set ylabel "S_s  [{/Symbol \264}10^{-8}]"
#set yrange [-0.8:4.5]
#set size 1,1
#set origin 0,0
#set grid
#set key opaque

# This plots the big plot
plot "spinDataRK4" using (sin($2)*1e8) w l dt 1 lw 2 lc 3 title '{/Symbol d}_E=-5e-4',\
     "spinDataRK4" using (sin($4)*1e8) w l dt 2 lw 4 lc 7 title '{/Symbol d}_E=-4e-4',\
     "spinDataRK4" using (sin($6)*1e8) w l dt 3 lw 4 lc 8 title '{/Symbol d}_E=-3e-4',\
     "spinDataRK4" using (sin($8)*1e8) w l dt 4 lw 3 lc 2 title '{/Symbol d}_E=-2e-4',\
     "spinDataRK4" using (sin($10)*1e8) w l dt 1 lw 2 lc 1 title '{/Symbol d}_E=-1e-4',\
     "spinDataRK4" using (sin($12)*1e8) w l dt 2 lw 4 lc 2 title '{/Symbol d}_E= 0     ',\
     "spinDataRK4" using (sin($14)*1e8) w l dt 3 lw 4 lc 6 title '{/Symbol d}_E= 1e-4',\
     "spinDataRK4" using (sin($16)*1e8) w l dt 4 lw 3 lc 4 title '{/Symbol d}_E= 2e-4',\
     "spinDataRK4" using (sin($18)*1e8) w l dt 1 lw 2 lc 5 title '{/Symbol d}_E= 3e-4',\
     "spinDataRK4" using (sin($20)*1e8) w l dt 2 lw 4 lc 2 title '{/Symbol d}_E= 4e-4',\
     "spinDataRK4" using (sin($22)*1e8) w l dt 3 lw 4 lc 1 title '{/Symbol d}_E= 5e-4
