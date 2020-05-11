import matplotlib.pyplot as plt
import os
from collections import defaultdict
import math
from scipy import signal
import shutil
from sklearn.metrics import mean_squared_error
from math import sqrt

plotname = 'bsa_filter_rmse_results'


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
        plt.plot(x, y, label=label, color=color)
    else:
        plt.plot(x, y, label=label)

def plotSpikeOutputs(populationID, neuronID, color='blue', fileName='event.csv'):
    readEventFile(fileName)
    x = [float(x[0]) for x in eventContent if populationID == x[1] and neuronID == x[2] and x[3] == '0']
    y = [int(neuronID) for x in eventContent if populationID == x[1] and neuronID == x[2] and x[3] == '0']
    plt.eventplot(x, lineoffsets=int(neuronID), linelengths=2, color=color, linewidths=1)

def calculateRMSE(population_id, scale=1, offset=0):
    y_signal = [float(x[4])*scale+offset for x in valueContent if '999' == x[1] and '0' == x[2] and '3' == x[3]]
    y_recon = [float(x[4])*scale+offset for x in valueContent if population_id == x[1] and '0' == x[2] and '3' == x[3]]
    rms = sqrt(mean_squared_error(y_signal, y_recon))
    return rms

###################### Hamming timestep dt ##############################
plt.rcParams['figure.figsize'] = (6,4)
plt.title('BSA encode and decode with different timesteps', fontsize='large', fontweight='bold')
plt.xlabel('Simulation timestep dt [s]', fontsize='x-large', fontweight='bold')
plt.ylabel('Root mean square error', fontsize='x-large', fontweight='bold')
plt.grid()
population_ids = ['94291922550896', '94651192725616', '94080395681904', '93978482081904', '94100860133488']
dts = ['0.01', '0.001', '0.0001', '0.00001', '0.000001']
timestep_rms = []

for dt, population_id in zip(dts, population_ids):
    readValueFile('value_dt_' + dt + '.csv')
    timestep_rms.append(calculateRMSE(population_id))
    pass
plt.plot(dts, timestep_rms, marker='o')
print(timestep_rms)

# plt.savefig(os.path.dirname(os.path.abspath(__file__)) + '/../figures/' + 'bsa_rmse_timestep' + '.png', bbox_inches='tight', dpi=300)

plt.figure()

###################### Triangle filter length ###########################
plt.title('BSA encode and decode with triangle window and different window lengths', fontsize='large', fontweight='bold')
plt.xlabel('Time [s]', fontsize='large', fontweight='bold')
plt.ylabel('Root mean square error', fontsize='large', fontweight='bold')
plt.grid()
population_ids = ['94110015368928', '94581992746720', '94354902032240', '94892930776944', '93942440992896', '93911992381568', '94896549965952', '94426309652608', '94470366523520', '94594856759424']
window_lengths = ['5', '8', '11', '14', '17', '20', '23', '26', '29', '32']
triangle_rms = []

for window, population_id in zip(window_lengths, population_ids):
    readValueFile('value_triangle_window_' + window + '.csv')
    triangle_rms.append(calculateRMSE(population_id))
    pass
plt.plot(window_lengths, triangle_rms, label='Triangle', marker='o')
print(window_lengths, triangle_rms)

# plt.savefig(os.path.dirname(os.path.abspath(__file__)) + '/../figures/' + 'bsa_rmse_triangle' + '.png', bbox_inches='tight', dpi=300)

# plt.figure()

##################### Hamming filter length ###########################
plt.title('BSA encode and decode with different window lengths', fontsize='large', fontweight='bold')
plt.xlabel('window length [samples]', fontsize='x-large', fontweight='bold')
plt.ylabel('Root mean square error', fontsize='x-large', fontweight='bold')
population_ids = ['94229527342816', '94410229939936', '94454115221360', '94858867162992', '94414832492672', '94051678793856', '94478510821504', '94575716790400', '94117942673536', '93879223545984']
window_lengths = ['5', '8', '11', '14', '17', '20', '23', '26', '29', '32']
hamming_rms = []

for window, population_id in zip(window_lengths, population_ids):
    readValueFile('value_hamming_window_' + window + '.csv')
    hamming_rms.append(calculateRMSE(population_id))
    pass
plt.plot(window_lengths, hamming_rms, label='Hamming', marker='o')
print(window_lengths, hamming_rms)
plt.legend(prop=dict(weight='bold', size='large'))

# plt.savefig(os.path.dirname(os.path.abspath(__file__)) + '/../figures/' + 'bsa_rmse_window_length' + '.png', bbox_inches='tight', dpi=300)

plt.figure()

##################### Hamming filter length ###########################
plt.title('BSA encode and decode with different thresholds', fontsize='large', fontweight='bold')
plt.xlabel('Threshold', fontsize='x-large', fontweight='bold')
plt.ylabel('Root mean square error', fontsize='x-large', fontweight='bold')
plt.grid()
population_ids = ['93931038548096', '94753190531200', '94150443618432', '94391239528576', '94785944887424', '94410193457280', '94164329078912', '94725967564928', '94329056620672', '94630930133120']
thresholds = ['0.1', '0.2', '0.3', '0.4', '0.5', '0.6', '0.7', '0.8', '0.9', '1.0']
threshold_rms = []

for threshold, population_id in zip(thresholds, population_ids):
    readValueFile('value_threshold_' + threshold + '.csv')
    threshold_rms.append(calculateRMSE(population_id))
    pass
plt.plot(thresholds, threshold_rms, marker='o')
print(thresholds, threshold_rms)

plt.savefig(os.path.dirname(os.path.abspath(__file__)) + '/../figures/' + 'bsa_rmse_threshold' + '.png', bbox_inches='tight', dpi=300)

plt.figure()

##################### Hamming filter length ###########################
plt.title('BSA encode and decode with different thresholds', fontsize='large', fontweight='bold')
plt.xlabel('Threshold', fontsize='x-large', fontweight='bold')
plt.ylabel('Root mean square error', fontsize='x-large', fontweight='bold')
plt.grid()
population_ids = ['93942103658624', '93861428195456', '94215622946944', '94378996555904', '94178262683776', '94113285300352', '94203854680192', '94017298378880', '93827113083008']
thresholds = ['0.91', '0.92', '0.93', '0.94', '0.95', '0.96', '0.97', '0.98', '0.99']
threshold_rms = []

for threshold, population_id in zip(thresholds, population_ids):
    readValueFile('value_threshold_' + threshold + '.csv')
    threshold_rms.append(calculateRMSE(population_id))
    pass
plt.plot(thresholds, threshold_rms, marker='o')
print(thresholds, threshold_rms)

plt.savefig(os.path.dirname(os.path.abspath(__file__)) + '/../figures/' + 'bsa_rmse_threshold_fine' + '.png', bbox_inches='tight', dpi=300)

# plotValueOutputs('999', '0', '3', label='Signal', fileName='value_dt_0.000001.csv', color='#000000')

# ------------- Save and show plot ------------- #
# plt.legend(prop=dict(weight='bold', size='large'))
# plt.savefig(os.path.dirname(os.path.abspath(__file__)) + '/../figures/' + plotname + '.png', bbox_inches='tight', dpi=300)
plt.show()
# ------------- Save and show plot ------------- #