N = int(input())

lst = [[0]*N for _ in range(3)]
count = 0
def recur(lst,r,c):
    global count
    if  r>2 or c>N-1:
        return
    elif lst[r][c]:
        if c != N-1:
            recur(lst,r,c+1)
        else:
            recur(lst,r+1,c)
    if r==2 and c==(N-1):
        count += 1
    lst[r][c]=1
    lst_1 = [[r for r in row] for row in lst]
    lst_2 = [[r for r in row] for row in lst]
    lst_1[]

