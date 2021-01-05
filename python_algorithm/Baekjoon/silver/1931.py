N = int(input())
lst = []
for _ in range(N):
    lst.append(list(map(int,input().split())))
lst.sort(key = lambda x: (x[1],x[0]))

result = 1
time = lst[0][1]
ind = 0

while True:
    end = True
    for i in range(ind+1, N):
        if lst[i][0] >= time:
            result += 1
            time = lst[i][1]
            ind = i
            end = False
            break
    if end:
        print(result)
        break    
    



