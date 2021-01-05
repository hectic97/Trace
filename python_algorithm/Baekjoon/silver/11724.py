import sys
sys.setrecursionlimit(10**6)

def dfs(graph, start_node):
    visit = list()
    stack = list()
    
    stack.append(start_node)

    while stack:
        node = stack.pop()
        if node not in visit:
            visit.append(node)
            stack.extend(list(graph[node]))
    return visit

N,M = list(map(int,sys.stdin.readline().split()))
all_node = list(range(1,N+1))
lst = []
for _ in range(M):
    lst.append(list(map(int,sys.stdin.readline().split())))

graph = {}

for x in range(1,N+1):
    graph[x] = set()

for s,d in lst:
    # if s not in graph:
    #     graph[s] = set()
    # if d not in graph:
    #     graph[d] = set()
    graph[s].add(d)
    graph[d].add(s)
result = 0

while all_node:
    result += 1
    visit = dfs(graph,all_node[0])
    
    for n in visit:
        all_node.remove(n)
    
print(result)

        
