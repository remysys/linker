import torch
import torch.nn as nn
import torch.optim as optim

inputs = torch.tensor([[1.0, 2.0, 3.0, 4.0, 5.0],
                       [1.0, 0.0, 0.0, 0.0, 0.0],
                       [0.0, 1.0, 0.0, 0.0, 0.0]])

labels = torch.tensor([0, 1, 2])

model = nn.Linear(5, 3)

loss_fn = nn.CrossEntropyLoss()
optimizer = optim.SGD(model.parameters(), lr=0.01)

outputs = model(inputs)

loss = loss_fn(outputs, labels)
print(f"loss: {loss.item()}")

optimizer.zero_grad()
loss.backward()
optimizer.step()