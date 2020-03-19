
w1 = [1.0, 1.0, -1.0]
w2 = [1.0, 2.0, -1.5]
w3 = [1.0, 1.0, -0.5]
y1 = []
y2 = []
def forward_propagation(x,w,is_y=False):
    net = 0
    for i in range(3):
        net += x[i]*w[i]
    if net > 0:
        y = 1
    else:
        y = 0
    if is_y:
        print('y1:',x[0],'y2:',x[1],'net:',net,'y:', y)
    else:
        print('x1:',x[0],'x2:',x[1],'net:',net,'y:', y)
    return y
print('First table answer')
#input: [x1,x2,b] and [w11,w12,w13]
y1.append(forward_propagation([0,0,1], w1))
y1.append(forward_propagation([0,1,1], w1))
y1.append(forward_propagation([1,0,1], w1))
y1.append(forward_propagation([1,1,1], w1))

print('Second table answer')
#input: [x1,x2,b] and [w21,w22,w23]
y2.append(forward_propagation([0,0,1], w2))
y2.append(forward_propagation([0,1,1], w2))
y2.append(forward_propagation([1,0,1], w2))
y2.append(forward_propagation([1,1,1], w2))

print('Third table answer')
#input: [y1,y2,b] and [w31,w32,w33]
print("If x1: 0 x2: 0")
forward_propagation([y1[0],y2[0],1], w3, True)
print("\nIf x1: 0 x2: 1")
forward_propagation([y1[1],y2[1],1], w3, True)
print("\nIf x1: 1 x2: 0")
forward_propagation([y1[2],y2[2],1], w3, True)
print("\nIf x1: 1 x2: 1")
forward_propagation([y1[3],y2[3],1], w3, True)


