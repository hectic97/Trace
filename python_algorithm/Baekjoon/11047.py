import sys
N, K = list(map(int,sys.stdin.readline().rstrip().split()))
lst = []
for _ in range(N):
    lst.append(int(sys.stdin.readline().rstrip()))
result = 0
for coin in reversed(lst):
    if int(K / coin) :
        result += int(K /coin)
        K = K % coin
print(result)
    