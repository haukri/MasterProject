import matplotlib.pyplot as plt
import os
from collections import defaultdict
import math
from scipy import signal
import scipy.fftpack
import shutil
import numpy as np

plotname = 'bsa_sine_lowpass_results'

# ------------- Plot Setup ------------- #
plt.rcParams['figure.figsize'] = (8,6)
fig, axs = plt.subplots(2, 1, sharex='col')
# axs[0].set_ylim(300, 1800)
axs[0].set_xlim(0.2, 0.6)
# axs[1].set_ylim(0, 200)
axs[0].set_title('Rate coding synapse with different time windows w', fontsize='large', fontweight='bold')
axs[1].set_title('200 Leaky intergrate-and-fire neurons (iaf_psc_alpha)', fontsize='large', fontweight='bold')
plt.xlabel('Time [s]', fontsize='large', fontweight='bold')
axs[0].set_ylabel('Spike Rate', fontsize='large', fontweight='bold')
axs[1].set_ylabel('Neuron Index', fontsize='large', fontweight='bold')
axs[0].grid()
axs[1].grid()
# ------------- Plot Setup ------------- #

latest_event_file = max([f for f in os.scandir("../../../Logs") if "event" in f.name], key=lambda x: x.stat().st_mtime).name
latest_value_file = max([f for f in os.scandir("../../../Logs") if "value" in f.name], key=lambda x: x.stat().st_mtime).name

# shutil.copy("../../../Logs/" + latest_event_file, 'event.csv')
# shutil.copy("../../../Logs/" + latest_value_file, 'value.csv')

valueContent = []
eventContent = []

nestValueContent = []
nestEventContent = []

with open('value.csv') as f:
    names = f.readline()
    valueContent = [x.strip().split(',') for x in f.readlines()]

with open('event.csv') as f:
    names = f.readline()
    eventContent = [x.strip().split(',') for x in f.readlines()]


def plotValueOutputs(populationID, neuronID, valueType, label='', scale=1, offset=0):
    x = [float(x[0]) for x in valueContent if populationID == x[1] and neuronID == x[2] and valueType == x[3]]
    y = [float(x[4])*scale+offset for x in valueContent if populationID == x[1] and neuronID == x[2] and valueType == x[3]]
    axs[0].plot(x, y, label=label)

def plotSpikeOutputs(populationID, neuronID, color='blue', neuronOffset=0):
    x = [float(x[0]) for x in eventContent if populationID == x[1] and neuronID == x[2] and x[3] == '0']
    y = [int(neuronID) for x in eventContent if populationID == x[1] and neuronID == x[2] and x[3] == '0']
    axs[1].eventplot(x, lineoffsets=int(neuronID)+neuronOffset, linelengths=1, color=color, linewidths=0.2)

def plotFFT(populationID, neuronID, dt):
    y = [float(x[4]) for x in valueContent if populationID == x[1] and neuronID == x[2] and '3' == x[3]]
    N = len(y)
    yf = scipy.fftpack.fft(y)
    xf = np.linspace(0.0, 1.0/(2.0*dt), int(N/2))
    fig, ax = plt.subplots()
    ax.plot(xf, 2.0/N * np.abs(yf[:N//2]))



# plotValueOutputs('93941600909440', '0', '3', 'w=0.05 s')
# plotValueOutputs('93941601059408', '0', '3', 'w=0.1 s')
# plotValueOutputs('93941601208816', '0', '3', 'w=0.15 s')
# plotValueOutputs('93941601358256', '0', '3', 'w=0.2 s')
plotValueOutputs('94256176358000', '0', '3', '')
plotValueOutputs('94256176360912', '0', '3')
plotValueOutputs('999', '0', '3', '')

plotSpikeOutputs('94256176358848', '0', '#2c3e50', neuronOffset=0)
plotSpikeOutputs('94256176362176', '0', '#2c3e50', neuronOffset=1)

plotFFT('999', '0', 0.0001)
# plotFFT('93827762442864', '0', 0.0001)


# ------------- Save and show plot ------------- #
axs[0].legend(prop=dict(weight='bold', size='large'))
# plt.savefig(os.path.dirname(os.path.abspath(__file__)) + '/../figures/' + plotname + '.png', bbox_inches='tight', dpi=300)
plt.show()
# ------------- Save and show plot ------------- #