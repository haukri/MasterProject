import matplotlib.pyplot as plt
import math
import numpy as np
import os
from scipy import signal

# ------------- Plot Setup ------------- #
plt.rcParams['figure.figsize'] = (8,6)
plt.title('Test signal 1', fontsize='xx-large', fontweight='bold')
plt.xlabel('Time [s]', fontsize='xx-large', fontweight='bold')
plt.ylabel('Amplitude', fontsize='xx-large', fontweight='bold')
plt.xlim([0,1])
plt.grid()
# ------------- Plot Setup ------------- #

def sinus(x):
    val = 0
    for f in [1, 50]:
        val = val + (math.sin(f*2*math.pi*x))
    return val


s = [sinus(x/1000)/16 + 0.5 for x in range(10000)]

filterTaps = 200
firFilter = signal.firwin(filterTaps, 20, fs=1000)

hiddenNeurons = [0.0]*filterTaps

output = []
for t in s:
    hiddenNeurons[0] = t
    saved = hiddenNeurons.copy()
    for i in range(1,filterTaps):
        hiddenNeurons[i] = saved[i-1]
    neuronOutput = 0
    for i in range(filterTaps):
        neuronOutput = neuronOutput + firFilter[i]*hiddenNeurons[i]
    output.append(neuronOutput)






plt.plot([x/1000.0 for x in range(10000)], output)

plt.show()