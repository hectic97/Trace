n = int(input())
lst = list(map(int,input().split()))
dp = [0]*n
dp[0] = 1

i=1
while i<n:
    candidate=[1]
    for j in range(i):
        if lst[i]<lst[j]:
            candidate.append(dp[j] + 1)
    dp[i] = max(candidate)
    i += 1
print(max(dp))