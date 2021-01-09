N = int(input())
dp1 = [0]*(N+1)
dp2 = [0]*(N+1)
# dp1=last 1, dp2 = else
if N==1:
    print(1)
    exit(0)
dp1[1] = 1
dp2[1] = 0
dp1[2] = 0
dp2[2] = 1
for i in range(3,N+1):
    dp1[i] = dp2[i-1] 
    dp2[i] = dp1[i-1] + dp2[i-1]
print(dp1[-1]+dp2[-1])
