## Results  
(Tested on a MacBook Air M3, 8GB RAM)

During this project, there were a few things that I noticed. To start, there were quite a few highlights of the significant performance differences between implementations. For the smaller arrays (sizes between 10 and 100), all of the different implementations completed in milliseconds or less, and even OpenMP achieved times as low as 0.000011 seconds. The difference between the single-threaded and threaded C was minor at smaller sizes, but as the size increases, the impact becomes more pronounced in these all.

For the larger arrays such as 1000 or 2000, the gap between the implementations became a lot more obvious. With C without threads, it took 58.7883 seconds, and C with threads took 59.5243 seconds, which showed minimal benefit at this scale. With Python, obviously, there was much slower performance, with the time reaching as high as 1280.67 seconds without threads and 1865.73 seconds with threads. This inefficiency for Python's threading showed worse performance with threads than without.
