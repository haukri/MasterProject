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

def plotFFT(ax, valueContent, populationID, neuronID, dt, color=''):
    y = [float(x[4]) for x in valueContent if populationID == x[1] and neuronID == x[2] and '3' == x[3]]
    N = len(y)
    yf = scipy.fftpack.fft(y)
    xf = np.linspace(0.0, 1.0/(2.0*dt), int(N/2))
    if color:
        ax.plot(xf, 2.0/N * np.abs(yf[:N//2]), color=color)
    else:
        ax.plot(xf, 2.0/N * np.abs(yf[:N//2]))


valueContents = []
eventContents = []
populationIDs = []

def generateFrequencies(scale):
    return [str(x*scale) for x in [1,4,7,12,18,24,50]]

arguments = [['0.5', '5', '0', '0', '0', '0', '0']]

for dt, cutoffFreq in zip(['0.0001'], ['2']):
    valueContents = []
    eventContents = []
    populationIDs = []
    for arg in arguments:
        output = check_output(['../../../build/Test/Latency_Coding_Lowpass_Example_Results', *arg, '0.01', dt, 'lowpass,' + cutoffFreq])
        populationIDs.append([output.decode('UTF-8').split('\n')[0], output.decode('UTF-8').split('\n')[1]])

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

    print(populationIDs)


    for valueContent, populationID, args in zip(valueContents, populationIDs, arguments):
        plt.rcParams['figure.figsize'] = (9,6)
        # ------------- Plot Setup ------------- #
        plt.rcParams['figure.figsize'] = (9,6)
        gs = gridspec.GridSpec(2, 2)
        fig = plt.figure()
        ax1 = fig.add_subplot(gs[0, :])
        ax1.set_xlim([0, 10])
        ax1.set_title('Latency coding \n Lowpass filtering, cutoff=' + cutoffFreq + 'Hz \n Signal frequencies = [' + ','.join(args) + ']', fontsize='x-large', fontweight='bold')
        ax1.set_xlabel('Time [s]', fontsize='x-large', fontweight='bold')
        ax1.set_ylabel('Amplitude', fontsize='x-large', fontweight='bold')

        ax2 = fig.add_subplot(gs[1, 0])
        ax2.set_ylim([0, 0.3])
        ax2.set_xlim([0, 10])
        ax2.set_title('FFT of original signal', fontsize='x-large', fontweight='bold')
        ax2.set_xlabel('Frequency [Hz]', fontsize='x-large', fontweight='bold')
        ax2.set_ylabel('Amplitude', fontsize='x-large', fontweight='bold')

        ax3 = fig.add_subplot(gs[1, 1])
        ax3.set_ylim([0, 0.3])
        ax3.set_xlim([0, 10])
        ax3.set_title('FFT of filtered signal', fontsize='x-large', fontweight='bold')
        ax3.set_xlabel('Frequency [Hz]', fontsize='x-large', fontweight='bold')
        ax3.set_ylabel('Amplitude', fontsize='x-large', fontweight='bold')

        # plt.title('Rate coding test signal 1, dt = ' + str(float(dt)*1000.0) + 'ms \n signal frequencies = [' + ','.join(args) + ']' , fontsize='xx-large', fontweight='bold')
        # plt.xlabel('Time [s]', fontsize='xx-large', fontweight='bold')
        # plt.ylabel('Amplitude', fontsize='xx-large', fontweight='bold')
        # plt.grid()

        plotFFT(ax2, valueContent, populationID[0], '0', float(dt))
        plotFFT(ax3, valueContent, populationID[1], '0', float(dt), color='C1')
        # ------------- Plot Setup ------------- #
        plotValueOutputs(ax1, valueContent, populationID[0], '0', '3', label='Original signal')
        plotValueOutputs(ax1, valueContent, populationID[1], '0', '3', label='Filtered signal')
        # plotValueOutputs(ax1, valueContent, '999', '0', '3', 'Test signal 1')
        ax1.legend(prop=dict(weight='bold', size='large'), loc='lower right')
        plt.tight_layout()
        if saveFigure:
            plt.savefig(os.path.dirname(os.path.abspath(__file__)) + '/../figures/' + 'latency_coding_lowpass_example_' + dt.replace('.', '_') + '_' + args[-1] + '.pdf', bbox_inches='tight', dpi=300, format='pdf')


# ------------- Save and show plot ------------- #
# plt.legend(prop=dict(weight='bold', size='large'))
# plt.savefig(os.path.dirname(os.path.abspath(__file__)) + '/../figures/' + plotname + '.png', bbox_inches='tight', dpi=300)
plt.show()
# ------------- Save and show plot ------------- #