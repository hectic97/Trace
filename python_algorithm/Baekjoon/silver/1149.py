N = int(input())
arr = []
arr.append([0,0,0])
for _ in range(N):
    arr.append(list(map(int,input().split(' '))))
dp = []
dp.append([0,0,0])
for i in range(1,N+1):
    dp.append([min(dp[i-1][1],dp[i-1][2])+arr[i][0],
               min(dp[i-1][0],dp[i-1][2])+arr[i][1],
               min(dp[i-1][0],dp[i-1][1])+arr[i][2]])
    # print(dp)
print(min(dp[N][0],dp[N][1],dp[N][2]))