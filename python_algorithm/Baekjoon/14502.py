import sys,copy
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

N,M = list(map(int,input().split()))
lst = []
for line in sys.stdin:
    lst.append(list(map(int,line.strip().split())))
for x in lst:
    for y in x:
        if y == 0:
            y = 1
            for 
