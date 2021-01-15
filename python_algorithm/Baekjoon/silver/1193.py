N = int(input())
lst = []

def recur(a,b):
    if len(lst) >= N:
        return
    if not b:
        recur(1,a)
    else:
        lst.append(str(a)+'/'+str(b))
        recur(a+1,b-1)
recur(1,1)
print(lst)
print(lst[N-1])
        

    