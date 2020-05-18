#include <iostream>
#include "LatencyDecodingSynapse.h"
#include <math.h>
#include "Network/utils/helperFunctions.h"

using namespace std;

LatencyDecodingSynapse::LatencyDecodingSynapse(Population* n_from, Population* n_to) : 
    param(new LatencyDecodingSynapse_param)
{
    initialize(n_from, n_to);
}

LatencyDecodingSynapse::LatencyDecodingSynapse(Population* n_from, Population* n_to, LatencyDecodingSynapse_param* param) : 
    param(param)
{
    initialize(n_from, n_to);
}

void LatencyDecodingSynapse::initialize(Population* n_from, Population* n_to) {
    inputSize = n_from->getNumberOfNeurons();
    outputSize = n_to->getNumberOfNeurons();
    if(inputSize != outputSize) {
        cout << "Number of input neurons not equal to number of output neurons" << endl;
        throw "Number of input neurons not equal to number of output neurons";
    }
    from_population = n_from;
    to_population = n_to;
    clock = Clock::getInstance();
    logger = Logging::getInstance();
    spikeTimes = Eigen::VectorXd(inputSize);
    spikeTimes.setConstant(-1);
    currentWindow = param->window_length_s + param->delay_s;
    for(int i = 0; i < inputSize; i++) {
        output.push_back(new NoEvent());
    }
}

void LatencyDecodingSynapse::resetOutput() {
    for(int i = 0; i < output.size(); i++) {
        if(output[i]) {
            delete output[i];
            output[i] = NULL;
        }
    }
}

void LatencyDecodingSynapse::update() {
    if(currentWindow + param->window_length_s <= clock->getCurrentTime()) {
        spikeTimes.setConstant(-1);
        currentWindow += param->window_length_s;
    }
    for(int i = 0; i < inputSize; i++) {
        if(spikeTimes(i) < 0 && from_population->output[i]->type == EventType::Spike) {      
            double s0 = from_population->output[i]->eventTime - currentWindow;
            s0 = s0/param->window_length_s;
            spikeTimes(i) = (s0 - 0.1) * 1.25;
            static_cast<ValueEvent*>(output[i])->setValue(spikeTimes(i));
            
        }
        to_population->setInput(i, output[i]);
        logger->logValue((long)this, i, EventType::Value, static_cast<ValueEvent*>(output[i])->value);
    }
}