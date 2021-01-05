import sys

while True:
    S = list(map(int,sys.stdin.readline().split()))
    if not S[0]:
        break
    for i in range(1,S[0]+1):
        for j in range(i+1,S[0]+1):
            for k in range(j+1,S[0]+1):
                for l in range(k+1,S[0]+1):
                    for m in range(l+1,S[0]+1):
                        for n in range(m+1,S[0]+1):
                            print(S[i],S[j],S[k],S[l],S[m],S[n])
    print()

