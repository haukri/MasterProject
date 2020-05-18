import matplotlib.pyplot as plt
import os
from collections import defaultdict
import math
from scipy import signal
import scipy.fftpack
import shutil
import numpy as np
from sklearn.metrics import mean_squared_error
from math import sqrt
from subprocess import check_output
import sys

saveFigure = any([x=='-s' or x =='--save' for x in sys.argv])

plotname = 'latency_coding_rmse'

# ------------- Plot Setup ------------- #
plt.rcParams['figure.figsize'] = (8,6)
plt.title('Test signal 1 \n RMSE for latency encoding and decoding', fontsize='xx-large', fontweight='bold')
plt.xlabel('Highest frequency in signal [Hz]', fontsize='xx-large', fontweight='bold')
plt.ylabel('Root mean square error', fontsize='xx-large', fontweight='bold')
plt.ylim([0, 0.3])
plt.grid()
# ------------- Plot Setup ------------- #

def calculateRMSE(valueContent, population_id, scale=1, offset=0):
    y_signal = [float(x[4])*scale+offset for x in valueContent if '999' == x[1] and '0' == x[2] and '3' == x[3]]
    y_recon = [float(x[4])*scale+offset for x in valueContent if population_id == x[1] and '0' == x[2] and '3' == x[3]]
    rms = sqrt(mean_squared_error(y_signal, y_recon))
    return rms

def plotValueOutputs(valueContent, populationID, neuronID, valueType, label='', scale=1, offset=0):
    x = [float(x[0]) for x in valueContent if populationID == x[1] and neuronID == x[2] and valueType == x[3]]
    y = [float(x[4])*scale+offset for x in valueContent if populationID == x[1] and neuronID == x[2] and valueType == x[3]]
    plt.plot(x, y, label=label)

def plotSpikeOutputs(eventContent, populationID, neuronID, color='blue', neuronOffset=0):
    x = [float(x[0]) for x in eventContent if populationID == x[1] and neuronID == x[2] and x[3] == '0']
    y = [int(neuronID) for x in eventContent if populationID == x[1] and neuronID == x[2] and x[3] == '0']
    plt.eventplot(x, lineoffsets=int(neuronID)+neuronOffset, linelengths=1, color=color, linewidths=0.2)

valueContents = []
eventContents = []
populationIDs = []

def generateFrequencies(scale):
    return [str(x*scale) for x in [1,4,7,12,18,24,50]]

# arguments = [generateFrequencies(x/10.0) for x in range(1,100)]
arguments = [generateFrequencies(1/10.0)] + [generateFrequencies(x/2.0) for x in range(1,20)]

for dt, window in zip(['0.001', '0.0001', '0.00001'], ['0.03', '0.003', '0.0003']):
    valueContents = []
    eventContents = []
    populationIDs = []
    for arg in arguments:
        output = check_output(['../../../build/Test/Latency_Coding_Encode_Decode_Results', *arg, window, dt])
        populationIDs.append(output.decode('UTF-8').split('\n')[0])

        latest_event_file = max([f for f in os.scandir("../../../Logs") if "event" in f.name], key=lambda x: x.stat().st_mtime).name
        latest_value_file = max([f for f in os.scandir("../../../Logs") if "value" in f.name], key=lambda x: x.stat().st_mtime).name

        shutil.copy("../../../Logs/" + latest_event_file, 'event.csv')
        shutil.copy("../../../Logs/" + latest_value_file, 'value.csv')

        with open('value.csv') as f:
            names = f.readline()
            valueContents.append([x.strip().split(',') for x in f.readlines()])

        with open('event.csv') as f:
            names = f.readline()
            eventContents.append([x.strip().split(',') for x in f.readlines()])

    RMSE = []

    for valueContent, populationID in zip(valueContents, populationIDs):
        RMSE.append(calculateRMSE(valueContent, populationID))
    plt.plot([float(x[6]) for x in arguments], RMSE, linewidth=2, label='dt = ' + dt, marker='.')



def plotFFT(valueContent, populationID, neuronID, dt):
    y = [float(x[4]) for x in valueContent if populationID == x[1] and neuronID == x[2] and '3' == x[3]]
    N = len(y)
    yf = scipy.fftpack.fft(y)
    xf = np.linspace(0.0, 1.0/(2.0*dt), int(N/2))
    fig, ax = plt.subplots()
    ax.plot(xf, 2.0/N * np.abs(yf[:N//2]))


for valueContent, populationID in zip(valueContents, populationIDs):
#     # ------------- Plot Setup ------------- #
#     plt.rcParams['figure.figsize'] = (8,6)
#     fig, axs = plt.subplots(2, 1, sharex='col')
#     # axs[0].set_ylim(300, 1800)
#     axs[0].set_xlim(0.2, 0.6)
#     # axs[1].set_ylim(0, 200)
#     axs[0].set_title('Rate coding synapse with different time windows w', fontsize='large', fontweight='bold')
#     axs[1].set_title('200 Leaky intergrate-and-fire neurons (iaf_psc_alpha)', fontsize='large', fontweight='bold')
#     plt.xlabel('Time [s]', fontsize='large', fontweight='bold')
#     axs[0].set_ylabel('Spike Rate', fontsize='large', fontweight='bold')
#     axs[1].set_ylabel('Neuron Index', fontsize='large', fontweight='bold')
#     axs[0].grid()
#     axs[1].grid()
#     # ------------- Plot Setup ------------- #
    # plotValueOutputs(valueContent, populationID, '0', '3')
    # plotValueOutputs(valueContent, '999', '0', '3', '')
    pass
    # RMSE.append(calculateRMSE(valueContent, populationID))

# plotValueOutputs(valueContent[0], populationIDs[0], '0', '3')
# plotValueOutputs(valueContent[0], '999', '0', '3', '')



# ------------- Save and show plot ------------- #
plt.legend(prop=dict(weight='bold', size='large'))
if saveFigure:
    plt.savefig(os.path.dirname(os.path.abspath(__file__)) + '/../figures/' + plotname + '.png', bbox_inches='tight', dpi=300)
plt.show()
# ------------- Save and show plot ------------- #