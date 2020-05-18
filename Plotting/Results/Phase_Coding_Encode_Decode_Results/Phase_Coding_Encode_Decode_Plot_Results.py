import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
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

def plotValueOutputs(ax, valueContent, populationID, neuronID, valueType, label='', scale=1, offset=0):
    x = [float(x[0]) for x in valueContent if populationID == x[1] and neuronID == x[2] and valueType == x[3]]
    y = [float(x[4])*scale+offset for x in valueContent if populationID == x[1] and neuronID == x[2] and valueType == x[3]]
    ax.plot(x, y, label=label)

def plotSpikeOutputs(eventContent, populationID, neuronID, color='blue', neuronOffset=0):
    x = [float(x[0]) for x in eventContent if populationID == x[1] and neuronID == x[2] and x[3] == '0']
    y = [int(neuronID) for x in eventContent if populationID == x[1] and neuronID == x[2] and x[3] == '0']
    plt.eventplot(x, lineoffsets=int(neuronID)+neuronOffset, linelengths=1, color=color, linewidths=0.2)

valueContents = []
eventContents = []
populationIDs = []

def generateFrequencies(scale):
    return [str(x*scale) for x in [1,4,7,12,18,24,50]]
    # return [str(x*scale) for x in [1,0,0,0,0,0,0]]

arguments = [generateFrequencies(1), generateFrequencies(6)]
plt.rcParams['figure.figsize'] = (9,6)
gs = gridspec.GridSpec(3, 2)
fig = plt.figure()
fig.suptitle('Temporal phase coding encode and decode of test signal 1', fontsize='large', fontweight='bold')

for index, dt, window in zip([0,1,2], ['0.001', '0.0001', '0.00001'], ['0.03', '0.003', '0.0003']):
    valueContents = []
    eventContents = []
    populationIDs = []
    for arg in arguments:
        output = check_output(['../../../build/Test/Phase_Coding_Encode_Decode_Results', *arg, '80000', '0', window , dt])
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


    for valueContent, populationID, args in zip(valueContents, populationIDs, arguments):
        plt.rcParams['figure.figsize'] = (8,6)
        column = int(args[-1] == '300')
        ax = fig.add_subplot(gs[index, column])
        # ------------- Plot Setup ------------- #
        plt.rcParams['figure.figsize'] = (8,6)
        plt.title('dt = ' + str(float(dt)*1000.0) + 'ms \n f = [' + ','.join(args) + ']' , fontsize='large', fontweight='bold')
        if column == 0:
            plt.ylabel('Amplitude', fontsize='medium', fontweight='bold')
        if index == 2:
            plt.xlabel('Time [s]', fontsize='medium', fontweight='bold')
        plt.grid()
        if args[-1] == '300':
            plt.xlim([0,1/6.0])
        else:
            plt.xlim([0, 1])
        # ------------- Plot Setup ------------- #
        plotValueOutputs(ax, valueContent, populationID, '0', '3', 'Decoded signal')
        plotValueOutputs(ax, valueContent, '999', '0', '3', 'Test signal 1')
        # plt.legend(prop=dict(weight='bold', size='large'))

fig.tight_layout()
fig.subplots_adjust(top=0.85)
if saveFigure:
    plt.savefig(os.path.dirname(os.path.abspath(__file__)) + '/../figures/' + 'phase_coding_plot_all' + '.pdf', bbox_inches='tight', dpi=300, marker='pdf')


# ------------- Save and show plot ------------- #
# plt.legend(prop=dict(weight='bold', size='large'))
# plt.savefig(os.path.dirname(os.path.abspath(__file__)) + '/../figures/' + plotname + '.png', bbox_inches='tight', dpi=300)
plt.show()
# ------------- Save and show plot ------------- #