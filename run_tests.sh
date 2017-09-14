#!/bin/bash

echo "running tests..."

# setup vars
str="time_val"
n=9500			# array size
k_start=100		# tile size start
k_end=300		# tile size end
k_inc=50		# tile increment amount
epochs=3		# tests per tile size

# clear previous results
> normal_time_results.txt
> tile_time_results.txt


###### time - non tiled ########

echo "time - non tiled"

# compile
icc exercise1.c -o exercise1 -O3 -D N=$n -D k=100

for ((i=0; i<epochs; i++))
do 

  # send stats to output file 
  perf stat -o perf.txt ./exercise1; 

  # parse time value from output file
  str=$(cat perf.txt | grep "seconds time elapsed" | sed  "s/ *//" | sed "s/ seconds.*//")
   
  # append time with trial number to time_results file
  echo -n "$str, " >> normal_time_results.txt

  # log trial number
  echo $i

done

echo ""


###### time - tiled ########

echo "time - tiled"

for ((j=k_start; j<=k_end; j+=k_inc))
do

	# compile
	icc exercise1.c -o exercise1 -O3 -D N=$n -D k=$j -D TILE_MODE

	# append tile size to time_results file
	echo -n "$j, " >> tile_time_results.txt
	
	for ((i=0; i<epochs; i++))
	do 

	  # send stats to output file 
	  perf stat -o perf.txt ./exercise1; 

	  # parse time value from output file
	  str=$(cat perf.txt | grep "seconds time elapsed" | sed  "s/ *//" | sed "s/ seconds.*//")
	   
	  # append time with trial number to time_results file
	  echo -n "$str, " >> tile_time_results.txt

	  # log trial number
	  echo $i

	done

done
	
echo ""



# log everything
cat normal_time_results.txt
echo ""
cat tile_time_results.txt
echo ""

