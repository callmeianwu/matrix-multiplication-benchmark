## System Specifications 
(Tested on a MacBook Air M3, 8GB RAM)

## Results
During this project, there were a few things that I noticed. To start, there were quite a few highlights of the significant performance differences between implementations. For the smaller arrays (sizes between 10 and 100), all of the different implementations completed in milliseconds or less, and even OpenMP achieved times as low as 0.000011 seconds. The difference between the single-threaded and threaded C was minor at smaller sizes, but as the size increases, the impact becomes more pronounced in these all.

For the larger arrays such as 1000 or 2000, the gap between the implementations became a lot more obvious. With C without threads, it took 58.7883 seconds, and C with threads took 59.5243 seconds, which showed minimal benefit at this scale. With Python, obviously, there was much slower performance, with the time reaching as high as 1280.67 seconds without threads and 1865.73 seconds with threads. This inefficiency for Python's threading showed worse performance with threads than without.

##Observations

- For small array sizes (10-100), all implementations complete in milliseconds.

- OpenMP achieves the fastest execution times, as low as 0.000011 seconds.

- As array size increases, Python's performance degrades significantly, with threading offering no improvement due to the Global Interpreter Lock (GIL).

- For large arrays (1000+), C remains highly efficient, while Python can take over 1800 seconds to complete a single run.

##Dependencies
Ensure you have:

- GCC (with OpenMP support)
- Python 3 installed