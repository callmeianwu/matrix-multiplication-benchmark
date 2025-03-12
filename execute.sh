#!/bin/bash

gcc -o matrixnothreads matrixnothreads.c -O2 -lm -pthread
gcc -o matrixthreads matrixthreads.c -O2 -pthread -lm
gcc -o openmp openmp.c -O2 -fopenmp -lm

if [[ ! -f "matrixnothreads" || ! -f "matrixthreads" || ! -f "openmp" ]]; then
    echo "Error: Compilation failed! Check for errors in your C source files."
    exit 1
fi

array_sizes=(10 50 100 500 1000 2000)

echo "Array Size,Time Without Threads (C),Time With Threads (C),Time With OpenMP,Time Without Threads (Python),Time With Threads (Python)" > results.csv

for num_threads in 1 2 4 8 16; do
    export OMP_NUM_THREADS=$num_threads

    echo "Running benchmarks with $num_threads threads..."

    for size in "${array_sizes[@]}"; do
        echo "Running for array size $size..."

        if [[ -x "./matrixnothreads" ]]; then
            time_without_threads_c=$(./matrixnothreads $size)
        else
            echo "Error: matrixnothreads executable not found!"
            exit 1
        fi

        if [[ -x "./matrixthreads" ]]; then
            time_with_threads_c=$(./matrixthreads $size)
        else
            echo "Error: matrixthreads executable not found!"
            exit 1
        fi

        if [[ -x "./openmp" ]]; then
            time_with_threads_openmp=$(./openmp $size)
        else
            echo "Error: openmp executable not found!"
            exit 1
        fi

        # Run Python implementations
        echo "Running Python implementations..."
        if command -v python3 &>/dev/null; then
            time_without_threads_py=$(python3 nothread.py <<< "$size")
            time_with_threads_py=$(python3 yesthread.py <<< "$size")
        else
            echo "Error: Python3 is not installed!"
            exit 1
        fi

        # Append results to CSV file
        echo "$size,$time_without_threads_c,$time_with_threads_c,$time_with_threads_openmp,$time_without_threads_py,$time_with_threads_py" >> results.csv
    done
done

echo "Benchmarking complete! Results saved in results.csv"

