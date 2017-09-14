#!/bin/bash

echo "running tests..."

# setup vars
str="time_val"
n=9500

# clear previous results
> normal_time_results.txt
> tile_time_results.txt


###### time - non tiled ########

# compile
icc exercise1.c -o exercise1 -O3 -D N=$n -D k=100

for i in {1..10} 
do 

  # send stats to output file 
  perf stat -o perf.txt ./exercise1; 

  # parse time value from output file
  str=$(cat perf.txt | grep "seconds time elapsed" | sed  "s/ *//" | sed "s/ seconds.*//")
   
  # append time with trial number to time_results file
  echo "T$i $str" >> normal_time_results.txt

  # log trial number
  echo $i

done

echo ""


###### time - tiled ########

# compile
icc exercise1.c -o exercise1 -O3 -D N=$n -D k=100 -D TILE_MODE

for i in {1..10} 
do 

  # send stats to output file 
  perf stat -o perf.txt ./exercise1; 

  # parse time value from output file
  str=$(cat perf.txt | grep "seconds time elapsed" | sed  "s/ *//" | sed "s/ seconds.*//")
   
  # append time with trial number to time_results file
  echo "T$i $str" >> tile_time_results.txt

  # log trial number
  echo $i

done

echo ""



# log everything
cat normal_time_results.txt
echo ""
cat tile_time_results.txt
echo ""

