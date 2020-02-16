import matplotlib.pyplot as plt
from scipy import signal

t = [x*10 for x in signal.firwin(24, 1, fs=100)]
plt.plot(t)

filt = ""
for s in t:
    filt = filt + str(s) + ","
print(filt)

plt.show()
