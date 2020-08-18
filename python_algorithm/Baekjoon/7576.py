import sys

dx = [-1,1,0,0]
dy = [0,0,-1,1]

def BFS(graph,start_node):
    visit = []
    queue = []
    queue.append(start_node)
    i = 1
    s_node = start_node.split('/')
    toma_lst[int(s_node[0])][int(s_node[1])] = 1 # need -1
    while queue:
        node = queue.pop(0)
        if node not in visit:
            visit.append(node)
            queue.extend(graph[node])
            for pos in visit:
                i += 1
                r_pos ,c_pos= list(map(int,pos.split('/')))
                if not toma_lst[r_pos][c_pos]:
                    toma_lst[r_pos][c_pos] = i
                elif toma_lst[r_pos][c_pos] > i:
                    toma_lst[r_pos][c_pos] = i 

    return

def make_graph(lst):
    graph = {}
    for i in range(N):
        for j in range(M):
            if lst[i][j] != -1:
                if str(i)+'/'+str(j) not in graph:
                    graph[str(i)+'/'+str(j)] = []
                for r_dif,c_dif in zip(dx,dy):
                    if 0 <= i + r_dif < N and 0<= j+c_dif < M:
                        if lst[i+r_dif][j+c_dif] != -1:
                            graph[str(i)+'/'+str(j)].append(str(i+r_dif)+'/'+str(j+c_dif))
    return graph
M,N = list(map(int,input().split()))
lst = []
toma_lst = []
for _ in range(N):
    lst.append(list(map(int,sys.stdin.readline().rstrip().split())))
    toma_lst.append([0]*M)
print(lst)
graph = make_graph(lst)
for n in range(N):
    for m in range(M):
        if lst[n][m] == 1:
            BFS(graph,str(n)+'/'+str(m))
print(max(max(toma_lst))-1)




