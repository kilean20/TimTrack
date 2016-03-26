#!/bin/sh


	for INDEX in 1 2 3 4 5 6
	do
		sed -i -e "1d" run.madx
		#echo 'dx='$INDEX'.0e-4; dy='$INDEX'.0e-4;' | cat - run.madx > temp && mv temp run.madx
		echo 'dp='$INDEX'.0e-3;' | cat - run.madx > temp && mv temp run.madx

		madx < run.madx

		cat track.obs0001.p0001 | tail -n +9 | awk '{print $3, "\t", $4}' > xBPM.page$INDEX
		cat track.obs0001.p0001 | tail -n +9 | awk '{print $5, "\t", $6}' > zBPM.page$INDEX
		cat track.obs0001.p0001 | tail -n +9 | awk '{print $7, "\t", $8}' > sBPM.page$INDEX
	done
cat xBPM.page1 xBPM.page2 > xtemp2
cat yBPM.page1 zBPM.page2 > ztemp2
cat sBPM.page1 sBPM.page2 > stemp2
for PAGE in 3 4 5 6
do
	cat xtemp$((PAGE-1)) xBPM.page$PAGE > xtemp$PAGE 
	cat ztemp$((PAGE-1)) zBPM.page$PAGE > ztemp$PAGE 
	cat stemp$((PAGE-1)) sBPM.page$PAGE > stemp$PAGE 
done

mv xtemp6 xDataMad
mv ztemp6 zDataMad
mv stemp6 sDataMad
rm xtemp*
rm ztemp*
rm stemp*
rm xBPM.page*
rm zBPM.page*
rm sBPM.page*
