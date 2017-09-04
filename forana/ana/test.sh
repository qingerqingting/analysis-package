#!/bin/bash
NTOT=20
for((i=1;i<$((NTOT+1));i++))
do
	#TMP_MYNUM=$((i+10000))
	#MYNUM=`echo $TMP_MYNUM |cut -c 3-6`
	#echo $i $MYNUM
	#FNAMEp mccir.sh
         x=`tail -4 ana_$i.txt.bosslog |head -1|awk '{print $3}'| cut -c 5-7` 
        #x=`tail -4 ana_$MYNUM.txt.bosslog |head -1|awk '{print $3}'` 
	let sum+=$x
        echo $i $MYNUM $x $sum
done
