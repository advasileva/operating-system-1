#!/bin/bash

for i in `seq 4 $1`
do
    gcc ./$i-points/main.c -o ./$i-points/main.exe
done
for i in `seq 8 9`
do
    gcc ./$i-points/first.c -o ./$i-points/first.exe
    gcc ./$i-points/second.c -o ./$i-points/second.exe
done
echo "Programs compiled"
