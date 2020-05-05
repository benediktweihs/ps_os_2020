
#!/bin/bash

#run task2 100 times with input $1 and $2 seconds between
#starting of task2_a and task2_b
echo "Results" > data2.txt
echo "Results" > data1.txt
echo "times" > times2.txt
echo "times" > times1.txt
for i in {1..30}; do
	for j in {1..50}; do
		./task2_a $i >> data2.txt & sleep $1; ./task2_b >> times2.txt
		sleep .01
		echo $i
	done
done

for i in {1..30}; do
	for j in {1..50}; do
		./task1_a $i >> data1.txt & sleep $1; ./task1_b >> times1.txt
		sleep .01
		echo $i
	done
done
