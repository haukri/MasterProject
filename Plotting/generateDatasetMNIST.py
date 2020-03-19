import json
import matplotlib.pyplot as plt

dataset = []
output_dataset = []

with open('mnist_train.txt') as f:
    dataset = json.loads(f.read())

for single_image in dataset:

    image_x = []
    image_y = []

    for x in single_image['input']:
        image_x = image_x + int(x[0])*[int(x[1])]

    output_dataset.append(','.join([str(single_image['label'])] + [str(x) for x in image_x]) + '\n')

with open('mnist_test.txt') as f:
    dataset = json.loads(f.read())

for single_image in dataset:

    image_x = []
    image_y = []

    for x in single_image['input']:
        image_x = image_x + int(x[0])*[int(x[1])]

    output_dataset.append(','.join([str(single_image['label'])] + [str(x) for x in image_x]) + '\n')

with open('mnist_train.csv', 'w') as f:
    f.writelines(output_dataset)