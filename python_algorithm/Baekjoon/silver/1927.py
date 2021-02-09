import heapq
import sys

N = int(input())
lst = []
for _ in range(N):
    x = int(sys.stdin.readline())
    if not x:
        if not lst:
            print(0)
            continue
        else:
            print(heapq.heappop(lst))
    else:
        heapq.heappush(lst,x)    



