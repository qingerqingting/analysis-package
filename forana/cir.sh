#!/bin/bash
num=100
while (( $num<=109 ))
do
root rhopi_$num.root
let num+=1
done
