import matplotlib.pyplot as plt
import math
import numpy as np

def som(freq, phase, window):
    return[math.cos(2*math.pi*freq*x + phase) for x in np.arange(0, window, 0.0001)]


phase = math.pi/4
som_freq = 60

plt.plot(np.arange(0, 1, 0.0001), som(som_freq, -phase, 1))
peak = (phase*1) / (2*math.pi*som_freq)
secondpeak = peak + 1.0/som_freq
plt.axvline(x=peak, color='r', linewidth=0.5)
plt.axvline(x=secondpeak, color='r', linewidth=0.5)
# plt.plot(np.arange(0, 1, 0.01), som(3, math.pi/2, 1))
# plt.plot(np.arange(0, 1, 0.01), som(3, math.pi, 1))
plt.show()