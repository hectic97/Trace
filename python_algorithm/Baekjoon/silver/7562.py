N = int(input())
dx = [1,2,2,1,-1,-2,-2,-1]
dy = [2,1,-1,-2,-2,-1,1,2]

def bfs(st, de):
    queue = [st]
    time = [[0]*L for _ in range(L)]
    time[st[0]][st[1]] = 1
    while queue:
        node = queue.pop(0)
        if node==de:
            return time[de[0]][de[1]]
            
        for x,y in zip(dx,dy):
            ny = node[0]+y
            nx = node[1]+x
            if 0<=nx<L and 0<=ny<L and not time[ny][nx]:
                queue.append([ny,nx])
                time[ny][nx] = time[node[0]][node[1]]+1            


for i in range(N):
    L = int(input())
    st = list(map(int,input().split()))
    de = list(map(int,input().split()))
    print(bfs(st,de)-1)
    

        