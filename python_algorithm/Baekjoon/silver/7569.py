from collections import deque
import sys

M, N, H = map(int, input().split())

board = []

for _ in range(H):
    lst = []
    for _ in range(N):
        lst.append(list(map(int, sys.stdin.readline().split())))
        
    board.append(lst)
    
toma = deque()

for i in range(H):
    for j in range(N):
        for k in range(M):
            if(board[i][j][k] == 1):
                toma.append([i, j, k])

dx = [1, -1, 0, 0, 0, 0]
dy = [0, 0, 1, -1, 0, 0]
dh = [0, 0, 0, 0, 1, -1]

while toma:
    h, r, c = toma.popleft()
    
    for k in range(6):
        _h = h + dh[k]
        _r = r + dy[k]
        _c = c + dx[k]
        
        if 0 <= _h < H and 0 <= _r < N and 0 <= _c < M and board[_h][_r][_c] == 0:
            toma.append([_h, _r, _c])
            board[_h][_r][_c] = board[h][r][c] + 1
            
check = False
result = -2

for i in board:
    for j in i:
        for k in j:
            if(k == 0):
                check = True
            result = max(result, k)
            
if check:
    print(-1)
elif(result == -1):
    print(0)
else:
    print(result - 1)