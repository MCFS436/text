import cv2
import torch
import torch.nn as nn
import torch.optim as optim
import torch.nn.functional as F
 
# 定义一个简单的卷积神经网络
class ConvNet(nn.Module):
    def __init__(self):
        super(ConvNet, self).__init__()
        self.conv1 = nn.Conv2d(in_channels=1, out_channels=10, kernel_size=5)
        self.conv2 = nn.Conv2d(in_channels=10, out_channels=20, kernel_size=5)
        self.fc = nn.Linear(in_features=20 * 4 * 4, out_features=10)
 
    def forward(self, x):
        in_size = x.size(0)
        x = F.relu(self.conv1(x))
        x = F.max_pool2d(x, kernel_size=2, stride=2)
        x = F.relu(self.conv2(x))
        x = F.max_pool2d(x, kernel_size=2, stride=2)
        x = x.view(in_size, -1)
        x = self.fc(x)
        return x
 
# 实例化网络、损失函数和优化器
model = ConvNet()
criterion = nn.CrossEntropyLoss()
optimizer = optim.SGD(model.parameters(), lr=0.01, momentum=0.5)
 
# 随机生成一些数据作为示例
inputs = torch.randn(1, 1, 28, 28)
labels = torch.randint(10, (1,), dtype=torch.long)
 
# 前向传播、计算损失、反向传播和优化
optimizer.zero_grad()
outputs = model(inputs)
loss = criterion(outputs, labels)
loss.backward()
optimizer.step()
 
print("Loss:", loss.item())
