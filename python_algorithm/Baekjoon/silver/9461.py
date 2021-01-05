T = int(input())
N = []
for _ in range(T):
    N.append(int(input()))

lst = [1,1,1,2,2]
for i in range(5,100):
    lst.append(lst[-1]+lst[i-5])

for n in N:
    print(lst[n-1])
