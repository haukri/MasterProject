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

plotname = 'rate_coding_plot'

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
decodePopulationIDs = []
spikePopulationIDs = []

for dt, window in zip(['0.0001'], ['0.01']):
    valueContents = []
    eventContents = []
    populationIDs = []
    spikePopulationIDs = []
    output = check_output(['../../../build/Test/Phase_Coding_Lowpass_Example_Results', '0.5', '5', '0', '0', '0', '0', '0', '0.01', '1000', '0.0001', 'lowpass,2'])
    populationIDs.append(output.decode('UTF-8').split('\n')[0])
    decodePopulationIDs.append(output.decode('UTF-8').split('\n')[1])
    spikePopulationIDs.append(output.decode('UTF-8').split('\n')[2])

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


    for eventContent, valueContent, populationID, decodePopulationID, spikePopulationID in zip(eventContents, valueContents, populationIDs, decodePopulationIDs, spikePopulationIDs):
        plt.rcParams['figure.figsize'] = (8,6)
        plt.figure()
        # ------------- Plot Setup ------------- #
        plt.rcParams['figure.figsize'] = (8,6)
        plt.title('Test signal 1 \n Latency coding, dt = ' + str(float(dt)*1000.0) + 'ms \n signal frequencies = [' , fontsize='xx-large', fontweight='bold')
        plt.xlabel('Time [s]', fontsize='xx-large', fontweight='bold')
        plt.ylabel('Amplitude', fontsize='xx-large', fontweight='bold')
        plt.grid()
        # ------------- Plot Setup ------------- #
        plotValueOutputs(valueContent, spikePopulationID, '0', '0', 'membrane')
        plotValueOutputs(valueContent, populationID, '0', '3', 'Decoded signal')
        plotValueOutputs(valueContent, '999', '0', '3', 'Test signal 1')
        # plotSpikeOutputs(eventContent, spikePopulationID, '0')
        plt.legend(prop=dict(weight='bold', size='large'))
        if saveFigure:
            pass
            # plt.savefig(os.path.dirname(os.path.abspath(__file__)) + '/../figures/' + 'latency_coding_example_plot_' + dt.replace('.', '_') + '.pdf', bbox_inches='tight', dpi=300, format='pdf')



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
# plt.savefig(os.path.dirname(os.path.abspath(__file__)) + '/../figures/' + plotname + '.png', bbox_inches='tight', dpi=300)
plt.show()
# ------------- Save and show plot ------------- #