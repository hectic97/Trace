import sys
N = int(input())
lst=list(map(int,sys.stdin.readline().rstrip().split()))
dp = [0]*(N+1)
for i in range(N):
    mx = 0
    for j in range(i):
        if lst[j] < lst[i] and dp[j+1] > mx:
            mx = dp[j+1]
    dp[i+1] = mx+1
print(max(dp))