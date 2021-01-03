def bfs(graph, start_node):
    visit = list()
    queue = list()

    queue.append(start_node)

    while queue:
        node = queue.pop(0)
        if node not in visit:
            visit.append(node)
            queue.extend(graph[node])
    
    return visit

def dfs(graph, start_node):
    visit = list()
    stack = list()

    stack.append(start_node)

    while stack:
        node = stack.pop()
        if node not in visit:
            visit.append(node)
            stack.extend(graph[node])
    
    return visit

C = int(input())
N = int(input())

graph = {}
for _ in range(N):
    lst = list(map(int,input().split()))
    if lst[0] not in graph:
        graph[lst[0]] = set()
    if lst[1] not in graph:
        graph[lst[1]] = set()
    graph[lst[0]].add(lst[1])
    graph[lst[1]].add(lst[0])

virus_com = bfs(graph,1)
print(len(virus_com)-1)
    

