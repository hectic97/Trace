A,B,C,X,Y = list(map(int,input().split(' ')))
cost = A*X+B*Y
for i in range(100001):
    if cost >= 2*i*C + max(0,X-i)*A + max(0,Y-i)*B :
        cost = 2*i*C + max(0,X-i)*A + max(0,Y-i)*B
print(cost)