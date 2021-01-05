T = int(input())
for _ in range(T):
    N = int(input())

    lst = []
    lst.append(list(map(int,input().split())))
    lst.append(list(map(int,input().split())))
    
    # D = 대각선 P = 대각선+1
    D = [[0]*N for _ in range(2)]
    P = [[0]*N for _ in range(2)]

    D[0][0] = lst[0][0]
    D[1][0] = lst[1][0]
    P[0][0] = lst[0][0]
    P[1][0] = lst[1][0]
    D[0][1] = lst[1][0] + lst[0][1]
    D[1][1] = lst[0][0] + lst[1][1]
    P[0][1] = lst[0][1]
    P[1][1] = lst[1][1]

    for i in range(2,N):
        for j in range(2):
            D[j][i] = max(D[abs(j-1)][i-1],P[abs(j-1)][i-1])+lst[j][i]
            P[j][i] = max(D[abs(j-1)][i-2],P[abs(j-1)][i-2])+lst[j][i]
    print(max(D[0][N-2],D[1][N-2],D[0][N-1],D[1][N-1],P[0][N-2],P[1][N-2],P[0][N-1],P[1][N-1]))
    
    # print(D)
    # print(P)



