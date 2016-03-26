#!/bin/bash		

sed -i -e "1d" run.madx
		echo 'dx=0;' | cat - run.madx > temp && mv temp run.madx

		madx < run.madx

		cat track.obs0001.p0001 | tail -n +9 | awk '{print $3, "\t", $4}' > xDataMadX
		cat track.obs0001.p0001 | tail -n +9 | awk '{print $7, "\t", $8}' > sDataMadX
