for _ in range(int(input())):
    lst=list(map(int,input().split(' ')))
    iter_lst = []
    i = 1
    while(1):
        if ((lst[0] % 10) ** i) % 10  in iter_lst:
            break
        iter_lst.append((lst[0]%10) ** i % 10)
        i += 1
    print(iter_lst[lst[1] % len(iter_lst) - 1])
