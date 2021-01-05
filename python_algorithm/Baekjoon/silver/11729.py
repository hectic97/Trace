def hanoi(s, t, e, n, lst):
    if n ==1:
        lst.append([s,e])
        return
    hanoi(s, e, t, n-1,lst)
    lst.append([s,e])
    hanoi(t, s, e, n-1,lst)
lst = []
hanoi(1,2,3,int(input()),lst)
print(len(lst))
for a in lst:
    print(*a)


