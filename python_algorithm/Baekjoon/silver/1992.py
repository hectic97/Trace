import sys

N = int(input())
lst = []
for _ in range(N):
    lst.append(list(map(int,sys.stdin.readline().strip())))
def recur(l,N):
    if N == 1:
        print(l[0][0],end='')
        return
    elif sum([sum(x) for x in l]) == 0:
        print(0,end='')
        return
    elif sum([sum(x) for x in l]) == N**2:
        print(1,end='')
        return
    else:
        left_up = [x[:int(N/2)] for x in l[:int(N/2)]]
        right_up = [x[int(N/2):] for x in l[:int(N/2)]]
        left_down = [x[:int(N/2)] for x in l[int(N/2):]]
        right_down = [x[int(N/2):] for x in l[int(N/2):]]
        print('(',end='')
        recur(left_up,int(N/2))
        recur(right_up,int(N/2))
        recur(left_down,int(N/2))
        recur(right_down,int(N/2))
        print(')',end='')
    
recur(lst,N)