import sys,copy

N = int(sys.stdin.readline().rstrip())
lst = []
dp = [0]
for _ in range(N):
    lst.append(int(sys.stdin.readline().rstrip()))
    dp.append(0)
if N == 1:
    print(lst[0])
    exit(0)
elif N == 2:
    print(lst[0]+lst[1])
    exit(0)

dp[0] = 0
dp[1] = lst[0]
dp[2] = lst[1]+lst[0]

for i in range(3,N+1):
    dp[i] = max(lst[i-1]+dp[i-2],dp[i-1],lst[i-1]+lst[i-2]+dp[i-3])

print(dp[i])