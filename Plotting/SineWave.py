from matplotlib import pyplot as plt
from scipy import signal
import math

f = 10.0
T = 1/10

dt = 0.001

x = [x*dt for x in range(1000)]

y = [math.sin(2*math.pi*f*d) for d in x]

plt.plot(x, y)
plt.show()