N = int(input())
dp = []
for _ in range(N+1):
    dp.append([0]*10)
if N ==1:
    print(9)
    exit(0)
dp[1] = [0]+[1]*9
for i in range(2,N+1):
    for j in range(10):
        if j == 0:
            dp[i][j] = dp[i-1][j+1]
        elif j == 9:
            dp[i][j] = dp[i-1][j-1]
        else:
            dp[i][j] = dp[i-1][j-1] + dp[i-1][j+1]
print(sum(dp[N])%1000000000)

    
