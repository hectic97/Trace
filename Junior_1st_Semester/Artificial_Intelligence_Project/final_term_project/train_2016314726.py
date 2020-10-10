import torch

import torchvision.transforms as transforms
import numpy as np
import torch.nn as nn
import torch.nn.init as init
import math
import sys
import torch.nn.functional as F
sys.path.append("./utils_2016314726")
from customloader import CustomDataset



train_transform = transforms.Compose([
    transforms.RandomHorizontalFlip(0.5),
    transforms.RandomCrop(32, padding=4),
    transforms.ToTensor(),
    transforms.Normalize((0.4911, 0.4824, 0.4462), (0.2469, 0.2434, 0.2617)),])
test_transform = transforms.Compose([
    transforms.ToTensor(),
    transforms.Normalize((0.4911, 0.4824, 0.4462), (0.2469, 0.2434, 0.2617)),])
trainset = CustomDataset("./data/train/x.npy",
                         "./data/train/y.npy", transform=train_transform)
validset = CustomDataset("./data/train/x.npy",
                         "./data/train/y.npy", transform=test_transform)

batch_size = 128
balance_val_index = []
for label in range(0, 91):
    label_index = (trainset.targets == label).nonzero()
    random_index = torch.randperm(label_index.size(0))
    if balance_val_index:
        balance_val_index[0] = torch.cat([balance_val_index[0], label_index[random_index][:1].view(-1, )])
    else:
        balance_val_index.append(label_index[random_index][:1].view(-1, ))


balance_val_index = balance_val_index[0]


balance_train_index = torch.ones(len(trainset.targets))
for x in balance_val_index:
    balance_train_index[x] = 0


balance_train_index = balance_train_index.nonzero().view(-1, )
sub_trainset = torch.utils.data.Subset(trainset, balance_train_index)
targets = trainset.targets[balance_train_index]
class_count = np.unique(targets, return_counts=True)[1]
weight = 1. / class_count
samples_weight = weight[targets]
samples_weight = torch.from_numpy(samples_weight)
train_sampler = torch.utils.data.sampler.WeightedRandomSampler(samples_weight, len(samples_weight))
valid_sampler = torch.utils.data.SubsetRandomSampler(balance_val_index)

train_loader = torch.utils.data.DataLoader(sub_trainset, batch_size=batch_size, sampler=train_sampler, )
val_loader = torch.utils.data.DataLoader(validset, batch_size=batch_size, sampler=valid_sampler)




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


class LabelSmoothLoss(nn.Module):

    def __init__(self, smoothing=0.0):
        super(LabelSmoothLoss, self).__init__()
        self.smoothing = smoothing

    def forward(self, input, target):
        log_prob = F.log_softmax(input, dim=-1)
        weight = input.new_ones(input.size()) * \
                 self.smoothing / (input.size(-1) - 1.)
        weight.scatter_(-1, target.unsqueeze(-1), (1. - self.smoothing))
        loss = (-weight * log_prob).sum(dim=-1).mean()
        return loss
def make_box(size, beta_rate):
    W = size[2]
    H = size[3]
    cm_rate = np.sqrt(1. - beta_rate)
    cut_w = np.int(W * cm_rate)
    cut_h = np.int(H * cm_rate)

    cx = np.random.randint(W)
    cy = np.random.randint(H)

    bbx1 = np.clip(cx - cut_w // 2, 0, W)
    bby1 = np.clip(cy - cut_h // 2, 0, H)
    bbx2 = np.clip(cx + cut_w // 2, 0, W)
    bby2 = np.clip(cy + cut_h // 2, 0, H)

    return bbx1, bby1, bbx2, bby2

device = 'cuda' if torch.cuda.is_available() else 'cpu'
model = WRN()
model= model.to(device)
LR=0.1
EPOCHS=160
cutmix_prob=0.5
loss_func = LabelSmoothLoss(smoothing=0.15)
optimizer = torch.optim.SGD(model.parameters(),lr=LR,momentum=0.9,weight_decay=0.0005,nesterov=True)
lr_scheduler = torch.optim.lr_scheduler.ReduceLROnPlateau(optimizer,mode='max',factor=0.1,patience=8,verbose=True)

for i in range(EPOCHS):
    model.train()
    correct = 0
    total = 0
    for j, [img, label] in enumerate(train_loader):
        r = np.random.rand(1)

        x = img.to(device)
        y = label.to(device)

        optimizer.zero_grad()
        if r < cutmix_prob:
            cut_rate = np.random.beta(1, 1)
            random_index = torch.randperm(x.size(0)).to(device)
            org_label = y
            rand_label = y[random_index]
            bbx1, bby1, bbx2, bby2 = make_box(x.size(), cut_rate)
            x[:, :, bbx1:bbx2, bby1:bby2] = x[random_index, :, bbx1:bbx2, bby1:bby2]
            cut_rate = 1 - ((bbx2 - bbx1) * (bby2 - bby1) / (x.size()[-1] * x.size()[-2]))
            output = model.forward(x)
            loss = loss_func(output, org_label) * cut_rate + loss_func(output, rand_label) * (1 - cut_rate)
        else:

            output = model.forward(x)
            loss = loss_func(output, y)


        _, output_index = torch.max(output, 1)
        loss.backward()
        optimizer.step()
        total += y.size()[0]
        correct += (output_index == y).sum().float()


    lr_scheduler.step(correct * 100 / total)
    with torch.no_grad():
        val_correct = 0
        val_total = 0
        for k, [val_img, val_label] in enumerate(val_loader):
            val_x = val_img.to(device)
            val_y = val_label.to(device)
            model.eval()
            val_output = model.forward(val_x)
            _, val_output_index = torch.max(val_output, 1)
            val_loss = loss_func(val_output, val_y)
            val_total += val_y.size()[0]
            val_correct += (val_output_index == val_y).sum().float()

    print('EPOCHS {:>3d}/{} | train_loss : {:.4f} | train_acc : {:.4f} | val_loss : {:.4f} | val_acc : {:.4f}' \
          .format(i + 1, EPOCHS, loss, correct * 100 / total, val_loss, 100 * val_correct / val_total))

torch.save(model, 'model_2016314726.pth')