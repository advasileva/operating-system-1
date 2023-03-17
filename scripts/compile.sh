#!/bin/bash

for i in `seq 4 $1`
do
    gcc ./$i-points/main.c -o ./$i-points/main.exe
done
gcc ./8-points/first.c -o ./8-points/first.exe
gcc ./8-points/second.c -o ./8-points/second.exe
echo "Programs compiled"
