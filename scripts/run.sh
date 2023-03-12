#!/bin/bash

for i in `seq 4 $1`
do
    for j in `seq 1 $2`
    do
        ./$i-points/main.exe tests/test$j.in $i-points/test$j.out
    done
done
echo "Programs run"
