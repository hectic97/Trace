import sys

N = int(input())
S = list(map(int,([sys.stdin.readline() for i in range(N)])))

D= [0]*(len(S)+1)
P= [0]*(len(S)+1)
S = [0] + S

if N == 1:
    print(S[1])
    exit(0)

# D 직전 계단 X
# P 직전 계단 O

D[0] = 0
P[0] = 0
D[1] = S[1]
D[2] = S[2]
P[1] = S[1]
P[2] = S[1]+S[2]

if N == 2:
    print(max(D[2],P[2]))
    exit(0)

def DP(S,D,P,i):
    D[i] = max(D[i-2],P[i-2])+S[i]
    P[i] = D[i-1]+S[i]

for i in range(2,N+1):
    DP(S,D,P,i)

print(max(D[N],P[N]))