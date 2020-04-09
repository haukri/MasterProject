#include <iostream>
#include "RateCodingSynapse.h"

using namespace std;

RateCodingSynapse::RateCodingSynapse(Population* n_from, Population* n_to) : 
    param(new RateCodingSynapse_param)
{
    initialize(n_from, n_to);
}

RateCodingSynapse::RateCodingSynapse(Population* n_from, Population* n_to, RateCodingSynapse_param* param) : 
    param(param)
{
    initialize(n_from, n_to);
}

void RateCodingSynapse::initialize(Population* n_from, Population* n_to) {
    inputSize = n_from->getNumberOfOutputNeurons();
    outputSize = n_to->getNumberOfInputNeurons();
    if(outputSize == 1) {
        singleOutput = true;
    }
    else if(inputSize != outputSize) {
        cout << "Number of input neurons not equal to number of output neurons" << endl;
        throw "Number of input neurons not equal to number of output neurons";
    }
    from_population = n_from;
    to_population = n_to;
    clock = Clock::getInstance();
    logger = Logging::getInstance();
    for(int i = 0; i < inputSize; i++) {
        output.push_back(new ValueEvent());
        spikes.assign(inputSize, deque<double>(0));
    }
}

void RateCodingSynapse::update() {
    double currentTime = clock->getCurrentTime();
    double value = 0.0;
    for(int i = 0; i < inputSize; i++) {
        if(from_population->output[i]->type == EventType::Spike) {
            spikes[i].push_back(currentTime);
            logger->logEvent(1, i, EventType::Spike);
        }
        while(spikes[i].size() && spikes[i].front() < currentTime - param->time_window) {
            spikes[i].pop_front(); 
        }
        for(double t : spikes[i]) {
            value += 1;
        }
        if(!singleOutput) {
            static_cast<ValueEvent*>(output[i])->setValue(value);
            to_population->setInput(i, output[i]);
            logger->logValue((long)this, i, EventType::Value, value);
            value = 0.0;
        }
    }
    value = value / (double)inputSize;
    if(singleOutput) {
        static_cast<ValueEvent*>(output[0])->setValue(value);
        to_population->setInput(0, output[0]);
        logger->logValue((long)this, 0, EventType::Value, value);
    }
}