from itertools import permutations
import math

N = int(input())
lst = []
for _ in range(N):
    lst.append(list(map(int,input().split())))
mn = math.inf
for p in permutations(list(range(N)),N):
    s = [lst[p[i]][p[i+1]] for i in range(N-1)]+[lst[p[-1]][p[0]]]
    if 0 in s:
        continue
    s = sum(s)
    if mn > s:
        mn = s
print(mn)

        
