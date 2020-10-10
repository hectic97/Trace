import sys
T = int(input())
for _ in range(T):
    N = int(input())
    lst = []
    lst.append([0]+list(map(int,sys.stdin.readline().split())))
    lst.append([0]+list(map(int,sys.stdin.readline().split())))
    dp = lst.copy()
    for x in dp:
        for y in x:
            y = 0
    dp[0][0] = 0
    dp[1][0] = 0
    dp[0][1] = lst[0][1]
    dp[1][1] = lst[1][1]
    for i in range(2,N+1):
        dp[0][i] = max(dp[1][i-1],dp[1][i-2])+lst[0][i]
        dp[1][i] = max(dp[0][i-1],dp[0][i-2])+lst[1][i]
    print(max(dp[0][N],dp[1][N]))