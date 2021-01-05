import sys
import math

prime = [True]*(123456*2+1)

for i in range(2,int(math.sqrt(123456*2+1))+1):
    if prime[i]:
        for j in range(i, 123456*2+1, i):
            prime[j]=False
        prime[i] = True

while True:
    n = int(sys.stdin.readline())
    if not n:
        break
    print(sum(prime[n+1:2*n+1]))




