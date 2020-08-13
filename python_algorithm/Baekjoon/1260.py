import sys
def DFS(graph,start_node):
    visit = []
    stack = []
    stack.append(start_node)
    if start_node not in graph:
        return [start_node]
    while stack:
        node = stack.pop()
        if node not in visit:
            visit.append(node)
            stack.extend(sorted(graph[node])[::-1])
    return visit

def BFS(graph,start_node):
    visit = []
    queue = []
    queue.append(start_node)
    if start_node not in graph:
        return [start_node]
    while queue:
        node = queue.pop(0)
        if node not in visit:
            visit.append(node)
            queue.extend(sorted(graph[node]))
    return visit

N,M,V = list(map(int,input().split(' ')))
graph = dict()
for _ in range(M):
    # k,v = list(map(int,input().split(' ')))
# for line in sys.stdin:
    k,v = list(map(int,sys.stdin.readline().rstrip().split()))
    # a, b = map(int, sys.stdin.readline().split())
    # k,v=line.split(' ')
    if k not in graph:
        graph[k] = list()
    if v not in graph:
        graph[v] = list()
    if v not in graph[k]:
        graph[k].append(v)
    if k not in graph[v]:
        graph[v].append(k)
    
print(*DFS(graph,V))
print(*BFS(graph,V))
