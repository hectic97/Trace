N = int(input())
dp = [[0]*10 for _ in range(N+1)]
dp[1] = [1]*10
for i in range(2,N+1):
    dp[i] = [sum(dp[i-1][:j]) for j in range(1,11)]
print(sum(dp[-1])%10007)
