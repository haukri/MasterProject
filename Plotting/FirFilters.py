import matplotlib.pyplot as plt
import math
import numpy as np
import os

# ------------- Plot Setup ------------- #
plt.rcParams['figure.figsize'] = (8,6)
plt.title('Lowpass FIR filter coefficients', fontsize='xx-large', fontweight='bold')
plt.xlabel('Coefficients', fontsize='xx-large', fontweight='bold')
plt.ylabel('Amplitude', fontsize='xx-large', fontweight='bold')
plt.grid()
# ------------- Plot Setup ------------- #

M = 2000
W = math.floor(M/2)
f = 0.3

y = [0]*M

i = -W

while i < W:
    if i == 0:
        y[W] = 2*f
    else:
        y[W+i] = math.sin(2*math.pi*f*i)/(i*math.pi)
    i = i + 1
    
plt.plot([x-W for x in range(M)],y)

# plt.savefig(os.path.dirname(os.path.abspath(__file__)) + '/Results/figures/' + 'lowpass_fir_filter' + '.png', bbox_inches='tight', dpi=300)

plt.figure()

# ------------- Plot Setup ------------- #
plt.rcParams['figure.figsize'] = (8,6)
plt.title('Highpass FIR filter coefficients', fontsize='xx-large', fontweight='bold')
plt.xlabel('Coefficients', fontsize='xx-large', fontweight='bold')
plt.ylabel('Amplitude', fontsize='xx-large', fontweight='bold')
plt.grid()
# ------------- Plot Setup ------------- #


M = 2000
W = math.floor(M/2)
f = 0.3

y = [0]*M

i = -W

while i < W:
    if i == 0:
        y[i+W] = 1-2*f
    else:
        y[W+i] = -math.sin(2*math.pi*f*i)/(i*math.pi)
    i = i + 1
    
plt.plot([x-W for x in range(M)],y)

# plt.savefig(os.path.dirname(os.path.abspath(__file__)) + '/Results/figures/' + 'highpass_fir_filter' + '.png', bbox_inches='tight', dpi=300)

plt.show()
