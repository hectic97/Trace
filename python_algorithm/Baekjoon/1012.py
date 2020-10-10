import sys

def BFS(graph,start_node):
    visit = []
    queue = []
    queue.append(start_node)
    if not graph[start_node]:
        return []
    while queue:
        node = queue.pop(0)
        if node not in visit:
            visit.append(node)
            queue.extend(graph[node])
    return visit
        
T = int(input())
for _ in range(T):
    result = 1
    lst = []
    M,N,K = list(map(int,input().split()))
    for _ in range(K):
        lst.append(list(map(int,sys.stdin.readline().split())))
    graph = {}
    check = [0]*K
    for i,ax_1 in enumerate(lst):
        if i not in graph:
            graph[i] = []
        for j,ax_2 in enumerate(lst[i+1:]):
            if j+i+1 not in graph:
                graph[j+i+1] = []
            if abs(ax_1[0] - ax_2[0]) <= 1 and ax_1[1] == ax_2[1]:
                graph[i].append(j+i+1)
                graph[j+i+1].append(i)
            elif abs(ax_1[1] - ax_2[1]) <= 1 and ax_1[0] == ax_2[0]:
                graph[i].append(j+i+1)
                graph[j+i+1].append(i)
    for point in graph:
        if not check[point]:
            for x in BFS(graph,point):
                if not check[x]:
                    check[x] = result
            result += 1
            
    print(result-1)
