import time
import random

def multiplication(a, b):
 ending = []
 for i in range(len(a)):
  str = []
  for ii in range(len(b[0])):
   val = 0
   for iii in range(len(b)):
    val += a[i][iii] * b[iii][ii]
   str.append(val)
   ending.append(str)
 return ending

def generateMatrix(sz):
 matrix = []
 for i in range(sz):
  row = []
  for ii in range(sz):
   row.append(random.randint(1,50))
  matrix.append(row)
 return matrix

size = int(input().strip())
a = generateMatrix(size)
b = generateMatrix(size)

start = time.time()
res = multiplication(a,b)
end = time.time()

print(end - start)
