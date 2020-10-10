Data = [(0.0,0.0),(1.0,1.0),(1.0,2.0),(2.0,1.0)]
from sympy import *            # I can't help using sympy package to solve eqiation and describe variable
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
numeric_w0, numeric_w1, numeric_w2 = 1, 1, 1   # arbitrarily choose initial weights


iteration = 1000
learning_rate = 0.01
for i in range(iteration):
    numeric_dw0 = dw0.subs([(w0, numeric_w0), (w1, numeric_w1), (w2, numeric_w2)])  # dE/dw0 when wi=numeric wi
    numeric_dw1 = dw1.subs([(w0, numeric_w0), (w1, numeric_w1), (w2, numeric_w2)])   # i = 0,1,2
    numeric_dw2 = dw2.subs([(w0, numeric_w0), (w1, numeric_w1), (w2, numeric_w2)])
    numeric_w0 -= learning_rate * numeric_dw0  # update weights
    numeric_w1 -= learning_rate * numeric_dw1
    numeric_w2 -= learning_rate * numeric_dw2

    total_loss = 0

    for x in Data:
        total_loss += loss_function(x, [numeric_w0,numeric_w1,numeric_w2])  # Sum all losses
    if i%10 == 0:

        print('iteration {}th LOSS: {:.6f}'.format(i,total_loss))  # print lose to watch lose decreased

print('###Final###\n{:.2f},{:.2f},{:.2f}'.format(numeric_w2, numeric_w1, numeric_w0)) #print Final optimized weights