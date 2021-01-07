# import sys
# sys.setrecursionlimit(10000) 

# n = int(input())
# lst = list(map(int,input().split()))
# mx = 0
# def recur(lst, total,i):
#     global mx
#     if i==len(lst):
#         if mx <= sum(total):
#             mx = sum(total)
#         return 
#     if lst[i] <= total[-1]:
#         recur(lst,total,i+1)
#         recur(lst,total[:-1],i)
#     else:
#         recur(lst,total+[lst[i]],i+1)
        
# recur(lst,[0],0)
# print(mx)

n = int(input())
lst = list(map(int,input().split()))
dp = [0]*n
dp[0] = lst[0]

i=1
while i<n:
    candidate=[lst[i]]
    for j in range(i):
        if lst[j] <lst[i]:
            candidate.append(dp[j] + lst[i])
    dp[i] = max(candidate)
    i += 1
print(max(dp))




