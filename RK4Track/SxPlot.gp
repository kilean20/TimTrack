set xlabel "turn number [{/Symbol \264}10^4]"
set ylabel "S_x  [{/Symbol \264}10^{-8}]"
#set yrange [-0.8:4.5]
#set size 1,1
#set origin 0,0
#set grid
#set key opaque

# This plots the big plot
plot "spinDataRK4" using (cos($2)*sin($1)*1e8) w l dt 1 lw 2 lc 3 title '{/Symbol d}_E=-5e-4',\
     "spinDataRK4" using (cos($4)*sin($3)*1e8) w l dt 2 lw 4 lc 7 title '{/Symbol d}_E=-4e-4',\
     "spinDataRK4" using (cos($6)*sin($5)*1e8) w l dt 3 lw 4 lc 8 title '{/Symbol d}_E=-3e-4',\
     "spinDataRK4" using (cos($8)*sin($7)*1e8) w l dt 4 lw 3 lc 2 title '{/Symbol d}_E=-2e-4',\
     "spinDataRK4" using (cos($10)*sin($9)*1e8) w l dt 1 lw 2 lc 1 title '{/Symbol d}_E=-1e-4',\
     "spinDataRK4" using (cos($12)*sin($11)*1e8) w l dt 2 lw 4 lc 2 title '{/Symbol d}_E= 0     ',\
     "spinDataRK4" using (cos($14)*sin($13)*1e8) w l dt 3 lw 4 lc 6 title '{/Symbol d}_E= 1e-4',\
     "spinDataRK4" using (cos($16)*sin($15)*1e8) w l dt 4 lw 3 lc 4 title '{/Symbol d}_E= 2e-4',\
     "spinDataRK4" using (cos($18)*sin($17)*1e8) w l dt 1 lw 2 lc 5 title '{/Symbol d}_E= 3e-4',\
     "spinDataRK4" using (cos($20)*sin($19)*1e8) w l dt 2 lw 4 lc 2 title '{/Symbol d}_E= 4e-4',\
     "spinDataRK4" using (cos($22)*sin($21)*1e8) w l dt 3 lw 4 lc 1 title '{/Symbol d}_E= 5e-4
