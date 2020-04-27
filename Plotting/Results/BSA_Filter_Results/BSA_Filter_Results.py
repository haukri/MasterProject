import matplotlib.pyplot as plt
import os
from collections import defaultdict
import math
from scipy import signal
import shutil
from sklearn.metrics import mean_squared_error
from math import sqrt

plotname = 'bsa_filter_results'

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


def readValueFile(fileName):
    global valueContent
    with open(fileName) as f:
        names = f.readline()
        valueContent = [x.strip().split(',') for x in f.readlines()]

def readEventFile(fileName):
    global valueContent
    with open(fileName) as f:
        names = f.readline()
        eventContent = [x.strip().split(',') for x in f.readlines()]


def plotValueOutputs(populationID, neuronID, valueType, label='', scale=1, offset=0, fileName='value.csv'):
    readValueFile(fileName)
    x = [float(x[0]) for x in valueContent if populationID == x[1] and neuronID == x[2] and valueType == x[3]]
    y = [float(x[4])*scale+offset for x in valueContent if populationID == x[1] and neuronID == x[2] and valueType == x[3]]
    axs[0].plot(x, y, label=label)

def plotSpikeOutputs(populationID, neuronID, color='blue', fileName='event.csv'):
    readEventFile(fileName)
    x = [float(x[0]) for x in eventContent if populationID == x[1] and neuronID == x[2] and x[3] == '0']
    y = [int(neuronID) for x in eventContent if populationID == x[1] and neuronID == x[2] and x[3] == '0']
    axs[1].eventplot(x, lineoffsets=int(neuronID), linelengths=2, color=color, linewidths=1)

def calculateRMSE(population_id, scale=1, offset=0):
    y_signal = [float(x[4])*scale+offset for x in valueContent if '999' == x[1] and '0' == x[2] and '3' == x[3]]
    y_recon = [float(x[4])*scale+offset for x in valueContent if population_id == x[1] and '0' == x[2] and '3' == x[3]]
    rms = sqrt(mean_squared_error(y_signal, y_recon))
    return rms

###################### Timestep dt ##############################
population_ids = ['94291922550896', '94651192725616', '94080395681904', '93978482081904', '94100860133488']
dts = ['0.01', '0.001', '0.0001', '0.00001', '0.000001']

for dt, population_id in zip(dts, population_ids):
    plotValueOutputs(population_id, '0', '3', label=dt, fileName='value_dt_' + dt + '.csv')
    print('Timestep: ' + str(dt) + ' rmse: ' + str(calculateRMSE(population_id)))

# plotValueOutputs('999', '0', '3', '', fileName='value_dt_0.000001.csv')


###################### Triangle filter ###########################



# ------------- Save and show plot ------------- #
axs[0].legend(prop=dict(weight='bold', size='large'))
# plt.savefig(os.path.dirname(os.path.abspath(__file__)) + '/../figures/' + plotname + '.png', bbox_inches='tight', dpi=300)
plt.show()
# ------------- Save and show plot ------------- #