N = int(input())
def print_line(row):
    arr=[' ']*(2*(row+1)-1)
    arr[0] = '*'
    arr[-1] = '*'
    print(' '*(N-1-row),end='')
    for x in arr:
        print(x,end='')
    print('')
    return

def print_last_line():
    print('*'*(2*N-1))

for i in range(N-1):
    print_line(i)
print_last_line()
