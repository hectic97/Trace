N = int(input())
arr = [' ']*N
for i in range(N):
    arr[i] = '*'
    for x in reversed(arr):
        print(x,end='')
    print('')
for i in reversed(range(N)):
    arr[i] = ' '
    for x in reversed(arr):
        print(x,end='')
    if i != 0:
        print('')