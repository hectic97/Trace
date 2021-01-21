import sys

graph = {}
N = int(input())

for _ in range(N):
    r,left,right = sys.stdin.readline().split()
    graph[r] = [left,right]

def preorder(node):
    if node == '.':
        return
    print(node,end='')
    preorder(graph[node][0])
    preorder(graph[node][1])

def inorder(node):
    if node == '.':
        return
    inorder(graph[node][0])
    print(node,end='')
    inorder(graph[node][1])

def postorder(node):
    if node == '.':
        return
    postorder(graph[node][0])
    postorder(graph[node][1])
    print(node,end='')
    
preorder('A')
print()
inorder('A')
print()
postorder('A')