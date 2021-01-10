# import itertools

# n = int(input())
# result = 0
# M = n // 2 
# for m in range(M+1):
#     n_ = n - m
#     numerator = 1
#     denominator = 1
#     for i,_ in enumerate(range(m)):
#         numerator *=  n_ - i
#         denominator *= m - i
#     result += int(numerator/denominator)
# print(result%10007)

n = int(input())
dp = [0]*(n+1)
if n ==1:
    print(1)
    exit(0)
dp[0] = 0
dp[1] = 1
dp[2] = 2
for i in range(3,n+1):
    dp[i] = dp[i-1]+dp[i-2]
# print(dp)
print(dp[n]%10007)