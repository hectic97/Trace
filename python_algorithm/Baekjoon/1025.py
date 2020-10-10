import sys,math
lst = []
lst_2 = []
final = [-1]

N,M = list(map(int,input().split()))

if N == 0 or M == 0:
    print(-1)
    exit(0)
for _ in range(N):
    lst.append(list(map(int,sys.stdin.readline().rstrip())))

if N ==1 and M == 1:
    if int(math.sqrt(lst[0][0])) == math.sqrt(lst[0][0]):
        print(lst[0][0])
    else:
        print(-1)
    exit(0)
for n in range(N):
    for m in range(M):
        lst_2.append([n,m])

for i,start in enumerate(lst_2):
    for nxt in lst_2[i+1:]:
        row_dif = nxt[0] - start[0]
        col_dif = nxt[1] - start[1]
        result = []
        i=1
    
        result.append(str(lst[start[0]][start[1]]))
        result.append(str(lst[start[0]][start[1]])+str(lst[nxt[0]][nxt[1]]))
        
        while(1):
            
            try:
                if nxt[0]+row_dif*i < 0 or nxt[1] + col_dif*i <0:
                    break
                result.append(result[-1]+str(lst[nxt[0]+row_dif*i][nxt[1]+col_dif*i]))
                i+=1
            except:
                break
        
        for r in result:
            num_r = int(r)
            reverse_r = int(r[::-1])
            if int(math.sqrt(num_r)) == math.sqrt(num_r):
                final.append(num_r)
            if int(math.sqrt(reverse_r)) == math.sqrt(reverse_r):
                final.append(reverse_r)
            
print(max(final))
