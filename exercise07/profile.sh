#!/bin/bash
#run program $1 100 times

#save data in file name:
name="times"$1".txt"
#delete content of file
echo "Times" > $name

for j in {1..10}; do
  start=`date +%s%N`
  for i in {1..10}; do
    ./$1 >> sredirectOutput.txt
  done
  end=`date +%s%N`
  echo `expr $end - $start` >> $name
  echo $j" of 50"
done