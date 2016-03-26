set xlabel "vt"
set ylabel "{/Symbol d}_E"
set grid

# This plots the big plot
plot "sDataRK4" using 1:2 title '{/Symbol d}_E=-5e-4',\
     "sDataRK4" using 3:4 title '{/Symbol d}_E=-4e-4',\
     "sDataRK4" using 5:6 title '{/Symbol d}_E=-3e-4',\
     "sDataRK4" using 7:8 title '{/Symbol d}_E=-2e-4',\
     "sDataRK4" using 9:10 title '{/Symbol d}_E=-1e-4',\
     "sDataRK4" using 11:12 title '{/Symbol d}_E= 0     ',\
     "sDataRK4" using 13:14 title '{/Symbol d}_E= 1e-4',\
     "sDataRK4" using 15:16 title '{/Symbol d}_E= 2e-4',\
     "sDataRK4" using 17:18 title '{/Symbol d}_E= 3e-4',\
     "sDataRK4" using 19:20 title '{/Symbol d}_E= 4e-4',\
     "sDataRK4" using 21:22 title '{/Symbol d}_E= 5e-4',\

#plot "sDataRK4" using 11:12 title '{/Symbol d}_E= 0     ',\
