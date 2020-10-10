graph= {'A': ['B', 'C'],
        'B': ['A', 'D'],
        'C': ['A', 'G', 'H', 'I'],
        'D': ['B', 'E', 'F'],
        'E': ['D'],
        'F': ['D'],
        'G': ['C'],
        'H': ['C'],
        'I': ['C', 'J'],
        'J': ['I']}

def DFS(graph,start_node):
    visit = []
    stack = []
    stack.append(start_node)
    while stack:
        node = stack.pop()
        if node not in visit:
            visit.append(node)
            stack.extend(graph[node])
    return visit

def BFS(graph,start_node):
    visit = []
    queue = []
    queue.append(start_node)
    while queue:
        node = queue.pop(0)
        if node not in visit:
            visit.append(node)
            queue.extend(graph[node])
    return visit

print('DFS : ',DFS(graph,'A'))
print('BFS : ',BFS(graph,'A'))
