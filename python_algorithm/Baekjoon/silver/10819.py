import sys
import itertools

N = int(input())
lst = list(map(int,sys.stdin.readline().split()))
    
mx = 0
for p in itertools.permutations(lst,N):
    r = 0
    for i in range(N-1):
        r += abs(p[i]-p[i+1])
    if r >= mx:
        mx = r
print(mx)




