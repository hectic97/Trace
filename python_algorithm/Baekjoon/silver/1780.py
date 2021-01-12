import sys
sys.setrecursionlimit(10**6)

    
N = int(input())
result = [0,0,0]
lst = []


def check(x,y,n):
    for i in range(x, x+n):
        for j in range(y, y+n):
            if lst[x][y] != lst[i][j]:
                return False
    return True


def sol(x,y,n):
    if check(x,y,n):
        result[lst[x][y]+1] += 1
        return
    n = n//3
    for i in range(3):
        for j in range(3):
            sol(x+i*n,y+n*j,n)

for _ in range(N):
    lst.append(list(map(int,sys.stdin.readline().split())))

sol(0,0,N)

for r in result:
    print(r)
