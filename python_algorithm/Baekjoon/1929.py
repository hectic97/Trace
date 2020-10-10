M,N = list(map(int,input().split(' ')))
lst = [True]*1000001
lst[0] = False
lst[1] = False
for i in range(2,1000001):
    if lst[i]:
        for x in range(i*2,1000001,i):
            lst[x] = False
        
for x in range(M,N+1):
    if lst[x]:
        print(x)
