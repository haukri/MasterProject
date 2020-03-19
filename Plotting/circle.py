import matplotlib.pyplot as plt
import random
import math

x = []
y = []

for i in range(1000):
    a = random.random() * 2 * math.pi
    r = 0.5 * math.sqrt(random.random())

    x.append(r * math.sin(a))
    y.append(r * math.cos(a))


plt.scatter(x, y)
plt.ylim(-1, 1)
plt.xlim(-1, 1)

plt.show()
