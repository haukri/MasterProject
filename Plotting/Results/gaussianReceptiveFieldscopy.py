import matplotlib.pyplot as plt
import math
import os

def gauss(x, center, variance):
    return 1 / variance * math.sqrt(2*math.pi) * math.exp(-0.5 * pow((x - center) / variance, 2))

def frange(n_from, n_to, dt):
    return [n_from + x*dt for x in range(int((n_to-n_from)/dt))]


Imin = 0
Imax = 1

m = 20
beta = 1.5 # between 1.0 and 2.0

center = Imin
variance = 1/beta*((Imax-Imin)/(m))
gaussianMax = gauss(0, center, variance)


for i in range(m):
    center = Imin + ((2*i+1)/2)*(Imax-Imin)/(m)
    variance = 1/beta*((Imax-Imin)/(m))
    plt.plot(frange(-5, 5, 0.001), [gauss(x, center, variance)/gaussianMax for x in frange(-5, 5, 0.001)])


plt.title('Gaussian Receptive Fields m = 20, beta = 1.5', fontsize='large', fontweight='bold')
plt.xlabel('Input value', fontsize='x-large', fontweight='bold')
plt.ylabel('Output value', fontsize='x-large', fontweight='bold')
plt.grid()


plt.axvline(x=Imin, color='r', linewidth=1)
plt.axvline(x=Imax, color='r', linewidth=1)
plt.ylim([-0.1,1.1])
plt.xlim([-0.1,1.1])
# plt.savefig(os.path.dirname(os.path.abspath(__file__)) + '/figures/' + 'gaussian_receptive_fields_m20' + '.png', bbox_inches='tight', dpi=300)
plt.show()
