#!/bin/bash
sum=0
i=1
while [[ $i -le 20 ]]
do 
x=`tail -4 ana_$i.txt.bosslog |head -1|awk '{print $3}'`
let i=$i+1
#let sum+=$x
echo $i $x  
#done
done
