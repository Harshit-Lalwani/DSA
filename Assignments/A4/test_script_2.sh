#!/bin/bash

# Compile the programs
gcc q2.c -o q2
gcc q2_shreyas.c -o q2_shreyas

# Function to generate a random number within a range
function random_number {
    shuf -i $1-$2 -n 1
}

# Test the programs with random test cases
for ((i=1; i<=100; i++))
do
    # Generate random test case
    n=$(random_number 1 100)
    k=$(random_number 1 30000)
    echo $n $k > input.txt
    for ((j=1; j<=n; j++))
    do
        oxygen_req=$(random_number 1 30000)
        echo $oxygen_req >> input.txt
    done
    for ((j=1; j<=n; j++))
    do
        change=$(( $(random_number 1 600) - 300 ))
        echo $change >> input.txt
    done

    # Run the programs with the generated test case
    ./q2 < input.txt > output1.txt
    ./q2_shreyas < input.txt > output2.txt

    # Compare the outputs
    if ! diff -q output1.txt output2.txt > /dev/null 2>&1
    then
        echo "Test case $i failed" >> differences.txt
        echo "Input:" >> differences.txt
        cat input.txt >> differences.txt
        echo "Output from q2.c:" >> differences.txt
        cat output1.txt >> differences.txt
        echo "Output from q2_shreyas.c:" >> differences.txt
        cat output2.txt >> differences.txt
        echo "" >> differences.txt
    fi
done

# Clean up
rm input.txt output1.txt output2.txt