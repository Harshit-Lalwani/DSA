#!/bin/bash

# Compile the programs
gcc q1.c -o q1
gcc q1_shreyas.c -o q1_shreyas

# Function to generate a random number within a range
function random_number {
    shuf -i $1-$2 -n 1
}

# Test the programs with random test cases
for ((i=1; i<=100; i++))
do
    # Generate random test case
    n=$(random_number 1 1000) # Reduced from 200000
    k=$(random_number 1 1000) # Reduced from 1000000000
    d=$(random_number 1 1000) # Reduced from 1000000000
    p=$(random_number 1 1000) # Reduced from 1000000000
    echo $n $k $d $p > input.txt
    for ((j=1; j<=n; j++))
    do
        depth=$(random_number 1 $((d-1)))
        time=$(random_number 1 1000) # Reduced from 1000000000
        echo $depth >> input.txt
    done
    for ((j=1; j<=n; j++))
    do
        time=$(random_number 1 1000) # Reduced from 1000000000
        echo $time >> input.txt
    done

    # Run the programs with the generated test case
    ./q1 < input.txt > output1.txt
    ./q1_shreyas < input.txt > output2.txt

    # Compare the outputs
    if ! diff -q output1.txt output2.txt > /dev/null 2>&1
    then
        echo "Test case $i failed" >> differences.txt
        echo "Input:" >> differences.txt
        cat input.txt >> differences.txt
        echo "Output from q1.c:" >> differences.txt
        cat output1.txt >> differences.txt
        echo "Output from q1_shreyas.c:" >> differences.txt
        cat output2.txt >> differences.txt
        echo "" >> differences.txt
    fi
done

# Clean up
rm input.txt output1.txt output2.txt