import collections
N,K = list(map(int,input().split()))
check_lst = [0]*100001
def BFS():
    queue = collections.deque()
    queue.append(N)
    check_lst[N] = 1
    while queue:
        node = queue.popleft()
        if  node == K:
            print(check_lst[node]-1)
            return
        if 0<= node*2 < 100001 and not check_lst[node*2]:
            queue.append(node*2)
            check_lst[node*2] = check_lst[node]+1
        if 0<= node+1 < 100001 and not check_lst[node+1]:
            queue.append(node+1)
            check_lst[node+1] = check_lst[node]+1
        if 0<= node-1 < 100001 and not check_lst[node-1] :
            queue.append(node-1)
            check_lst[node-1] = check_lst[node]+1
        
BFS()
