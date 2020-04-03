import matplotlib.pyplot as plt
import os
from collections import defaultdict
import math
from scipy import signal

plotname = 'one_neuron_nest_tinyspike'

# ------------- Plot Setup ------------- #
plt.rcParams['figure.figsize'] = (8,6)
fig, axs = plt.subplots(2, 1, sharex='col')
axs[0].set_ylim(-80, -54)
axs[0].set_xlim(0, 1.0)
axs[1].set_ylim(-0.00008, 0.00008)
axs[0].set_title('Leaky integrate-and-fire neuron (iaf_psc_alpha)', fontsize='large', fontweight='bold')
axs[1].set_title('Error between Nest simulation and TinySpike', fontsize='large', fontweight='bold')
plt.xlabel('Time [s]', fontsize='large', fontweight='bold')
axs[0].set_ylabel('Membrane Potential [mV]', fontsize='large', fontweight='bold')
axs[1].set_ylabel('Error [mV]', fontsize='large', fontweight='bold')
axs[0].grid()
axs[1].grid()
# ------------- Plot Setup ------------- #

latest_event_file = max([f for f in os.scandir("../../../Logs") if "event" in f.name], key=lambda x: x.stat().st_mtime).name
latest_value_file = max([f for f in os.scandir("../../../Logs") if "value" in f.name], key=lambda x: x.stat().st_mtime).name

valueContent = []
eventContent = []

nestValueContent = []
nestEventContent = []

with open('./value.csv') as f:
    names = f.readline()
    valueContent = [x.strip().split(',') for x in f.readlines()]

with open('./event.csv') as f:
    names = f.readline()
    eventContent = [x.strip().split(',') for x in f.readlines()]

with open('./Nest_output.csv') as f:
    nestValueContent = [x.strip().split(',') for x in f.readlines()]


def plotValueOutputs(populationID, neuronID, valueType, label):
    x = [float(x[0]) for x in valueContent if populationID == x[1] and neuronID == x[2] and valueType == x[3]]
    y = [float(x[4]) for x in valueContent if populationID == x[1] and neuronID == x[2] and valueType == x[3]]
    axs[0].plot(x, y, label=label)

def plotSpikeOutputs(populationID, neuronID, color='blue'):
    x = [float(x[0]) for x in eventContent if populationID == x[1] and neuronID == x[2] and x[3] == '0']
    y = [int(neuronID) for x in eventContent if populationID == x[1] and neuronID == x[2] and x[3] == '0']
    plt.eventplot(x, lineoffsets=int(neuronID), linelengths=0.7, color=color)



plotValueOutputs('94575147126784', '0', '0', 'TinyNN Neuron')

# Plot Nest values
x = [float(x[0]) for x in nestValueContent]
y = [float(x[1]) for x in nestValueContent]
axs[0].plot(x, y, label='Nest Neuron')

# Plot difference
y = []
for nest, sim in zip([float(x[1]) for x in nestValueContent], [float(x[4]) for x in valueContent if '94575147126784' == x[1] and '0' == x[2] and '0' == x[3]][:-1]):
    y.append(nest - sim)
axs[1].plot(x, y, label='Nest Neuron Membrane Potential')


# ------------- Save and show plot ------------- #
axs[0].legend(prop=dict(weight='bold', size='large'))
plt.savefig(os.path.dirname(os.path.abspath(__file__)) + '/../figures/' + plotname + '.png', bbox_inches='tight', dpi=300)
plt.show()
# ------------- Save and show plot ------------- #