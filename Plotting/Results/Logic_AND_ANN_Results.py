import matplotlib.pyplot as plt
import os

plotname = 'logic_and_ann'

# ------------- Plot Setup ------------- #
plt.ylim(0, 3)
plt.xlim(0, 2000)
plt.title('ANN Training on AND Gate', fontsize='large', fontweight='bold')
plt.xlabel('Trained batches', fontsize='large', fontweight='bold')
plt.ylabel('Mean Square Error', fontsize='large', fontweight='bold')
plt.grid()
# ------------- Plot Setup ------------- #

data = []
with open('Logic_AND_ANN_Results.txt') as f:
    data = f.readlines()

data = [[float(y) for y in x.strip().split(',')] for x in data]

plt.plot([x[0] for x in data], [x[1] for x in data], color='b', linewidth=1.5, label='Training set')

# ------------- Save and show plot ------------- #
plt.legend(prop=dict(weight='bold', size='large'))
plt.savefig(os.path.dirname(os.path.abspath(__file__)) + '/figures/' + plotname + '.png', bbox_inches='tight', dpi=300)
plt.show()
# ------------- Save and show plot ------------- #