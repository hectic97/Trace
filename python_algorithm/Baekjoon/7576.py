import sys,collections

dx = [-1,1,0,0]
dy = [0,0,-1,1]
time = 1
first_all_tomato = True
def BFS_tomato_search(lst):
    global time
    global first_all_tomato
    queue = collections.deque()
    for n in range(N):
        for m in range(M):
            if lst[n][m] == 1:
                queue.append([n,m,1])
    while queue:
        node = queue.popleft()
        for xx, yy in zip(dx,dy):
            if 0<=node[0]+xx<N and 0<=node[1]+yy <M:
                if lst[node[0]+xx][node[1]+yy] == 0:
                    queue.append([node[0]+xx,node[1]+yy,node[2]+1])
                    time = node[2]
                    lst[node[0]+xx][node[1]+yy] = 1
                    first_all_tomato = False
    

M,N = list(map(int,input().split()))
lst = []
for i in range(N):
    lst.append(list(map(int,sys.stdin.readline().rstrip().split())))
BFS_tomato_search(lst)
if first_all_tomato:
    print(0)
    exit(0)
for ls in lst:
    for l in ls:
        if not l:
            print(-1)
            exit(0)
print(time)
