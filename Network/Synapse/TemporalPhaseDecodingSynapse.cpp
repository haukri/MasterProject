#include <iostream>
#include "TemporalPhaseDecodingSynapse.h"
#include <math.h>
#include "Network/utils/helperFunctions.h"

using namespace std;

TemporalPhaseDecodingSynapse::TemporalPhaseDecodingSynapse(Population* n_from, Population* n_to) : 
    param(new TemporalPhaseDecodingSynapse_param)
{
    initialize(n_from, n_to);
}

TemporalPhaseDecodingSynapse::TemporalPhaseDecodingSynapse(Population* n_from, Population* n_to, TemporalPhaseDecodingSynapse_param* param) : 
    param(param)
{
    initialize(n_from, n_to);
}

void TemporalPhaseDecodingSynapse::initialize(Population* n_from, Population* n_to) {
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
    phaseStep = param->window_length_s / param->som_frequency;
    phaseOffset = (param->som_phase * 1.0) / (2 * M_PI * param->som_frequency);
    for(int i = 0; i < inputSize; i++) {
        output.push_back(new NoEvent());
    }
}

void TemporalPhaseDecodingSynapse::resetOutput() {
    for(int i = 0; i < output.size(); i++) {
        if(output[i]) {
            delete output[i];
            output[i] = NULL;
        }
    }
}

void TemporalPhaseDecodingSynapse::update() {
    for(int i = 0; i < inputSize; i++) {
        if(currentWindow + param->window_length_s <= clock->getCurrentTime()) {
            spikeTimes.setConstant(-1);
            currentWindow += param->window_length_s;
        }
        for(int j = 0; j < spikeTimes.size(); j++) {
            if(spikeTimes(j) < 0 && from_population->output[i]->type == EventType::Spike) {
                
                double s0 = from_population->output[i]->eventTime - currentWindow - phaseOffset;
                s0 = round(s0/param->window_length_s*param->som_frequency);
                spikeTimes(j) = s0 * 1 / (param->som_frequency);
                spikeTimes(j) = (spikeTimes(j) - 0.1) * 1.25;

                static_cast<ValueEvent*>(output[i])->setValue(spikeTimes(j));
            } 
            to_population->setInput(i, output[i]);
        }
        logger->logValue((long)this, i, EventType::Value, static_cast<ValueEvent*>(output[i])->value);
    }
}