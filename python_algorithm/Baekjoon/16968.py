a = input()
num = 1
for i,x in enumerate(a):
    cnt = 26 if x == 'c' else 10
    if i > 0 and a[i] == a[i-1]:
        cnt -= 1
    num *= cnt
print(num)