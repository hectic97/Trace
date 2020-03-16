"""net = x1*w1 + x2*w2 + x3*w3
to make (0,1) is the only variable that y is 1
in w1 and w2 coordinate system the gradient of x1*w1+x2*w2+w3=0 should be a postive number
and w2-axis intercept == bias should be between range(0,1)
 for example x2 = 1*x1 + 0.5 can discriminate only (0,1)
 So w1 = -1, w2 = 1, w3 = -0.5 can be one of the answers"""

#Verification
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

forward_propagation()
