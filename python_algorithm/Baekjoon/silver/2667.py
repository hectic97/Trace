import sys,copy 

def BFS(graph,start_node):
    visit= []
    queue= []
    queue.append(start_node)
    while queue:
        node = queue.pop(0)
        # s_node = node.split('/')
        if node not in visit:
            visit.append(node)
            queue.extend(graph[node])
    return visit


def make_graph(lst):
    graph = {}
    for r in range(N):
        for c in range(N):
            if str(r)+'/'+str(c) not in graph:
                graph[str(r)+'/'+str(c)]=[]
            for r_dif,c_dif in zip(dx,dy):
                if 0 <= r+r_dif < N and 0 <= c+c_dif < N:
                    if lst[r+r_dif][c+c_dif]:
                        graph[str(r)+'/'+str(c)].append(str(r+r_dif)+'/'+str(c+c_dif))
    return graph
            
    
N = int(input())
lst = []
cluster_lst = []
result_lst = []
cl_num = 1
result = 0
dx = [-1,1,0,0]
dy = [0,0,-1,1]
for _ in range(N):
    lst.append(list(map(int,sys.stdin.readline().rstrip())))
    cluster_lst.append([0]*N)
graph = make_graph(lst)
for n in range(N):
    for m in range(N):
        if lst[n][m] and not cluster_lst[n][m]:
            cl = BFS(graph,str(n)+'/'+str(m))
            for x in cl:
                pos=x.split('/')
                cluster_lst[int(pos[0])][int(pos[1])] = cl_num
            cl_num += 1
print(cl_num-1)
for cn in range(1,cl_num):
    result = 0
    for ls in cluster_lst:
        result += ls.count(cn)
    result_lst.append(result)
for x in sorted(result_lst):
    print(x)