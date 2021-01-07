N = int(input())
arr = []
for i in range(N):
    arr.append(' '*i+'*'*(2*(N-i)-1))
    print(' '*i+'*'*(2*(N-i)-1))
for line in reversed(arr[:-1]):
    print(line)