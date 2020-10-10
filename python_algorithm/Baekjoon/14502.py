import copy,sys
arr = []
virusList = []
dx = [-1, 1, 0, 0]
dy = [0, 0, -1, 1]
maxVal = 0

def getSafeArea(copyed):
    safe = 0
    for i in range(N):
        for j in range(M):
            if copyed[i][j] == 0:
                safe += 1
    return safe

def spreadVirus(x, y, copyed):
    for i in range(4):
        nx = x + dx[i]
        ny = y + dy[i]

        if 0 <= nx and nx < N and 0 <= ny and ny < M:
            if copyed[nx][ny] == 0:
                copyed[nx][ny] = 2
                spreadVirus(nx, ny, copyed)

def setWall(start, depth):
    global maxVal

    if depth == 3:
        copyed = copy.deepcopy(arr) 
        length = len(virusList)
        for i in range(length):
            [virusX, virusY] = virusList[i]
            spreadVirus(virusX, virusY, copyed)
        maxVal = max(maxVal, getSafeArea(copyed))
        return
    
    for i in range(start, N*M):
        x = (int) (i / M)
        y = (int) (i % M)

        if arr[x][y] == 0:
            arr[x][y] = 1
            setWall(i + 1, depth + 1)
            arr[x][y] = 0


N, M = map(int, sys.stdin.readline().split())
for i in range(N):
    arr.append(list(map(int, sys.stdin.readline().split())))
for i in range(N):
    for j in range(M):
        if arr[i][j] == 2:
            virusList.append([i, j])
setWall(0, 0)
print(maxVal)
