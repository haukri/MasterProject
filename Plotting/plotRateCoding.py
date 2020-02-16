import matplotlib.pyplot as plt
import os
from collections import defaultdict
import math

latest_event_file = max([f for f in os.scandir("../Logs") if "event" in f.name], key=lambda x: x.stat().st_mtime).name
latest_value_file = max([f for f in os.scandir("../Logs") if "value" in f.name], key=lambda x: x.stat().st_mtime).name

data = defaultdict(lambda: [])

valueContent = []
eventContent = []

with open('../Logs/' + latest_value_file) as f:
    names = f.readline()
    valueContent = [x.strip().split(',') for x in f.readlines()]

with open('../Logs/' + latest_event_file) as f:
    names = f.readline()
    eventContent = [x.strip().split(',') for x in f.readlines()]

def plotValueOutputs(populationID, neuronID, valueType):
    x = [float(x[0]) for x in valueContent if populationID == x[1] and neuronID == x[2] and valueType == x[3]]
    y = [float(x[4]) for x in valueContent if populationID == x[1] and neuronID == x[2] and valueType == x[3]]
    plt.plot(x, y)

def plotSpikeOutputs(populationID, neuronID):
    x = [float(x[0]) for x in eventContent if populationID == x[1] and neuronID == x[2] and x[3] == '0']
    y = [int(neuronID) for x in eventContent if populationID == x[1] and neuronID == x[2] and x[3] == '0']
    plt.eventplot(x, lineoffsets=int(neuronID), linelengths=0.7)
    # plt.scatter(x, y)

# plotValueOutputs('1', '0', '3')
# plotValueOutputs('1', '1', '3')
# plotValueOutputs('1', '2', '3')
# plotValueOutputs('1', '3', '3')
# plotValueOutputs('1', '4', '3')
# plotValueOutputs('1', '5', '3')
for x in range(9):
    plotSpikeOutputs('1', str(x))
plt.show()