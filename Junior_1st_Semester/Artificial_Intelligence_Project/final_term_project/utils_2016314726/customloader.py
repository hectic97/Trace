import torch

import numpy as np
from torch.utils.data import Dataset, DataLoader
from PIL import Image


class CustomDataset(Dataset):
    def __init__(self, x_path, y_path, transform=None):
        self.x_path = x_path
        self.y_path = y_path
        self.transform = transform

        self.data = np.transpose(np.load(self.x_path), (0, 3, 1, 2))
        self.targets = torch.LongTensor(np.load(self.y_path))

        print(self.data.shape)
        print(self.targets.shape)

    def __len__(self):
        return self.targets.shape[0]

    def __getitem__(self, index):
        x = self.data[index]
        y = self.targets[index]

        if self.transform:
            x = Image.fromarray(self.data[index].astype(np.uint8).transpose(1, 2, 0))
            x = self.transform(x)

        return x, y
