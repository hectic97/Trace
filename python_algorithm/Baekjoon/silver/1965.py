N = int(input())
lst = [0]
lst.extend(list(map(int,input().split())))
dp = [0]*(N+1)
dp[1] = 1
for i in range(2,N+1):
    mx = 1
    for j in range(1,i):
        if lst[j] < lst[i] and dp[j] >= mx:
            mx = dp[j]+1
    dp[i] = mx

print(max(dp))



    