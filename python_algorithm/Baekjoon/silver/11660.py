import sys

N, M = list(map(int, sys.stdin.readline().split()))

lst = [[0] * (N + 1)]

for _ in range(N):
    ls = [0] + [int(x) for x in sys.stdin.readline().split()]
    lst.append(ls)


for i in range(1, N + 1):
    for j in range(1, N):
        lst[i][j + 1] += lst[i][j]
for j in range(1, N + 1):
    for i in range(1, N):
        lst[i + 1][j] += lst[i][j]

for _ in range(M):
    x1, y1, x2, y2 = map(int, sys.stdin.readline().split())
    print(lst[x2][y2] - lst[x1 - 1][y2] - lst[x2][y1 - 1] + lst[x1 - 1][y1 - 1])