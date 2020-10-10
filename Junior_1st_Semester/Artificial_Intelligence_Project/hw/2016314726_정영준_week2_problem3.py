Data = [(0.0,0.0),(1.0,1.0),(1.0,2.0),(2.0,1.0)]
from sympy import *            # I can't help using sympy package to solve equation and describe variables
w0, w1, w2 = symbols('w0 w1 w2') # w0, w1, w2 are variable
w = [w0,w1,w2]                   # w list contains all weights
def forward(input,w):            # define function that derives output
    return w[2]*(input[0]**2)+w[1]*(input[0])+w[0]   # input is one of Data and weight list

def loss(y,output):
    return (y-output)**2

def loss_function(input,w):          #define function to calculate loss between output of forward function and y
    output = forward(input,w)
    return loss(input[1],output)

total_loss = 0

for x in Data:
    total_loss += loss_function(x,w)  # Sum all losses
print(total_loss)            # E(w0,w1,w2)
dw0 = diff(total_loss, w0)    #dE/dw0
dw1 = diff(total_loss, w1)    #dE/dw1
dw2 = diff(total_loss, w2)    #dE/dw2
print(dw0)
print(dw1)
print(dw2)

# dE/dw0 dE/dw1  dE/dw2 is 0 when sum of losses is minimized

print(solve([dw0,dw1,dw2], [w0,w1,w2])) # solve the equation

"""w0: 0.0   w1: 2.5    w2: -1.0"""
