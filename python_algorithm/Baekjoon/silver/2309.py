lst = []
for _ in range(9):
    lst.append(int(input()))
for i in range(9):
    for j in range(i+1,9):
        if sum(lst)-lst[i]-lst[j] == 100:
            for k,x in enumerate(sorted(lst)):
                if x != lst[i] and x != lst[j]:
                    print(x)
            exit(0)




