import matplotlib.pyplot as plt
import os

plotname = 'mnist_ann'

# ------------- Plot Setup ------------- #
plt.ylim(0, 100)
# plt.xlim(0, 1000)
plt.title('ANN Training on MNIST dataset', fontsize='large', fontweight='bold')
plt.xlabel('Trained batches', fontsize='large', fontweight='bold')
plt.ylabel('Accuracy (%)', fontsize='large', fontweight='bold')
plt.grid()
# ------------- Plot Setup ------------- #

data = []
with open('MNIST_ANN_Results_3.txt') as f:
    data = f.readlines()

data = [[float(y) for y in x.strip().split(',')] for x in data]

plt.plot([x[0] for x in data], [x[1]*100 for x in data], color='b', linewidth=1.5, label='Current batch')
plt.plot([x[0] for x in data], [x[2]*100 for x in data], color='r', linewidth=1.5, label='Validation set')

# ------------- Save and show plot ------------- #
plt.legend(prop=dict(weight='bold', size='large'))
plt.savefig(os.path.dirname(os.path.abspath(__file__)) + '/figures/' + plotname + '.png', bbox_inches='tight', dpi=300)
plt.show()
# ------------- Save and show plot ------------- #