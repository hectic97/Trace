import sys,copy

i = 1
lst= []
dp = []
N = int(input())
for _ in range(N):
    lst.append(list(map(int,sys.stdin.readline().rstrip().split())))
    dp.append([0]*i)
    i += 1
if N ==1:
    print(lst[0][0])
    exit(0)
dp[0][0] = lst[0][0]
dp[1][0] = lst[0][0] + lst[1][0]
dp[1][1] = lst[0][0] + lst[1][1]
for i in range(2,N):
    for j in range(i+1):
        if j == 0:
            dp[i][j] = dp[i-1][0] + lst[i][j]
        elif j == i:
            dp[i][j] = dp[i-1][-1] + lst[i][j]
        else:
            dp[i][j] = max(dp[i-1][j-1],dp[i-1][j]) + lst[i][j]
print(max(max(dp)))