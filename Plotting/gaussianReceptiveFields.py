import matplotlib.pyplot as plt
import math

def gauss(x, center, variance):
    return 1 / variance * math.sqrt(2*math.pi) * math.exp(-0.5 * pow((x - center) / variance, 2))

def frange(n_from, n_to, dt):
    return [n_from + x*dt for x in range(int((n_to-n_from)/dt))]


Imin = 0
Imax = 1

m = 5
beta = 1.5 # between 1.0 and 2.0


for i in range(m):
    center = Imin + ((2*i+1-1)/2)*((Imax-Imin)/(m-1))
    variance = 1/beta*((Imax-Imin)/(m-1))
    plt.plot(frange(-5, 5, 0.01), [gauss(x, center, variance) for x in frange(-5, 5, 0.01)])


plt.axvline(x=Imin, color='r', linewidth=1)
plt.axvline(x=Imax, color='r', linewidth=1)
plt.show()