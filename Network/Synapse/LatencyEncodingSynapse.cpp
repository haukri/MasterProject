#include <iostream>
#include "LatencyEncodingSynapse.h"
#include <math.h>
#include "Network/utils/helperFunctions.h"

using namespace std;

LatencyEncodingSynapse::LatencyEncodingSynapse(Population* n_from, Population* n_to) : 
    param(new LatencyEncodingSynapse_param)
{
    initialize(n_from, n_to);
}

LatencyEncodingSynapse::LatencyEncodingSynapse(Population* n_from, Population* n_to, LatencyEncodingSynapse_param* param) : 
    param(param)
{
    initialize(n_from, n_to);
}

void LatencyEncodingSynapse::initialize(Population* n_from, Population* n_to) {
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
    currentWindow = param->window_length_s;
    for(int i = 0; i < inputSize; i++) {
        output.push_back(new NoEvent());
    }
}

void LatencyEncodingSynapse::resetOutput() {
    for(int i = 0; i < output.size(); i++) {
        if(output[i]) {
            delete output[i];
            output[i] = NULL;
        }
    }
}

void LatencyEncodingSynapse::update() {
    for(int i = 0; i < inputSize; i++) {
        resetOutput();
        for(int j = 0; j < spikeTimes.size(); j++) {
            if(spikeTimes(j) <= clock->getCurrentTime() && spikeTimes(j) > -1) {
                output[j] = new SpikeEvent();
                output[j]->setWeight(1.0);
                spikeTimes(j) = -1;
            }
            else {
                output[j] = new NoEvent();
            }
            to_population->setInput(j, output[j]);
            logger->logEvent((long)this, j, output[j]->type);
        }
        if(currentWindow <= clock->getCurrentTime()) {
            for(int j = 0; j < spikeTimes.size(); j++) {
                double scaledValue = 0.1 + static_cast<ValueEvent*>(from_population->output[j])->value * 0.8;
                double vs = scaledValue * param->window_length_s;
                spikeTimes(j) = currentWindow + helperFunctions::clamp(vs, 0, param->window_length_s*0.9);
            }
            currentWindow += param->window_length_s;
        }
    }
}