#!/bin/bash
num=1
while (( $num <= 20 ))
do
tail -10 jobOptions_ana_$num.txt.bosslog >> result.txt
let num+=1
done
