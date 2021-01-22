import sys

N = int(input())
lst = []
for _ in range(N):
    lst.append(list(map(int,sys.stdin.readline().split())))

dx = [-1,0,1,0]
dy = [0,1,0,-1]

def bfs(i,j,lst,board):
    queue = [[i,j]]
    while queue:
        x, y= queue.pop()
        if board[x][y] == -1:
                    if lst[x][y] <= h:
                        board[x][y] = 0
                    else:
                        board[x][y] = 1
                        for dx_, dy_ in zip(dx,dy):
                            if 0 <= x+dx_ < N and 0 <= y+dy_ < N:
                                queue.append([x+dx_,y+dy_])

mx = -1

for h in range(0,101):
    safe = 0
    board = [[-1]*N for _ in range(N)]
    queue = [[0,0]]
    for i in range(N):
        for j in range(N):
            if board[i][j] == -1:
                if lst[i][j] <= h:
                    board[i][j] = 0
                else:
                    safe += 1
                    bfs(i,j,lst,board)
                
                
    if safe > mx:
        mx = safe

print(mx)
    
                








