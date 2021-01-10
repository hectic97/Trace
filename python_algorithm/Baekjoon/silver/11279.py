import heapq
import sys

N = int(input())
heap = []
for _ in range(N):
    cmd = int(sys.stdin.readline())
    if not cmd:
        if heap:
            print(-heapq.heappop(heap))
        else:
            print(0)
    else:
        heapq.heappush(heap,-cmd)

    
