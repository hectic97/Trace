import sys,copy
N,M = list(map(int,input().split()))
lst = []
cnt_lst = []
for _ in range(N):
    lst.append(list(map(int,sys.stdin.readline().rstrip())))
    cnt_lst.append([0]*M)
dx = [-1,1,0,0]
dy = [0,0,-1,1]
cnt = 1
def BFS(graph,start_node):
    global cnt
    visit = []
    queue = []
    queue.append(start_node)
    cnt_lst[N-1][M-1] = cnt
    while queue:
        node = queue.pop(0)
        s_node = node.split('/')
        cnt = cnt_lst[int(s_node[0])][int(s_node[1])]+1
        if node not in visit:
            visit.append(node)
            queue.extend(graph[node])
            for pos in graph[node]:
                s_pos = pos.split('/')
                if not cnt_lst[int(s_pos[0])][int(s_pos[1])]:
                    cnt_lst[int(s_pos[0])][int(s_pos[1])] = cnt
                elif cnt_lst[int(s_pos[0])][int(s_pos[1])] >= cnt:
                    cnt_lst[int(s_pos[0])][int(s_pos[1])] = cnt
    
graph={}
for n in range(N):
    for m in range(M):
        if str(n)+'/'+str(m) not in graph:
            graph[str(n)+'/'+str(m)] = []
        if lst[n][m]:
            for dr,dc in zip(dx,dy):
                if 0 <= n+dr <= N-1 and 0 <= m + dc <= M-1:
                    if lst[n+dr][m+dc]:
                        graph[str(n)+'/'+str(m)].append(str(n+dr)+'/'+str(m+dc))
                       
BFS(graph,str(N-1)+'/'+str(M-1))
print(cnt_lst[0][0])