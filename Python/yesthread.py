import random
import time
import concurrent.futures


def generateMatrix(sz):
    return [[random.randint(1, 10) for _ in range(sz)] for _ in range(sz)]


def multiply(args):
    a, b, i, ii = args
    return i, ii, sum(a[i][iii] * b[iii][ii] for iii in range(len(b)))


def multThreads(a, b):
    size = len(a)
    res = [[0] * size for _ in range(size)]
    
    with concurrent.futures.ThreadPoolExecutor(max_workers=8) as executor:
        tasks = [(a, b, i, ii) for i in range(size) for ii in range(size)]
        for i, ii, val in executor.map(multiply, tasks):
            res[i][ii] = val
            
    return res


size = int(input().strip())
a = generateMatrix(size)
b = generateMatrix(size)

start = time.time()
res = multThreads(a, b)
end = time.time()

print(end - start)

