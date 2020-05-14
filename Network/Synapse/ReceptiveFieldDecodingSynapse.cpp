#include <iostream>
#include "ReceptiveFieldDecodingSynapse.h"
#include <math.h>
#include "Network/utils/helperFunctions.h"

using namespace std;

ReceptiveFieldDecodingSynapse::ReceptiveFieldDecodingSynapse(Population* n_from, Population* n_to) : 
    param(new ReceptiveFieldDecodingSynapse_param)
{
    initialize(n_from, n_to);
}

ReceptiveFieldDecodingSynapse::ReceptiveFieldDecodingSynapse(Population* n_from, Population* n_to, ReceptiveFieldDecodingSynapse_param* param) : 
    param(param)
{
    initialize(n_from, n_to);
}

void ReceptiveFieldDecodingSynapse::initialize(Population* n_from, Population* n_to) {
    inputSize = n_from->getNumberOfNeurons();
    outputSize = n_to->getNumberOfNeurons();
    if(outputSize != 1) {
        cout << "ReceptiveFieldDecodingSynapse: There should only be one output neuron" << endl;
        throw "ReceptiveFieldDecodingSynapse: There should only be one output neuron";
    }
    from_population = n_from;
    to_population = n_to;
    clock = Clock::getInstance();
    logger = Logging::getInstance();
    spikeTimes = Eigen::VectorXd(param->number_of_neurons);
    spikeTimes.setConstant(-1);
    currentWindow = param->window_length_s;
    outputStep = (param->input_max - param->input_min) / (param->number_of_neurons -1);
    for(int i = 0; i < param->number_of_neurons; i++) {
        output.push_back(new NoEvent());
    }
}

void ReceptiveFieldDecodingSynapse::resetOutput() {
    for(int i = 0; i < output.size(); i++) {
        if(output[i]) {
            delete output[i];
            output[i] = NULL;
        }
    }
}

void ReceptiveFieldDecodingSynapse::update() {
    if(currentWindow + param->window_length_s <= clock->getCurrentTime()) {
        spikeTimes.setConstant(-1);
        currentWindow += param->window_length_s;
        earliestSpike = false;
    }
    for(int j = 0; j < spikeTimes.size(); j++) {
        if(spikeTimes(j) < 0 && from_population->output[j]->type == EventType::Spike && !earliestSpike) {
            double outputValue = j * outputStep;
            static_cast<ValueEvent*>(output[0])->setValue(outputValue);
            to_population->setInput(0, output[0]);
            earliestSpike = true;
        }
    }
    logger->logValue((long)this, 0, EventType::Value, static_cast<ValueEvent*>(output[0])->value);
}