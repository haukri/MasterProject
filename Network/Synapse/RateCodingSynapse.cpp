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
    inputSize = n_from->getNumberOfNeurons();
    outputSize = n_to->getNumberOfNeurons();
    if(inputSize != outputSize) {
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
    for(int i = 0; i < inputSize; i++) {
        if(from_population->output[i]->type == EventType::Spike) {
            spikes[i].push_back(currentTime);
            logger->logEvent(1, i, EventType::Spike);
        }
        double value = 0.0;
        while(spikes[i].size() && spikes[i].front() < currentTime - param->time_window) {
            spikes[i].pop_front(); 
        }
        for(double t : spikes[i]) {
            value += 1;
        }
        static_cast<ValueEvent*>(output[i])->setValue(value);
        logger->logValue(1, i, EventType::Value, value);
    }
}