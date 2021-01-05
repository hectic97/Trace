N = int(input())
P = list(map(int,input().split()))

print(sum([sum(sorted(P)[:i+1]) for i in range(N)]))