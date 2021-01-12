N = int(input())
p = list(map(int,input().split()))
m = int(input())
lst = [] 
graph={}
for _ in range(m):
    a,b = list(map(int,input().split()))
    if a not in graph:
        graph[a] = set()
    if b not in graph:
        graph[b] = set()
    graph[a].add(b)
    graph[b].add(a)
def bfs(start_node, end_node, graph):
    visit = [0]*(N+1)
    queue = [start_node]
    visit[start_node] = 1

    while queue:
        node = queue.pop(0)
        if node == end_node:
            return visit[end_node]-1
        for nt in graph[node]:
            if not visit[nt]:
                queue.append(nt)
                visit[nt] = visit[node]+1
    return -1

print(bfs(p[0],p[1],graph))
            




