set xlabel "turn number [{/Symbol \264}10^4]"
set ylabel "1-S_z [{/Symbol \264}10^-15]"
#set yrange [-0.8:4.5]
#set size 1,1
#set origin 0,0
#set grid
#set key opaque

#set logscale y

# This plots the big plot
plot "spinDataRK4" using (1e15*(1-cos($2)*cos($1))) w l dt 1 lw 2 lc 3 title '{/Symbol d}_E=-5e-4',\
     "spinDataRK4" using (1e15*(1-cos($4)*cos($3))) w l dt 2 lw 4 lc 7 title '{/Symbol d}_E=-4e-4',\
     "spinDataRK4" using (1e15*(1-cos($6)*cos($5))) w l dt 3 lw 4 lc 8 title '{/Symbol d}_E=-3e-4',\
     "spinDataRK4" using (1e15*(1-cos($8)*cos($7))) w l dt 4 lw 3 lc 2 title '{/Symbol d}_E=-2e-4',\
     "spinDataRK4" using (1e15*(1-cos($10)*cos($9))) w l dt 1 lw 2 lc 1 title '{/Symbol d}_E=-1e-4',\
     "spinDataRK4" using (1e15*(1-cos($12)*cos($11))) w l dt 2 lw 4 lc 2 title '{/Symbol d}_E= 0     ',\
     "spinDataRK4" using (1e15*(1-cos($14)*cos($13))) w l dt 3 lw 4 lc 6 title '{/Symbol d}_E= 1e-4',\
     "spinDataRK4" using (1e15*(1-cos($16)*cos($15))) w l dt 4 lw 3 lc 4 title '{/Symbol d}_E= 2e-4',\
     "spinDataRK4" using (1e15*(1-cos($18)*cos($17))) w l dt 1 lw 2 lc 5 title '{/Symbol d}_E= 3e-4',\
     "spinDataRK4" using (1e15*(1-cos($20)*cos($19))) w l dt 2 lw 4 lc 2 title '{/Symbol d}_E= 4e-4',\
     "spinDataRK4" using (1e15*(1-cos($22)*cos($21))) w l dt 3 lw 4 lc 1 title '{/Symbol d}_E= 5e-4
