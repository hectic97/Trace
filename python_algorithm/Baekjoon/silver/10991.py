N = int(input())
def line_arr(row):
    arr=[' ']*(N+row)
    i = N+row-1
    num_star = 0
    while(i >= 0 and num_star < row+1):
        arr[i] = '*'
        i -= 2
        num_star += 1
    return arr

for i in range(N):
    for x in line_arr(i):
        print(x,end='')
    print('')
        


