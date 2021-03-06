import matplotlib.pyplot as plt
import math
import numpy as np
import os

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
    for f in [1, 4, 7, 12, 18, 24, 50]:
        val = val + (math.sin(f*2*math.pi*x))
    return val

y = [sinus(x/1000)/16 + 0.5 for x in range(1000)]

plt.plot([x/1000.0 for x in range(1000)], y)

plt.savefig(os.path.dirname(os.path.abspath(__file__)) + '/Results/figures/' + 'test_signal_1' + '.png', bbox_inches='tight', dpi=300)

plt.figure()

# ------------- Plot Setup ------------- #
plt.rcParams['figure.figsize'] = (8,6)
plt.title('Test signal 2', fontsize='xx-large', fontweight='bold')
plt.xlabel('Time [s]', fontsize='xx-large', fontweight='bold')
plt.ylabel('Amplitude', fontsize='xx-large', fontweight='bold')
plt.xlim([0,1])
plt.grid()
# ------------- Plot Setup ------------- #

noise = np.random.normal(0, 0.1, len(y))

y = [x+y for x, y in zip(noise, y)]

plt.plot([x/1000.0 for x in range(1000)], y)

plt.savefig(os.path.dirname(os.path.abspath(__file__)) + '/Results/figures/' + 'test_signal_2' + '.png', bbox_inches='tight', dpi=300)

plt.show()
