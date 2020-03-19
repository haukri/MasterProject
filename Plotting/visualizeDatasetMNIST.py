import json
import matplotlib.pyplot as plt

dataset = []

with open('mnist_train.txt') as f:
    dataset = json.loads(f.read())
    # print(dataset[0]['input'])
    # print(sum([x[0] for x in dataset[0]['input']]))

image_x = []
image_y = []

for x in dataset[10]['input']:
    image_x = image_x + int(x[0])*[int(x[1])]

image_x_index = []
for x in range(20):
    image_x_index = image_x_index + 20*[x]

image_y = list(range(20))*20

image = list(zip(image_x, image_x_index, image_y))

image_x = [x[2] for x in image if x[0] == 1]
image_y = [x[1] for x in image if x[0] == 1]

print(dataset[10]['label'])

plt.scatter(image_x, image_y, marker='s', linewidths=8)

plt.show()