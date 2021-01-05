import sys

N = int(input())
lst = []

for _ in range(N-1):
    lst.append(list(map(int,sys.stdin.readline().split())))

graph = {n:set() for n in range(1,N+1)}

for n1, n2 in lst:
    graph[n1].add(n2)
    graph[n2].add(n1)

def bfs(graph, start_node):
    visit = [False] * (N-1)
    visit = [True,True]+visit
    queue = []
    result = {}

    queue.append(start_node)

    while queue:
        node = queue.pop(0)
        visit[node]= True
        for n in graph[node]:
            if not visit[n]:
                queue.append(n)
                result[n] = node
    return result


result = bfs(graph, 1)
for x in range(2,N+1):
    print(result[x])



        