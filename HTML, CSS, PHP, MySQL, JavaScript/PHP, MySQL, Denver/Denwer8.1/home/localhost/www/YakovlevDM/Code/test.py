# A. Sum of Two Squares
""" import math

def FindTwoSquares(n, aPtr, bPtr):
	for a in range(int(math.sqrt(n))+1):
		bSq = n - a*a
		b = int(math.sqrt(bSq))
		if(b*b==bSq):
			aPtr[0]=a
			bPtr[0]=b
			return True
	return False

n = int(input())
aPtr=[0]
bPtr=[0]

if FindTwoSquares(n, aPtr, bPtr):
	a,b = sorted([aPtr[0], bPtr[0]])
	print(f"{a} {b}")
else:
	print("NO") """ 

# B. Dependencies

""" from collections import defaultdict, deque

def BuildGraph(dotFile):
    graph = defaultdict(list)
    inDegree = defaultdict(int)
    with open(dotFile, 'r') as file:
        for line in file:
            if '->' in line:
                line = line.split('[')[0]
                parts = line.strip().split('->')
                fromLabel = parts[0].strip().strip('"')
                toLabel = parts[1].strip().strip('"')
                if fromLabel not in graph:
                    graph[fromLabel]=[]
                if toLabel not in graph:
                    graph[toLabel]=[]
                graph[fromLabel].append(toLabel)
                inDegree[toLabel] += 1
    return graph, inDegree

def TopologicalSort(graph, inDegree):
    dq=deque([node for node in graph if inDegree[node]==0])
    sortedOrder=[]
    while dq:
        node = dq.popleft()
        sortedOrder.append(node)
        for neighbor in graph[node]:
            inDegree[neighbor] -= 1
            if inDegree[neighbor] == 0:
                dq.append(neighbor)
    return reversed(sortedOrder)

def main():
    dotFile = 'input.txt'
    graph, inDegree = BuildGraph(dotFile)
    sortedPackages = TopologicalSort(graph, inDegree)
    for package in sortedPackages:
        print(package)

if __name__ == "__main__":
    main() """

# C. Decorator

""" import sys
from functools import wraps

def takes(*types):
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            lenMin = min(len(args), len(types))
            for arg, expType in zip(args[:lenMin], types[:lenMin]):
                if not isinstance(arg, expType):
                    raise TypeError
            return func(*args, **kwargs)
        return wrapper
    return decorator
            
exec(sys.stdin.read()) """

# D. Student's grub

""" def solveHunger(n, a, b):    
    maxVol = n // a
    for x in range(maxVol + 1):
        leftover = n - x*a
        if leftover%b==0:
            y = leftover//b
            return True, x, y
    return False, 0, 0

n = int(input())
a = int(input())
b = int(input())

result, x, y = solveHunger(n, a, b)
if result:
    print("YES")
    print(x, y)
else:
    print("NO") """

from math import ceil, floor


def gcd(a, b):
    if b == 0:
        return a
    else:
        d = gcd(b, a % b)
        return d
    
def extended_gcd(a, b):
    if b == 0:
        return a, 1, 0
    else:
        d, x_prev, y_prev = extended_gcd(b, a % b)
        x = y_prev
        y = x_prev - (a // b) * y_prev
        return d, x, y
    
def f(a, b, n):
  d = gcd(a, b)
  if n % d == 0:
    new_a = a // d
    new_b = b // d
    new_n = n // d
    _, x0, y0 = extended_gcd(new_a, new_b)
    new_x0, new_y0 = x0 * new_n, y0 * new_n
    t_min, t_max = ceil(-new_x0/new_b), floor(new_y0/new_a)
    for t in range(t_min, t_max + 1):
      t = (t_min + t_max) // 2
      x = new_x0 + new_b * t
      y = new_y0 - new_a * t
      if x >= 0 and y >= 0:
        return x, y
  return False


n = int(input())
a = int(input())
b = int(input())
result = f(a, b, n)
if result is False:
    print("NO")
else:
    print("YES")
    print(result[0], result[1])