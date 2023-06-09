#!/bin/bash

for i in `seq 4 $1`
do
    echo "Program for $i points"
    for j in `seq 1 $2`
    do
        echo "Test $j"
        ./$i-points/main.exe tests/test$j.in $i-points/test$j.out
        chmod -R +xr $i-points/test$j.out
        diff tests/test$j.out $i-points/test$j.out
    done
    echo
done
for i in `seq 8 9`
do
    echo "Program for $i points"
    for j in `seq 1 $2`
    do
        echo "Test $j"
        ./$i-points/first.exe tests/test$j.in $i-points/test$j.out & ./$i-points/second.exe
        chmod -R +xr $i-points/test$j.out
        diff tests/test$j.out $i-points/test$j.out
    done
    echo
done
echo "Programs finished"
