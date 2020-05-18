from matplotlib import pyplot as plt
from scipy import signal
import math

last_input = 0

def neuron(i):
    global last_input
    output = math.tanh(i - 0.1 + 2.42*last_input)
    last_input = output
    return output

f = 50.0
f1 = 60.0

dt = 1/44100.0

x = [x*dt for x in range(10000)]

y = [math.sin(2*math.pi*f*d)+ math.sin(2*math.pi*f1*d) for d in x]

y = list(map(neuron, y))

plt.plot(x, y)
plt.show()