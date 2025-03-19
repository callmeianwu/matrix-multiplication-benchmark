# Matrix Multiplication Benchmark
(Note these results inside the repository are specific to the system they were run on and may be different)

This repository benchmarks matrix multiplication performance across different implementations in C and Python. The benchmarks compare execution time for various array sizes using:

- **C (Single-threaded)**
- **C (Pthreads - Multi-threaded)**
- **C (OpenMP - Parallel Processing)**
- **Python (Single-threaded)**
- **Python (Threaded)**

## Setup & Execution

### 1. Compile the C Programs
```bash
bash execute.sh
```
This script compiles the C implementations and runs the benchmark for different array sizes and thread configurations.

### 2. Run Python Implementations
The script also executes Python versions of the benchmark automatically.

### 3. View Results 
The results are stored in `results.csv` in the format:
```
Array Size,Time Without Threads (C),Time With Threads (C),Time With OpenMP,Time Without Threads (Python),Time With Threads (Python)
```

## Observations
- For small array sizes (10-100), all implementations complete in milliseconds.
- OpenMP achieves the fastest execution times, as low as **0.000011 seconds**.
- As array size increases, Python's performance degrades significantly, with threading offering no improvement due to the Global Interpreter Lock (GIL).
- For large arrays (1000+), C remains highly efficient, while Python can take over **1800 seconds** to complete a single run.

## Dependencies
Ensure you have:
- GCC (with OpenMP support)
- Python 3 installed

## License
This project is licensed under the MIT License.

