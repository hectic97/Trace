import itertools
import sys

N = int(input())
lst = list(map(int,sys.stdin.readline().split()))
op= list(map(int,sys.stdin.readline().split()))
op_lst = []
op_lst.extend(['+']*op[0])
op_lst.extend(['-']*op[1])
op_lst.extend(['x']*op[2])
op_lst.extend(['/']*op[3])

result = []
for p in set(itertools.permutations(op_lst)):
    r = lst[0]
    for i,o in enumerate(p):
        if o == '+':
            r += lst[i+1]
        elif o == '-':
            r -= lst[i+1]
        elif o == 'x':
            r *= lst[i+1]
        elif o == '/':
            if r*lst[i+1] < 0:
                r = -int(abs(r)//abs(lst[i+1]))
            else:
                r = int(r//lst[i+1])
    result.append(r)
print(max(result))
print(min(result))

        
        
        