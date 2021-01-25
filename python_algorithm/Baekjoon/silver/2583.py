M,N,K = list(map(int,input().split()))

sq_list = []
for _ in range(K):
    sq_list.append(list(map(int,input().split())))

board = [[-1]*N for _ in range(M)]

for sq in sq_list:
    c1,r1,c2,r2 = sq
    for c in range(c1,c2):
        for r in range(r1,r2):
            board[r][c] = 0

dx=[-1,0,1,0]
dy=[0,1,0,-1]

island = []

for r in range(M):
    for c in range(N):
        if board[r][c] == -1:
            ct = 0
            queue = [[r,c]]
            while queue:
                node = queue.pop()
                if board[node[0]][node[1]] == -1:
                    ct += 1
                    board[node[0]][node[1]] = 1
                    for dx_, dy_ in zip(dx,dy):
                        if 0 <= node[0]+dy_ < M and 0 <= node[1]+dx_ < N:
                            queue.append([node[0]+dy_,node[1]+dx_])
            island.append(ct)

island = sorted(island)
print(len(island))
print(*island)

                




