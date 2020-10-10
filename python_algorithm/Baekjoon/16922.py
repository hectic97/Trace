N = int(input())
lst = [0 for x in range(20*50+1)]
for i in range(N+1):
    for v in range(N+1-i):
        for x in range(N+1-i-v):
            l = N-i-v-x
            lst[i+5*v+10*x+50*l] = 1
cnt = 0
for x in lst:
    if x:
        cnt += 1
print(cnt)