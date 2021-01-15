import sys
from collections import deque

T = int(input())

for _ in range(T):
    p = input()
    n = int(input())
    lst = sys.stdin.readline().strip()
    try:
        dq=deque(list(map(int,lst.replace('[','').replace(']','').split(','))))
    except:
        dq = deque([])
    err = False
    r = 0
    for f in p:
        if f=='R':
            r = abs(r-1)
        else:
            try:
                if r:
                    dq.pop()
                else:
                    dq.popleft()
            except:
                err =True
                print('error')
                break
    if err:
        continue
    else:
        if r:
            dq.reverse()
            print(str(list(dq)).replace(' ',''))
        else:
            print(str(list(dq)).replace(' ',''))
    

