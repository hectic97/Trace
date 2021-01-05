n = int(input())

ct = 0
def queen(n, lst):
    global ct
    if len(lst) == n:
        ct += 1
        return 0
    poten = list(range(n))
    for i,col in enumerate(lst):
        if col in poten:
            poten.remove(col)
        # print('lst: ',lst,'i: ',i)
        dist = len(lst)-i
        # print('dist:', dist)
        if col+dist in poten:
            poten.remove(col+dist)
        if col-dist in poten:
            poten.remove(col-dist)
        # print(poten,'\n')
    if poten == []:
        # print('!empty!')
        return 0
    else:
        for p in poten:
            queen(n, lst+[p])

for i in range(n):
    queen(n,[i])
print(ct)
