#include <iostream>
#include "TemporalPhaseEncodingSynapse.h"
#include <math.h>
#include "Network/utils/helperFunctions.h"

using namespace std;

TemporalPhaseEncodingSynapse::TemporalPhaseEncodingSynapse(Population* n_from, Population* n_to) : 
    param(new TemporalPhaseEncodingSynapse_param)
{
    initialize(n_from, n_to);
}

TemporalPhaseEncodingSynapse::TemporalPhaseEncodingSynapse(Population* n_from, Population* n_to, TemporalPhaseEncodingSynapse_param* param) : 
    param(param)
{
    initialize(n_from, n_to);
}

void TemporalPhaseEncodingSynapse::initialize(Population* n_from, Population* n_to) {
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
    phaseStep = param->window_length_s / param->som_frequency;
    phaseOffset = (param->som_phase * 1.0) / (2 * M_PI * param->som_frequency);
    for(int i = 0; i < inputSize; i++) {
        output.push_back(new NoEvent());
    }
}

void TemporalPhaseEncodingSynapse::resetOutput() {
    for(int i = 0; i < output.size(); i++) {
        if(output[i]) {
            delete output[i];
            output[i] = NULL;
        }
    }
}

void TemporalPhaseEncodingSynapse::update() {
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
                double bin = round(vs * param->som_frequency);
                spikeTimes(j) = currentWindow + helperFunctions::clamp(bin / param->som_frequency + phaseOffset, 0*param->window_length_s, param->window_length_s*0.9);

                // double spikeTime = floor(static_cast<ValueEvent*>(from_population->output[j])->value * param->som_frequency) * phaseStep +param->som_phase;
                // spikeTimes(j) = currentWindow + helperFunctions::clamp((spikeTime * 0.8), 0, 0.9*param->window_length_s);
            }
            currentWindow += param->window_length_s;
        }
    }
}