import matplotlib.pyplot as plt
import os
from collections import defaultdict
import math

latest_event_file = max([f for f in os.scandir("../Logs") if "event" in f.name], key=lambda x: x.stat().st_mtime).name
latest_value_file = max([f for f in os.scandir("../Logs") if "value" in f.name], key=lambda x: x.stat().st_mtime).name

data = defaultdict(lambda: [])

content = []

with open('../Logs/' + latest_value_file) as f:
    names = f.readline()
    content = [x.strip().split(',') for x in f.readlines()]

def plotOutputs(populationID, neuronID, valueType):
    x = [float(x[0]) for x in content if populationID == x[1] and neuronID == x[2] and valueType == x[3]]
    y = [float(x[4]) for x in content if populationID == x[1] and neuronID == x[2] and valueType == x[3]]
    # plt.plot(x, y, marker='o')
    plt.plot(x, y)


plotOutputs('94256613895840', '0', '0')
plotOutputs('94256613895840', '1', '0')
plotOutputs('94256613895840', '2', '0')
plotOutputs('94256613895840', '3', '0')
plotOutputs('94256613895840', '4', '0')
plotOutputs('94256613895840', '5', '0')
plt.show()
# plotOutputs(['TL1', 'TR1', 'CL1','CR1', 'FL1', 'FR1'])
# plotOutputs(['CL1'])
# plotOutputs(['sawtooth1', 'M2', 'sawtooth2'])

# plt.plot(data['sawtooth1'])
# plt.plot(data['sawtooth2'])
# plt.show()