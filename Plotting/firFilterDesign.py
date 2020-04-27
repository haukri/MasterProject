import matplotlib.pyplot as plt
from scipy import signal
import math

t = [x*10 for x in signal.firwin(24, 1, fs=100)]
plt.plot(t)

filt = ""
for s in t:
    filt = filt + str(s) + ","
# print(filt)

N = 11
hamwin = []
for i in range(N):
    hamwin.append(0.54-0.46*math.cos(6.283185307179586*i/(N-1)))
# print(hamwin)

plt.plot(hamwin)

triang = [1/N*x for x in range(11)] + list(reversed([1/N*x for x in range(11)][:-1]))
triang = [x/3 for x in triang]
plt.plot(triang)

filt = ""
for s in triang:
    filt = filt + str(s) + ","
print(filt)





plt.show()
