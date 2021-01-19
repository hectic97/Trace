n, k = list(map(int,input().split()))
c=[]
for _ in range(n):
    c.append(int(input()))
 
dp = [0]*(k+1)
dp[0] = 1
for i in c:
    for j in range(i, k+1):
        dp[j] += dp[j-i]
 
print(dp[k])