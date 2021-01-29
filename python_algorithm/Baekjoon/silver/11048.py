import sys
N,M = list(map(int,input().split()))

lst = []
for _ in range(N):
    lst.append(list(map(int,sys.stdin.readline().split())))

dp = [[0]*M for _ in range(N)]

dp[0][0] = lst[0][0]

for c in range(1,M):
    dp[0][c] = dp[0][c-1] + lst[0][c]
for r in range(1,N):
    dp[r][0] = dp[r-1][0] + lst[r][0]

if M > 1 and N > 1:
    for r in range(1,N):
        for c in range(1,M):
            dp[r][c] = max(dp[r-1][c],dp[r][c-1],dp[r-1][c-1])+lst[r][c]

mx = -1
for x in dp:
    if mx < max(x):
        mx = max(x)
print(mx)
