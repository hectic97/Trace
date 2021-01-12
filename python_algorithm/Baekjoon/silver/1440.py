s = list(map(int,input().split(':')))
count = 0 
for c in s:
    if c >= 60:
        count = 3
        break
    elif not 1 <= c <= 12:
        count += 1
print(6-count*2)
