import sys,collections

def BFS(graph,start_node):
    visit = collections.deque()
    queue = collections.deque()
    queue.extend(graph[start_node])
    while queue:
        node = queue.popleft()
        if node not in visit:
            visit.append(node)
            queue.extend(graph[node])
    return visit


N = int(sys.stdin.readline().rstrip())
lst = []
graph = {}
for _ in range(N):
    lst.append(list(map(int,sys.stdin.readline().rstrip().split())))
for i in range(N):
    graph[i] = []
    for j in range(N):
        if lst[i][j]:
            graph[i].append(j)
for i in range(N):
    visit=BFS(graph,i)
    ls = [0]*N 
    for x in visit:
        ls[x] = 1
    print(*ls)
