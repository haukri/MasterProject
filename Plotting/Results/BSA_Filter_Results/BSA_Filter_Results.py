import matplotlib.pyplot as plt
import os
from collections import defaultdict
import math
from scipy import signal
import shutil
from sklearn.metrics import mean_squared_error
from math import sqrt

plotname = 'bsa_filter_triangle_results'

# ------------- Plot Setup ------------- #
plt.rcParams['figure.figsize'] = (8,6)
fig, axs = plt.subplots(1, 1)
# axs[0].set_ylim(300, 1800)
axs.set_xlim(0, 1)
# axs[1].set_ylim(0, 200)
axs.set_title('BSA encode and decode with hamming window', fontsize='large', fontweight='bold')
# axs[1].set_title('200 Leaky intergrate-and-fire neurons (iaf_psc_alpha)', fontsize='large', fontweight='bold')
axs.set_xlabel('Time [s]', fontsize='large', fontweight='bold')
axs.set_ylabel('Value', fontsize='large', fontweight='bold')
# axs[1].set_ylabel('Root mean square error', fontsize='large', fontweight='bold')
axs.grid()
# axs[1].grid()
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


def plotValueOutputs(populationID, neuronID, valueType, label='', scale=1, offset=0, fileName='value.csv', color=''):
    readValueFile(fileName)
    x = [float(x[0]) for x in valueContent if populationID == x[1] and neuronID == x[2] and valueType == x[3]]
    y = [float(x[4])*scale+offset for x in valueContent if populationID == x[1] and neuronID == x[2] and valueType == x[3]]
    if(color):
        axs.plot(x, y, label=label, color=color)
    else:
        axs.plot(x, y, label=label)

def plotSpikeOutputs(populationID, neuronID, color='blue', fileName='event.csv'):
    readEventFile(fileName)
    x = [float(x[0]) for x in eventContent if populationID == x[1] and neuronID == x[2] and x[3] == '0']
    y = [int(neuronID) for x in eventContent if populationID == x[1] and neuronID == x[2] and x[3] == '0']
    axs.eventplot(x, lineoffsets=int(neuronID), linelengths=2, color=color, linewidths=1)

def calculateRMSE(population_id, scale=1, offset=0):
    y_signal = [float(x[4])*scale+offset for x in valueContent if '999' == x[1] and '0' == x[2] and '3' == x[3]]
    y_recon = [float(x[4])*scale+offset for x in valueContent if population_id == x[1] and '0' == x[2] and '3' == x[3]]
    rms = sqrt(mean_squared_error(y_signal, y_recon))
    return rms

###################### Hamming timestep dt ##############################
population_ids = ['94291922550896', '94651192725616', '94080395681904', '93978482081904', '94100860133488']
dts = ['0.01', '0.001', '0.0001', '0.00001', '0.000001']
timestep_rms = []

for dt, population_id in zip(dts, population_ids):
    # plotValueOutputs(population_id, '0', '3', label='dt = '+str(dt) + ' s', fileName='value_dt_' + dt + '.csv')
    # timestep_rms.append(calculateRMSE(population_id))
    pass
# axs.plot(dts, timestep_rms, marker='o')
print(timestep_rms)


###################### Triangle filter length ###########################
population_ids = ['94110015368928', '94581992746720', '94354902032240', '94892930776944', '93942440992896', '93911992381568', '94896549965952', '94426309652608', '94470366523520', '94594856759424']
window_lengths = ['5', '8', '11', '14', '17', '20', '23', '26', '29', '32']
triangle_rms = []

for window, population_id in zip(window_lengths, population_ids):
    plotValueOutputs(population_id, '0', '3', label=window, fileName='value_triangle_window_' + window + '.csv')
    print('Timestep: ' + str(dt) + ' rmse: ' + str(calculateRMSE(population_id)))
    # triangle_rms.append(calculateRMSE(population_id))
    pass
# axs[1].plot(triangle_rms)
print(triangle_rms)

##################### Hamming filter length ###########################
population_ids = ['94229527342816', '94410229939936', '94454115221360', '94858867162992', '94414832492672', '94051678793856', '94478510821504', '94575716790400', '94117942673536', '93879223545984']
window_lengths = ['5', '8', '11', '14', '17', '20', '23', '26', '29', '32']
hamming_rms = []

for window, population_id in zip(window_lengths, population_ids):    
    # plotValueOutputs(population_id, '0', '3', label=window, fileName='value_hamming_window_' + window + '.csv')
    # print('Timestep: ' + str(dt) + ' rmse: ' + str(calculateRMSE(population_id)))
    # hamming_rms.append(calculateRMSE(population_id))
    pass
print(hamming_rms)


plotValueOutputs('999', '0', '3', label='Signal', fileName='value_dt_0.000001.csv', color='#000000')

# ------------- Save and show plot ------------- #
axs.legend(prop=dict(weight='bold', size='large'), loc='lower right')
plt.savefig(os.path.dirname(os.path.abspath(__file__)) + '/../figures/' + plotname + '.png', bbox_inches='tight', dpi=300)
plt.show()
# ------------- Save and show plot ------------- #