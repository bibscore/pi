#!/bin/bash

gcc -o pi_serial.out pi_serial.c -lm

for i in $(seq 1 40)
do
    (time -p ./pi_serial.out) |& awk '$1 == "real" {print $2}' | tee -a serialtime.txt
done

gcc -o pi_parallel.out pi_parallel.c -lm -fopenmp

for i in $(seq 1 40)
do
    (time -p ./pi_parallel.out) |& awk '$1 == "real" {print $2}' | tee -a paralleltime.txt
done