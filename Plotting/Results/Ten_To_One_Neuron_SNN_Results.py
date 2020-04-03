import matplotlib.pyplot as plt
import os
from collections import defaultdict
import math
from scipy import signal

plotname = 'ten_to_one_neuron_snn'

# ------------- Plot Setup ------------- #
plt.rcParams['figure.figsize'] = (8,6)
fig, axs = plt.subplots(2, 1, sharex='col')
plt.ylim(-2, 18)
plt.xlim(0, 0.4)
axs[0].set_title('Incoming spikes from 10 neurons', fontsize='large', fontweight='bold')
axs[1].set_title('Leaky integrate-and-fire neuron (iaf_psc_alpha)', fontsize='large', fontweight='bold')
plt.xlabel('Time [s]', fontsize='large', fontweight='bold')
axs[0].set_ylabel('Neuron index', fontsize='large', fontweight='bold')
axs[1].set_ylabel('Membrane Potential [mV]', fontsize='large', fontweight='bold')
plt.grid()
# ------------- Plot Setup ------------- #

valueContent = []
eventContent = []

with open('./Ten_To_One_Neuron_SNN_Results_Value.csv') as f:
    names = f.readline()
    valueContent = [x.strip().split(',') for x in f.readlines()]

with open('./Ten_To_One_Neuron_SNN_Results_Event.csv') as f:
    names = f.readline()
    eventContent = [x.strip().split(',') for x in f.readlines()]

def plotValueOutputs(populationID, neuronID, valueType, label):
    x = [float(x[0]) for x in valueContent if populationID == x[1] and neuronID == x[2] and valueType == x[3]]
    y = [float(x[4]) for x in valueContent if populationID == x[1] and neuronID == x[2] and valueType == x[3]]
    axs[1].plot(x, y, label=label)

def plotSpikeOutputs(populationID, neuronID, color='blue'):
    x = [float(x[0]) for x in eventContent if populationID == x[1] and neuronID == x[2] and x[3] == '0']
    y = [int(neuronID) for x in eventContent if populationID == x[1] and neuronID == x[2] and x[3] == '0']
    axs[0].eventplot(x, lineoffsets=int(neuronID), linelengths=0.7, color=color)

for i in [float(x[0]) for x in eventContent if '93977314611376' == x[1] and '0' == x[2] and x[3] == '0']:
    axs[1].axvline(x=i, color='r', linewidth=1)

plotValueOutputs('93977314611376', '0', '0', 'Neuron Membrane Potential')

for i in range(10):
    plotSpikeOutputs('93977314607008', str(i))


# ------------- Save and show plot ------------- #
# plt.legend(prop=dict(weight='bold', size='large'))
plt.savefig(os.path.dirname(os.path.abspath(__file__)) + '/figures/' + plotname + '.png', bbox_inches='tight', dpi=300)
plt.show()
# ------------- Save and show plot ------------- #