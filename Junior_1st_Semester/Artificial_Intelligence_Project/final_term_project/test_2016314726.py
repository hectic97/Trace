import torchvision.transforms as transforms
import sys
sys.path.append("./utils_2016314726")
from customloader import CustomDataset
import torch
import torch.nn as nn
import torch.nn.init as init
import math



class SENet(nn.Module):
    def __init__(self, channel, reduction):
        super(SENet, self).__init__()
        self.avg_pool = nn.AdaptiveAvgPool2d(1)
        self.dense_1 = nn.Linear(channel, channel // reduction, True)
        self.relu = nn.ReLU()
        self.dense_2 = nn.Linear(channel // reduction, channel, True)
        self.sigmoid = nn.Sigmoid()

    def forward(self, x):
        batch = x.size(0)
        ch = x.size(1)
        out = self.avg_pool(x)
        out = out.view(batch, ch)
        out = self.dense_1(out)
        out = self.relu(out)
        out = self.dense_2(out)
        out = self.sigmoid(out)
        out = out.view(batch, ch, 1, 1)
        return x * out.expand(x.size())


def _weights_init(m):
    classname = m.__class__.__name__
    if isinstance(m, nn.Linear) or isinstance(m, nn.Conv2d):
        init.kaiming_normal_(m.weight)



class LayerBlock(nn.Module):
    def __init__(self, in_dim, out_dim, stride=1, down=None):
        super(LayerBlock, self).__init__()

        self.bn1 = nn.BatchNorm2d(in_dim)
        self.bn2 = nn.BatchNorm2d(out_dim)
        self.relu = nn.ReLU(inplace=True)
        self.conv1 = nn.Conv2d(in_dim, out_dim, 3, stride, 1, bias=False)
        self.conv2 = nn.Conv2d(out_dim, out_dim, 3, 1, padding=1, bias=False)
        self.down = down
        self.in_dim = in_dim
        self.out_dim = out_dim
        self.stride = stride

        self.match_size = nn.Sequential(
            nn.Conv2d(in_dim, out_dim, 1, self.stride, bias=False),
        )
        self.se_layer = nn.Sequential(SENet(self.out_dim, 16))

    def forward(self, x):
        out = self.bn1(x)
        out = self.relu(out)
        out = self.conv1(out)
        out = self.bn2(out)
        out = self.relu(out)
        out = self.conv2(out)

        if self.down:
            down_x = self.match_size(x)

            out = self.se_layer(out)
            out = out + down_x
        else:

            out = self.se_layer(out)
            out = out + x

        return out


class WRN(nn.Module):
    def __init__(self):
        super(WRN, self).__init__()
        self.conv1 = nn.Conv2d(3, 16, 3, 1, 1, bias=False)
        self.bn = nn.BatchNorm2d(640)
        self.avgpool = nn.AvgPool2d(8)
        self.relu = nn.ReLU(inplace=True)
        self.layer1 = nn.Sequential(
            LayerBlock(16, 160, stride=1, down=True),
            LayerBlock(160, 160),
            LayerBlock(160, 160),
            LayerBlock(160, 160),

        )
        self.layer2 = nn.Sequential(
            LayerBlock(160, 320, stride=2, down=True),
            LayerBlock(320, 320),
            LayerBlock(320, 320),
            LayerBlock(320, 320),

        )
        self.layer3 = nn.Sequential(
            LayerBlock(320, 640, stride=2, down=True),
            LayerBlock(640, 640),
            LayerBlock(640, 640),
            LayerBlock(640, 640),

        )
        self.dense = nn.Linear(640, 91)
        for m in self.modules():
            if isinstance(m, nn.Conv2d):
                n = m.kernel_size[0] * m.kernel_size[1] * m.out_channels
                m.weight.data.normal_(0, math.sqrt(2. / n))
            elif isinstance(m, nn.BatchNorm2d):
                m.weight.data.fill_(1)
                m.bias.data.zero_()
            elif isinstance(m, nn.Linear):
                init.kaiming_normal(m.weight)
                m.bias.data.zero_()

    def forward(self, x):
        out = self.conv1(x)
        out = self.layer1(out)
        out = self.layer2(out)
        out = self.layer3(out)
        out = self.bn(out)
        out = self.relu(out)
        out = self.avgpool(out)
        out = out.view(out.size(0), -1)
        out = self.dense(out)

        return out
device = 'cuda' if torch.cuda.is_available() else 'cpu'

test_transform = transforms.Compose([
    transforms.ToTensor(),
    transforms.Normalize((0.4911, 0.4824, 0.4462), (0.2469, 0.2434, 0.2617)),])

model=torch.load('model_2016314726.pth',map_location=torch.device(device))

testset = CustomDataset("./data/test/x.npy","./data/test/y.npy",transform=test_transform)
test_loader = torch.utils.data.DataLoader(testset,batch_size=128, )

model.eval()
correct = 0
total = 0

with torch.no_grad():

    for image, label in test_loader:

        x = image.to(device)
        y = label.to(device)


        output = model.forward(x)
        _, output_index = torch.max(output, 1)
        total += label.size(0)
        correct += (output_index == y).sum().float()



    print('Accuracy of Testset : {:.4f}'.format(100 * correct / total))