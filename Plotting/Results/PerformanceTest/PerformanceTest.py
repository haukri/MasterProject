import matplotlib.pyplot as plt
from subprocess import check_output
import sys
import json
import os.path

saveFigure = any([x=='-s' or x =='--save' for x in sys.argv])
runTests = any([x=='-r' or x =='--run' for x in sys.argv])

def extractExecutionTime(output):
    temp = output.decode('UTF-8').split('\n')[1]
    executionTime = temp[temp.find('time:')+6:temp.find(' m')]
    return float(executionTime)

if runTests:
    # executionTimes = []
    # for x in range(100):
    #     output = check_output(['../../../build/Test/SpikingNeuronPerformanceTest', str(x*50)])
    #     executionTimes.append(extractExecutionTime(output))
    #     print(executionTimes[-1])
    #     if executionTimes[-1] > 10000:
    #         break
    # with open('spiking-execution-times.json', 'w') as f:
    #     f.write(json.dumps(executionTimes))
    # 
    executionTimes = []
    for x in range(100):
        output = check_output(['../../../build/Test/NonSpikingNeuronPerformanceTest', str(x*50)])
        executionTimes.append(extractExecutionTime(output))
        print(executionTimes[-1])
        if executionTimes[-1] > 10000:
            break
    with open('non-spiking-execution-times.json', 'w') as f:
        f.write(json.dumps(executionTimes))

plt.title('Intel i5 running Ubuntu\n Execution time for 10 second simulation\n with populations of neurons', fontsize='x-large', fontweight='bold')
plt.xlabel('Total number of neurons', fontsize='x-large', fontweight='bold')
plt.ylabel('Execution time [ms]', fontsize='x-large', fontweight='bold')
plt.grid()

if os.path.exists('spiking-execution-times.json'):
    with open('spiking-execution-times.json', 'r') as f:
        executionTimes = json.loads(f.read())
        plt.plot([x*100 for x in range(len(executionTimes))],executionTimes, marker='o', label='Spiking neurons')

if os.path.exists('non-spiking-execution-times.json'):
    with open('non-spiking-execution-times.json', 'r') as f:
        executionTimes = json.loads(f.read())
        plt.plot([x*100 for x in range(len(executionTimes))],executionTimes, marker='o', label='Non-spiking neurons')

plt.legend(prop=dict(weight='bold', size='large'))

if saveFigure:
    plt.savefig(os.path.dirname(os.path.abspath(__file__)) + '/../figures/' + 'performance_test_spiking_pc.pdf', bbox_inches='tight', dpi=300, format='pdf')

plt.show()

