import numpy as np
import matplotlib.pyplot as plt

class scratchMLP():
    def __init__(self, **kwargs):
        self.num_of_nodes = kwargs['num_of_nodes']
        self.lr = kwargs['lr']
        self.act_func = [None]
        self.weights = [None]
        self.bias = [None]

    def identity(self, x):
        return x

    def sigmoid(self, x, mode='f'):
        if mode == 'f':
            return 1 / (1 + np.power(np.e, -x))

        elif mode == 'b':
            y = self.sigmoid(x, 'f')
            return y * (1-y)

    def init_params(self):
        for i in range(1, len(self.num_of_nodes)):
            self.weights.append(np.random.normal(0, np.sqrt(2 / (self.num_of_nodes[i-1] + self.num_of_nodes[i])), size=(self.num_of_nodes[i-1],self.num_of_nodes[i])))
            self.bias.append(np.zeros((self.num_of_nodes[i])))    
            if i == len(self.num_of_nodes) - 1:
                self.act_func.append(self.identity)
            else:
                self.act_func.append(self.sigmoid)
            
    def forward(self, x):
        self.Z = [x]
        self.A = [x]
        for i in range(1, len(self.num_of_nodes)):
            z = self.A[i-1].dot(self.weights[i]) + self.bias[i]
            a = self.act_func[i](z)
            self.Z.append(z)
            self.A.append(a)

        return self.A[-1]

    def backward(self, x, y):
        pred = self.forward(x)
        self.dZ = []

        for i in reversed(range(1, len(self.num_of_nodes))):
            if i == len(self.num_of_nodes) - 1:
                c_dZ = pred - y
            else:
                c_dZ = self.sigmoid(self.Z[i], mode='b') * (self.dZ[-1].dot(self.weights[i+1].T))
            
            dW = self.A[i-1].T.dot(c_dZ)
            db = np.sum(c_dZ, axis=0)

            self.weights[i] -= self.lr * dW
            self.bias[i] -= self.lr*db
            self.dZ.append(c_dZ)
    
    def eval(self, x, y):
        pred = self.forward(x)
        loss = np.mean(np.sqrt(np.power(pred - y, 2)))
        return loss


if __name__ == '__main__':
    
    smlp = scratchMLP(num_of_nodes = [1,5,5,5,1], lr=0.001)
    x = np.linspace(-2,2,100)
    y = np.cos(x)
    x = x[..., np.newaxis]
    y = y[..., np.newaxis]

    smlp.init_params()
    pred = smlp.forward(x)

    for i in range(20000):
        smlp.backward(x, y)
        err = smlp.eval(x, y)
        if not i % 100 :
            print(f"epoch {i} loss:{err}")
            plt.figure(figsize=(16,16))
            plt.plot(x.ravel(), y.ravel(), c='r', label='true')
            plt.plot(x.ravel(), smlp.forward(x).ravel(), c='b', label='pred')
            plt.legend()
            plt.savefig(f'{i}_step.png')
    

    

