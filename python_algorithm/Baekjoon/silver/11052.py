import sys
N = int(sys.stdin.readline().rstrip())
lst=[0]+list(map(int,sys.stdin.readline().rstrip().split()))
dp = [0]*(N+1)
if N == 1:
    print(lst[1])
    exit(0)
dp[1] = lst[1]
for i in range(2,N+1):
    temp = []
    for j in range(i+1):
        temp.append(dp[i-j]+lst[j])
        dp[i] = max(temp)
print(dp[N])